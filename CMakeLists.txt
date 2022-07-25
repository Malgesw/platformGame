cmake_minimum_required(VERSION 3.20)
project(platformGame3)

set(CMAKE_CXX_STANDARD 14)

add_executable(platformGame3 main.cpp Game.cpp Game.h State.cpp State.h headers.h GameState.cpp GameState.h MainMenuState.cpp MainMenuState.h Button.cpp Button.h PauseMenu.cpp PauseMenu.h SettingsState.cpp SettingsState.h TextField.cpp TextField.h TileMap.cpp TileMap.h LevelTile.cpp LevelTile.h GameCharacter.cpp GameCharacter.h main.cpp)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(platformGame3 sfml-system sfml-window sfml-graphics sfml-audio)