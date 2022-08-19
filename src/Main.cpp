#include <array>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "BingoRandomizer.hpp"
#include "Utils.hpp"

int WinMain() {
    // Parse csv for options
    Bingo::BINGO_CARD bingoCardOptions = Utils::parseCSV("Config/bingoOptions.csv");
    // Shuffle options
    Bingo::randomize_bingo(bingoCardOptions);

    // Open image
    cv::Mat bingoCard = Bingo::open_image("Images/bingoCard.png");
    // Add the bingo card cells to the image
    Bingo::array_to_card(bingoCard, bingoCardOptions, bingoCard.rows / 4 - 15);
    // Save the image
    bool isWritten = cv::imwrite("Images/RandomizedBingoCard.png", bingoCard);
    // Make sure there are no errors
    if (!isWritten) {
        Utils::__log("Error saving image.");
        std::cin.get();
        return -1;
    }
    Utils::__log("Successfuly saved image.");
    return 0;
}
