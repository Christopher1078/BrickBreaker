cmake_minimum_required(VERSION 3.16)

project(BrickBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BrickBreaker main.cpp)

include(GNUInstallDirs)
install(TARGETS BrickBreaker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
