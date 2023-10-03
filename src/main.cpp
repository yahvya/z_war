#include <iostream>
#include "game/core/Game.h"

int main() {
    auto game = new Game::Core::Game();

    if(!game->launch() ){
        std::cerr << "Echec de lancement de la partie" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
