#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::ifstream inputFile("../input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }
    std::string line;
    int safeCount = 0;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num, prev_num;
        ss >> prev_num >> num;
        const bool is_inc = num > prev_num;
        do {
            if (is_inc) {
                if (num - prev_num > 3 || num - prev_num < 1) {
                    --safeCount;
                    break;
                }
            } else {
                if (prev_num - num > 3 || prev_num - num < 1) {
                    --safeCount;
                    break;
                }
            }
            prev_num = num;
        } while (ss >> num);
        ++safeCount;
    }
    std::cout << safeCount << std::endl;
    // 606
    return 0;
}
