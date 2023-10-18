//
// Created by devel on 12/10/2023.
//

#include <cstring>
#include "FileCharacter.hpp"

#include <iostream>
namespace Game::Player::Character::GameCharacters {
    FileCharacter::FileCharacter(Core::Game *linkedGame,const std::string characterDirname) : Character::Character(linkedGame),characterDirname(characterDirname.c_str() ) {}

    bool FileCharacter::loadAnimationDatas() noexcept{
        TraceLog(LOG_INFO,"Chargement des données d'animation du personnage");

        try{
            if(this->characterDatas->getPresentationAnimationDataIsLoaded()) return true;

            // chargement des données requises à l'animation du personnage
                std::vector<const char*> keysToLoad{
                    "presentation-animation.form",
                    "presentation-animation.required-actions",
                    "presentation-animation.animation"
                };

                // ajout des clés requises à charger si non chargé
                    if(!this->characterDatas->getControllersAreLoaded() ) keysToLoad.push_back("controllers");
                    if(!this->characterDatas->getCharacterFormsAreLoaded() ) keysToLoad.push_back("forms");

                auto configDatas = FileCharacter::partialLoadFrom(
                    (std::string(this->characterDirname) + "/config/config.yaml").c_str(),
                    keysToLoad
                );

                auto presentationAnimationData = new PresentationAnimationData();

                std::cout << "valeur : \n" << configDatas  << std::endl;

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données d'animation du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    YAML::Node FileCharacter::partialLoadFrom(const char* filePath,std::vector<const char*> pathList,bool exceptOnKeyNotFound){
        try{
            TraceLog(LOG_INFO,"Chargement de données partielles à partir du fichier");

            return FileCharacter::partialLoadFrom(YAML::LoadFile(filePath),pathList,exceptOnKeyNotFound);
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de données partielles à partir du fichier");

            if(exceptOnKeyNotFound) throw std::runtime_error(e.what() );

            return {};
        }
    }

    YAML::Node FileCharacter::partialLoadFrom(YAML::Node datas,std::vector<const char*> pathList,bool exceptOnKeyNotFound){
        try{
            TraceLog(LOG_INFO,"Chargement de données partielles à partir des données yaml");

            YAML::Node resultNode;

            // chargement des données
                std::for_each(pathList.begin(),pathList.end(),[&resultNode,datas](auto path){
                    if(std::string(path).empty() ) throw std::runtime_error("Un chemin de clé est attendu");

                    std::stringstream stream(path);
                    std::string pathPart;

                    // copie de l'objet
                    resultNode[path] = datas;

                    while(std::getline(stream,pathPart,'.') ){
                        if(std::strcmp(pathPart.c_str(),"*") != 0){
                            if(!resultNode[path][pathPart]) throw std::runtime_error("Clé non trouvé");

                            resultNode[path] = resultNode[path][pathPart];
                        }
                    }
                });

            return resultNode;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de données partielles à partir des données");
            TraceLog(LOG_ERROR,e.what() );

            if(exceptOnKeyNotFound) throw std::runtime_error(e.what() );

            return {};
        }
    }
}
