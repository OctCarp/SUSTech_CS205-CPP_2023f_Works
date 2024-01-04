cmake_minimum_required(VERSION 3.12.1)
project(assign4)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC "src/*.cpp")
file(GLOB INC "src/*.hpp")
add_executable(assign4 ${SRC} ${INC})
