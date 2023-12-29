#include "day09.h"
#include <iostream>

int main() {
    try {
        Day09 day09;
        day09.testAndRunChallenges("test.txt", "114", "test.txt", "2", "input.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
