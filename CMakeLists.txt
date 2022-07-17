cmake_minimum_required(VERSION 3.21)
project(platformGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(platformGame main.cpp Game.cpp Game.h State.cpp State.h headers.h GameState.cpp GameState.h MainMenuState.cpp MainMenuState.h Button.cpp Button.h)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(platformGame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)