//
// Created by devel on 12/10/2023.
//

#include "TextUtils.hpp"

#include <iostream>
namespace Game::Utils{
    // définition des constantes
    const boost::regex TextUtils::varsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");
    const boost::regex TextUtils::normalizedVarsMatcher = boost::regex("\\{([^\\{\\}]+)\\}");

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

    std::vector<TextUtils::FunctionData> TextUtils::extractFunctionDatas(std::map<std::string,std::any> variablesMap,std::string toParse,bool keepVariables) noexcept{
        std::vector<TextUtils::FunctionData> results{};

        return results;
    }

    std::string TextUtils::normalizeVarNamesIn(std::string toParse){
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
}