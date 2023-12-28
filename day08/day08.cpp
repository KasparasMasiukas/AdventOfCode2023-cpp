#include "day08.h"

#include <sstream>
#include <regex>
#include <unordered_map>
#include <numeric>

struct Node {
    std::string id;
    std::string left;
    std::string right;
};

class DesertMap {
public:
    DesertMap(std::string instructions, const std::unordered_map<std::string, Node> &nodes)
        : instructions(std::move(instructions)), nodes(nodes) {
    }

    // Execute an instruction to go Left or Right from a node
    std::string execute(const std::string &currentNode, const char instruction) {
        auto [_, left, right] = nodes[currentNode];
        if (instruction == 'L') {
            return left;
        }
        if (instruction == 'R') {
            return right;
        }
        throw std::runtime_error("Invalid instruction: " + std::string(1, instruction));
    }

    [[nodiscard]] char getInstruction(const int i) const {
        return instructions[i % instructions.length()];
    }

    std::vector<std::string> getStartingNodes() {
        std::vector<std::string> startingNodes;
        for (const auto &[id, _]: nodes) {
            if (id.back() == 'A') {
                startingNodes.push_back(id);
            }
        }
        return startingNodes;
    }

    static bool isEndingNode(const std::string &id) {
        return id.back() == 'Z';
    }

private:
    std::string instructions;
    std::unordered_map<std::string, Node> nodes;
};

DesertMap parseInput(std::ifstream &inputFile) {
    std::string instructions;
    std::unordered_map<std::string, Node> nodes;
    const std::regex nodePattern(R"(^(\w+)\s*=\s*\((\w+),\s*(\w+)\)$)");

    if (getline(inputFile, instructions)) {
        std::string line;
        while (getline(inputFile, line)) {
            std::smatch matches;
            if (std::regex_match(line, matches, nodePattern)) {
                if (matches.size() == 4) {
                    nodes[matches[1].str()] = {matches[1].str(), matches[2].str(), matches[3].str()};
                }
            }
        }
    }

    return {instructions, nodes};
}

std::string Day08::solveChallenge1(std::ifstream &input) {
    int i = 0;
    auto desertMap = parseInput(input);
    std::string currentNode = "AAA";
    while (currentNode != "ZZZ") {
        const char instruction = desertMap.getInstruction(i++);
        currentNode = desertMap.execute(currentNode, instruction);
    }
    return std::to_string(i);
}

std::string Day08::solveChallenge2(std::ifstream &input) {
    auto desertMap = parseInput(input);
    std::vector<std::string> currentNodes = desertMap.getStartingNodes();
    std::vector<int> loopLengths;
    for (auto &node: currentNodes) {
        int i = 0;
        std::cout << node << ": ";
        int endsFound = 0;
        int loopLength = 1;
        while (endsFound < 5) {
            node = desertMap.execute(node, desertMap.getInstruction(i++));
            if (DesertMap::isEndingNode(node)) {
                if (!endsFound) {
                    loopLength = i;
                } else {
                    std::cout << i % loopLength;
                }
                std::cout << "(" << i << ": " << node << "), ";
                // Verify existence of a loop with the same length
                assert(!endsFound || i % loopLength == 0);
                endsFound++;
            }
        }
        std::cout << std::endl;
        loopLengths.push_back(loopLength);
    }
    long long result = 1;
    for (const auto &loopLength: loopLengths) {
        result = std::lcm(result, loopLength);
    }
    return std::to_string(result);
}
