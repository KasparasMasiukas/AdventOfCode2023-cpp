#include "day09.h"

#include <sstream>
#include <unordered_map>
#include <iomanip>

class Readings {
public:
    explicit Readings(const std::string &line) {
        std::istringstream ss(line);
        int value;
        std::vector<int> values;
        while (ss >> value) {
            values.push_back(value);
        }
        values.push_back(NO_VALUE);
        size = static_cast<int>(values.size());
        cache.resize(size, std::vector(size, NO_VALUE));
        cache[0] = values;
        cache[size - 1][0] = 0;
    }

    int getValue(int i, int j) {
        if (j < 0 || i < 0) {
            printCache();
            throw std::runtime_error("Going out of bounds!");
        }
        if (const auto cachedValue = getCachedValue(i, j)) {
            return *cachedValue;
        }
        if (i + j < size - 1) {
            // Compute up
            // std::cout << "f(" << i << ", " << j << ") = f(" << i - 1 << ", " << j + 1 << ") - f(" << i - 1 << ", " << j
            //         << ")" << std::endl;
            return cache[i][j] = getValue(i - 1, j + 1) - getValue(i - 1, j);
        }
        // Compute down
        // std::cout << "f(" << i << ", " << j << ") = f(" << i << ", " << j - 1 << ") + f(" << i + 1 << ", " << j - 1 <<
        //         ")" << std::endl;
        return cache[i][j] = getValue(i, j - 1) + getValue(i + 1, j - 1);
    }

    int extrapolateForward() {
        return getValue(0, size - 1);
    }

    int extrapolateBack() {
        int last = 0;
        for (int i = size - 1; i >= 0; --i) {
            last = getValue(i, 0) - last;
        }
        return last;
    }

    void printCache() const {
        for (const auto &row: cache) {
            for (const int val: row) {
                std::cout << std::setw(10);
                if (val != NO_VALUE) {
                    std::cout << val << " ";
                } else {
                    std::cout << "-" << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    static constexpr int NO_VALUE = INT_MAX;
    int size;
    std::vector<std::vector<int> > cache;

    std::optional<int> getCachedValue(int i, int j) {
        if (i < 0 || j < 0 || i >= size || j >= size) {
            return std::nullopt;
        }
        if (cache[i][j] == NO_VALUE) {
            return std::nullopt;
        }
        return cache[i][j];
    }
};

std::string Day09::solveChallenge1(std::istream &input) {
    long long sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Readings readings(line);
        sum += readings.extrapolateForward();
        readings.printCache();
    }
    return std::to_string(sum);
}

std::string Day09::solveChallenge2(std::istream &input) {
    long long sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        Readings readings(line);
        sum += readings.extrapolateBack();
        readings.printCache();
    }
    return std::to_string(sum);
}
