#include "day04.h"

#include <sstream>
#include <regex>
#include <unordered_set>

std::unordered_set<int> parseWinningNumbers(const std::string& line) {
    std::unordered_set<int> numbers;
    const std::regex numberRegex(R"(\b\d+\b)");
    std::smatch matches;

    // Only parse the numbers between the colon and the pipe
    const auto colonPos = line.find(':');
    const auto pipePos = line.find('|');
    const std::string numbersPart = line.substr(colonPos + 1, pipePos - colonPos - 1);
    std::istringstream iss(numbersPart);
    int number;
    while (iss >> number) {
        numbers.insert(number);
    }

    return numbers;
}

std::vector<int> parseOwnNumbers(const std::string& line) {
    std::vector<int> numbers;

    // Parse all numbers after the pipe character
    const auto pipePos = line.find('|');
    const std::string numbersPart = line.substr(pipePos + 1);

    std::istringstream iss(numbersPart);
    int number;
    while (iss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

int findMatches(const std::unordered_set<int>& winningNumbers, const std::vector<int>& ownNumbers) {
    int matches = 0;
    for (auto num: ownNumbers) {
        if (winningNumbers.count(num) > 0) {
            matches++;
        }
    }
    return matches;
}

std::string Day04::solveChallenge1(std::istream &input) {
    int sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        auto winningNumbers = parseWinningNumbers(line);
        auto ownNumbers = parseOwnNumbers(line);
        int matches = findMatches(winningNumbers, ownNumbers);
        int result = 0;
        while (matches-- > 0) {
            if (result == 0) {
                result = 1;
            } else {
                result *= 2;
            }
        }
        sum += result;
    }

    return std::to_string(sum);
}

std::string Day04::solveChallenge2(std::istream &input) {
    std::vector<int> cards;
    int sum = 0;
    int i = 0;
    std::string line;
    while (std::getline(input, line)) {
        if (i == cards.size()) {
            // This card only had the original
            cards.push_back(1);
        } else {
            // Account for the original
            cards[i]++;
        }
        sum += cards[i];

        auto winningNumbers = parseWinningNumbers(line);
        auto ownNumbers = parseOwnNumbers(line);
        const int matches = findMatches(winningNumbers, ownNumbers);
        for (int j = i + 1; j <= i + matches; j++) {
            // j - index of a card ahead that we're winning copies of.
            int copies = cards[i]; // add copies depending on how many scratchcards we scratched
            if (j == cards.size()) {
                cards.push_back(copies);
            } else {
                cards[j] += copies;
            }
        }

        i++;
    }

    return std::to_string(sum);
}
