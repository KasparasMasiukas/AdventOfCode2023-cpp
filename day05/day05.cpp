#include "day05.h"

#include <sstream>
#include <regex>
#include <unordered_set>

struct MappingInterval {
    long long keyFrom;
    long long valueFrom;
    long long length;

    [[nodiscard]] bool includes(const long long key) const {
        return key >= keyFrom && key < keyFrom + length;
    }
};

class Mapping {
public:
    explicit Mapping(const std::vector<MappingInterval>& intervals) : sortedIntervals(intervals) {
        std::sort(sortedIntervals.begin(), sortedIntervals.end(),
                  [](const MappingInterval& a, const MappingInterval& b) {
                      return a.keyFrom < b.keyFrom;
                  });
    }

    [[nodiscard]] long long getValue(long long key) const {
        const auto it = std::upper_bound(sortedIntervals.begin(), sortedIntervals.end(), key,
                                         [](const long long key, const MappingInterval& interval) {
                                             return key < interval.keyFrom;
                                         });

        if (it != sortedIntervals.begin()) {
            const auto prevIt = std::prev(it);
            if (prevIt->includes(key)) {
                return prevIt->valueFrom + (key - prevIt->keyFrom);
            }
        }

        return key;
    }

private:
    std::vector<MappingInterval> sortedIntervals;
};

std::vector<long long> parseSeeds(std::istream& input) {
    std::vector<long long> seeds;
    std::string line;
    std::getline(input, line);
    std::istringstream seedStream(line.substr(7)); // Skip "seeds: "
    long long seed;
    while (seedStream >> seed) {
        seeds.push_back(seed);
    }
    return seeds;
}

std::vector<Mapping> parseMappings(std::istream& input) {
    std::vector<Mapping> mappings;
    std::vector<MappingInterval> currentIntervals;
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) continue;

        if (line.find("map:") != std::string::npos) {
            if (!currentIntervals.empty()) {
                mappings.emplace_back(currentIntervals);
                currentIntervals.clear();
            }
        } else {
            std::istringstream intervalStream(line);
            long long keyFrom, valueFrom, length;
            intervalStream >> valueFrom >> keyFrom >> length;
            currentIntervals.push_back({keyFrom, valueFrom, length});
        }
    }

    if (!currentIntervals.empty()) {
        mappings.emplace_back(currentIntervals);
    }
    return mappings;
}

long long trackLocation(const long long start, const std::vector<Mapping>& mappings) {
    long long location = start;
    for (const Mapping& mapping: mappings) {
        location = mapping.getValue(location);
    }
    return location;
}

std::string Day05::solveChallenge1(std::istream &input) {
    const std::vector<long long> seeds = parseSeeds(input);
    const std::vector<Mapping> mappings = parseMappings(input);
    long long minLocation = LONG_LONG_MAX;
    for (const long long seed: seeds) {
        const long long location = trackLocation(seed, mappings);
        if (location < minLocation) {
            minLocation = location;
        }
    }

    return std::to_string(minLocation);
}

std::string Day05::solveChallenge2(std::istream &input) {
    const std::vector<long long> seeds = parseSeeds(input);
    const std::vector<Mapping> mappings = parseMappings(input);
    long long minLocation = LONG_LONG_MAX;
    for (int i = 0; i < seeds.size(); ++i) {
        const long long start = seeds[i];
        const long long length = seeds[++i];
        for (long long seed = start; seed < start + length; ++seed) {
            const long long location = trackLocation(seed, mappings);
            if (location < minLocation) {
                minLocation = location;
            }
        }
    }

    return std::to_string(minLocation);
}
