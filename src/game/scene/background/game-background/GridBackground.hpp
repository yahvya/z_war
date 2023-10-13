//
// Created by devel on 10/10/2023.
//

#ifndef Z_WAR_GRIDBACKGROUND_HPP
#define Z_WAR_GRIDBACKGROUND_HPP

#include "../background/SceneBackground.hpp"
#include "../../../player/player/Player.hpp"
#include "yaml-cpp/yaml.h"

using namespace Game::Scene::Background::Background;

namespace Game::Scene::Background::GameBackground{

    /**
     * fond de scène en mode grille
     */
    class GridBackground : public SceneBackground{
        public:
            explicit GridBackground(Game::Core::Game* linkedGame);

            /**
             * fond de scène suivant le joueur
             * @param linkedGame le jeux lié
             * @param toFollow le joueur à suivre
             */
            explicit GridBackground(Game::Core::Game* linkedGame,Game::Player::Player::Player* toFollow);

            /**
             * met à jour la taille des carrés
             * @param newSquareSize taille des carrés
             * @return self
             */
            GridBackground* setSquareSize(float newSquareSize);

            SceneBackground* drawIn(Rectangle container) noexcept override;

        private:
            bool loadConfig() noexcept override;

            /**
             * dessine un carré dans le conteur
             * @param container le conteneur
             * @param color la couleur de la ligne
             * @param drawSquareSize taille du carré
             * @return self
             */
            GridBackground* drawSquareIn(Rectangle container,Color color,float drawSquareSize);

        private:
            /**
             * joueur à suivre
             */
            Game::Player::Player::Player* playerToFollow;

            /**
             * taille des carrées de la grille
             */
            float squareSize;
    };
}



#endif //Z_WAR_GRIDBACKGROUND_HPP
