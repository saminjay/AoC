#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream inputFile("../input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to load input.txt";
        return 1;
    }

    std::string line;
    std::unordered_map<int, std::vector<int>> umap;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        int delim = line.find('|');
        int a = std::stoi(line.substr(0, delim));
        int b = std::stoi(line.substr(delim + 1));

        umap[a].push_back(b);
    }

    int count = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> update;
        int i = 0;
        int delim = line.find(',');
        while (delim != std::string::npos) {
            int num = std::stoi(line.substr(i, delim));
            update.push_back(num);
            i = delim + 1;
            delim = line.find(',', i);
        }
        update.push_back(std::stoi(line.substr(i)));

        std::unordered_map<int, bool> visited;
        bool in_order = true;
        for (int i : update) {
            visited[i] = true;
            for (int j : umap[i]) {
                if (visited[j]) {
                    in_order = false;
                    break;
                }
            }
            if (!in_order)
                break;
        }
        count += in_order * update[(update.size() - 1) / 2];
    }
    std::cout << count << std::endl;

    return 0;
}
