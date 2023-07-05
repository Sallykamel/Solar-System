cmake_minimum_required(VERSION 3.24)
project(solar)

set(CMAKE_CXX_STANDARD 17)

add_executable(solar main.cpp)
target_link_libraries(solar -lglew32 -lopengl32 -lfreeglut -lglu32)