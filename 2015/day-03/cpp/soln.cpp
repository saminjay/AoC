#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
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

void move(std::set<std::pair<int, int>> &visited, int &i, int &j,
          const char c) {
    switch (c) {
    case '>':
        visited.insert(std::make_pair(i, ++j));
        break;
    case '<':
        visited.insert(std::make_pair(i, --j));
        break;
    case 'v':
        visited.insert(std::make_pair(++i, j));
        break;
    case '^':
        visited.insert(std::make_pair(--i, j));
        break;
    }
}

void part1(std::string line) {
    int i = 0, j = 0;
    std::set<std::pair<int, int>> visited;
    visited.insert(std::make_pair(i, j));
    for (auto c : line) {
        move(visited, i, j, c);
    }
    std::cout << visited.size() << std::endl;
}

void part2(std::string line) {
    int si = 0, sj = 0;
    int ri = 0, rj = 0;
    std::set<std::pair<int, int>> visited;
    visited.insert(std::make_pair(0, 0));
    for (int i = 0; i < line.length(); ++i) {
        if (i % 2)
            move(visited, si, sj, line[i]);
        else
            move(visited, ri, rj, line[i]);
    }
    std::cout << visited.size() << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
