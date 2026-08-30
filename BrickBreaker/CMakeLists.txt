cmake_minimum_required(VERSION 3.16)

project(BrickBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(BrickBreaker
    main.cpp
    Juego.cpp
    Juego.h
    Pelota.cpp
    Pelota.h
    Paleta.cpp
    Paleta.h
    Bloque.cpp
    Bloque.h
    menuinicio.h menuinicio.cpp
    Recursos.qrc
    crearcuenta.h crearcuenta.cpp
)

qt_add_resources(BrickBreaker "recursos"
    PREFIX "/"
    FILES
        imagenes/menu.png
	imagenes/crearcuenta.png
)

target_link_libraries(BrickBreaker
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)