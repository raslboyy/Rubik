cmake_minimum_required(VERSION 3.19)
project(Rubik)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rubik main.cpp Cube/Field.h Cube/Cube.h Cube/Field.cpp Cube/Cube.cpp genetic_algorithm/genetic_algorithm.cpp genetic_algorithm/genetic_algorithm.h)
target_link_libraries(Rubik -lglut -lGL -lGLU -lGLEW)