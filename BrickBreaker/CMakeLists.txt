cmake_minimum_required(VERSION 3.16)

project(BrickBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

message(STATUS "Qt6_DIR = ${Qt6_DIR}")
message(STATUS "Qt6_INCLUDE_DIRS = ${Qt6_INCLUDE_DIRS}")

add_executable(BrickBreaker
    main.cpp
)

target_link_libraries(BrickBreaker
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)