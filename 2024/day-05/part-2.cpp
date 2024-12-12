#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to load input.txt";
        return 1;
    }

    std::string line;
    std::unordered_map<int, std::set<int>> umap;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        int delim = line.find('|');
        int a = std::stoi(line.substr(0, delim));
        int b = std::stoi(line.substr(delim + 1));

        umap[a].insert(b);
    }

    int count = 0;
    std::vector<std::vector<int>> out_of_order;
    while (std::getline(inputFile, line)) {
        std::vector<int> update;
        std::unordered_map<int, bool> visited;
        bool in_order = true;
        int i = 0, delim;
        do {
            delim = line.find(',', i);
            int num = std::stoi(line.substr(i, delim));

            visited[num] = true;
            for (int j : umap[num]) {
                if (visited[j]) {
                    in_order = false;
                    break;
                }
            }

            update.push_back(num);
            i = delim + 1;
        } while (delim != std::string::npos);

        if (!in_order) out_of_order.push_back(update);
        count += in_order * update[(update.size() - 1) / 2];
    }
    std::cout << count << std::endl;

    count = 0;
    for (auto arr : out_of_order) {
        for (int i = arr.size() - 1; i > 0; --i) {
            int at = i;
            int num = arr[i];
            for (int j = i - 1; j >= 0; --j) {
                if (umap[num].find(arr[j]) != umap[num].end()) {
                    at = j;
                }
            }
            if (at != i) {
                arr.erase(arr.begin() + i);
                arr.insert(arr.begin() + at, num);
                ++i;
            }
        }
        count += arr[(arr.size() - 1) / 2];
    }
    std::cout << std::endl << count << std::endl;
    return 0;
}
