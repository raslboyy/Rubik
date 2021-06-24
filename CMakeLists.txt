cmake_minimum_required(VERSION 3.19)
project(gen_algo)

set(CMAKE_CXX_STANDARD 20)

add_executable(gen_algo main.cpp Cube/Field.cpp Cube/Field.h Cube/Cube.cpp Cube/Cube.h)