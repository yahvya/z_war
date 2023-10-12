//
// Created by devel on 10/10/2023.
//

#include "GridBackground.hpp"
#include "raylib.h"

namespace Game::Scene::Background::GameBackground{
    GridBackground::GridBackground(Game::Core::Game* linkedGame) : SceneBackground(linkedGame),playerToFollow(nullptr) {
        GridBackground::loadConfig();
    }

    GridBackground::GridBackground(Game::Core::Game* linkedGame,Game::Player::Player::Player* toFollow) : SceneBackground(linkedGame),playerToFollow(toFollow) {
        GridBackground::loadConfig();
    }

    SceneBackground* GridBackground::drawIn(Rectangle container) noexcept{
        try{
            // copie du conteneur
                Rectangle containerCopy = container;

            // constantes des gestions de la perspective
                // hauteur réservé à la partie haute de la fenêtre
                const float perspectivePercent = 0.73;
                // valeur de décalage de ligne après chaque passage
                const int reductFactor = 43;
                // distance entre chaque point (complémentaire à reductFactor)
                auto dist = this->squareSize * 5;

                // y bas de la page
                const int persectiveHeightEnd = containerCopy.y + containerCopy.height;

            // changement de la hauteur du conteneur pour dessiner sur la partie haute
                container.height *= perspectivePercent;

            // récupération des couleurs de dessin
                auto backgroundColorDatas = this->colorConfig["background-color"].as<std::array<int,4> >();
                auto primaryLineColorDatas = this->colorConfig["primary-line-color"].as<std::array<int,4> >();
                auto secondaryLineColorDatas = this->colorConfig["secondary-line-color"].as<std::array<int,4> >();

                auto primaryLineColor = Color(primaryLineColorDatas[0],primaryLineColorDatas[1],primaryLineColorDatas[2],primaryLineColorDatas[3]);
                auto secondaryLineColor = Color(secondaryLineColorDatas[0],secondaryLineColorDatas[1],secondaryLineColorDatas[2],secondaryLineColorDatas[3]);

            // ajout de la couleur de fond
                ClearBackground(Color(backgroundColorDatas[0],backgroundColorDatas[1],backgroundColorDatas[2],backgroundColorDatas[3]) );

            // calcul du nombre de ligne nécessaires pour les petits carré
                // remplissage décalé de la page sur la largeur
                auto countOfWidthLines = std::floor(container.width / this->squareSize) + 1;
                // remplissage de la page sur la hauteur
                auto countOfHeightLines = std::floor(containerCopy.height / this->squareSize) + 1;

            // calcul de taille des petits carrés et définition du conteneur descriptif
                auto littleDrawSize = this->squareSize / 2;
                auto littleSquareContainer = container;

                littleSquareContainer.width = this->squareSize;
                littleSquareContainer.height = this->squareSize;

            // dessin des carrés présent dans les carré de base
                for(int i = 0; i < countOfWidthLines; i++){
                    auto ySave = littleSquareContainer.y;

                    for(int i2 = 0; i2 < countOfHeightLines; i2++) {
                        this->drawSquareIn(littleSquareContainer, secondaryLineColor, littleDrawSize);

                        littleSquareContainer.y += this->squareSize;
                    }

                    littleSquareContainer.y = ySave;
                    littleSquareContainer.x += this->squareSize;
                }

            // dessin des lignes primaires
                this->drawSquareIn(container,primaryLineColor,this->squareSize);

            // dessin de la partie base (perspective)

                auto tmpX = container.x + (this->squareSize / 2);
                auto startY = container.y + container.height;
                auto countOfWidthLinesHalf = std::floor((container.width - this->squareSize) / this->squareSize) / 2;

                // dessin des lignes de perspectives

                DrawLine(container.x,startY,container.x + container.width,startY,primaryLineColor);

                for(int i = 0; i < countOfWidthLinesHalf; i++){
                    auto baseX =  tmpX + (i * this->squareSize);

                    DrawLine(baseX,startY,baseX - dist,persectiveHeightEnd,primaryLineColor);
                    dist -= reductFactor;
                }

                for(int i = 0; i < countOfWidthLinesHalf + 1; i++){
                    auto baseX =  tmpX + ((i + countOfWidthLinesHalf) * this->squareSize);

                    DrawLine(baseX,startY,baseX + dist,persectiveHeightEnd,primaryLineColor);
                    dist += reductFactor;
                }

            DrawFPS(30,30);
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de dessin du fond");
            TraceLog(LOG_ERROR,e.what() );
        }

        return this;
    }

    GridBackground* GridBackground::setSquareSize(int newSquareSize){
        this->squareSize = newSquareSize;

        return this;
    }

    GridBackground* GridBackground::drawSquareIn(Rectangle container,Color color,int drawSquareSize){
        // on réduit un peu la dimension pour l'affichage des lignes
            auto tmpX = container.x + (drawSquareSize / 2);
            auto tmpWidth = container.width - drawSquareSize;

        // calcul des dimensions et nombres de lignes nécessaires
            auto countOfHeightLines = std::floor(container.height / drawSquareSize) ;
            auto countOfWidthLines = std::floor(tmpWidth / drawSquareSize) + 1;
            auto endY = container.y + container.height;

        // dessin des lignes verticales
            for(int i = 0; i < countOfWidthLines;i++){
                auto x  = tmpX + (i * drawSquareSize);

                DrawLine(x,container.y,x,endY,color);
            }

        // dessin des lignes horizontales
            for(int i = 0; i< countOfHeightLines; i++){
                auto yPos = container.y + (i * drawSquareSize);

                DrawLine(container.x,yPos,container.x + container.width,yPos,color);
            }

        return this;
    }

    bool GridBackground::loadConfig() noexcept{
        TraceLog(LOG_INFO,"Chargement de la configuration du fond de page grid");

        try{
            auto backgroundConfig = YAML::LoadFile(
                std::string(this->linkedGame->getResourcesManager()->getGameGlobalResources()->resourcesDirPath) + ResourcesManager::CONFIG_DIR_PATH +
                "scenes/background/grid-background.yaml"
            );

            // vérification d'existance et contenu des élements
                if(
                    backgroundConfig["background-color"] &&
                    backgroundConfig["primary-line-color"] &&
                    backgroundConfig["primary-line-color"]
                ){
                    this->colorConfig = backgroundConfig;

                    return true;
                }
                else{
                    // configuration par défaut
                        this->colorConfig["background-color"] = std::array<int,4>{36,36,36,255};
                        this->colorConfig["primary-line-color"] = std::array<int,4>{125,124,127,255};
                        this->colorConfig["primary-line-color"] = std::array<int,4>{24,24,24,255};
                }
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de la configuration du fond grid");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }
}