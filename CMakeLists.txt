cmake_minimum_required(VERSION 3.0)

project(tooreadable)

file(GLOB SOURCES
    src/*.h
    src/*.cpp
    src/parse-states/*.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tooreadable ${SOURCES})

install(TARGETS tooreadable RUNTIME DESTINATION bin)
