#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {
    std::vector<std::vector<std::string>> parseCSV(const std::string& filename);

    template <typename T>
    void __log(T msg) {
        std::cout << "[BINGO LOG]: " << msg << "\n";
    }
}