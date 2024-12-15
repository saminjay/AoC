#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

bool safetyChecker(std::vector<int> &arr, bool dampner_used = false,
                   int skipIdx = 0) {
    bool is_inc = arr[0] < arr[1];
    int prev_num = arr[0];
    int i = 1;
    if (dampner_used) {
        if (skipIdx == 0) {
            is_inc = arr[1] < arr[2];
            prev_num = arr[1];
            i = 2;
        } else if (skipIdx == 1) {
            is_inc = arr[0] < arr[2];
        }
    }

    for (; i < arr.size(); ++i) {
        if (dampner_used && i == skipIdx)
            continue;

        int num = arr[i];
        if (is_inc) {
            if (num - prev_num > 3 || num - prev_num < 1) {
                if (dampner_used)
                    return false;

                return safetyChecker(arr, true, 0) ||
                       safetyChecker(arr, true, 1) ||
                       safetyChecker(arr, true, i - 1) ||
                       safetyChecker(arr, true, i);
            }
        } else {
            if (prev_num - num > 3 || prev_num - num < 1) {
                if (dampner_used)
                    return false;

                return safetyChecker(arr, true, 0) ||
                       safetyChecker(arr, true, 1) ||
                       safetyChecker(arr, true, i - 1) ||
                       safetyChecker(arr, true, i);
            }
        }
        prev_num = num;
    }
    return true;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input.txt";
        return 1;
    }
    std::string line;
    int safeCount = 0;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<int> arr;
        int num;
        while (ss >> num) {
            arr.push_back(num);
        }
        const bool is_safe = safetyChecker(arr);
        if (is_safe)
            ++safeCount;
    }
    std::cout << safeCount << std::endl;
    return 0;
}
