#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "thirdparty/abseil-cpp/absl/strings/str_split.h"

const std::string PATH = "../input/01.txt";

std::vector<int> parse(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<int> output;
    int sum = 0;
    for (auto &&line : lines) {
        if (line.empty()) {
            output.push_back(sum);
            sum = 0;
        } else {
            sum += atoi(line.c_str());
        }
    }
    if (sum > 0) {
        output.push_back(sum);
    }
    return output;
}

int part1(const std::vector<int> &parsed) {
    return *std::max_element(parsed.begin(), parsed.end());
}

int part2(const std::vector<int> &parsed) {
    std::priority_queue<int> queue(parsed.begin(), parsed.end());
    int result = 0;
    for (size_t i = 0; i < 3; i++) {
        result += queue.top();
        queue.pop();
    }
    return result;
}

int main(int, char **) {
    std::ifstream input_file("input/01.txt");
    if (!input_file.is_open()) {
        std::cout << "Could not open file " << PATH << std::endl;
        exit(1);
    }
    std::string input((std::istreambuf_iterator<char>(input_file)),
                      (std::istreambuf_iterator<char>()));

    std::vector<int> v = parse(input);
    std::cout << part1(v) << std::endl;
    std::cout << part2(v) << std::endl;
}
