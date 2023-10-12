//
// Created by devel on 12/10/2023.
//

#include "CharacterSwitcherAnimation.hpp"

namespace Game::Scene::Components::Animation{
    CharacterSwitcherAnimation::CharacterSwitcherAnimation(int switchTime) : switchTime(switchTime) {}

    Animation* CharacterSwitcherAnimation::animate() noexcept{


        return this;
    }
}