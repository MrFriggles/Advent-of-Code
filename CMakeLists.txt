cmake_minimum_required(VERSION 3.8)
project("Advent of Code" LANGUAGES CXX)

# No optimization and keep debugging symbols so we can run gdb for now
add_compile_options(-Wall -Wextra -pedantic -Werror -O0 -g)
set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
add_executable(aoc src/main.cpp)
