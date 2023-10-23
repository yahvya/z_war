//
// Created by devel on 12/10/2023.
//

#ifndef Z_WAR_TEXTUTILS_HPP
#define Z_WAR_TEXTUTILS_HPP

#include "raylib.h"
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
            typedef struct {
                public:
                    enum ParamSpecificType{
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
                    };

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
             * @return la liste des variables contenu dans la chaine
             */
            std::vector<std::string> extractVarsIn(std::string toParse);

            /**
             * traite une chaine contenant une ou plusieurs fonctions
             * @param variablesMap map des variables , key nom de la variable , value valeur de la variable
             * @param toParse la chaine à traiter
             * @param keepVariables si false alors les variables sont remplacés par leurs valeurs dans le traitement (sauf si nullptr est associé comme valeur à la variable) sinon si true alors les variables sont conservés par nom
             * @return les données de fonctions
             */
            std::vector<FunctionData> extractFunctionDatas(std::map<std::string,std::any> variablesMap,std::string toParse,bool keepVariables = false);

            /**
             * normalise le nom des variables au format "{VAR_NAME}"
             * @param toParse la chaine à parsé
             * @return la chaine normalisé
             */
            std::string normalizeVarNamesIn(std::string toParse);
    };
}

#endif //Z_WAR_TEXTUTILS_HPP
