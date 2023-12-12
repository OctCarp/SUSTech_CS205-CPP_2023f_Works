cmake_minimum_required(VERSION 3.10)
project(lab11)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. DIR_SRCS)

add_executable(lab11 ${DIR_SRCS})