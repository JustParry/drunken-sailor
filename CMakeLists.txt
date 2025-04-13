cmake_minimum_required(VERSION 3.10)

project(drunkensailor)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(drunkensailor src/main.cpp src/game.cpp)