//
// Created by devel on 12/10/2023.
//

#include "TextUtils.hpp"
#include <sstream>
#include <algorithm>

namespace Game::Utils{
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