//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_CHARACTER_HPP
#define Z_WAR_CHARACTER_HPP

#include "../../../core/Game.hpp"

using namespace Game::Core;

namespace Game::Player::Character::Character{
    /**
     * personnage du jeux
     */
    class Character{
        public:
            /**
             * données globales d'un personnage du jeux
             */
            typedef struct{
                public:
                    /**
                     * nom du personnage
                     */
                    const char* name;
            }CharacterDatas;

        public:
            /**
             *
             * @param linkedGame le jeux lié
             */
            explicit Character(Core::Game* linkedGame) noexcept;

            /**
             *
             * @return les données du personnage
             */
            CharacterDatas getDatas() noexcept;

            /**
             * charge les données pour l'animation
             * @return si le chargement à bien réussi
             */
            virtual bool loadAnimationDatas() noexcept = 0;

        protected:
            /**
             * données globales du personnage
             */
            CharacterDatas characterDatas;

            /**
             * jeux lié
             */
            Core::Game* linkedGame;
    };
}

#endif //Z_WAR_CHARACTER_HPP
