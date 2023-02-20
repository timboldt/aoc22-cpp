#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "thirdparty/abseil-cpp/absl/strings/str_split.h"

const std::string INPUT_FILE = "../input/02.txt";

enum Hand { Rock, Paper, Scisssors };

class GameRound {
    Hand us_;
    Hand them_;

   public:
    GameRound(Hand them, Hand us);

    int score() const;

    GameRound reinterpret_for_part2() const;
};

GameRound::GameRound(Hand them, Hand us) : us_(us), them_(them) {}

int GameRound::score() const {
    switch (this->us_) {
        case Hand::Rock:
            switch (this->them_) {
                case Hand::Rock:
                    return 1 + 3;
                case Hand::Paper:
                    return 1;
                case Hand::Scisssors:
                    return 1 + 6;
            }
            break;
        case Hand::Paper:
            switch (this->them_) {
                case Hand::Rock:
                    return 2 + 6;
                case Hand::Paper:
                    return 2 + 3;
                case Hand::Scisssors:
                    return 2;
            }
            break;
        case Hand::Scisssors:
            switch (this->them_) {
                case Hand::Rock:
                    return 3;
                case Hand::Paper:
                    return 3 + 6;
                case Hand::Scisssors:
                    return 3 + 3;
            }
            break;
    }
    std::cout << "Invalid GameRound (" << this->us_ << "," << this->them_
              << ")." << std::endl;
    exit(1);
}

GameRound GameRound::reinterpret_for_part2() const {
    Hand choice = this->them_;
    switch (this->us_) {
        case Hand::Rock:
            switch (this->them_) {
                case Hand::Rock:
                    choice = Hand::Scisssors;
                    break;
                case Hand::Paper:
                    choice = Hand::Rock;
                    break;
                case Hand::Scisssors:
                    choice = Hand::Paper;
                    break;
            }
            break;
        case Hand::Scisssors:
            switch (this->them_) {
                case Hand::Rock:
                    choice = Hand::Paper;
                    break;
                case Hand::Paper:
                    choice = Hand::Scisssors;
                    break;
                case Hand::Scisssors:
                    choice = Hand::Rock;
                    break;
            }
            break;
        default:
            choice = this->them_;
    }
    return GameRound(this->them_, choice);
}

Hand parse_hand(char c) {
    switch (c) {
        case 'A':
        case 'X':
            return Hand::Rock;
        case 'B':
        case 'Y':
            return Hand::Paper;
        case 'C':
        case 'Z':
            return Hand::Scisssors;
        default:
            std::cout << "Cannot parse hand '" << c << "'." << std::endl;
            exit(1);
    }
}

std::vector<GameRound> parse(const std::string &input) {
    const std::vector<std::string> lines = absl::StrSplit(input, "\n");
    std::vector<GameRound> output;
    for (auto &&line : lines) {
        if (!line.empty()) {
            output.push_back(
                GameRound(parse_hand(line[0]), parse_hand(line[2])));
        }
    }
    return output;
}

int part1(std::vector<GameRound> &parsed) {
    int sum = 0;
    for (auto &&gr : parsed) {
        sum += gr.score();
    }
    return sum;
}

int part2(std::vector<GameRound> &parsed) {
    int sum = 0;
    for (auto &&gr : parsed) {
        sum += gr.reinterpret_for_part2().score();
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
