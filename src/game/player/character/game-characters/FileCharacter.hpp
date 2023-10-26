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
             * @param characterDirname chemin du dossier du personnage
             */
            explicit FileCharacter(Core::Game* linkedGame,std::string dirPath);

            bool loadAnimationDatas() noexcept override;

            /**
             * gère les variables pouvant être géré au chargement de l'action
             * @param action l'action à gérer
             * @return si l'action réussi
             */
            bool manageActionVars(CharacterAction* action) noexcept;

            /**
             * charge le formulaire donnée
             * @param formName nom de la forme
             * @param formConfigFilePath chemin de configuration du formulaire à charger
             * @return si le chargement réussi
             */
            bool loadForm(std::string formName,std::string formConfigFilePath) noexcept;

            /**
             * charge partiellement les données du fichier
             * @param filePath chemin du fichier
             * @param pathList liste des clés à récupéré au format (clé.sous-clé...) ou (clé.* pour récupéré tout le contenu de l'objet)
             * @param exceptOnKeyNotFound envoyé une exception si une clé n'est pas trouvé , default true
             * @return les données récupéré indicés par les clés fournies
             */
            static YAML::Node partialLoadFrom(std::string filePath,std::vector<std::string> pathList,bool exceptOnKeyNotFound = true);

            /**
             * charge partiellement les données du fichier
             * @param datas données du fichier
             * @param pathList liste des clés à récupéré au format (clé.sous-clé...) ou (clé.* pour récupéré tout le contenu de l'objet)
             * @param exceptOnKeyNotFound envoyé une exception si une clé n'est pas trouvé , default true
             * @return les données récupéré indicés par les clés fournies
             */
            static YAML::Node partialLoadFrom(YAML::Node datas,std::vector<std::string> pathList,bool exceptOnKeyNotFound = true);

        private:
            /**
             * chemin du dossier du personnage
             */
            std::string dirPath;
    };
}

#endif //Z_WAR_FILECHARACTER_HPP
