//
// Created by devel on 12/10/2023.
//

#include "Character.hpp"
#include "yaml-cpp/yaml.h"

namespace Game::Player::Character::Character{
    Character::Character(Core::Game *linkedGame) noexcept : linkedGame(linkedGame),characterDatas(new CharacterDatas() ) {}

    CharacterDatas* Character::getDatas() noexcept{
        return this->characterDatas;
    }
}

