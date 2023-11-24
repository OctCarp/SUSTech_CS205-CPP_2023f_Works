cmake_minimum_required(VERSION 3.10)

project(lab10_e1)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

add_subdirectory(liba)
add_subdirectory(libs)

add_executable(lab10_e1 main.cpp)

target_link_libraries(lab10_e1 MyLiba MyLibs)