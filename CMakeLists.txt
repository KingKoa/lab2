cmake_minimum_required(VERSION 3.14)

project(Lab2)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp Parser.cpp Scanner.cpp Token.cpp DatalogProgram.cpp)
add_executable(Lab2 ${SOURCE_FILES})