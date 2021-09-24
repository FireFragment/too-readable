cmake_minimum_required(VERSION 3.0)

project(tooreadable)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES
    src/parse-states/*.cpp
    src/*.h
    src/*.cpp
)

add_executable(tooreadable ${SOURCES})

install(TARGETS tooreadable RUNTIME DESTINATION bin)

enable_testing()

file(GLOB TEST_SOURCES
    src/parse-states/*.cpp
    tests.cpp
)

add_executable(
  tests
  ${TEST_SOURCES}
)
target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
