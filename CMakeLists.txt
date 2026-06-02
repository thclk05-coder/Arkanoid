cmake_minimum_required(VERSION 3.10)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 11)

# SFML kütüphanesini bul
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Tüm kaynak dosyalarını (src olmadan, direkt ana dizinden) ekle
set(SOURCE_FILES 
    main.cpp Game.cpp Brick.cpp Item.cpp Paddle.cpp Ball.cpp
)

add_executable(Arkanoid ${SOURCE_FILES})

# SFML'i projeye bağla
target_link_libraries(Arkanoid sfml-graphics sfml-audio sfml-window sfml-system)