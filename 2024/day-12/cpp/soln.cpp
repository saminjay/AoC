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

bool inbound(std::vector<std::string> &arr, int i, int j) {
    return i >= 0 && i < arr.size() && j >= 0 && j < arr[0].length();
}

int cell_perim(std::vector<std::string> &arr, int i, int j) {
    char reg = arr[i][j];
    int perim = 0;

    if (!inbound(arr, i + 1, j) || arr[i + 1][j] != reg) {
        ++perim;
    }

    if (!inbound(arr, i - 1, j) || arr[i - 1][j] != reg) {
        ++perim;
    }

    if (!inbound(arr, i, j + 1) || arr[i][j + 1] != reg) {
        ++perim;
    }

    if (!inbound(arr, i, j - 1) || arr[i][j - 1] != reg) {
        ++perim;
    }

    return perim;
}

std::pair<int, int> calc_area_perim(std::vector<std::string> &arr, int i, int j,
                                    std::set<std::pair<int, int>> &visited) {
    char reg = arr[i][j];
    std::pair<int, int> res, area_perim;
    visited.insert(std::make_pair(i, j));

    res.first = 1;
    res.second = cell_perim(arr, i, j);

    if (inbound(arr, i + 1, j) && arr[i + 1][j] == reg &&
        !visited.count(std::make_pair(i + 1, j))) {
        area_perim = calc_area_perim(arr, i + 1, j, visited);
        res.first += area_perim.first;
        res.second += area_perim.second;
    }

    if (inbound(arr, i - 1, j) && arr[i - 1][j] == reg &&
        !visited.count(std::make_pair(i - 1, j))) {
        area_perim = calc_area_perim(arr, i - 1, j, visited);
        res.first += area_perim.first;
        res.second += area_perim.second;
    }

    if (inbound(arr, i, j + 1) && arr[i][j + 1] == reg &&
        !visited.count(std::make_pair(i, j + 1))) {
        area_perim = calc_area_perim(arr, i, j + 1, visited);
        res.first += area_perim.first;
        res.second += area_perim.second;
    }

    if (inbound(arr, i, j - 1) && arr[i][j - 1] == reg &&
        !visited.count(std::make_pair(i, j - 1))) {
        area_perim = calc_area_perim(arr, i, j - 1, visited);
        res.first += area_perim.first;
        res.second += area_perim.second;
    }

    return res;
}

void part1(std::vector<std::string> arr) {
    long long sol = 0;
    int rows = arr.size();
    int cols = arr[0].length();
    std::set<std::pair<int, int>> visited;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited.count(std::make_pair(i, j))) {
                auto [area, perim] = calc_area_perim(arr, i, j, visited);
                sol += area * perim;
            }
        }
    }
    std::cout << sol << std::endl;
}

int count_corners(std::vector<std::string> &arr, int i, int j) {
    int count = 0;
    char reg = arr[i][j];

    if ((!inbound(arr, i + 1, j) || arr[i + 1][j] != reg) &&
        (!inbound(arr, i, j + 1) || arr[i][j + 1] != reg)) {
        ++count;
    } else if (inbound(arr, i + 1, j + 1) && arr[i + 1][j + 1] != reg &&
               arr[i + 1][j] == reg && arr[i][j + 1] == reg) {
        ++count;
    }

    if ((!inbound(arr, i + 1, j) || arr[i + 1][j] != reg) &&
        (!inbound(arr, i, j - 1) || arr[i][j - 1] != reg)) {
        ++count;
    } else if (inbound(arr, i + 1, j - 1) && arr[i + 1][j - 1] != reg &&
               arr[i + 1][j] == reg && arr[i][j - 1] == reg) {
        ++count;
    }

    if ((!inbound(arr, i - 1, j) || arr[i - 1][j] != reg) &&
        (!inbound(arr, i, j + 1) || arr[i][j + 1] != reg)) {
        ++count;
    } else if (inbound(arr, i - 1, j + 1) && arr[i - 1][j + 1] != reg &&
               arr[i - 1][j] == reg && arr[i][j + 1] == reg) {
        ++count;
    }

    if ((!inbound(arr, i - 1, j) || arr[i - 1][j] != reg) &&
        (!inbound(arr, i, j - 1) || arr[i][j - 1] != reg)) {
        ++count;
    } else if (inbound(arr, i - 1, j - 1) && arr[i - 1][j - 1] != reg &&
               arr[i - 1][j] == reg && arr[i][j - 1] == reg) {
        ++count;
    }

    return count;
}

std::pair<int, int> calc_area_perim2(std::vector<std::string> &arr, int i,
                                     int j,
                                     std::set<std::pair<int, int>> &visited) {
    std::pair<int, int> area_perim;
    char reg = arr[i][j];
    visited.insert(std::make_pair(i, j));
    area_perim.first = 1;
    area_perim.second = count_corners(arr, i, j);

    if (inbound(arr, i + 1, j) && arr[i + 1][j] == reg &&
        !visited.count(std::make_pair(i + 1, j))) {
        auto [area, perim] = calc_area_perim2(arr, i + 1, j, visited);
        area_perim.first += area;
        area_perim.second += perim;
    }

    if (inbound(arr, i - 1, j) && arr[i - 1][j] == reg &&
        !visited.count(std::make_pair(i - 1, j))) {
        auto [area, perim] = calc_area_perim2(arr, i - 1, j, visited);
        area_perim.first += area;
        area_perim.second += perim;
    }

    if (inbound(arr, i, j + 1) && arr[i][j + 1] == reg &&
        !visited.count(std::make_pair(i, j + 1))) {
        auto [area, perim] = calc_area_perim2(arr, i, j + 1, visited);
        area_perim.first += area;
        area_perim.second += perim;
    }

    if (inbound(arr, i, j - 1) && arr[i][j - 1] == reg &&
        !visited.count(std::make_pair(i, j - 1))) {
        auto [area, perim] = calc_area_perim2(arr, i, j - 1, visited);
        area_perim.first += area;
        area_perim.second += perim;
    }

    return area_perim;
}

void part2(std::vector<std::string> arr) {
    long long sol = 0;
    int rows = arr.size();
    int cols = arr[0].length();
    std::set<std::pair<int, int>> visited;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited.count(std::make_pair(i, j))) {
                auto [area, perim] = calc_area_perim2(arr, i, j, visited);
                sol += area * perim;
            }
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
