#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int search_xmas(std::vector<std::string> word_search, int x_i, int x_j) {
    std::string word = "XMAS";
    int count = 0;
    int i, j;
    int rows = word_search.size();
    int cols = word_search[0].size();

    i = x_i;
    j = x_j;

    // Right
    if (j + 3 < cols) {
        count += word_search[i][j] == word[0] &&
                 word_search[i][j + 1] == word[1] &&
                 word_search[i][j + 2] == word[2] &&
                 word_search[i][j + 3] == word[3];

        // Right Up
        if (i - 3 >= 0) {
            count += word_search[i][j] == word[0] &&
                     word_search[i - 1][j + 1] == word[1] &&
                     word_search[i - 2][j + 2] == word[2] &&
                     word_search[i - 3][j + 3] == word[3];
        }

        // Right Down
        if (i + 3 < rows) {
            count += word_search[i][j] == word[0] &&
                     word_search[i + 1][j + 1] == word[1] &&
                     word_search[i + 2][j + 2] == word[2] &&
                     word_search[i + 3][j + 3] == word[3];
        }
    }

    // Left
    if (j - 3 >= 0) {
        count += word_search[i][j] == word[0] &&
                 word_search[i][j - 1] == word[1] &&
                 word_search[i][j - 2] == word[2] &&
                 word_search[i][j - 3] == word[3];

        // Left Up
        if (i - 3 >= 0) {
            count += word_search[i][j] == word[0] &&
                     word_search[i - 1][j - 1] == word[1] &&
                     word_search[i - 2][j - 2] == word[2] &&
                     word_search[i - 3][j - 3] == word[3];
        }

        // Left Down
        if (i + 3 < rows) {
            count += word_search[i][j] == word[0] &&
                     word_search[i + 1][j - 1] == word[1] &&
                     word_search[i + 2][j - 2] == word[2] &&
                     word_search[i + 3][j - 3] == word[3];
        }
    }

    // Down
    if (i + 3 < rows) {
        count += word_search[i][j] == word[0] &&
                 word_search[i + 1][j] == word[1] &&
                 word_search[i + 2][j] == word[2] &&
                 word_search[i + 3][j] == word[3];
    }

    // Up
    if (i - 3 >= 0) {
        count += word_search[i][j] == word[0] &&
                 word_search[i - 1][j] == word[1] &&
                 word_search[i - 2][j] == word[2] &&
                 word_search[i - 3][j] == word[3];
    }

    return count;
}

int main() {
    std::ifstream inputFile("../input.txt");
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

    for (int i = 0; i < word_search.size(); ++i) {
        for (int j = 0; j < word_search[i].length(); ++j) {
            if (word_search[i][j] == 'X') {
                count += search_xmas(word_search, i, j);
            }
        }
    }

    std::cout << count << std::endl;
    return 0;
}
