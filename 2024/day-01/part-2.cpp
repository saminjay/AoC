#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }
    std::unordered_map<int, int> right_count;
    std::vector<int> left;

    int a, b;
    while (inputFile >> a >> b) {
        left.push_back(a);
        right_count[b] += 1;
    }

    int sum = 0;
    for (auto a : left) {
        sum += a * right_count[a];
    }

    std::cout << sum << std::endl;
    return 0;
}
