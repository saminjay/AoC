#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

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

bool inbound(const std::vector<std::string> &arr, const int i, const int j) {
    return i >= 0 && i < arr.size() && j >= 0 && j < arr[0].length();
}

int count_trails(std::vector<std::string> &arr, int i, int j,
                 std::set<std::pair<int, int>> *counted =
                     new std::set<std::pair<int, int>>()) {
    if (!inbound(arr, i, j))
        return 0;

    if (arr[i][j] == '9' && !(counted->count(std::make_pair(i, j)))) {
        counted->insert(std::make_pair(i, j));
        return 1;
    }

    int count = 0;
    if (inbound(arr, i + 1, j) && arr[i][j] + 1 == arr[i + 1][j]) {
        count += count_trails(arr, i + 1, j, counted);
    }
    if (inbound(arr, i - 1, j) && arr[i][j] + 1 == arr[i - 1][j]) {
        count += count_trails(arr, i - 1, j, counted);
    }
    if (inbound(arr, i, j + 1) && arr[i][j] + 1 == arr[i][j + 1]) {
        count += count_trails(arr, i, j + 1, counted);
    }
    if (inbound(arr, i, j - 1) && arr[i][j] + 1 == arr[i][j - 1]) {
        count += count_trails(arr, i, j - 1, counted);
    }
    return count;
}

void part1(std::vector<std::string> arr) {
    int sol = 0;
    int rows = arr.size();
    int cols = arr[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] == '0') {
                sol += count_trails(arr, i, j);
            }
        }
    }
    std::cout << sol << std::endl;
}

int count_distinct_trails(std::vector<std::string> &arr, int i, int j) {
    /*std::cout << i << " " << j << " " << arr[i][j] << "\n";*/
    if (!inbound(arr, i, j))
        return 0;

    if (arr[i][j] == '9') {
        return 1;
    }

    int count = 0;
    if (inbound(arr, i + 1, j) && arr[i][j] + 1 == arr[i + 1][j]) {
        count += count_distinct_trails(arr, i + 1, j);
    }
    if (inbound(arr, i - 1, j) && arr[i][j] + 1 == arr[i - 1][j]) {
        count += count_distinct_trails(arr, i - 1, j);
    }
    if (inbound(arr, i, j + 1) && arr[i][j] + 1 == arr[i][j + 1]) {
        count += count_distinct_trails(arr, i, j + 1);
    }
    if (inbound(arr, i, j - 1) && arr[i][j] + 1 == arr[i][j - 1]) {
        count += count_distinct_trails(arr, i, j - 1);
    }
    return count;
}

void part2(std::vector<std::string> arr) {
    int sol = 0;
    int rows = arr.size();
    int cols = arr[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] == '0') {
                sol += count_distinct_trails(arr, i, j);
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
