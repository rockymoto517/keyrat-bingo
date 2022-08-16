#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>
#include <iterator>
#include <opencv2/opencv.hpp>

namespace Bingo {
    const cv::Scalar __WHITE__ = cv::Scalar::all(255);
    const cv::Scalar __BLACK__ = cv::Scalar::all(0);

    // Function definitions
    std::vector<std::string> split(const std::string& string, char delimiter);
    void _split(const std::string& string, char delimiter, std::vector<std::string>& result);
    void add_bingo_text(cv::Mat& image, const std::string& text, int widthIncrement, int heightOrigin);
    template <typename T>
    void __log(T msg);

    cv::Mat open_image(const char* _path) {
        return cv::imread(_path);
    }

    // Shuffles the bingo options array
    typedef std::array<std::array<std::string, 5>, 5> BINGO_CARD;
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

        return card;
    }

    void add_bingo_text(cv::Mat& image, const std::string& text, int x_origin, int y_origin) {
        std::vector<std::string> splitVector = split(text, ' ');

        // Splits the text into two words at a time
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
                    __log("Pushing back: " + temp);
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
                    __log("Pushing back: " + temp);
                }
            }
            
            index++;
            // If we reach the end of the pairs of words and didn't add the last word, add it
            if (index == splitVector.size() && !pushedBack)
                stringPairs.push_back(temp);
            pushedBack = false;
        }

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
                // Make sure stream starts goes in the middle
                if (cell == "stream starts") {
                    continue;
                }

                if (rowCounter == 2 && colCounter == 2) {
                    colCounter++;
                    continue;
                }

                add_bingo_text(card, cell, 70 + 133 * rowCounter, y_origin + colCounter * 133);
                colCounter++;
                __log("Writing: " + cell);
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

    template <typename T>
    void __log(T msg) {
        std::cout << "[BINGO LOG]: " << msg << "\n";
    }
}

int WinMain() {
    // Array of bingo options
    Bingo::BINGO_CARD bingoCardOptions = { {
        {"die from reading chat", "db grimm or gas gl", "pub leaves after down or custody", "tare104ka mute after dumb tts", "lobby with wrong tactic"},
        {"forced to play jimmy", "creepy wants eclipse", "cant pick a build for too long", "dog", "leech player downs 8+ times"},
        {"\"what is he doing\"", "pub mentions infamy", "stream starts", "hidden modlist cheater", "less than level 100 player"},
        {"i outkill the entire pub combined", "pub with inspire doesnt revive", "pd2 related tts", "tts scams someone", "bay1k joins the lobby"},
        {"timeout revenge", "kicked", "pub build has a mistake", "rocky says one thing and vanishes", "someone doesnt know that i stream"}
    } };

    // Shuffle options
    Bingo::randomize_bingo(bingoCardOptions);

    // Open image
    cv::Mat bingoCard = Bingo::open_image("bingoCard.png");
    // Add the bingo card cells to the image
    Bingo::array_to_card(bingoCard, bingoCardOptions, bingoCard.rows / 4 - 15);
    // Display the image
    cv::imshow("Display Image", bingoCard);
    // Don't immediately close the image
    cv::waitKey(0);
    return 0;
}