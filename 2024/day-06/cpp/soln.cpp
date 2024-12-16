#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

void printmap(const std::vector<std::string> &map) {
    for (const auto &s : map)
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

bool inbound(std::vector<std::string> &map, int i, int j) {
    int rows = map.size();
    int cols = map[0].length();
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

void move(std::vector<std::string> &map, int &i, int &j, int &dir) {
    int n_i = i, n_j = j;

    switch (dir) {
    case 0: // Up
        --n_i;
        break;
    case 1: // Left
        ++n_j;
        break;
    case 2: // Down
        ++n_i;
        break;
    case 3: // Right
        --n_j;
        break;
    }

    if (inbound(map, n_i, n_j) && map[n_i][n_j] == '#') {
        dir = (dir + 1) % 4;
    } else {
        i = n_i;
        j = n_j;
    }
}

void part1(std::vector<std::string> map) {
    int sol = 0;
    int rows = map.size();
    int cols = map[0].length();
    int i, j;
    bool brfl = false;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if (map[i][j] == '^') {
                brfl = true;
                break;
            }
        }
        if (brfl)
            break;
    }

    int dir = 0;
    while (i >= 0 && i < rows && j >= 0 && j < cols) {
        sol += (map[i][j] != 'X');
        map[i][j] = 'X';
        move(map, i, j, dir);
    }

    std::cout << sol << std::endl;
}

bool put_obstacle(std::vector<std::string> &map, int i, int j, int dir,
                  const int &idx, const int &jdx,
                  std::set<std::tuple<int, int>> &obstacles) {
    switch (dir) {
    case 0: // Up
        --i;
        break;
    case 1: // Left
        ++j;
        break;
    case 2: // Down
        ++i;
        break;
    case 3: // Right
        --j;
        break;
    }
    if (!inbound(map, i, j) || (i == idx && j == jdx) || map[i][j] == '#' ||
        obstacles.count(std::make_tuple(i, j))) {
        return false;
    }
    map[i][j] = '#';
    obstacles.insert(std::make_tuple(i, j));
    return true;
}

int check_loop(std::vector<std::string> map, int i, int j, int dir,
               const int &idx, const int &jdx,
               const std::set<std::tuple<int, int, int>> &map_visits,
               std::set<std::tuple<int, int>> &obstacles) {
    if (!put_obstacle(map, i, j, dir, idx, jdx, obstacles))
        return 0;

    std::set<std::tuple<int, int, int>> visited = map_visits;
    dir = (dir + 1) % 4;

    int count = 0;
    while (inbound(map, i, j)) {
        auto state = std::make_tuple(i, j, dir);
        if (visited.count(state)) {
            return 1;
        }
        visited.insert(state);
        move(map, i, j, dir);
    }
    return 0;
}

void part2(std::vector<std::string> map) {
    int sol = 0;
    int rows = map.size();
    int cols = map[0].length();
    int i, j;
    bool brfl = false;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if (map[i][j] == '^') {
                brfl = true;
                break;
            }
        }
        if (brfl)
            break;
    }

    const int idx = i, jdx = j;
    int dir = 0;
    std::set<std::tuple<int, int, int>> visited;
    std::set<std::tuple<int, int>> obstacles;
    while (inbound(map, i, j)) {
        visited.insert(std::make_tuple(i, j, dir));
        sol += check_loop(map, i, j, dir, idx, jdx, visited, obstacles);
        move(map, i, j, dir);
    }

    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
