#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printmap(std::vector<std::vector<int>> &arr) {
    for (auto v : arr) {
        for (auto i : v)
            std::cout << i << ", ";
        std::cout << "\n";
    }
}

std::vector<int> split_string(std::string str, std::string delim) {
    std::vector<int> splits;
    int i = 0, j;
    int inc = delim.length();
    while (j != std::string::npos) {
        j = str.find(delim, i);
        splits.push_back(std::stoi(str.substr(i, j - i)));
        i = j + inc;
    }
    return splits;
}

std::vector<std::vector<int>> read_file(std::string file_name) {
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::vector<int>> arr;
    while (std::getline(input_file, line)) {
        std::vector<int> v = split_string(line, "x");
        std::sort(v.begin(), v.end());
        arr.push_back(v);
    }

    return arr;
}

void part1(std::vector<std::vector<int>> arr) {
    int sol = 0;
    for (auto v : arr)
        sol += (3 * v[0] * v[1]) + (2 * v[1] * v[2]) + (2 * v[0] * v[2]);

    std::cout << sol << std::endl;
}

void part2(std::vector<std::vector<int>> arr) {
    int sol = 0;
    for (auto v : arr)
        sol += 2 * v[0] + 2 * v[1] + v[0] * v[1] * v[2];

    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
