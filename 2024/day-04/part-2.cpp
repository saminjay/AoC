#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int search_xmas(std::vector<std::string> word_search, int const i, int const j) {
    int count = 0;
    int rows = word_search.size();
    int cols = word_search[0].size();

    count += (word_search[i + 1][j - 1] == 'M' && word_search[i - 1][j + 1] == 'S') &&
        (
            (word_search[i + 1][j + 1] == 'M' && word_search[i - 1][j - 1] == 'S') ||
            (word_search[i + 1][j + 1] == 'S' && word_search[i - 1][j - 1] == 'M')
        );
    count += (word_search[i + 1][j - 1] == 'S' && word_search[i - 1][j + 1] == 'M') &&
        (
            (word_search[i + 1][j + 1] == 'M' && word_search[i - 1][j - 1] == 'S') ||
            (word_search[i + 1][j + 1] == 'S' && word_search[i - 1][j - 1] == 'M')
        );
    return count;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }

    std::vector<std::string> word_search;
    std::string line;
    while (std::getline(inputFile, line)) {
        word_search.push_back(line);
    }

    int count = 0;

    for (int i = 1; i < word_search.size() - 1; ++i) {
        for (int j = 1; j < word_search[i].length() - 1; ++j) {
            if (word_search[i][j] == 'A') {
                count += search_xmas(word_search, i, j);
            }
        }
    }

    std::cout << count << std::endl;
    return 0;
}
