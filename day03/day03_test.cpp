#include "day03.h"
#include <iostream>

int main() {
    try {
        Day03 day03;
        day03.testAndRunChallenges("test.txt", "4361", "test.txt", "467835", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
