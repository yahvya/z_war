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
            explicit FileCharacter(Core::Game* linkedGame,const std::string characterDirname);

            bool loadAnimationDatas() noexcept override;

            /**
             * charge partiellement les données du fichier
             * @param filePath chemin du fichier
             * @param pathList liste des clés à récupéré au format (clé.sous-clé...) ou (clé.* pour récupéré tout le contenu de l'objet)
             * @param exceptOnKeyNotFound envoyé une exception si une clé n'est pas trouvé , default true
             * @return les données récupéré indicés par les clés fournies
             */
            static YAML::Node partialLoadFrom(const char* filePath,std::vector<const char*> pathList,bool exceptOnKeyNotFound = true);

            /**
             * charge partiellement les données du fichier
             * @param datas données du fichier
             * @param pathList liste des clés à récupéré au format (clé.sous-clé...) ou (clé.* pour récupéré tout le contenu de l'objet)
             * @param exceptOnKeyNotFound envoyé une exception si une clé n'est pas trouvé , default true
             * @return les données récupéré indicés par les clés fournies
             */
            static YAML::Node partialLoadFrom(YAML::Node datas,std::vector<const char*> pathList,bool exceptOnKeyNotFound = true);

        private:
            /**
             * nom du dossier du personnage
             */
            const char* characterDirname;
    };
}

#endif //Z_WAR_FILECHARACTER_HPP
