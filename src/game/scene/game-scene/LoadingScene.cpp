//
// Created by devel on 07/10/2023.
//

#include "LoadingScene.hpp"
#include <iostream>
#include "../background/game-background/GridBackground.hpp"

using namespace Game::Scene::Background::GameBackground;

namespace Game::Scene::GameScene {
    LoadingScene::LoadingScene(Core::Game *linkedGame) :  BaseScene(linkedGame) {}

    bool LoadingScene::draw(int countOfRetry) noexcept {
        try {
            std::wcout << "(Début d'affichage de la page de chargement)" << std::endl;

            if(!this->configWindow() ) throw std::runtime_error("Echec de configuration de la fenêtre de chargement");

            // création du fond de la page
            auto background = new GridBackground();
            auto backgroundDrawingZone = Rectangle(0,0,this->width,this->height);

            // dessin de la page
            while (this->isDrawing && !WindowShouldClose() ) {
                auto mousePos = GetMousePosition();

                BeginDrawing();
                    ClearBackground(BLANK);

                    // dessin du fond
                    background->drawIn(backgroundDrawingZone);

                EndDrawing();
            }
        }
        catch(std::exception& e){
            if(countOfRetry == 0) {
                std::wcerr << "(Echec de dessin de la page de chargement)" << std::endl;
                std::wcerr << "(Erreur : )" << e.what() << std::endl;
            }
            else this->draw(countOfRetry - 1);
        }

        return true;
    }

    bool LoadingScene::configWindow() noexcept{
        try {
            std::wcout << "(Configuration de la fenêtre de chargement)" << std::endl;

            Image appIcon = LoadImage(this->linkedGame->getResourcesManager()->getGameGlobalResources()->appIconPath.c_str() );

            if (!IsImageReady(appIcon)) {
                throw std::runtime_error("Echec de récupération de l'icone de l'application");

                return false;
            }

            // largeur hauteur nom de la page de chargement
            this->width = 600;
            this->height = 350;
            this->windowName = "Page de chargement - ";

            // configuration manuelle

            SetWindowIcon(appIcon);
            ClearWindowState(FLAG_WINDOW_HIDDEN);
            SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);

            auto success = BaseScene::configWindow();

            if(success) this->centerWindow();

            return success;
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de configuration de la page de chargement)" << std::endl;
            std::wcerr << "(Erreur : " << e.what() << ")"  << std::endl;

        }

        return false;
    }
}