#include "day01.h"
#include <iostream>

int main() {
    try {
        Day01 day01;
        day01.testAndRunChallenges("test.txt", "142", "test2.txt", "281", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
