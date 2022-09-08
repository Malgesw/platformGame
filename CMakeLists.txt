cmake_minimum_required(VERSION 3.21)
project(platformGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(platformGame main.cpp Game.cpp Game.h State.cpp State.h headers.h GameState.cpp GameState.h MainMenuState.cpp MainMenuState.h Button.cpp Button.h PauseMenu.cpp PauseMenu.h SettingsState.cpp SettingsState.h TextField.cpp TextField.h GameCharacter.cpp GameCharacter.h Movement.h Movement.cpp WalkingMovement.cpp WalkingMovement.h FlyingMovement.cpp FlyingMovement.h LevelTile.cpp LevelTile.h TileMap.cpp TileMap.h DropDownList.cpp DropDownList.h Animation.cpp Animation.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)

target_link_libraries(platformGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_subdirectory(test)