//
// Created by devel on 28/10/2023.
//

#ifndef Z_WAR_GAMEFUNCTION_HPP
#define Z_WAR_GAMEFUNCTION_HPP

#include <vector>
#include <variant>
#include <map>
#include <string>
#include "boost/regex.hpp"

namespace Game::Functions::Functions{
    /**
     * gestions des fonctions de l'application
     */
    class GameFunction{
        public:
            /**
             * type de paramètres
             */
            typedef struct ParamsType{
                public:
                    typedef enum ParamSpecificType{
                        /**
                         * chaine contenant le nom de variable au format normalisé + d'autres élements si keepVariables vaux true sinon chaine contenant des variables remplacés si elles existaient
                         */
                        VARIABLE_IN = 1,

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
                     * données du paramètre
                     */
                    std::variant<std::string,std::pair<std::string,std::vector<ParamsType> > > data;

                    /**
                     * type de données contenu
                     * std::string ou FunctionData
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
             * @attention si une variable trouvé n'existe pas dans la liste fournie alors elle reste sous forme de variable
             * @attention si plusieurs fonctions fournies alors séparé avec ;
             * @param variablesMap map des variables , key nom de la variable , value valeur de la variable, peut être vide si keepVariables = true
             * @param toParse la chaine à traiter
             * @param keepVariables si false alors les variables sont remplacés par leurs valeurs dans le traitement (sauf si nullptr est associé comme valeur à la variable) sinon si true alors les variables sont conservés par nom
             * @return les données de fonctions
             */
            static std::vector<FunctionData> extractFunctionDatas(std::map<std::string,std::string> variablesMap,std::string toParse,bool keepVariables = false) noexcept;

            /**
             * normalise le nom des variables au format
             * suppression d'espace début et fin
             * upperstring
             * @param toParse la chaine à parsé
             * @return la chaine normalisé
             */
            static std::string normalizeVarNamesIn(std::string toParse);

            /**
    * remplace les variables dans la chaine par la valeur donnée
    * @param str la chaine à parser (chaine normalisé attendue)
    * @param variablesMap la map des variables key nom de la variable value valeur de la variable si nullptr comme value ou variable non trouvé variable laissé dans la chaine
    * @return la chaine modifié
    */
            static std::string replaceVars(std::string str,std::map<std::string,std::string> variablesMap) noexcept;

        public:
            /**
             * regex permettant de matcher les variables
             */
            static const boost::regex varsMatcher;

            /**
             * regex permettant de matcher les variables déjà normalisés
             */
            static const boost::regex normalizedVarsMatcher;

            /**
             * regex permettant de matcher les fonctions
             */
            static const boost::regex functionsMatcher;
    };
}

#endif //Z_WAR_GAMEFUNCTION_HPP
