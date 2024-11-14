cmake_minimum_required(VERSION 3.14)
project(SpaceShooter)

# Nastavení C++ standardu
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp
        Menu.cpp
        Menu.h
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        Bullet.cpp
        Bullet.h
        Alien.cpp
        Alien.h
        BasicAlien.cpp
        BasicAlien.h
        EnemyBullet.cpp
        EnemyBullet.h
        AdvancedAlien.cpp
        AdvancedAlien.h
        HealthKit.cpp
        HealthKit.h)

# Přidání spustitelného souboru
add_executable(SpaceShooter ${SOURCE_FILES})

# Nastavení proměnné SFML_DIR podle systému
if(WIN32)
    set(SFML_DIR "C:/path/to/SFML/lib/cmake/SFML")
elseif(APPLE)
    set(SFML_DIR "/path/to/SFML/lib/cmake/SFML")
endif()

# Hledání balíčku SFML. Pokud není nalezeno, proměnná SFML_DIR musí být nastavena
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SpaceShooter sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
