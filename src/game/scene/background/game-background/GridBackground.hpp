//
// Created by devel on 10/10/2023.
//

#ifndef Z_WAR_GRIDBACKGROUND_HPP
#define Z_WAR_GRIDBACKGROUND_HPP

#include "../background/SceneBackground.hpp"

using namespace Game::Scene::Background::Background;

namespace Game::Scene::Background::GameBackground{

    /**
     * fond de scène en mode grille
     */
    class GridBackground : public SceneBackground{
        public:
            SceneBackground* drawIn(Rectangle container) noexcept override;
    };
}



#endif //Z_WAR_GRIDBACKGROUND_HPP
