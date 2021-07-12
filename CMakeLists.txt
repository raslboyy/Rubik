cmake_minimum_required(VERSION 3.19)
project(Rubik)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Rubik
        main.cpp
        Cube/Side.h Cube/Side.cpp
        Cube/Cube.h Cube/Cube.cpp
        Random.cpp Random.h
        genetic_algorithm/genetic_algorithm.h genetic_algorithm/genetic_algorithm.cpp
)
target_link_libraries(Rubik -lglut -lGL -lGLU -lGLEW)