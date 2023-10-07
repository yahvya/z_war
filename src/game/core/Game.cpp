//
// Created by devel on 03/10/2023.
//

#include <iostream>
#include "Game.hpp"

namespace Game::Core {
    bool Game::launch() noexcept{
        this->appGlobalRessources = ResourcesLoader::loadGlobalResources();

        if(this->appGlobalRessources == nullptr){
            std::cerr << "(Echec de chargement du fichier des ressources de l'application)" << std::endl;

            return false;
        }

        // libération des ressources
        delete this->appGlobalRessources;

        return true;
    }
}