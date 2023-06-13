cmake_minimum_required(VERSION 3.21)
project(platformGame)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Game.cpp Game.h State.cpp State.h headers.h GameState.cpp GameState.h
        MainMenuState.cpp MainMenuState.h Button.cpp Button.h PauseMenu.cpp PauseMenu.h SettingsState.cpp
        SettingsState.h TextField.cpp TextField.h GameCharacter.cpp GameCharacter.h Movement.h Movement.cpp
        WalkingMovement.cpp WalkingMovement.h FlyingMovement.cpp FlyingMovement.h LevelTile.cpp LevelTile.h
        TileMap.cpp TileMap.h AutoWalking.cpp AutoWalking.h Attack.cpp Attack.h AStar.cpp AStar.h Pathfinder.cpp
        Pathfinder.h AutoFlying.cpp AutoFlying.h AutoMovement.h AttackTarget.cpp AttackTarget.h Room.cpp Room.h AutoAttack.h
        Animation.cpp Animation.h DropDownList.cpp DropDownList.h MeleeAttack.cpp MeleeAttack.h AutoMelee.cpp AutoMelee.h
        simpleini/SimpleIni.h Observer.h Subject.h Achievement.cpp Achievement.h
        Bullet.cpp Bullet.h RangedAttack.cpp RangedAttack.h spriteType.h AutoRanged.cpp AutoRanged.h NoAttack.cpp NoAttack.h
        NoMovement.cpp NoMovement.h usefulFunctions.cpp
        usefulFunctions.h InvalidComponent.cpp InvalidComponent.h
        exceptions.h StarRangedAttack.cpp StarRangedAttack.h Item.cpp Item.h Droid.cpp Droid.h SpecialAbility.cpp SpecialAbility.h
        NoSpecialAbility.cpp NoSpecialAbility.h Shell.cpp Shell.h SpecialAttack.cpp SpecialAttack.h GlidingMovement.cpp GlidingMovement.h Resilience.cpp Resilience.h
        PeriodicFlying.cpp PeriodicFlying.h AutoStarRanged.cpp AutoStarRanged.h)


add_executable(platformGame main.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(platformGame core)
add_subdirectory(test)