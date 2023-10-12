//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_CHARACTERSWITCHERANIMATION_HPP
#define Z_WAR_CHARACTERSWITCHERANIMATION_HPP

#include "Animation.hpp"
#include "../../../player/character/Character.hpp"
#include <array>

using namespace Game::Player::Character;

namespace Game::Scene::Components::Animation{
    /**
     * animation d'affichage et de changement des personnages
     */
    class CharacterSwitcherAnimation : public Animation::Animation{
        public:
            /**
             *
             * @param switchTime temps d'animation entre chaque passage
             */
            CharacterSwitcherAnimation(int switchTime);

            Animation* animate() noexcept override;
        private:
            /**
             * liste des personnages à afficher à la suite
             */

            /**
             * temps d'animation entre chaque
             */
            int switchTime;
    };
}

#endif //Z_WAR_CHARACTERSWITCHERANIMATION_HPP
