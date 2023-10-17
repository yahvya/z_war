//
// Created by devel on 12/10/2023.
//

#include "CharacterSwitcherAnimation.hpp"

namespace Game::Scene::Components::Animation{
    CharacterSwitcherAnimation::CharacterSwitcherAnimation(std::vector<Character*> characters) noexcept {
        // chargement des données d'animation
        std::for_each(characters.begin(),characters.end(),[this](auto character){
            if(character->loadAnimationDatas() ) this->characters.push_back(character);
        });

        this->characters = characters;
    }

    Animation* CharacterSwitcherAnimation::animate(int speed) noexcept{
        

        return this;
    }

    CharacterSwitcherAnimation* CharacterSwitcherAnimation::setCharacters(std::vector<Character*> newCharacters) noexcept{
        this->characters = newCharacters;

        return this;
    }
}