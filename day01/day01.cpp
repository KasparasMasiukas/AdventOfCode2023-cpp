#include "day01.h"
#include <sstream>
#include <regex>

int findCalibrationValue(const std::string& line) {
    int firstDigit = 0, secondDigit = 0;
    for (const char c: line) {
        if (isdigit(c)) {
            secondDigit = c - '0';
            if (!firstDigit) {
                firstDigit = secondDigit;
            }
        }
    }
    return firstDigit * 10 + secondDigit;
}

std::string convertDigits(std::string line) {
    const std::string digitWords[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < std::size(digitWords); i++) {
        std::regex pattern(digitWords[i]);
        std::string replacement = digitWords[i] + std::to_string(i) + digitWords[i]; // e.g. one1one
        line = std::regex_replace(line, pattern, replacement);
    }
    return line;
}

std::string Day01::solveChallenge1(std::istream &input) {
    int sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        sum += findCalibrationValue(line);
    }
    return std::to_string(sum);
}

std::string Day01::solveChallenge2(std::istream &input) {
    int sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        line = convertDigits(line);
        int value = findCalibrationValue(line);
        sum += value;
    }
    return std::to_string(sum);
}
