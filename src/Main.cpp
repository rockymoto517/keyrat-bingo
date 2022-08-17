#include <array>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "BingoRandomizer.hpp"
#include "Utils.hpp"

int WinMain() {
    // Parse csv for options
    Bingo::BINGO_CARD bingoCardOptions = Utils::parseCSV("bingoOptions.csv");
    // Shuffle options
    Bingo::randomize_bingo(bingoCardOptions);

    // Open image
    cv::Mat bingoCard = Bingo::open_image("bingoCard.png");
    // Add the bingo card cells to the image
    Bingo::array_to_card(bingoCard, bingoCardOptions, bingoCard.rows / 4 - 15);
    // Save the image
    bool isWritten = cv::imwrite("RandomizedBingoCard.png", bingoCard);
    // Make sure there are no errors
    if (!isWritten) {
        Utils::__log("Error saving image.");
        std::cin.get();
        return -1;
    }
    Utils::__log("Successfuly saved image.");

    // Confirmation window
    cv::imshow("Bingo Card", bingoCard);
    cv::waitKey(0);
    return 0;
}