cmake_minimum_required(VERSION 3.0)

project(tooreadable)

add_executable(tooreadable main.cpp)

install(TARGETS tooreadable RUNTIME DESTINATION bin)
