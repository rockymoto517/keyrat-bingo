#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Utils.hpp"

namespace Utils {
    std::vector<std::vector<std::string>> parseCSV(const std::string& filename) {
        std::ifstream data(filename);
        std::string line;
        std::vector<std::vector<std::string>> parsedCsv;
        while (std::getline(data, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> parsedRow;
            while (std::getline(lineStream, cell, ','))
                parsedRow.push_back(cell);

            parsedCsv.push_back(parsedRow);
        }

        return parsedCsv;
    }
}