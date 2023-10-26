//
// Created by devel on 12/10/2023.
//

#include "TextUtils.hpp"
#include <sstream>

namespace Game::Utils{
    // définition des constantes
    const boost::regex TextUtils::varsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");
    const boost::regex TextUtils::normalizedVarsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");
    const boost::regex TextUtils::functionsMatcher = boost::regex("([A-Za-z][A-Za-z0-9_-]*)\\(([^\\;]+)\\)");

    std::vector<std::string> TextUtils::extractVarsIn(std::string toParse,bool isNormalized) noexcept{
        std::vector<std::string> results{};

        if(!isNormalized) toParse = TextUtils::normalizeVarNamesIn(toParse);

        boost::sregex_iterator iterator(toParse.begin(),toParse.end(),TextUtils::normalizedVarsMatcher);
        boost::sregex_iterator end;

        while(iterator != end){
            auto variableStr = iterator->str();

            results.push_back(variableStr.substr(1,variableStr.length() - 2) );

            iterator++;
        }

        return results;
    }

    std::vector<TextUtils::FunctionData> TextUtils::extractFunctionDatas(std::map<std::string,std::string> variablesMap,std::string toParse,bool keepVariables) noexcept{
        toParse = TextUtils::trim(TextUtils::normalizeVarNamesIn(toParse) );

        std::vector<TextUtils::FunctionData> results{};

        try {
            boost::smatch matches;

            // récupération des fonctions niveau 1
            while(boost::regex_search(toParse,matches,TextUtils::functionsMatcher) ){
                const auto functionName = TextUtils::trim(matches[1].str() );
                const auto paramsListStr = TextUtils::trim(matches[2].str() );

                std::vector<ParamsType> paramsDatas{};

                // traitement des paramètres
                    auto params = TextUtils::split(paramsListStr,',');

                    for(auto paramStr : params){
                        ParamsType paramType;

                        if(boost::regex_match(paramStr.begin(),paramStr.end(),TextUtils::functionsMatcher) ){
                            // alors type fonction
                            paramType.data = TextUtils::extractFunctionDatas(variablesMap,paramStr,keepVariables).front();
                            paramType.type = ParamsType::FUNCTION;
                        }
                        else if(boost::regex_search(paramStr.begin(),paramStr.end(),TextUtils::varsMatcher) ){
                            // alors contient une ou des variable
                            paramType.data = !keepVariables ? TextUtils::replaceVars(paramStr,variablesMap) : paramStr;
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

    std::string TextUtils::replaceVars(std::string str,std::map<std::string,std::string> variablesMap) noexcept{
        const auto variablesList = TextUtils::extractVarsIn(str,true);

        for(auto& variableName : variablesList){
            if(!variablesMap.contains(variableName) ) continue;

            str = TextUtils::replaceString(str,"{" + variableName + "}",variablesMap.find(variableName)->second);
        }

        return str;
    }

    std::string TextUtils::normalizeVarNamesIn(std::string toParse){
        TraceLog(LOG_INFO,"Normalisation des variables");

        boost::smatch matches;

        std::string subStr = toParse;

        size_t index = 0;

        while(boost::regex_search(subStr,matches,TextUtils::varsMatcher) ){
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

    std::string TextUtils::replaceString(std::string str,std::string search,std::string replaceString) noexcept{
        TraceLog(LOG_INFO,"Remplacement de chaine");

        const auto toReplaceLen = search.length();
        const auto replaceLen = replaceString.length();

        size_t index = 0;

        while((index = str.find(search,index) ) != std::string::npos){
            str.replace(index,toReplaceLen,replaceString);
            index += replaceLen;
        }

        return str;
    }

    std::string TextUtils::trim(std::string str) noexcept{
        str.erase(0,str.find_first_not_of(' ') );
        str.erase(str.find_last_not_of(' ') + 1);

        return str;
    }

    std::string TextUtils::changeCase(std::string str,bool lower) noexcept{
        const auto toApply = lower ? ::tolower : ::toupper;

        std::transform(str.begin(),str.end(),str.begin(),toApply);

        return str;
    }

    std::vector<std::string> TextUtils::split(std::string toSplit,char delimiter) noexcept{
        std::stringstream stream(toSplit);
        std::string part;

        std::vector<std::string> results{};

        while(std::getline(stream,part,delimiter) ) results.push_back(part);

        return results;
    }
}