#include "day03.h"
#include <sstream>
#include <cctype>
#include <regex>

int convertToInt(const std::vector<char>& vec) {
    int result = 0;
    for (const char c: vec) {
        if (isdigit(c)) {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

class Schematic {
public:
    void addLine(const std::string& line) {
        const std::vector lineChars(line.begin(), line.end());
        grid.push_back(lineChars);
    }

    [[nodiscard]] std::vector<std::vector<char>> getGrid() const {
        return grid;
    }

    [[nodiscard]] bool findSymbol(const int minI, const int maxI, const int minJ, const int maxJ,
                                  const int number) {
        bool found = false;
        for (int i = minI; i <= maxI; i++) {
            for (int j = minJ; j <= maxJ; j++) {
                // Ensure bounds
                if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) {
                    continue;
                }
                char c = grid[i][j];
                if (!isdigit(c) && c != '.') {
                    found = true;
                    if (c == '*') {
                        gearNumbers[i][j].push_back(number);
                    }
                }
            }
        }
        return found;
    }

    /**
     * Analyzes the grid to calculate the sum of part numbers.
     *
     * Iterates through each cell of the grid to identify and sum up part numbers. The function
     * relies on the grid being previously populated via calls to the addLine() function.
     *
     * @return The sum of all part numbers found in the grid.
     * @see addLine
     */
    int analyzeGrid() {
        gearNumbers.clear();
        gearNumbers.resize(grid.size(), std::vector<std::vector<int>>(grid[0].size()));

        int sum = 0; // sum of numbers adjacent to parts
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                std::vector<char> numberVec;
                while (isdigit(grid[i][j])) {
                    // assemble full number
                    numberVec.push_back(grid[i][j++]);
                }
                if (numberVec.empty()) {
                    continue; // no number found
                }
                // number found. Search for a symbol around the number
                const int number = convertToInt(numberVec);
                const int minI = i - 1, maxI = i + 1, minJ = j - numberVec.size() - 1, maxJ = j;
                if (findSymbol(minI, maxI, minJ, maxJ, number)) {
                    // Symbol exists, convert to actual integer and add to sum
                    sum += number;
                }
            }
        }

        return sum;
    }

    [[nodiscard]] const std::vector<std::vector<std::vector<int>>>& getGearNumbers() const {
        return gearNumbers;
    }

private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<std::vector<int>>> gearNumbers;
};

std::string Day03::solveChallenge1(std::ifstream& input) {
    Schematic schematic;
    std::string line;
    while (std::getline(input, line)) {
        schematic.addLine(line);
    }

    const int sum = schematic.analyzeGrid();
    return std::to_string(sum);
}

std::string Day03::solveChallenge2(std::ifstream& input) {
    Schematic schematic;
    std::string line;
    while (std::getline(input, line)) {
        schematic.addLine(line);
    }

    schematic.analyzeGrid();
    const auto gearNumbers = schematic.getGearNumbers();
    long int sum = 0;
    for (const auto& row: gearNumbers) {
        for (auto cell: row) {
            if (cell.size() != 2) {
                continue;
            }
            const long int product = cell[0] * cell[1];
            sum += product;
        }
    }
    return std::to_string(sum);
}
