#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>

int main() {
    std::vector<int> left, right;
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }
    int a, b;
    while (inputFile >> a >> b) {
        left.push_back(a);
        right.push_back(b);
    }
    inputFile.close();
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int sum = 0;
    for (int i = 0; i < left.size(); ++i) {
        sum += abs(left[i] - right[i]);
    }
    std::cout << sum << std::endl;
    return 0;
}
