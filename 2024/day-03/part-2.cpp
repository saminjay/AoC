#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int get_mul(std::string::iterator begin, std::string::iterator end) {
    int sum = 0;
    std::regex mul("(mul)\\((\\d{1,3}),(\\d{1,3})\\)|(do)\\(\\)|(don't)\\(\\)");

    auto match_begin = std::sregex_iterator(begin, end, mul);
    auto match_end = std::sregex_iterator();
    bool enabled = true;
    for (auto it = match_begin; it != match_end; ++it) {
        auto match = *it;
        switch (match.str()[2]) {
        case 'n':
            enabled = false;
            break;
        case '(':
            enabled = true;
            break;
        case 'l':
            sum += enabled * (std::stoi(match[2]) * std::stoi(match[3]));
            break;
        }
    }
    return sum;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }

    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string inputString = ss.str();

    int sum = get_mul(inputString.begin(), inputString.end());
    std::cout << sum << std::endl;
    return 0;
}
