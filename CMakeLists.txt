cmake_minimum_required(VERSION 4.2)
project(Loom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(loom ${SOURCES})