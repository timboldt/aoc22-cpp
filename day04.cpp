#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "thirdparty/abseil-cpp/absl/strings/str_split.h"

const std::string INPUT_FILE = "../input/04.txt";

class Assignment {
    int low_;
    int hi_;

   public:
    Assignment(const std::string &s);

    bool contained_within(const Assignment &other);
    bool overlapping(const Assignment &other);
};

Assignment::Assignment(const std::string &s) {
    const std::vector<std::string> vals = absl::StrSplit(s, "-");
    this->low_ = atoi(vals[0].c_str());
    this->hi_ = atoi(vals[1].c_str());
}

bool Assignment::contained_within(const Assignment &other) {
    return this->low_ <= other.low_ && this->hi_ >= other.hi_;
}

bool Assignment::overlapping(const Assignment &other) {
    return  (this->low_ >= other.low_ && this->low_ <= other.hi_)
            || (this->hi_ >= other.low_ && this->hi_ <= other.hi_)
            || (this->low_ < other.low_ && this->hi_ > other.hi_);
}

typedef std::pair<Assignment, Assignment> AssignmentPair;

std::vector<AssignmentPair> parse(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<AssignmentPair> output;
    for (auto &&line : lines) {
        if (!line.empty()) {
            const std::vector<std::string> assignments =
                absl::StrSplit(line, ",");
            output.push_back(AssignmentPair(assignments[0], assignments[1]));
        }
    }
    return output;
}

int part1(std::vector<AssignmentPair> &parsed) {
    int sum = 0;
    for (auto &&p : parsed) {
        if (p.first.contained_within(p.second) ||
            p.second.contained_within(p.first)) {
            sum += 1;
        }
    }
    return sum;
}

int part2(std::vector<AssignmentPair> &parsed) {
    int sum = 0;
    for (auto &&p : parsed) {
        if (p.first.overlapping(p.second)) {
            sum += 1;
        }
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

    auto parsed = parse(input);
    std::cout << part1(parsed) << std::endl;
    std::cout << part2(parsed) << std::endl;
}
