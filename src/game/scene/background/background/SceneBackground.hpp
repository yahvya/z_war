//
// Created by devel on 10/10/2023.
//

#ifndef Z_WAR_SCENEBACKGROUND_HPP
#define Z_WAR_SCENEBACKGROUND_HPP

#include "raylib.h"
#include "../../../pattern/observer/ClassicObserver.hpp"

using namespace Game::Pattern::Observer;

namespace Game::Scene::Background::Background{
    /**
     * représente le fond d'une scène
     */
    class SceneBackground : public ClassicObserver{
    public:
        /**
         * dessine la scène
         * @param container délimitation de la zone de dessin
         * @return self
         */
        virtual SceneBackground* drawIn(Rectangle container) noexcept = 0;
    };
}

#endif //Z_WAR_SCENEBACKGROUND_HPP
