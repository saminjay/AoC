#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <openssl/md5.h>

void printmap(std::vector<std::string> &arr) {
    for (auto s : arr)
        std::cout << s << "\n";
}

std::string read_file(std::string file_name) {
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(input_file, line);

    return line;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

std::string calculateMD5(const std::string &input) {
    unsigned char result[MD5_DIGEST_LENGTH];

    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), result);

    std::ostringstream hexStream;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(result[i]);
    }
    return hexStream.str();
}

#pragma clang diagnostic pop

bool five_zero_check(const std::string &str, int n = 5) {
    for (int i = 0; i < n; ++i)
        if (str[i] != '0')
            return false;
    return true;
}

void part1(std::string line) {
    int sol = 0;
    std::string sum = "";
    do {
        sum = calculateMD5(line + std::to_string(sol++));
    } while (!five_zero_check(sum));

    std::cout << sol - 1 << std::endl;
}

void part2(std::string line) {
    int sol = 0;
    std::string sum = "";
    do {
        sum = calculateMD5(line + std::to_string(sol++));
    } while (!five_zero_check(sum, 6));

    std::cout << sol - 1 << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
