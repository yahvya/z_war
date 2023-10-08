//
// Created by devel on 07/10/2023.
//

#include "LoadingScene.hpp"
#include <iostream>

namespace Game::Scene::GameScene {
    LoadingScene::LoadingScene(Core::Game *linkedGame) : BaseScene(linkedGame) {}

    bool LoadingScene::draw(int countOfRetry) noexcept {
        try {
            std::wcout << "Début d'affichage de la page de chargement" << std::endl;

            while (this->isDrawing) {
                std::cout << "dessin" << std::endl;
            }
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de dessin de la page de chargement)" << std::endl;
            std::wcerr << "(Erreur : )" << e.what() << std::endl;
        }

        return true;
    }
}