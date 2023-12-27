cmake_minimum_required(VERSION 3.27)
project(AdventOfCode2023_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(day01 day01/day01.cpp day01/day01_test.cpp)
add_executable(day02 day02/day02.cpp day02/day02_test.cpp)
add_executable(day03 day03/day03.cpp day03/day03_test.cpp)
add_executable(day04 day04/day04.cpp day04/day04_test.cpp)
add_executable(day05 day05/day05.cpp day05/day05_test.cpp)
add_executable(day06 day06/day06.cpp day06/day06_test.cpp)
add_executable(day07 day07/day07.cpp day07/day07_test.cpp)