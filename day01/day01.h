#ifndef DAY01_H
#define DAY01_H

#include "day.h"

class Day01 final : public Day {
public:
    std::string solveChallenge1(std::ifstream& input) override;

    std::string solveChallenge2(std::ifstream& input) override;
};

#endif // DAY01_H
