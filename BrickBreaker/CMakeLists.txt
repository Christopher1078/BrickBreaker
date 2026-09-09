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
    crearcuenta.h crearcuenta.cpp
    usuario.h usuario.cpp
    usermanager.h usermanager.cpp
    iniciarsesion.h iniciarsesion.cpp
    menuprincipal.h menuprincipal.cpp
    menuniveles.h menuniveles.cpp
    nivel1.h nivel1.cpp
    pantallavictoria.h pantallavictoria.cpp
    pantalladerrota.h pantalladerrota.cpp
    nivel2.h nivel2.cpp
    nivel3.h nivel3.cpp
    nivel4.h nivel4.cpp
    nivel5.h nivel5.cpp
    powerup.h powerup.cpp
)

qt_add_resources(BrickBreaker "recursos"
    PREFIX "/"
    FILES
        imagenes/menu.png
	imagenes/crearcuenta.png
	imagenes/ojo1.png
	imagenes/ojo2.png
	imagenes/iniciarsesion.png
	imagenes/menuprincipal.png
	imagenes/menuniveles.png
	imagenes/bloque_morado.png
	imagenes/bloque_naranja.png
	imagenes/bloque_verde.png
	imagenes/bloque_azul.png
	imagenes/pelota.png
	imagenes/paleta.png
	imagenes/bloque_rojo.png
	imagenes/fondo.png
	imagenes/corazon.png
	imagenes/victoria.png
	imagenes/estrellas.png
	imagenes/1-0.png
	imagenes/1-1.png
	imagenes/1-2.png
	imagenes/1-3.png
	imagenes/2.png
	imagenes/2-0.png
	imagenes/2-1.png
	imagenes/2-2.png
	imagenes/2-3.png
	imagenes/3.png
	imagenes/3-0.png
	imagenes/3-1.png
	imagenes/3-2.png
	imagenes/3-3.png
	imagenes/4.png
	imagenes/4-0.png
	imagenes/4-1.png
	imagenes/4-2.png
	imagenes/4-2.png
	imagenes/4-3.png
	imagenes/5.png
	imagenes/5-0.png
	imagenes/5-1.png
	imagenes/5-2.png
	imagenes/5-3.png
	imagenes/derrota.png
	imagenes/blindado_0.png
	imagenes/blindado_1.png
	imagenes/blindado_2.png
	imagenes/vida_extra.png
	imagenes/pelota_extra.png
	imagenes/pelota_veloz.png
	imagenes/paleta_larga.png
	imagenes/metalico.png
)

target_link_libraries(BrickBreaker
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)