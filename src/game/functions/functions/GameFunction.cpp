//
// Created by devel on 28/10/2023.
//

#include "GameFunction.hpp"
#include "../../utils/TextUtils.hpp"
#include "../game-functions/SimpleFunctions.hpp"

using namespace Game::Utils;

#include <iostream>
namespace Game::Functions::Functions {
    // définition des constantes
    const boost::regex GameFunction::varsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");
    const boost::regex GameFunction::normalizedVarsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");
    const boost::regex GameFunction::functionsMatcher = boost::regex("([A-Za-z][A-Za-z0-9_-]*)\\(([^\\;]+)\\)");

    // définition de la liste des fonctions
    std::map<std::string,GameFunction::FunctionMarker> GameFunction::gameFunctionsMap{};

    std::map<std::string,std::string> GameFunction::functionsNameMap{};

    std::vector<std::string> GameFunction::extractVarsIn(std::string toParse,bool isNormalized) noexcept{
        std::vector<std::string> results{};

        if(!isNormalized) toParse = GameFunction::normalizeVarNamesIn(toParse);

        // recherche des variables
            boost::sregex_iterator iterator(toParse.begin(),toParse.end(),GameFunction::normalizedVarsMatcher);
            boost::sregex_iterator end;

            while(iterator != end){
                auto variableStr = iterator->str();

                results.push_back(variableStr.substr(1,variableStr.length() - 2) );

                iterator++;
            }

        return results;
    }

    std::vector<GameFunction::FunctionData> GameFunction::extractFunctionDatas(std::map<std::string,std::string> variablesMap,std::string toParse,bool keepVariables) noexcept{
        toParse = TextUtils::trim(GameFunction::normalizeVarNamesIn(toParse) );

        std::vector<GameFunction::FunctionData> results{};

        try {
            boost::smatch matches;

            // récupération des fonctions niveau 1
                while(boost::regex_search(toParse,matches,GameFunction::functionsMatcher) ){
                    const auto functionName = TextUtils::trim(matches[1].str() );
                    const auto paramsListStr = TextUtils::trim(matches[2].str() );

                    std::vector<ParamsType> paramsDatas{};

                    // traitement des paramètres
                        auto params = TextUtils::split(paramsListStr,',');

                        for(auto paramStr : params){
                            ParamsType paramType;

                            if(boost::regex_match(paramStr.begin(),paramStr.end(),GameFunction::functionsMatcher) ){
                                // alors type fonction
                                paramType.data = GameFunction::extractFunctionDatas(variablesMap,paramStr,keepVariables).front();
                                paramType.type = ParamsType::FUNCTION;
                            }
                            else if(boost::regex_search(paramStr.begin(),paramStr.end(),GameFunction::varsMatcher) ){
                                // alors contient une ou des variable
                                paramType.data = !keepVariables ? GameFunction::replaceVars(paramStr,variablesMap) : paramStr;
                                paramType.type = ParamsType::VARIABLE_IN;
                            }
                            else{
                                // alors
                                paramType.data = paramStr;
                                paramType.type = ParamsType::STATIC_TYPE;
                            }

                            paramsDatas.push_back(paramType);
                        }

                        toParse = matches.suffix().str();

                        results.push_back({functionName,paramsDatas});
                }
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec d'extraction des données de fonction");
            TraceLog(LOG_ERROR,e.what());
        }

        return results;
    }

    std::string GameFunction::replaceVars(std::string str,std::map<std::string,std::string> variablesMap) noexcept{
        const auto variablesList = GameFunction::extractVarsIn(str,true);

        for(auto& variableName : variablesList){
            if(!variablesMap.contains(variableName) ) continue;

            str = TextUtils::replaceString(str,"{" + variableName + "}",variablesMap.find(variableName)->second);
        }

        return str;
    }

    std::string GameFunction::normalizeVarNamesIn(std::string toParse){
        TraceLog(LOG_INFO,"Normalisation des variables");

        boost::smatch matches;

        std::string subStr = toParse;

        size_t index = 0;

        while(boost::regex_search(subStr,matches,GameFunction::varsMatcher) ){
            auto varStr = matches[0].str();
            auto varName = matches[1].str();

            // normalisation du nom
                varName = TextUtils::changeCase(TextUtils::trim(varName),false);

            // remplacement par le nom normalisé
                auto pos = subStr.find(varStr);
                index += pos;

                toParse.replace(index,varStr.length(),"{" + varName + "}");

                index += varName.length() + 2;

                subStr = toParse.substr(index);
        }

        return toParse;
    }

    GameFunction::GameFunctionReturnType GameFunction::execFunction(FunctionData toExec,FunctionRequiredGlobalData* globalDatas,std::vector<FunctionData>* nextFunctions){
        auto [functionName,params] = toExec;

        // recherche du nom réel de la fonction
        std::string functionRealName;

        for(auto [userFunctionName,realName] : GameFunction::functionsNameMap){
            if(functionName == userFunctionName){
                functionRealName = realName;
                break;
            }
        }

        if(functionRealName.empty() || !GameFunction::gameFunctionsMap.contains(functionRealName) ) throw std::runtime_error("Fonction non trouvé");

        return  GameFunction::gameFunctionsMap.find(functionRealName)->second(toExec,globalDatas,nextFunctions);
    }

    bool GameFunction::execFunctionsList(std::vector<FunctionData> functions,FunctionRequiredGlobalData* globalDatas) noexcept{
        // exécution des fonctions si une exception est envoyé alors échec de la fonction
        while(!functions.empty() ){
            try{
                FunctionData toExec = functions.begin()[0];

                functions.erase(functions.begin() );

                GameFunction::execFunction(toExec,globalDatas,&functions);
            }
            catch(std::exception& e){
                TraceLog(LOG_ERROR,"Echec d'exécution de fonction");
                TraceLog(LOG_ERROR,e.what() );

                return false;
            }
        }

        return true;
    }

    bool GameFunction::config(ResourcesManager* manager) noexcept{
        TraceLog(LOG_INFO,"Chargement de la configuration de nommage des fonctions");

        try{
            // chargement du mapage des noms
            GameFunction::functionsNameMap = YAML::LoadFile(std::string(manager->getGameGlobalResources()->resourcesDirPath) + ResourcesManager::CONFIG_DIR_PATH  + "functions/config.yaml").as<std::map<std::string,std::string> >();

            GameFunction::registerFunctions();

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de la configuration de nommage des fonctions");
            TraceLog(LOG_ERROR,e.what() );

            return false;
        }
    }

    void GameFunction::registerFunctions(){
        /**
         * @attention pour chaque fonction ajoutée , vérifier qu'elle n'existe pas dans la liste et ajouter son nom dans liste doc
         * @attention pour chaque fonction ajoutée, vérifier que son type de retour existe dans GameFunctionReturnType
         * listes des fonctions\n
         * @attention une fonction qui renvoi une exception est considéré comme ayant échoué
         */

        // contient les fonctions []
        GameFunctions::SimpleFunctions::registerFunctions();
    }
}