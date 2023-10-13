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
            typedef struct CharacterDatas{
                public:
                    /**
                     * nom du personnage
                     */
                    const char* name;

                    /**
                     * si les données sont chargés
                     */
                    bool isLoaded;

                    CharacterDatas() noexcept : isLoaded(false)  {};
            }CharacterDatas;

        public:
            /**
             *
             * @param linkedGame le jeux lié
             */
            explicit Character(Core::Game* linkedGame) noexcept;

            /**
             * charge les données du joueur
             * @return si le chargement à réussi
             */
            virtual bool loadCharacterDatas() noexcept = 0;

            /**
             *
             * @return les données du personnage
             */
            CharacterDatas getDatas() noexcept;

        protected:
            /**
             * charge la configuration personnage à partir d'un fichier yaml au chemin donné
             * @param path chemin du fichier joueur dans les ressources
             * @return si le chargement a réussi
             */
             virtual bool loadFromFile(const char* path) noexcept;

             /**
              * charge la configuration personnage à partir d'un contenu de fichier yaml
              * @param fileCcontent contenu du fichier
              * @return si le chargement a réussi
              */
             virtual bool loadFromContent(const char* fileContent) noexcept;

             /**
              * charge la configuration personnage à partir d'un node yaml
              * @param characterDatas données yaml dans le node
              * @attention utilisé par les autres fonction de chargement
              * @return si le chargement a réussi
              */
             virtual bool loadFromNode(YAML::Node characterDatas) noexcept;

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
