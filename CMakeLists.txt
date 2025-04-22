cmake_minimum_required(VERSION 3.10)

project(AICreator LANGUAGES C CXX)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_FLAGS "-Wall -Wextra -O2")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")