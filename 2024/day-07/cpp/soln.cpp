#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<long long>> read_file(std::string file_name) {
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open " << file_name << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::vector<long long>> arr;
    while (std::getline(input_file, line)) {
        std::vector<long long> nums;
        long long i = 0;
        long long delim = line.find(": ");
        nums.push_back(std::stoll(line.substr(i, delim)));
        i = delim + 2;
        delim = line.find(' ', i);
        while (delim != std::string::npos) {
            nums.push_back(std::stoll(line.substr(i, delim)));
            i = delim + 1;
            delim = line.find(' ', i);
        }
        nums.push_back(std::stoll(line.substr(i)));
        arr.push_back(nums);
    }

    return arr;
}

bool is_valid(std::vector<long long> &nums, long long op = 0, long long i = 1,
              long long sum = 0) {
    long long res = nums[0];
    long long len = nums.size();

    if (op == 0) {
        sum += nums[i];
    } else {
        sum *= nums[i];
    }

    if (i == len - 1) {
        return res == sum;
    }
    return is_valid(nums, 0, i + 1, sum) || is_valid(nums, 1, i + 1, sum);
}

void part1(std::vector<std::vector<long long>> arr) {
    long long sol = 0;
    for (auto nums : arr) {
        sol += is_valid(nums) ? nums[0] : 0;
    }
    std::cout << sol << std::endl;
}

bool is_valid_2(std::vector<long long> &nums, long long op = 0, long long i = 1,
                long long sum = 0) {
    long long res = nums[0];
    long long len = nums.size();

    if (op == 0) {
        sum += nums[i];
    } else if (op == 1) {
        sum *= nums[i];
    } else {
        sum = std::stoll(std::to_string(sum) + std::to_string(nums[i]));
    }

    if (i == len - 1) {
        return res == sum;
    }
    return is_valid_2(nums, 0, i + 1, sum) || is_valid_2(nums, 1, i + 1, sum) ||
           is_valid_2(nums, 2, i + 1, sum);
}

void part2(std::vector<std::vector<long long>> arr) {
    long long sol = 0;
    for (auto nums : arr) {
        sol += is_valid_2(nums) ? nums[0] : 0;
    }
    std::cout << sol << std::endl;
}

int main() {
    auto arr = read_file("../input.txt");
    part1(arr);
    part2(arr);

    return 0;
}
