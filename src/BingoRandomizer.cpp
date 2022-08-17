#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include "BingoRandomizer.hpp"
#include "Utils.hpp"

namespace Bingo {
    cv::Mat open_image(const char* _path) {
        return cv::imread(_path);
    }

    // Shuffles the bingo options array
    BINGO_CARD randomize_bingo(BINGO_CARD& card) {
        for (auto& row : card) {
            std::shuffle(std::begin(row),
                std::end(row),
                std::mt19937{ std::random_device{}() }
            );
        }

        std::shuffle(std::begin(card),
            std::end(card),
            std::mt19937{ std::random_device{}() }
        );

        if (card[2][2] != "stream starts") {
            for (auto& row : card) {
                for (auto& cell : row) {
                    if (cell == "stream starts") {
                        cell = card[2][2];
                        card[2][2] = DO_NOT_RENDER;
                        break;
                    }
                }
            }
        }

        return card;
    }

    void add_bingo_text(cv::Mat& image, const std::string& text, int x_origin, int y_origin) {
        std::vector<std::string> splitVector = split(text, ' ');
        std::vector<std::string> stringPairs = pair(splitVector);

        // Draw the text on the image
        uint8_t counter = 0;
        for (const auto& inText : stringPairs) {
            cv::putText(image,
                        inText,
                        cv::Point(x_origin, y_origin + 30 * counter),
                        cv::FONT_HERSHEY_DUPLEX,
                        0.5,
                        __BLACK__,
                        3,
                        cv::LINE_AA
            );

            cv::putText(image,
                        inText,
                        cv::Point(x_origin, y_origin + 30 * counter),
                        cv::FONT_HERSHEY_DUPLEX,
                        0.5,
                        __WHITE__,
                        1,
                        cv::LINE_AA
            );
            counter++;
        }
    }

    // Draws the array on the image cell-by-cell
    void array_to_card(cv::Mat& card, const BINGO_CARD& cardText, int y_origin) {
        uint8_t colCounter = 0;
        uint8_t rowCounter = 0;
        for (const auto& row : cardText) {
            for (const auto& cell : row) {
                if (cell == DO_NOT_RENDER) {
                    colCounter++;
                    continue;
                }
                add_bingo_text(card, cell, 70 + 133 * rowCounter, y_origin + colCounter * 133);
                colCounter++;
                Utils::__log("Writing: " + cell);
            }
            rowCounter++;
            colCounter = 0;
        }

        add_bingo_text(card, "stream starts", 343, y_origin + 30 + 2 * 133);
    }

    // String splitting function
    std::vector<std::string> split(const std::string& string, char delimiter) {
        std::vector<std::string> splitVector;
        _split(string, delimiter, splitVector);
        return splitVector;
    }

    // Helper function
    void _split(const std::string& string, char delimiter, std::vector<std::string>& result) {
        std::istringstream isstream(string);
        std::string item;
        while (std::getline(isstream, item, delimiter)) {
            result.emplace_back(item);
        }
    }

    std::vector<std::string> pair(const std::vector<std::string>& splitVector) {
        uint8_t index = 0;
        std::string temp;
        std::vector<std::string> stringPairs;
        bool pushedBack = false;
        while (index != splitVector.size()) {
            // This word is too long to fit two in one line :weirdge:
            if (splitVector[0] == "tare104ka") {
                if (index % 2 == 1)
                    temp = splitVector[index];
                else {
                    if (index != 0) temp += " ";
                    temp += splitVector[index];
                    stringPairs.push_back(temp);
                    pushedBack = true;
                    Utils::__log("Pushing back: " + temp);
                }
            }
            else {
                if (index % 2 == 0)
                    temp = splitVector[index];
                else {
                    temp += " ";
                    temp += splitVector[index];
                    stringPairs.push_back(temp);
                    pushedBack = true;
                    Utils::__log("Pushing back: " + temp);
                }
            }
            index++;
            // If we reach the end of the pairs of words and didn't add the last word, add it
            if (index == splitVector.size() && !pushedBack)
                stringPairs.push_back(temp);
            pushedBack = false;
        }

        return stringPairs;
    }
}