#include <iostream>
#include "game/core/Game.hpp"

int main() {
    try {
        // lancement du jeux
        auto game = new Game::Core::Game();

        if (!game->launch() ) {
            TraceLog(LOG_ERROR,"(Echec de lancement de la partie)");

            return EXIT_FAILURE;
        }
    }
    catch (std::exception&){
        TraceLog(LOG_ERROR,"(Une erreur interne s'est prosuite)");
        std::wcerr << "(Une erreur interne s'est produite)" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

