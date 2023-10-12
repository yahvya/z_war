//
// Created by devel on 07/10/2023.
//

#include "LoadingScene.hpp"
#include "../background/game-background/GridBackground.hpp"

using namespace Game::Scene::Background::GameBackground;

namespace Game::Scene::GameScene {
    LoadingScene::LoadingScene(Core::Game *linkedGame) :  BaseScene(linkedGame) {}

    bool LoadingScene::draw(int countOfRetry) noexcept {
        try {
            TraceLog(LOG_INFO,"Début d'affichage de la page de chargement");

            if(!this->configWindow() ) throw std::runtime_error("Echec de configuration de la fenêtre de chargement");

            // création et coonfiguration du fond de la page
                auto background = new GridBackground(this->linkedGame);
                auto backgroundDrawingZone = Rectangle(0,0,this->width,this->height);

                background->setSquareSize(55);

            // dessin de la page
                while (this->isDrawing && !WindowShouldClose() ) {
                    BeginDrawing();

                        ClearBackground(BLANK);

                        // dessin du fond
                        background->drawIn(backgroundDrawingZone);

                    EndDrawing();
                }
        }
        catch(std::exception& e){
            if(countOfRetry == 0) {
                TraceLog(LOG_ERROR,"Echec de dessin de la page de chargement");
                TraceLog(LOG_ERROR,e.what() );
            }
            else this->draw(countOfRetry - 1);
        }

        return true;
    }

    bool LoadingScene::configWindow() noexcept{
        try {
            TraceLog(LOG_INFO,"Configuration de la fenêtre de chargement");

            // chargement de l'icone de l'application
                Image appIcon = LoadImage(this->linkedGame->getResourcesManager()->getGameGlobalResources()->appIconPath.c_str() );

                if (!IsImageReady(appIcon)) {
                    throw std::runtime_error("Echec de récupération de l'icone de l'application");

                    return false;
                }

            // configuration interne de la fenêtre
                this->width = 800;
                this->height = 380;
                this->windowName = "";

            // configuration manuelle

                SetWindowIcon(appIcon);
                ClearWindowState(FLAG_WINDOW_HIDDEN);
                SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);

            auto success = BaseScene::configWindow();

            if(success) this->centerWindow();

            return success;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de configuration de la page de chargement");
            TraceLog(LOG_ERROR,e.what() );

        }

        return false;
    }
}