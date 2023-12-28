#include "day02.h"
#include <sstream>
#include <unordered_map>
#include <regex>

class Game {
public:
    int getGameId() const {
        return gameId;
    }

    void setGameId(const int id) {
        gameId = id;
    }

    void addColorCount(const std::string& color, const int count) {
        maxColorCounts[color] = std::max(maxColorCounts[color], count);
    }

    int getColorMaxCount(const std::string& color) const {
        if (const auto it = maxColorCounts.find(color); it != maxColorCounts.end()) {
            return it->second;
        }
        return 0;
    }

private:
    int gameId = 0;
    std::unordered_map<std::string, int> maxColorCounts;
};

Game parseGameLine(const std::string& line) {
    Game gameState;
    const std::regex idPattern(R"(Game (\d+):)");
    const std::regex colorPattern(R"((\d+) (\w+))");
    std::smatch matches;

    // Extract game ID
    if (std::regex_search(line, matches, idPattern) && matches.size() > 1) {
        const int gameId = std::stoi(matches[1].str());
        gameState.setGameId(gameId);
    }

    // Extract color counts
    std::istringstream iss(line);
    std::string segment;
    while (std::getline(iss, segment, ';')) {
        while (std::regex_search(segment, matches, colorPattern)) {
            const int count = std::stoi(matches[1].str());
            std::string color = matches[2];

            gameState.addColorCount(color, count);

            segment = matches.suffix().str();
        }
    }

    return gameState;
}

std::string Day02::solveChallenge1(std::istream &input) {
    int sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Game game = parseGameLine(line);
        if (game.getColorMaxCount("red") <= 12 &&
            game.getColorMaxCount("green") <= 13 &&
            game.getColorMaxCount("blue") <= 14) {
            sum += game.getGameId();
        }
    }
    return std::to_string(sum);
}

std::string Day02::solveChallenge2(std::istream &input) {
    int sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Game game = parseGameLine(line);
        const int power = game.getColorMaxCount("red")
                          * game.getColorMaxCount("green")
                          * game.getColorMaxCount("blue");
        sum += power;
    }
    return std::to_string(sum);
}
