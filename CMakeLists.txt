cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(RAYLIB_VERSION 4.5.0)

project(z_war)

#recherche raylib des packages (raylib,ryml)

find_package(raylib ${RAYLIB_VERSION} QUIET)
find_package(ryml CONFIG REQUIRED)

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
        src/game/resources/ResourcesLoader.cpp
        src/game/resources/ResourcesLoader.hpp
)

target_link_libraries(${PROJECT_NAME}
        raylib
        ryml::ryml
)

#copie du dossier ressources

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

# copie du fichier de configuration de base

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/app.yaml $<TARGET_FILE_DIR:${PROJECT_NAME}>/app.yaml)
