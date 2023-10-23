//
// Created by devel on 12/10/2023.
//

#include "TextUtils.hpp"
#include <regex>

#include <iostream>
namespace Game::Utils{
    std::vector<std::string> TextUtils::extractVarsIn(std::string toParse){
        std::vector<std::string> results{};

        return results;
    }

    std::vector<TextUtils::FunctionData> TextUtils::extractFunctionDatas(std::map<std::string,std::any> variablesMap,std::string toParse,bool keepVariables){
        std::vector<TextUtils::FunctionData> results{};

        return results;
    }

    std::string TextUtils::normalizeVarNamesIn(std::string toParse){
        std::regex regex("");
        std::smatch matches;

        std::regex_match(toParse,matches,regex);

        for(auto c : matches){
            std::cout << c << std::endl;
        }

        return toParse;
    }
}