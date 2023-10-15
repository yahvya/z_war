//
// Created by devel on 12/10/2023.
//

#include "FileCharacter.hpp"

namespace Game::Player::Character::GameCharacters {
    FileCharacter::FileCharacter(Core::Game *linkedGame,const char* characterDirname) : Character::Character(linkedGame),characterDirname(characterDirname) {}

    bool FileCharacter::loadCharacterDatas() noexcept{
        return this->loadFromFile((std::string(this->characterDirname) + "/config.yaml").c_str() );
    }
}