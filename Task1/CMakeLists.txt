cmake_minimum_required(VERSION 3.16)

project(Variant5Lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------
# Project 1: class library
# -------------------------
add_library(
    Library
    STATIC
    Library/Generator.cpp
    Library/RandomGenerator.cpp
    Library/IStreamGenerator.cpp
    Library/ZeroGenerator.cpp
    Library/ConstantGenerator.cpp
    Library/Matrix.cpp
    Library/Exercise.cpp
    Library/Task1.cpp
    Library/Task2.cpp
)

target_include_directories(
    Library
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Library
)

# -------------------------
# Project 2: console app
# -------------------------
add_executable(
    ConsoleApp
    ConsoleApp/main.cpp
)

target_link_libraries(
    ConsoleApp
    PRIVATE
    Library
)

# -------------------------
# Project 3: tests
# -------------------------
enable_testing()

add_executable(
    Tests
    Tests/Tests.cpp
)

target_link_libraries(
    Tests
    PRIVATE
    Library
)

add_test(
    NAME Variant5Tests
    COMMAND Tests
)

# Усиленные предупреждения компилятора помогают заметить потенциальные ошибки.
if (MSVC)
    target_compile_options(Library PRIVATE /W4)
    target_compile_options(ConsoleApp PRIVATE /W4)
    target_compile_options(Tests PRIVATE /W4)
else()
    target_compile_options(Library PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ConsoleApp PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(Tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
