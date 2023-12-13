#include "day05.h"
#include <iostream>

int main() {
    try {
        Day05 day05;
        day05.testAndRunChallenges("test.txt", "35", "test.txt", "46", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
