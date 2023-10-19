//
// Created by devel on 12/10/2023.
//

#include <cstring>
#include <filesystem>
#include "FileCharacter.hpp"

#include <iostream>
namespace Game::Player::Character::GameCharacters {
    FileCharacter::FileCharacter(Core::Game *linkedGame,std::string characterDirname) : Character::Character(linkedGame),characterDirname( characterDirname) {}

    bool FileCharacter::loadForm(std::string formName,std::string formConfigFilePath) noexcept{
        TraceLog(LOG_INFO,"Chargement d'une forme");

        if(this->characterDatas->getCharacterFormIsLoaded(formName) ) return true;

        try{
            // récupération des données du formulaire
                auto formConfigFileContent = YAML::LoadFile(this->characterDirname + formConfigFilePath);

                auto formData = new CharacterFormData();

                // récupération des images du personnages
                    if(!formConfigFileContent["images"]) throw std::runtime_error("Les images de la forme sont manquantes dans la configuration");

                    formData->imagesMap = formConfigFileContent["images"].as<std::map<std::string,std::string> >();

//                    for(auto imageData : formData->imagesMap) if(!FileExists(imageData.second.c_str() ) ) throw std::runtime_error("Une des images fournis n'existe pas");

                // récupération du nom du personnage
                    if(!formConfigFileContent["name"]) throw std::runtime_error("Le nom du personnage est manquant dans la configuration");

                    formData->characterName = formConfigFileContent["name"].as<std::string>();

                // récupération de l'énergie requise pour la forme
                    if(!formConfigFileContent["energy"]) throw std::runtime_error("L'énergie requise pour charger la forme est manquant dans la configuration");

                    formData->requiredEnergy = formConfigFileContent["energy"].as<float>();

                // récupération de la durée de la forme
                    if(!formConfigFileContent["duration"]) throw std::runtime_error("La durée de la forme est manquant dans la configuration");
                    // en attente de récupération de variable
                    formData->duration = 10;

                // récupération de la formule de calcul combo
                    if(!formConfigFileContent["combo-gain-formula"]) throw std::runtime_error("La formule de calcul du combo manque dans la configuration");

                    formData->comboGainFormula = formConfigFileContent["combo-gain-formula"].as<std::string>();

                // récupération des points de vie de base du bouclier
                    if(!formConfigFileContent["shield-points"]) throw std::runtime_error("Les points de vie du bouclier sont manquant dans la configuration");

                    formData->shieldPoints = formConfigFileContent["shield-points"].as<float>();

                // récupération des images de la séquence bouclier
                    if(!formConfigFileContent["shield-images"]) throw std::runtime_error("La liste des clés d'images décrivant le bouclier mis manque dans la configuration");

                    formData->shieldImagesList = formConfigFileContent["shield-images"].as<std::vector<std::string> >();

                    for(auto& key : formData->shieldImagesList) if(!formData->imagesMap.contains(key) ) throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence bouclier");

                // récupération des images de la séquence tomber
                    if(!formConfigFileContent["fell-images"]) throw std::runtime_error("La liste des clés d'images décrivant la chute manque dans la configuration");

                    formData->fellImagesList = formConfigFileContent["fell-images"].as<std::vector<std::string> >();

                    for(auto& key : formData->fellImagesList) if(!formData->imagesMap.contains(key) ) throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence chute");

                // récupération de la vitesse d'attaque
                    if(!formConfigFileContent["attack-speed"]) throw std::runtime_error("La vitesse d'attaque du personnage manque dans la configuration");

                    formData->attackSpeed = formConfigFileContent["attack-speed"].as<float>();

                // récupération des images de la séquence relever
                    if(!formConfigFileContent["get-up-images"]) throw std::runtime_error("La liste des clés d'images décrivant se relever manque dans la configuration");

                    formData->getUpImagesList = formConfigFileContent["get-up-images"].as<std::vector<std::string> >();

                    for(auto& key : formData->getUpImagesList) if(!formData->imagesMap.contains(key) ) throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence chute");

                // récupération des actions
//                    formData->actionsMap["test"] = new CharacterAction();
//                    formData->actionsMap["test"]->actionDescription = "t'et";
//                    formData->actionsMap["test"]->actionName = "encore";
//                    formData->actionsMap["test"]->actionDescriptionFilePath = "beinbe";

            this->characterDatas->characterFormsMap[formName] = formData;

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de la forme");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool FileCharacter::loadAnimationDatas() noexcept{
        TraceLog(LOG_INFO,"Chargement des données d'animation du personnage");

        try{
            if(this->characterDatas->getPresentationAnimationDataIsLoaded()) return true;

            // chargement des données requises à l'animation du personnage
                std::vector<std::string> keysToLoad{
                    "presentation-animation.form",
                    "presentation-animation.required-actions",
                    "presentation-animation.animation"
                };

                // ajout des clés requises à charger si non chargé
                    if(!this->characterDatas->getControllersAreLoaded() ) keysToLoad.push_back("controllers");
                    if(!this->characterDatas->getCharacterFormsAreLoaded() ) keysToLoad.push_back("forms");

                auto configDatas = FileCharacter::partialLoadFrom(
                    this->characterDirname + "/config/config.yaml",
                    keysToLoad
                );

                // chargement des données non chargés
                    if(!this->characterDatas->getControllersAreLoaded() ) this->characterDatas->controllers = std::vector<std::string>();

                    auto controllersList = configDatas["controllers"].as<std::vector<std::string> >();

                    for(auto controllerName : controllersList) this->characterDatas->controllers.push_back(controllerName);

                // remplissage de l'animation
                this->characterDatas->presentationAnimationData = new PresentationAnimationData();

                // recherche du formulaire à charger et chargement
                    auto formName = configDatas["presentation-animation.form"].as<std::string>();

                    if(!this->characterDatas->getCharacterFormIsLoaded(formName) ){
                        std::string formConfigFilePath;

                        auto formList = configDatas["forms"].as<std::vector<YAML::Node> >();

                        for(auto form : formList){
                            if(form["name"] && std::strcmp(form["name"].as<std::string>().c_str(),formName.c_str() ) == 0 && form["path"]){
                                formConfigFilePath = form["path"].as<std::string>();

                                break;
                            }
                        }

                    if(formConfigFilePath.empty() || !this->loadForm(formName,formConfigFilePath) ) return false;
                }

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des données d'animation du personnage");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    YAML::Node FileCharacter::partialLoadFrom(std::string filePath,std::vector<std::string> pathList,bool exceptOnKeyNotFound){
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

    YAML::Node FileCharacter::partialLoadFrom(YAML::Node datas,std::vector<std::string> pathList,bool exceptOnKeyNotFound){
        try{
            TraceLog(LOG_INFO,"Chargement de données partielles à partir des données yaml");

            YAML::Node resultNode;

            // chargement des données
            for(auto path : pathList){
                if(path.empty() ) throw std::runtime_error("Un chemin de clé est attendu");

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
            }

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
