#include <iostream>
#include "game/core/Game.hpp"

int main() {
    try {
        // lancement du jeux
        auto game = new Game::Core::Game();

        if (!game->launch() ) {
            std::wcerr << "(Echec de lancement de la partie)" << std::endl;

            return EXIT_FAILURE;
        }
    }
    catch (std::exception&){
        std::wcerr << "(Une erreur interne s'est produite)" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

