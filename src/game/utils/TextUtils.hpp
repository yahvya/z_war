//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_TEXTUTILS_HPP
#define Z_WAR_TEXTUTILS_HPP

#include <string>
#include <vector>
#include "raylib.h"

namespace Game::Utils{
    /**
     * utilitaire de texte
     */
    class TextUtils{
        public:
            /**
             * remplace les occurences d'une chaine dans une autre
             * @param str la chaine de base
             * @param search la recherche
             * @param replaceString le texte à remplacer
             * @return la chaine rempalcé
             */
            static std::string replaceString(std::string str,std::string search,std::string replaceString) noexcept;

            /**
             * supprime les espaces en début et en fin de chaine
             * @param str la chaine
             * @return la chaine trimé
             */
            static std::string trim(std::string str) noexcept;

            /**
             * transforme la chaine
             * @param str la chaine
             * @param lower si true changement en lowercase sinon uppercase
             * @return la chaine transformé
             */
            static std::string changeCase(std::string str,bool lower) noexcept;

            /**
             * coupe une chaine en plusieurs
             * @param toSplit la chaine à séparer
             * @param delimiter le délimiteur
             * @return la liste des parties de la chaine
             */
            static std::vector<std::string> split(std::string toSplit,char delimiter) noexcept;
    };
}

#endif //Z_WAR_TEXTUTILS_HPP
