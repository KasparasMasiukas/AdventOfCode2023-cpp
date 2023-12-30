#include "day11.h"
#include <iostream>

int main() {
    try {
        Day11 day11;
        day11.testAndRunChallenges("test.txt", "374", "test.txt", "82000210", "input.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
