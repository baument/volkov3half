cmake_minimum_required(VERSION 3.16)
project(PersonnelVariant5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Library
    Library/Person.cpp
    Library/Position.cpp
    Library/Worker.cpp
    Library/WorkingWorker.cpp
    Library/VacationWorker.cpp
    Library/ChildCareWorker.cpp
    Library/Department.cpp
)

target_include_directories(Library PUBLIC Library)

add_executable(ConsoleApp ConsoleApp/main.cpp)
target_link_libraries(ConsoleApp PRIVATE Library)

add_executable(Tests Tests/Tests.cpp)
target_link_libraries(Tests PRIVATE Library)

enable_testing()
add_test(NAME PersonnelTests COMMAND Tests)
