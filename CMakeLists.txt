cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS -static)

project(z_war)

#recherche raylib des packages (raylib)
find_package(raylib CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex)

# ajout de raylib gui
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

# création de l'executable
add_executable(z_war src/main.cpp
        src/game/core/Game.cpp
        src/game/core/Game.hpp
        src/game/pattern/observer/ClassicObservable.cpp
        src/game/pattern/observer/ClassicObservable.hpp
        src/game/pattern/observer/ClassicObserver.cpp
        src/game/pattern/observer/ClassicObserver.hpp
        src/game/scene/scene/BaseScene.hpp
        src/game/scene/scene/BaseScene.cpp
        src/game/scene/game-scene/LoadingScene.cpp
        src/game/scene/game-scene/LoadingScene.hpp
        src/game/resources/ResourcesManager.cpp
        src/game/resources/ResourcesManager.hpp
        src/game/scene/background/background/SceneBackground.cpp
        src/game/scene/background/background/SceneBackground.hpp
        src/game/scene/background/game-background/GridBackground.cpp
        src/game/scene/background/game-background/GridBackground.hpp
        src/game/player/player/Player.cpp
        src/game/player/player/Player.hpp
        src/game/scene/components/animation/CharacterSwitcherAnimation.cpp
        src/game/scene/components/animation/CharacterSwitcherAnimation.hpp
        src/game/scene/components/animation/CharacterSwitcherAnimation.hpp
        src/game/scene/components/animation/Animation.cpp
        src/game/scene/components/animation/Animation.hpp
        src/game/player/character/character/Character.cpp
        src/game/player/character/character/Character.hpp
        src/game/player/character/character/Character.hpp
        src/game/utils/TextUtils.cpp
        src/game/utils/TextUtils.hpp
        src/game/player/character/game-characters/FileCharacter.cpp
        src/game/player/character/game-characters/FileCharacter.hpp
        src/game/utils/FileUtils.cpp
        src/game/utils/FileUtils.hpp
        src/game/player/character/character/CharacterDescription.hpp
        src/game/player/character/character/CharacterActionDescription.hpp
        src/game/functions/functions/GameFunction.cpp
        src/game/functions/functions/GameFunction.hpp
        src/game/functions/game-functions/SimpleFunctions.cpp
        src/game/functions/game-functions/SimpleFunctions.hpp
)

# ajout de yaml-cpp
add_subdirectory(libs/yaml-cpp)
include_directories(libs/yaml-cpp/include ${RAYGUI_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

# ajout des librairies
target_link_libraries(${PROJECT_NAME}
        raylib
        yaml-cpp
        ${Boost_LIBRARIES}
)

#copie du dossier ressources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# copie du fichier de configuration de base
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/app.yaml $<TARGET_FILE_DIR:${PROJECT_NAME}>/app.yaml
)
