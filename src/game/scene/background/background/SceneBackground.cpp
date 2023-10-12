//
// Created by devel on 10/10/2023.
//

#include "SceneBackground.hpp"

namespace Game::Scene::Background::Background{
    SceneBackground::SceneBackground(Game::Core::Game* linkedGame) : linkedGame(linkedGame) {}

    YAML::Node SceneBackground::getColorConfig() noexcept{
        return this->colorConfig;
    }
}