cmake_minimum_required(VERSION 3.0)

project(tooreadable)

file(GLOB SOURCES
    src/*.h
    src/*.cpp
    src/parse-states/*.cpp
)

add_executable(tooreadable ${SOURCES})

install(TARGETS tooreadable RUNTIME DESTINATION bin)
