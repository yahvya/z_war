//
// Created by devel on 12/10/2023.
//

#include "Character.hpp"
#include "yaml-cpp/yaml.h"

namespace Game::Player::Character::Character{
    Character::Character(Core::Game *linkedGame) noexcept : linkedGame(linkedGame) {}

    Character::CharacterDatas Character::getDatas() noexcept{
        return this->characterDatas;
    }

    bool Character::loadFromFile(const char* path) noexcept{
        try{
            auto configFileContent = YAML::LoadFile(path);

            return Character::loadFromNode(configFileContent);
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool Character::loadFromContent(const char* fileContent) noexcept{
        try{
            auto configFileContent = YAML::Load(fileContent);

            return Character::loadFromNode(configFileContent);
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool Character::loadFromNode(YAML::Node characterDatas) noexcept{
        // récupération des informations du personnage
        TraceLog(LOG_INFO,characterDatas["name"].as<std::string>().c_str());

        return false;
    }
}

