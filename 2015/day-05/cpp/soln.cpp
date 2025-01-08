#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printmap(std::vector<std::string> &arr) {
    for (auto s : arr)
        std::cout << s << "\n";
}

std::vector<std::string> read_file(std::string file_name) {
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::string> arr;
    while (std::getline(input_file, line)) {
        arr.push_back(line);
    }

    return arr;
}

bool is_vowel(const char c) {
    for (auto a : {'a', 'e', 'i', 'o', 'u'})
        if (c == a)
            return true;
    return false;
}

bool has_naughty(const std::string &str) {
    for (auto s : {"ab", "cd", "pq", "xy"})
        if (str.find(s) != std::string::npos)
            return true;
    return false;
}

bool is_nice(const std::string &str) {
    if (has_naughty(str))
        return false;

    int vowel = 0;
    bool has_double = false;
    for (int i = 0; i < str.size(); ++i) {
        vowel += is_vowel(str[i]);
        if (!has_double && i > 0 && str[i] == str[i - 1])
            has_double = true;
    }
    return vowel > 2 && has_double;
}

void part1(std::vector<std::string> arr) {
    int sol = 0;
    for (auto s : arr)
        sol += is_nice(s);
    std::cout << sol << std::endl;
}

bool is_nice_2(const std::string &str) {
    bool has_double = false;
    bool has_2_twice = false;
    for (int i = 0; i < str.size(); ++i) {
        if (!has_2_twice) {
            const std::string ch(str.begin() + i, str.begin() + i + 2);
            has_2_twice = str.find(ch, i + 2) != std::string::npos;
        }
        if (!has_double && i < str.size() - 2 && str[i] == str[i + 2])
            has_double = true;
        if (has_double && has_2_twice)
            return true;
    }
    return has_double && has_2_twice;
}

void part2(std::vector<std::string> arr) {
    int sol = 0;
    for (auto s : arr)
        sol += is_nice_2(s);
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
