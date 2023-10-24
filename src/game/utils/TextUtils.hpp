//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_TEXTUTILS_HPP
#define Z_WAR_TEXTUTILS_HPP

#include "raylib.h"
#include "boost/regex.hpp"
#include <vector>
#include <string>
#include <any>
#include <map>

namespace Game::Utils{
    /**
     * utilitaire de texte
     */
    class TextUtils{
        public:
        /**
         * type de paramètres
         */
            typedef struct ParamsType{
                public:
                    typedef enum ParamSpecificType{
                        /**
                         * nom d'une variable comme donnée
                         */
                        VARIABLE = 1,

                        /**
                         * type c++
                         */
                        STATIC_TYPE,

                        /**
                         * une fonction a appellé
                         */
                        FUNCTION
                    }ParamSpecificType;

                    /**
                     * donnée du paramètre
                     */
                    std::any data;

                    /**
                     * type de la donnée
                     */
                    ParamSpecificType type;
            }ParamsType;

        /**
         * type définissant les données d'une fonction
         */
            typedef std::pair<std::string,std::vector<ParamsType> > FunctionData;

        public:
            /**
             * cherche les variables dans une chaine
             * @param toParse la chaine à parsé
             * @param isNormalized si la chaine est normalisé sinon elle sera normalisé pour les besoins de la fonction
             * @return la liste des variables contenu dans la chaine
             */
            static std::vector<std::string> extractVarsIn(std::string toParse,bool isNormalized = false) noexcept;

            /**
             * traite une chaine contenant une ou plusieurs fonctions
             * @param variablesMap map des variables , key nom de la variable , value valeur de la variable
             * @param toParse la chaine à traiter
             * @param keepVariables si false alors les variables sont remplacés par leurs valeurs dans le traitement (sauf si nullptr est associé comme valeur à la variable) sinon si true alors les variables sont conservés par nom
             * @return les données de fonctions
             */
            static std::vector<FunctionData> extractFunctionDatas(std::map<std::string,std::any> variablesMap,std::string toParse,bool keepVariables = false) noexcept;

            /**
             * normalise le nom des variables au format
             * suppression d'espace début et fin
             * upperstring
             * @param toParse la chaine à parsé
             * @return la chaine normalisé
             */
            static std::string normalizeVarNamesIn(std::string toParse);

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

        public:
            /**
             * regex permettant de matcher les variables
             */
            static const boost::regex varsMatcher;

            /**
             * regex permettant de matcher les variables déjà normalisés
             */
            static const boost::regex normalizedVarsMatcher;
    };
}

#endif //Z_WAR_TEXTUTILS_HPP
