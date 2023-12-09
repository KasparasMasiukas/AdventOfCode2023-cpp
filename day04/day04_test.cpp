#include "day04.h"
#include <iostream>

int main() {
    try {
        Day04 day04;
        day04.testAndRunChallenges("test.txt", "13", "test.txt", "30", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
