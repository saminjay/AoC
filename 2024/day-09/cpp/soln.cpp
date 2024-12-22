#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

template <typename T> void printv(std::vector<T> &arr) {
    for (auto i : arr)
        std::cout << i << "\n";
    std::cout << "\n";
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

std::vector<int> defrag(std::vector<int> fs) {
    int left = 0;
    int right = fs.size() - 1;
    while (left < right) {
        if (fs[left] == -1) {
            while (fs[right] == -1)
                --right;
            fs[left] = fs[right];
            fs[right] = -1;
            --right;
        }
        ++left;
    }
    return fs;
}

long long checksum(std::vector<int> dfs) {
    long long c = 0;
    for (int i = 0; i < dfs.size(); ++i) {
        if (dfs[i] > -1)
            c += i * dfs[i];
    }
    return c;
}

void part1(std::string arr) {
    long long sol = 0;
    int len = arr.length();
    int id = 0;
    std::vector<int> fs;
    for (int i = 0; i < len; ++i) {
        char a = arr[i];
        if (i % 2) {
            fs.insert(fs.end(), a - '0', -1);
        } else {
            id = i / 2;
            fs.insert(fs.end(), a - '0', id);
        }
    }
    auto dfs = defrag(fs);
    sol = checksum(dfs);
    std::cout << sol << std::endl;
}

void part2(std::string arr) {
    long long sol = 0;
    int len = arr.length();
    std::vector<int> dfs;
    std::set<int> used;
    int id;
    int left = 0;
    int right = len - 1;
    while (left < len) {
        int count = arr[left] - '0';
        if (left % 2) {
            while (right > left) {
                int r_count = arr[right] - '0';
                if (r_count <= count && !used.count(right / 2)) {
                    id = right / 2;
                    dfs.insert(dfs.end(), r_count, id);
                    used.insert(id);
                    count -= r_count;
                }
                if (!count)
                    break;
                right -= 2;
            }
            dfs.insert(dfs.end(), count, -1);
            right = len - 1;
        } else {
            id = left / 2;
            int val = used.count(id) ? -1 : id;
            dfs.insert(dfs.end(), count, val);
            used.insert(id);
        }
        ++left;
    }
    sol = checksum(dfs);
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
