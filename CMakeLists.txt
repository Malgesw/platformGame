cmake_minimum_required(VERSION 3.21)
project(platformGame)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR /usr/include/SFML)


add_executable(platformGame main.cpp Game.cpp Game.h State.cpp State.h headers.h GameState.cpp GameState.h MainMenuState.cpp MainMenuState.h Button.cpp Button.h PauseMenu.cpp PauseMenu.h SettingsState.cpp SettingsState.h TextField.cpp TextField.h GameCharacter.cpp GameCharacter.h Movement.h Movement.cpp WalkingMovement.cpp WalkingMovement.h FlyingMovement.cpp FlyingMovement.h LevelTile.cpp LevelTile.h TileMap.cpp TileMap.h AutoWalking.cpp AutoWalking.h Attack.cpp Attack.h AStar.cpp AStar.h Pathfinder.cpp Pathfinder.h AutoFlying.cpp AutoFlying.h AutoMovement.h AttackTarget.cpp AttackTarget.h)

include_directories(/usr/local/include)



find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(platformGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_subdirectory(test)