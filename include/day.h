#ifndef DAY_H
#define DAY_H

#include <fstream>
#include <string>
#include <cassert>
#include <iostream>

class Day {
public:
    virtual ~Day() = default;

    virtual std::string solveChallenge1(std::istream &input) = 0;

    virtual std::string solveChallenge2(std::istream &input) = 0;

    void testAndRunChallenges(const std::string &testFilePath1, const std::string &expectedTestResult1,
                              const std::string &testFilePath2, const std::string &expectedTestResult2,
                              const std::string &inputFilePath) {
        // Test and Run Challenge 1
        testAndRunSingleChallenge(testFilePath1, expectedTestResult1, inputFilePath, &Day::solveChallenge1,
                                  "Challenge 1");

        // Test and Run Challenge 2
        testAndRunSingleChallenge(testFilePath2, expectedTestResult2, inputFilePath, &Day::solveChallenge2,
                                  "Challenge 2");
    }

private:
    void testAndRunSingleChallenge(const std::string &testFilePath, const std::string &expectedTestResult,
                                   const std::string &inputFilePath,
                                   std::string (Day::*challengeSolver)(std::istream &),
                                   const std::string &challengeName) {
        std::ifstream testFile(testFilePath);
        if (!testFile.is_open()) {
            throw std::runtime_error("Failed to open test file: " + testFilePath);
        }

        std::string testResult = (this->*challengeSolver)(testFile);
        std::cout << challengeName << " Test result: " << testResult << " , expected: " << expectedTestResult <<
                std::endl;
        assert(testResult == expectedTestResult);
        std::cout << "Test passed!" << std::endl;

        std::ifstream inputFile(inputFilePath);
        if (!inputFile.is_open()) {
            throw std::runtime_error("Failed to open input file: " + inputFilePath);
        }

        std::string challengeResult = (this->*challengeSolver)(inputFile);
        std::cout << challengeName << " Actual result: " << challengeResult << std::endl;
    }
};

#endif // DAY_H
