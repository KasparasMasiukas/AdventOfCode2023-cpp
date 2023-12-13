#include "day06.h"
#include <iostream>

int main() {
    try {
        Day06 day06;
        day06.testAndRunChallenges("test.txt", "288", "test.txt", "71503", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
