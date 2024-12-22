#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void printmap(std::vector<std::string> &arr) {
    for (auto s : arr)
        std::cout << s << "\n";
}

std::vector<long> read_file(std::string file_name) {
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<long> arr;
    std::getline(input_file, line);
    std::stringstream ss(line);
    long l;
    while (ss >> l) {
        arr.push_back(l);
    }

    return arr;
}

std::vector<long> blink(const std::vector<long> &arr) {
    std::vector<long> vec;
    std::string s;
    for (auto a : arr) {
        s = std::to_string(a);
        if (a == 0) {
            vec.push_back(1);
        } else if (s.length() % 2 == 0) {
            vec.push_back(
                std::stol(std::string(s.begin(), s.begin() + s.length() / 2)));
            vec.push_back(
                std::stol(std::string(s.begin() + s.length() / 2, s.end())));
        } else {
            vec.push_back(a * 2024);
        }
    }
    return vec;
}

void part1(std::vector<long> arr) {
    int sol = 0;
    for (int i = 0; i < 25; ++i) {
        arr = blink(arr);
    }
    sol = arr.size();
    std::cout << sol << std::endl;
}

std::unordered_map<std::string, long long> umap;

long long count_stone(long long val, int blink) {
    if (!blink) {
        return 1;
    }

    std::string s = std::to_string(val);
    std::string b1 = std::to_string(blink - 1);

    if (val == 0) {
        long long count = umap["1-" + b1];
        if (!count) {
            count = count_stone(1, blink - 1);
            umap["1-" + b1] = count;
        }
        return count;
    }

    if (s.length() % 2) {
        long long count = umap[std::to_string(val * 2024) + '=' + b1];
        if (!count) {
            count = count_stone(val * 2024, blink - 1);
            umap[std::to_string(val * 2024) + '=' + b1] = count;
        }
        return count;
    }

    int len = s.length();
    auto beg = s.begin();
    auto end = s.end();

    std::string val1(beg, beg + len / 2);
    long long count1 = umap[val1 + '-' + b1];
    if (!count1) {
        count1 = count_stone(std::stoi(val1), blink - 1);
        umap[val1 + '-' + b1] = count1;
    }

    std::string val2(beg + len / 2, end);
    long long count2 = umap[val2 + '-' + b1];
    if (!count2) {
        count2 = count_stone(std::stoi(val2), blink - 1);
        umap[val2 + '-' + b1] = count2;
    }

    return count1 + count2;
}

void part2(std::vector<long> arr) {
    long long sol = 0;
    for (auto a : arr) {
        sol += count_stone(a, 75);
    }
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
