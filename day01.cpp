#include <iostream>
#include <string>
#include <vector>

#include "thirdparty/abseil-cpp/absl/strings/str_split.h"

std::vector<int> parse(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<int> output;
    for (auto &&line : lines) {
        output.push_back(atoi(line.c_str()));
    }
    return output;
}

int main(int, char**) {
    std::vector<int> v = parse("42\n32\n22");
    std::cout << "Hello, day01!\n" << v.size() << "\n";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << "\n";
    }
}
