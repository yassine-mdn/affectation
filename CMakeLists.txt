cmake_minimum_required(VERSION 3.21)
project(affectation)

set(CMAKE_CXX_STANDARD 20)

add_executable(affectation main.cpp Matrice.cpp Matrice.h Output.cpp Output.h Affectation.cpp Affectation.h ConsoleColor.h)
