//
// Created by devel on 07/10/2023.
//

#include "LoadingScene.hpp"
#include "../background/game-background/GridBackground.hpp"
#include "../components/animation/CharacterSwitcherAnimation.hpp"
#include "../../player/character/game-characters/FileCharacter.hpp"
#include "../../utils/FileUtils.hpp"

using namespace Game::Utils;
using namespace Game::Scene::Background::GameBackground;
using namespace Game::Scene::Components::Animation;
using namespace Game::Player::Character::GameCharacters;

namespace Game::Scene::GameScene {
    LoadingScene::LoadingScene(Core::Game *linkedGame) :  BaseScene(linkedGame) {}

    bool LoadingScene::draw(int countOfRetry) noexcept {
        try {
            TraceLog(LOG_INFO,"Début d'affichage de la page de chargement");

            if(!this->configWindow() ) throw std::runtime_error("Echec de configuration de la fenêtre de chargement");

            auto globalRessource = this->linkedGame->getResourcesManager()->getGameGlobalResources();

            // création et configuration du fond de la page
                auto background = new GridBackground(this->linkedGame);
                auto backgroundDrawingZone = Rectangle(0,0,this->width,this->height);

                background->setSquareSize(55);

            // création et configuration de l'animation de joueur
                CharacterSwitcherAnimation* charactersAnimation = nullptr;

                const auto animationSpeed = 10;

                // récupération des dossiers aléatoires
                    try{
                        auto dirPath = (std::string(globalRessource->resourcesDirPath) + ResourcesManager::CHARACTERS_DIR_PATH).c_str();

                        auto countOfFiles = FileUtils::countOfFileInDir(dirPath);

                        if(countOfFiles <= 0) throw std::runtime_error("Pas de personnage d'animation trouvé");

                        // récupération de la liste des dossiers de personnage et création de l'animation
                            const unsigned int maxCharacters = 2;

                            auto charactersDirList = FileUtils::getRandomElementsInDir(dirPath,GetRandomValue(1,static_cast<int>(countOfFiles > maxCharacters ? maxCharacters : countOfFiles) ) );

                            std::vector<Character*> charactersList{};

                            // chargement des personnages et création de l'animation
                                std::for_each(charactersDirList.begin(), charactersDirList.end(), [this,&charactersList](const auto dirPath){
                                    charactersList.push_back(new FileCharacter(this->linkedGame,dirPath) );
                                });

                                charactersAnimation = new CharacterSwitcherAnimation(charactersList);
                    }
                    catch(std::exception& e){
                        TraceLog(LOG_ERROR,"Echec de listage du dossier des personnages");
                        TraceLog(LOG_ERROR,e.what() );
                    }

            // configuration du dessin de titre
                auto appName = globalRessource->appName.c_str();
                auto textColor = background->getColorFromConfig("special-on-bg");
                auto fontSize = 90.f;
                auto textPos = Vector2(
                    (this->width - static_cast<float>(MeasureText(appName,static_cast<int>(fontSize) ) ) ) / 2,
                    this->height * 0.10f
                );

            // dessin de la page
                while (this->isDrawing && !WindowShouldClose() ) {
                    BeginDrawing();

                        ClearBackground(BLANK);

                        // dessin du fond
                        background->drawIn(backgroundDrawingZone);

                        // affichage du nom du jeux
                        DrawTextEx(globalRessource->specialTextFont,appName,textPos,fontSize,0,textColor);

                        // animation d'apparition
                        if(charactersAnimation != nullptr) charactersAnimation->animate(animationSpeed);

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