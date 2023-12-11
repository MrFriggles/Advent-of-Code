cmake_minimum_required(VERSION 3.8)
project("Advent of Code" LANGUAGES CXX)

# No optimization and keep debugging symbols so we can run gdb for now
add_compile_options(-Wall -Wextra -pedantic -Werror -O0 -g)
set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

# Tidy this line up...
set(DAY_SOURCE_FILES src/day10.cpp  src/day13.cpp  src/day16.cpp  src/day19.cpp  src/day21.cpp  src/day24.cpp  src/day4.cpp  src/day7.cpp src/day11.cpp  src/day14.cpp  src/day17.cpp  src/day1.cpp   src/day22.cpp  src/day2.cpp   src/day5.cpp  src/day8.cpp src/day12.cpp  src/day15.cpp  src/day18.cpp  src/day20.cpp  src/day23.cpp  src/day3.cpp   src/day6.cpp  src/day9.cpp)

add_executable(aoc src/main.cpp src/day_base.cpp ${DAY_SOURCE_FILES})
