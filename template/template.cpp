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

void part1(std::vector<std::string> arr) {
    int sol = 0;
    std::cout << sol << std::endl;
}

void part2(std::vector<std::string> arr) {
    int sol = 0;
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
