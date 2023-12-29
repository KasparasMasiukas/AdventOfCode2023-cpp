#include "day10.h"

#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <vector>

class PipeNetwork {
public:
    explicit PipeNetwork(std::vector<std::string> network): network(std::move(network)) {
        distance.resize(network.size(), std::vector(network[0].size(), NOT_VISITED));
        for (int i = 0; i < network.size(); ++i) {
            for (int j = 0; j < network[i].size(); ++j) {
                if (network[i][j] == 'S') {
                    start = {i, j};
                    distance[i][j] = 0;
                    bfsQueue.emplace(i, j);
                }
            }
        }
    }

private:
    static constexpr int NOT_VISITED = INT_MAX;
    std::queue<std::pair<int, int>> bfsQueue;
    std::pair<int, int> start;
    std::vector<std::string> network;
    std::vector<std::vector<int>> distance;
};

std::vector<std::string> parseNetwork(std::istream &input) {
    std::vector<std::string> map;
    std::string line;
    while (std::getline(input, line)) {
        map.push_back(line);
    }
    return map;
}

std::string Day10::solveChallenge1(std::istream &input) {
    long long sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Readings readings(line);
        sum += readings.extrapolateForward();
        readings.printCache();
    }
    return std::to_string(sum);
}

std::string Day10::solveChallenge2(std::istream &input) {
    long long sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Readings readings(line);
        sum += readings.extrapolateBack();
        readings.printCache();
    }
    return std::to_string(sum);
}
