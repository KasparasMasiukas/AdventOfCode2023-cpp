#include "day11.h"

#include <vector>

class SpaceGrid {
public:
    explicit SpaceGrid(std::vector<std::string> grid) {
        horizontalSpace.resize(grid.size(), 1);
        verticalSpace.resize(grid[0].length(), 1);
        this->grid = std::move(grid);
    }

    void expand(const int times = 2) {
        for (int i = 0; i < grid.size(); ++i) {
            // Check empty lines (vertical space)
            bool empty = true;
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == '#') {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                verticalSpace[i] *= times;
            }
            // Check empty columns (horizontal space)
            empty = true;
            for (int j = 0; j < grid.size(); ++j) {
                if (grid[j][i] == '#') {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                horizontalSpace[i] *= times;
            }
        }
    }

    [[nodiscard]] long long sumOfDistances() const {
        const auto galaxies = getGalaxyCoordinates();
        long long sum = 0;
        for (int i = 0; i < galaxies.size(); ++i) {
            for (int j = i + 1; j < galaxies.size(); ++j) {
                sum += distance(galaxies[i].first, galaxies[i].second, galaxies[j].first, galaxies[j].second);
            }
        }
        return sum;
    }

    [[nodiscard]] std::vector<std::pair<int, int> > getGalaxyCoordinates() const {
        std::vector<std::pair<int, int> > coordinates;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == '#') {
                    coordinates.emplace_back(i, j);
                }
            }
        }
        return coordinates;
    }

    [[nodiscard]] long long distance(int iFrom, int jFrom, int iTo, int jTo) const {
        long long sum = 0;
        for (int i = std::min(iFrom, iTo); i < std::max(iFrom, iTo); ++i) {
            sum += verticalSpace[i];
        }
        for (int j = std::min(jFrom, jTo); j < std::max(jFrom, jTo); ++j) {
            sum += horizontalSpace[j];
        }
        return sum;
    }

private:
    std::vector<std::string> grid;
    std::vector<int> horizontalSpace;
    std::vector<int> verticalSpace;
};

std::vector<std::string> parseGrid(std::istream &input) {
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(input, line)) {
        grid.push_back(line);
    }
    return grid;
}

std::string Day11::solveChallenge1(std::istream &input) {
    const auto grid = parseGrid(input);
    SpaceGrid spaceGrid(grid);
    spaceGrid.expand();
    const auto sum = spaceGrid.sumOfDistances();
    return std::to_string(sum);
}

std::string Day11::solveChallenge2(std::istream &input) {
    const auto grid = parseGrid(input);
    SpaceGrid spaceGrid(grid);
    spaceGrid.expand(1e6);
    const auto sum = spaceGrid.sumOfDistances();
    return std::to_string(sum);
}
