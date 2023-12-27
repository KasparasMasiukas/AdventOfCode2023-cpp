#include "day07.h"
#include <iostream>

int main() {
    try {
        Day07 day07;
        day07.testAndRunChallenges("test.txt", "6440", "test.txt", "5905", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
