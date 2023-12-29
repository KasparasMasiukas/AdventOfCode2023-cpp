#include "day10.h"

#include <sstream>
#include <set>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <vector>

class PipeNetworkRender {
public:
    explicit PipeNetworkRender(const std::vector<std::string> &network) {
        render.resize(network.size() * SHAPE_SIZE, std::vector(network[0].size() * SHAPE_SIZE, EMPTY));
        for (int i = 0; i < network.size(); ++i) {
            for (int j = 0; j < network[i].size(); ++j) {
                auto it = shapes.find(network[i][j]);
                if (it == shapes.end()) {
                    continue;
                }
                const auto &shape = it->second;
                for (int k = 0; k < SHAPE_SIZE; ++k) {
                    for (int l = 0; l < SHAPE_SIZE; ++l) {
                        render[i * SHAPE_SIZE + k][j * SHAPE_SIZE + l] = shape[k][l];
                    }
                }
            }
        }
        fill(0, 0);
        markEnclosedSpaces();
        print();
    }

    void fill(const int i, const int j) {
        if (i < 0 || i >= render.size() || j < 0 || j >= render[i].size()) {
            return;
        }
        if (render[i][j] != EMPTY) {
            return;
        }
        render[i][j] = FILLED;
        fill(i - 1, j);
        fill(i + 1, j);
        fill(i, j - 1);
        fill(i, j + 1);
    }

    void print() const {
        for (auto &row: render) {
            for (auto &cell: row) {
                std::cout << cell;
            }
            std::cout << std::endl;
        }
    }

    void markEnclosedSpaces() {
        constexpr int mid = SHAPE_SIZE / 2;
        for (int i = mid; i < render.size(); i += SHAPE_SIZE) {
            for (int j = mid; j < render[i].size(); j += SHAPE_SIZE) {
                if (render[i][j] == EMPTY) {
                    render[i][j] = ENCLOSED;
                }
            }
        }
    }

    [[nodiscard]] int countEnclosedSpaces() const {
        int count = 0;
        for (auto &row: render) {
            for (auto &cell: row) {
                if (cell == ENCLOSED) {
                    ++count;
                }
            }
        }
        return count;
    }

private:
    static constexpr char WALL = '#';
    static constexpr char EMPTY = ' ';
    static constexpr char FILLED = '.';
    static constexpr char ENCLOSED = 'X';
    static constexpr int SHAPE_SIZE = 3;
    inline static const std::unordered_map<char, std::array<std::array<char, SHAPE_SIZE>, SHAPE_SIZE> > shapes = {
        {
            'L', {
                {
                    {' ', '#', ' '},
                    {' ', '#', '#'},
                    {' ', ' ', ' '}
                }
            }
        },
        {
            'J', {
                {
                    {' ', '#', ' '},
                    {'#', '#', ' '},
                    {' ', ' ', ' '}
                }
            }
        },
        {
            '7', {
                {
                    {' ', ' ', ' '},
                    {'#', '#', ' '},
                    {' ', '#', ' '}
                }
            }
        },
        {
            'F', {
                {
                    {' ', ' ', ' '},
                    {' ', '#', '#'},
                    {' ', '#', ' '}
                }
            }
        },
        {
            '|', {
                {
                    {' ', '#', ' '},
                    {' ', '#', ' '},
                    {' ', '#', ' '}
                }
            }
        },
        {
            '-', {
                {
                    {' ', ' ', ' '},
                    {'#', '#', '#'},
                    {' ', ' ', ' '}
                }
            }
        }
    };

    std::vector<std::vector<char> > render;
};

class PipeNetwork {
public:
    explicit PipeNetwork(const std::vector<std::string> &network): network(network) {
        distance.resize(network.size(), std::vector(network[0].length(), NOT_VISITED));
        for (int i = 0; i < network.size(); ++i) {
            for (int j = 0; j < network[i].size(); ++j) {
                if (network[i][j] == 'S') {
                    start = {i, j};
                    distance[i][j] = 0;
                }
            }
        }
        uncoverStart();
        bfs();
        printNetwork();
        printDistances();
    }

    void uncoverStart() {
        auto neighboursFromUp = getNeighbours(start.first - 1, start.second);
        const bool up = std::find(neighboursFromUp.begin(), neighboursFromUp.end(), start) != neighboursFromUp.end();
        auto neighboursFromDown = getNeighbours(start.first + 1, start.second);
        const bool down = std::find(neighboursFromDown.begin(), neighboursFromDown.end(), start) != neighboursFromDown.
                          end();
        auto neighboursFromLeft = getNeighbours(start.first, start.second - 1);
        const bool left = std::find(neighboursFromLeft.begin(), neighboursFromLeft.end(), start) != neighboursFromLeft.
                          end();
        auto neighboursFromRight = getNeighbours(start.first, start.second + 1);
        const bool right = std::find(neighboursFromRight.begin(), neighboursFromRight.end(), start) !=
                           neighboursFromRight.
                           end();

        char pipe = 'S';
        if (up && down) {
            pipe = '|';
        } else if (left && right) {
            pipe = '-';
        } else if (up && right) {
            pipe = 'L';
        } else if (up && left) {
            pipe = 'J';
        } else if (down && right) {
            pipe = 'F';
        } else if (down && left) {
            pipe = '7';
        }
        network[start.first][start.second] = pipe;
    }

    void bfs() {
        prepareStartingQueueForBfs();
        while (!bfsQueue.empty()) {
            const auto node = bfsQueue.front();
            bfsQueue.pop();
            for (auto &neighbour: getNeighbours(node.first, node.second)) {
                const int i = neighbour.first, j = neighbour.second;
                if (i < 0 || i >= network.size() || j < 0 || j >= network[i].size()) {
                    continue;
                }
                if (distance[i][j] != NOT_VISITED) {
                    continue;
                }
                distance[i][j] = distance[node.first][node.second] + 1;
                bfsQueue.push(neighbour);
            }
        }
    }

    void prepareStartingQueueForBfs() {
        while (!bfsQueue.empty()) {
            bfsQueue.pop();
        }
        // Find starting neighbours that are connected to the start node
        const auto neighbours = getNeighbours(start.first, start.second);
        for (auto &neighbour: neighbours) {
            auto neighboursFromSide = getNeighbours(neighbour.first, neighbour.second);
            if (std::find(neighboursFromSide.begin(), neighboursFromSide.end(), start) != neighboursFromSide.end()) {
                distance[neighbour.first][neighbour.second] = distance[start.first][start.second] + 1;
                bfsQueue.push(neighbour);
            }
        }
    }

    [[nodiscard]] int getMaxDistance() const {
        int maxDistance = 0;
        for (auto &row: distance) {
            for (auto &cell: row) {
                if (cell != NOT_VISITED && cell > maxDistance) {
                    maxDistance = cell;
                }
            }
        }
        return maxDistance;
    }

    [[nodiscard]] int countEnclosedSpaces() const {
        // Copy only the loop, ignoring the junk
        std::vector<std::string> loop;
        for (int i = 0; i < network.size(); ++i) {
            std::string row;
            for (int j = 0; j < network[i].size(); ++j) {
                if (distance[i][j] == NOT_VISITED) {
                    row += '.';
                } else {
                    row += network[i][j];
                }
            }
            loop.push_back(row);
        }
        const auto render = PipeNetworkRender(loop);
        return render.countEnclosedSpaces();
    }

    void printNetwork() const {
        for (auto &row: network) {
            std::cout << row << std::endl;
        }
    }

    void printDistances() const {
        for (auto &row: distance) {
            for (auto &cell: row) {
                std::cout << std::setw(5);
                if (cell == NOT_VISITED) {
                    std::cout << "X ";
                } else {
                    std::cout << cell << " ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    static constexpr int NOT_VISITED = INT_MAX;
    inline static const std::set<char> upPipes = {'|', 'L', 'J', 'S'};
    inline static const std::set<char> downPipes = {'|', '7', 'F', 'S'};
    inline static const std::set<char> leftPipes = {'-', 'J', '7', 'S'};
    inline static const std::set<char> rightPipes = {'-', 'L', 'F', 'S'};

    std::queue<std::pair<int, int> > bfsQueue;
    std::pair<int, int> start;
    std::vector<std::string> network;
    std::vector<std::vector<int> > distance;

    [[nodiscard]] std::vector<std::pair<int, int> > getNeighbours(int i, int j) const {
        if (i < 0 || i >= network.size() || j < 0 || j >= network[i].size()) {
            return {};
        }
        const char pipe = network[i][j];
        std::vector<std::pair<int, int> > neighbours;
        if (upPipes.find(pipe) != upPipes.end()) {
            neighbours.emplace_back(i - 1, j);
        }
        if (downPipes.find(pipe) != downPipes.end()) {
            neighbours.emplace_back(i + 1, j);
        }
        if (leftPipes.find(pipe) != leftPipes.end()) {
            neighbours.emplace_back(i, j - 1);
        }
        if (rightPipes.find(pipe) != rightPipes.end()) {
            neighbours.emplace_back(i, j + 1);
        }
        return neighbours;
    }
};


PipeNetwork parseNetwork(std::istream &input) {
    std::vector<std::string> network;
    std::string line;
    while (std::getline(input, line)) {
        network.push_back(line);
    }
    return PipeNetwork(network);
}

std::string Day10::solveChallenge1(std::istream &input) {
    const auto network = parseNetwork(input);
    const int maxDistance = network.getMaxDistance();
    return std::to_string(maxDistance);
}

std::string Day10::solveChallenge2(std::istream &input) {
    const auto network = parseNetwork(input);
    const int enclosedSpaces = network.countEnclosedSpaces();
    return std::to_string(enclosedSpaces);
}
