#include "day10.h"
#include <iostream>

int main() {
    try {
        Day10 day10;
        day10.testAndRunChallenges("test.txt", "8", "test.txt", "unknown", "input.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
