//
// Created by devel on 12/10/2023.
//

#include "FileCharacter.hpp"

namespace Game::Player::Character::GameCharacters {
    FileCharacter::FileCharacter(Core::Game *linkedGame,const char* characterDirname) : Character::Character(linkedGame),characterDirname(characterDirname) {}

    bool FileCharacter::loadFromFile(const char* path) noexcept{
        try{
            auto configFileContent = YAML::LoadFile(path);

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool FileCharacter::loadFromContent(const char* fileContent) noexcept{
        try{
            auto configFileContent = YAML::Load(fileContent);

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool FileCharacter::loadAnimationDatas() noexcept{


        return true;
    }
}
