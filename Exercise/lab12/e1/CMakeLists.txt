cmake_minimum_required(VERSION 3.10)
project(lab12)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. DIR_SRCS)

add_executable(lab12 ${DIR_SRCS})