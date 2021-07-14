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
        Cube/Action/IAction.cpp Cube/Action/IAction.h
        Cube/Action/Move.cpp Cube/Action/Move.h
        Cube/Action/Scramble.cpp Cube/Action/Scramble.h
        Cube/Action/Rotate.cpp Cube/Action/Rotate.h
        Cube/Action/Skip.cpp Cube/Action/Skip.h Cube/Model3D.cpp Cube/Model3D.h)
target_link_libraries(Rubik -lglut -lGL -lGLU -lGLEW)