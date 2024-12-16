#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void printmap(std::vector<std::string> arr) {
    for (auto &s : arr)
        std::cout << s << std::endl;
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

int countAntinodes(std::vector<std::string> &arr, const char sig,
                   const std::vector<std::pair<int, int>> &locs,
                   std::set<std::pair<int, int>> &visited) {
    int len = locs.size();
    int rows = arr.size();
    int cols = arr[0].length();
    int count = 0;

    for (int i = 0; i < len; ++i) {
        const int m_i = locs[i].first;
        const int m_j = locs[i].second;
        for (int j = i + 1; j < len; ++j) {
            const int d_i = locs[j].first - m_i;
            const int d_j = locs[j].second - m_j;
            std::pair<int, int> anti_1, anti_2;
            anti_1 = std::make_pair(m_i - d_i, m_j - d_j);
            anti_2 = std::make_pair(locs[j].first + d_i, locs[j].second + d_j);
            if (anti_1.first >= 0 && anti_1.first < rows &&
                anti_1.second >= 0 && anti_1.second < cols &&
                visited.count(anti_1) == 0) {
                ++count;
            }
            if (anti_2.first >= 0 && anti_2.first < rows &&
                anti_2.second >= 0 && anti_2.second < cols &&
                visited.count(anti_2) == 0) {
                ++count;
            }
            visited.insert(anti_1);
            visited.insert(anti_2);
        }
    }
    return count;
}

void part1(std::vector<std::string> arr) {
    int sol = 0;
    int rows = arr.size();
    int cols = arr[0].length();
    std::unordered_map<char, std::vector<std::pair<int, int>>> signal_map;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] != '.')
                signal_map[arr[i][j]].push_back(std::make_pair(i, j));
        }
    }

    std::set<std::pair<int, int>> visited;

    for (auto &[key, value] : signal_map) {
        const int count = countAntinodes(arr, key, value, visited);
        sol += count;
    }
    std::cout << sol << std::endl;
}

int countRecurringAntinodes(std::vector<std::string> arr, const char sig,
                            const std::vector<std::pair<int, int>> &locs,
                            std::set<std::pair<int, int>> &visited) {
    int len = locs.size();
    int rows = arr.size();
    int cols = arr[0].length();
    int count = 0;

    for (int i = 0; i < len; ++i) {
        const int m_i = locs[i].first;
        const int m_j = locs[i].second;
        int j;
        for (j = i + 1; j < len; ++j) {
            if (visited.count(locs[j]) == 0) {
                ++count;
                visited.insert(locs[j]);
            }
            const int d_i = locs[j].first - m_i;
            const int d_j = locs[j].second - m_j;
            std::pair<int, int> anti_1, anti_2;

            anti_1 = std::make_pair(m_i - d_i, m_j - d_j);
            while (anti_1.first >= 0 && anti_1.first < rows &&
                   anti_1.second >= 0 && anti_1.second < cols) {
                if (visited.count(anti_1) == 0) {
                    arr[anti_1.first][anti_1.second] = '#';
                    ++count;
                    visited.insert(anti_1);
                }
                anti_1 =
                    std::make_pair(anti_1.first - d_i, anti_1.second - d_j);
            }

            anti_2 = std::make_pair(locs[j].first + d_i, locs[j].second + d_j);
            while (anti_2.first >= 0 && anti_2.first < rows &&
                   anti_2.second >= 0 && anti_2.second < cols) {
                if (visited.count(anti_2) == 0) {
                    arr[anti_2.first][anti_2.second] = '#';
                    ++count;
                    visited.insert(anti_2);
                }
                anti_2 =
                    std::make_pair(anti_2.first + d_i, anti_2.second + d_j);
            }
        }
        if (j > i + 1 && visited.count(locs[i]) == 0) {
            ++count;
            visited.insert(locs[i]);
        }
    }
    return count;
}

void part2(std::vector<std::string> arr) {
    int sol = 0;
    int rows = arr.size();
    int cols = arr[0].length();
    std::unordered_map<char, std::vector<std::pair<int, int>>> signal_map;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] != '.')
                signal_map[arr[i][j]].push_back(std::make_pair(i, j));
        }
    }

    std::set<std::pair<int, int>> visited;

    for (auto &[key, value] : signal_map) {
        const int count = countRecurringAntinodes(arr, key, value, visited);
        sol += count;
    }
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
