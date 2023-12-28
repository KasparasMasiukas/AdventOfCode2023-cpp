#include "day06.h"

#include <sstream>
#include <regex>
#include <unordered_set>

namespace {
    std::vector<int> parseLine(const std::string& line) {
        std::vector<int> nums;
        const auto pos = line.find(':') + 1;
        const std::string numsString = line.substr(pos);
        std::istringstream iss(numsString);
        int num;
        while (iss >> num) {
            nums.push_back(num);
        }
        return nums;
    }

    long long mergeNums(const std::vector<int>& nums) {
        long long merged = 0;
        long long exp = 1;
        for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
            int num = *it;
            while (num > 0) {
                merged += (num % 10) * exp;
                num /= 10;
                exp *= 10;
            }
        }
        return merged;
    }

    int findWinningVariants(const long long fullTime, const long long recordDistance) {
        int winningVariants = 0;
        for (long long speed = 1; speed < fullTime; ++speed) {
            const long long remainingTime = fullTime - speed;
            const long long distance = speed * remainingTime;
            if (distance > recordDistance) {
                winningVariants++;
            }
        }
        return winningVariants;
    }
}

std::string Day06::solveChallenge1(std::istream &input) {
    std::string line;
    std::getline(input, line);
    const std::vector<int> times = parseLine(line);
    std::getline(input, line);
    const std::vector<int> distances = parseLine(line);
    long long product = 1;
    for (int i = 0; i < times.size(); ++i) {
        const int fullTime = times[i];
        const int recordDistance = distances[i];
        const int winningVariants = findWinningVariants(fullTime, recordDistance);
        product *= winningVariants;
    }

    return std::to_string(product);
}

std::string Day06::solveChallenge2(std::istream &input) {
    std::string line;
    std::getline(input, line);
    const std::vector<int> times = parseLine(line);
    std::getline(input, line);
    const std::vector<int> distances = parseLine(line);

    const long long fullTime = mergeNums(times);
    const long long recordDistance = mergeNums(distances);
    const int winningVariants = findWinningVariants(fullTime, recordDistance);
    return std::to_string(winningVariants);
}
