#include "day02.h"
#include <iostream>

int main() {
    try {
        Day02 day02;
        day02.testAndRunChallenges("test.txt", "8", "test.txt", "2286", "input.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
