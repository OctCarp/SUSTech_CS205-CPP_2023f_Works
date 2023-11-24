cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(lab10_e2)

aux_source_directory(. DIR_SRCS)

add_executable(lab10_e2 ${DIR_SRCS})
