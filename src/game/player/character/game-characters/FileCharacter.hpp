//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_FILECHARACTER_HPP
#define Z_WAR_FILECHARACTER_HPP

#include "../character/Character.hpp"

using namespace Game::Player::Character::Character;

namespace Game::Player::Character::GameCharacters {

    /**
     * personnage classique chargé à partir d'un fichier
     */
    class FileCharacter : public Character::Character{
        public:
            /**
             *
             * @param linkedGame jeux lié
             * @param characterDirname nom du dossier du personnage
             */
            explicit FileCharacter(Core::Game* linkedGame,const char* characterDirname);

            /**
             * charge la configuration personnage à partir d'un fichier yaml au chemin donné
             * @param path chemin du fichier joueur dans les ressources
             * @return si le chargement a réussi
             */
            bool loadFromFile(const char* path) noexcept;

            /**
             * charge la configuration personnage à partir d'un contenu de fichier yaml
             * @param fileCcontent contenu du fichier
             * @return si le chargement a réussi
             */
            bool loadFromContent(const char* fileContent) noexcept;

            bool loadAnimationDatas() noexcept override;

        private:
            /**
             * nom du dossier du personnage
             */
            const char* characterDirname;
    };
}

#endif //Z_WAR_FILECHARACTER_HPP
