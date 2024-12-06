#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }

    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string inputString = ss.str();

    std::regex mul("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    int sum = 0;
    auto match_begin = std::sregex_iterator(inputString.begin(), inputString.end(), mul);
    auto match_end = std::sregex_iterator();
    for (auto it = match_begin; it != match_end; ++it) {
        auto match = *it;
        sum += std::stoi(match[1]) * std::stoi(match[2]);
    }
    std::cout << sum << std::endl;
    return 0;
}
