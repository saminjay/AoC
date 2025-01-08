#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

void part1(const std::string line) {
    int sol = 0;
    for (auto c : line) {
        sol += (c == '(') ? 1 : -1;
    }
    std::cout << sol << std::endl;
}

void part2(const std::string line) {
    int sol = 0;
    for (int i = 0; i < line.length(); ++i) {
        char c = line[i];
        sol += (c == '(') ? 1 : -1;
        if (sol == -1) {
            std::cout << i + 1 << std::endl;
            return;
        }
    }
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
