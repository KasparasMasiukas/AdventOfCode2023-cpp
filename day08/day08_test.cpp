#include "day08.h"
#include <iostream>

int main() {
    try {
        Day08 day08;
        day08.testAndRunChallenges("test.txt", "6", "test2.txt", "6", "input.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
