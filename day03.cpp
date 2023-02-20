#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "thirdparty/abseil-cpp/absl/container/btree_set.h"
#include "thirdparty/abseil-cpp/absl/strings/str_split.h"

const std::string INPUT_FILE = "../input/03.txt";

typedef std::pair<std::string, std::string> Part1Pair;
typedef std::tuple<std::string, std::string, std::string> Part2Tuple;

std::vector<Part1Pair> parse_part1(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<Part1Pair> output;
    for (auto &&line : lines) {
        if (!line.empty()) {
            output.push_back(Part1Pair(line.substr(0, line.length() / 2),
                                       line.substr(line.length() / 2)));
        }
    }
    return output;
}

std::vector<Part2Tuple> parse_part2(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<Part2Tuple> output;
    std::vector<std::string> chunk;
    size_t offset = 0;
    for (auto &&line : lines) {
        if (!line.empty()) {
            chunk.push_back(line);
            if (chunk.size() == 3) {
                output.push_back(Part2Tuple(chunk[0], chunk[1], chunk[2]));
                chunk.clear();
            }
        }
    }
    return output;
}

int item_priority(char ch) {
    if (islower(ch)) {
        return ch - 'a' + 1;
    }
    if (isupper(ch)) {
        return ch - 'A' + 27;
    }
    return 0;
}

char common_item(std::string s1, std::string s2) {
    absl::btree_set<char> set1(s1.begin(), s1.end());
    absl::btree_set<char> set2(s2.begin(), s2.end());
    std::vector<char> result(set1.size() + set2.size());
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          result.begin());
    return result[0];
}

char common_item_among_three(std::string s1, std::string s2, std::string s3) {
    absl::btree_set<char> set1(s1.begin(), s1.end());
    absl::btree_set<char> set2(s2.begin(), s2.end());
    absl::btree_set<char> set3(s3.begin(), s3.end());

    // TODO: There is probably a better way to do this that doesn't involve an intermediate vector.
    std::vector<char> result1(set1.size() + set2.size());
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                          result1.begin());
    absl::btree_set<char> set1_2(result1.begin(), result1.end());

    std::vector<char> result2(set1_2.size() + set3.size());
    std::set_intersection(set1_2.begin(), set1_2.end(), set3.begin(), set3.end(),
                          result2.begin());
    return result2[0];
}

int part1(std::vector<Part1Pair> &parsed) {
    int sum = 0;
    for (auto &&rs : parsed) {
        sum += item_priority(common_item(rs.first, rs.second));
    }
    return sum;
}

int part2(std::vector<Part2Tuple> &parsed) {
    int sum = 0;
    for (auto &&rs : parsed) {
        const auto [ one, two, three ] = rs;
        sum += item_priority(common_item_among_three(one, two, three));
    }
    return sum;
}

int main(int, char **) {
    std::ifstream input_file(INPUT_FILE);
    if (!input_file.is_open()) {
        std::cout << "Could not open file " << INPUT_FILE << std::endl;
        exit(1);
    }
    std::string input((std::istreambuf_iterator<char>(input_file)),
                      (std::istreambuf_iterator<char>()));

    auto parsed1 = parse_part1(input);
    std::cout << part1(parsed1) << std::endl;

    auto parsed2 = parse_part2(input);
    std::cout << part2(parsed2) << std::endl;
}
