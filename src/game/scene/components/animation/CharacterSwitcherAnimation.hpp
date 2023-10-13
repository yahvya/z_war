//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_CHARACTERSWITCHERANIMATION_HPP
#define Z_WAR_CHARACTERSWITCHERANIMATION_HPP

#include "Animation.hpp"
#include "../../../player/character/character/Character.hpp"

using namespace Game::Player::Character::Character;

namespace Game::Scene::Components::Animation{
    /**
     * animation d'affichage et de changement des personnages
     */
    class CharacterSwitcherAnimation : public Animation::Animation{
        public:
            CharacterSwitcherAnimation(std::vector<Character *> characters) noexcept;

            /**
             * remplace les personnages affichés
             * @param newCharacters liste des personnages de l'animation
             * @return self
             */
            CharacterSwitcherAnimation* setCharacters(std::vector<Character*> newCharacters) noexcept;

            Animation* animate(int speed) noexcept override;
        private:
            /**
             * liste des personnages
             */
            std::vector<Character*> characters;
    };
}

#endif //Z_WAR_CHARACTERSWITCHERANIMATION_HPP
