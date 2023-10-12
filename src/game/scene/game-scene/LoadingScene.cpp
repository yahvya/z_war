//
// Created by devel on 07/10/2023.
//

#include "LoadingScene.hpp"
#include "../background/game-background/GridBackground.hpp"
#include "../components/animation/CharacterSwitcherAnimation.hpp"

using namespace Game::Scene::Background::GameBackground;
using namespace Game::Scene::Components::Animation;

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

            // création et configuration de l'animation de joueur
                auto charactersAnimation = new CharacterSwitcherAnimation(300);

            // configuration du dessin de titre
                auto globalRessource = this->linkedGame->getResourcesManager()->getGameGlobalResources();
                auto appName = globalRessource->appName.c_str();
                auto textColor = background->getColorFromConfig("special-on-bg");
                auto fontSize = 100.f;
                auto textPos = Vector2(
                    (this->width - static_cast<float>(MeasureText(appName,static_cast<int>(fontSize) ) ) ) / 2,
                    this->height * 0.25f
                );


            // dessin de la page
                while (this->isDrawing && !WindowShouldClose() ) {
                    BeginDrawing();

                        ClearBackground(BLANK);

                        // dessin du fond
                        background->drawIn(backgroundDrawingZone);

                        // affichage du titre du jeux

                        DrawTextEx(globalRessource->specialTextFont,appName,textPos,fontSize,0,textColor);

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
                this->height = 480;
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