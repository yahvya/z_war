//
// Created by devel on 10/10/2023.
//

#ifndef Z_WAR_SCENEBACKGROUND_HPP
#define Z_WAR_SCENEBACKGROUND_HPP

#include "raylib.h"
#include "../../../pattern/observer/ClassicObserver.hpp"
#include "../../../core/Game.hpp"

using namespace Game::Pattern::Observer;

namespace Game::Scene::Background::Background{
    /**
     * représente le fond d'une scène
     */
    class SceneBackground : public ClassicObserver{
        public:
            /**
             *
             * @param linkedGame jeux lié
             */
            SceneBackground(Game::Core::Game* linkedGame);

            /**
             * dessine la scène
             * @param container délimitation de la zone de dessin
             * @return self
             */
            virtual SceneBackground* drawIn(Rectangle container) noexcept = 0;

            /**
             *
             * @return la configuration de couleur du fond
             */
            virtual YAML::Node getColorConfig() noexcept;

        protected:
            /**
             * charge les couleurs du fond ou défini celle par défaut
             * @return si la configuration à réussi
             */
            virtual bool loadConfig() noexcept = 0;

        protected:
            /**
             * jeux lié
             */
            Game::Core::Game* linkedGame;

            /**
             * congiguration des couleurs
             */
            YAML::Node colorConfig;
    };
}

#endif //Z_WAR_SCENEBACKGROUND_HPP
