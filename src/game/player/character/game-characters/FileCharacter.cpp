//
// Created by devel on 12/10/2023.
//

#include <cstring>
#include <filesystem>
#include <map>
#include "FileCharacter.hpp"
#include "../../../functions/functions/GameFunction.hpp"

using namespace Game::Functions::Functions;
using namespace Game::Player::Character::Character;

#include <iostream>
namespace Game::Player::Character::GameCharacters {
    FileCharacter::FileCharacter(Core::Game *linkedGame,std::string dirPath) : Character::Character(linkedGame), dirPath(dirPath) {}

    bool FileCharacter::loadForm(std::string formName,std::string formConfigFilePath) noexcept{
        TraceLog(LOG_INFO,"Chargement d'une forme de personnage");

        if(this->characterDatas->getCharacterFormIsLoaded(formName) ) return true;

        try{
            // récupération des données de la forme du personnage
                auto formConfigFileContent = YAML::LoadFile(this->dirPath + formConfigFilePath);

                auto formData = new CharacterFormData();

                // récupération des images du personnages
                    if (!formConfigFileContent["images"])
                        throw std::runtime_error("Les images de la forme sont manquantes dans la configuration");

                    auto imagesConfig = formConfigFileContent["images"].as<std::map<std::string,YAML::Node> >();

                    std::vector<std::string> imagesPath{};

                    // vérification des chemins d'image
                    for (auto imageData: imagesConfig){
                        ImageConfig imageConfig = {
                            .path = imageData.second["path"].as<std::string>(),
                            .width = imageData.second["width"].as<float>(),
                            .height = imageData.second["height"].as<float>()
                        };

                        if (!FileExists((this->dirPath + imageConfig.path).c_str()))
                            throw std::runtime_error("Une des images fournis n'existe pas");

                        formData->imagesMap.insert({imageData.first,imageConfig});
                        imagesPath.push_back(imageConfig.path);
                    }

                // récupération du nom du personnage
                    if (!formConfigFileContent["name"])
                        throw std::runtime_error("Le nom du personnage est manquant dans la configuration");

                    formData->characterName = formConfigFileContent["name"].as<std::string>();

                // récupération de l'énergie requise pour la forme
                    if (!formConfigFileContent["energy"])
                        throw std::runtime_error("L'énergie requise pour charger la forme est manquant dans la configuration");

                    formData->requiredEnergy = formConfigFileContent["energy"].as<float>();

                // récupération de la durée de la forme
                    if (!formConfigFileContent["duration"])
                        throw std::runtime_error("La durée de la forme est manquante dans la configuration");

                    formData->duration = std::stof(GameFunction::replaceVars(
                            GameFunction::normalizeVarNamesIn(formConfigFileContent["duration"].as<std::string>()),
                            DURATION_VAR
                    ));

                // récupération de la formule de calcul combo
                    if (!formConfigFileContent["combo-gain-formula"])
                        throw std::runtime_error("La formule de calcul du combo manque dans la configuration");

                    formData->comboGainFormula = formConfigFileContent["combo-gain-formula"].as<std::string>();

                // récupération des points de vie de base du bouclier
                    if (!formConfigFileContent["shield-points"])
                        throw std::runtime_error("Les points de vie du bouclier sont manquant dans la configuration");

                    formData->shieldPoints = formConfigFileContent["shield-points"].as<float>();

                // récupération des images de la séquence bouclier
                    if (!formConfigFileContent["shield-images"])
                        throw std::runtime_error(
                                "La liste des clés d'images décrivant le bouclier mis manque dans la configuration");

                    formData->shieldImagesList = formConfigFileContent["shield-images"].as<std::vector<std::string> >();

                    for (auto &key: formData->shieldImagesList)
                        if (!formData->imagesMap.contains(key))
                            throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence bouclier");

                // récupération des images de la séquence tomber
                    if (!formConfigFileContent["fell-images"])
                        throw std::runtime_error("La liste des clés d'images décrivant la chute manque dans la configuration");

                    formData->fellImagesList = formConfigFileContent["fell-images"].as<std::vector<std::string> >();

                    for (auto &key: formData->fellImagesList)
                        if (!formData->imagesMap.contains(key))
                            throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence chute");

                // récupération des images de victoire
                    if (!formConfigFileContent["victory-images"])
                        throw std::runtime_error("La liste des clés d'images de victoire manquent dans la configuration");

                    formData->victoryImagesList = formConfigFileContent["victory-images"].as<std::vector<std::vector<std::string> > >();

                    for (auto &imagesList: formData->victoryImagesList) {
                        if (imagesList.empty()) throw std::runtime_error("La liste des images de victoire est vide");

                        for (auto &key: imagesList)
                            if (!formData->imagesMap.contains(key))
                                throw std::runtime_error(
                                        "Une des clés d'images fournis n'existe pas dans la séquence images de victoire");
                    }

                // récupération des images de coup pris à la tête
                    if (!formConfigFileContent["head-hit-images"])
                        throw std::runtime_error("La liste des images de coup pris à la tête manque");

                    formData->headHitImagesList = formConfigFileContent["head-hit-images"].as<std::vector<std::string> >();

                    for (auto &key: formData->headHitImagesList)
                        if (!formData->imagesMap.contains(key))
                            throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence coup pris à la tête");

                // récupération des images de coup pris au corps
                    if (!formConfigFileContent["body-hit-images"])
                        throw std::runtime_error("La liste des images de coup pris au corps manque");

                    formData->bodyHitImagesList = formConfigFileContent["body-hit-images"].as<std::vector<std::string> >();

                    for (auto &key: formData->bodyHitImagesList)
                        if (!formData->imagesMap.contains(key))
                            throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence coup pris au corps");

                // récupération de la vitesse d'attaque
                    if (!formConfigFileContent["attack-speed"])
                        throw std::runtime_error("La vitesse d'attaque du personnage manque dans la configuration");

                    formData->attackSpeed = formConfigFileContent["attack-speed"].as<float>();

                // récupération des images de la séquence relever
                    if (!formConfigFileContent["get-up-images"])
                        throw std::runtime_error("La liste des clés d'images décrivant se relever manque dans la configuration");

                    formData->getUpImagesList = formConfigFileContent["get-up-images"].as<std::vector<std::string> >();

                    for (auto &key: formData->getUpImagesList)
                        if (!formData->imagesMap.contains(key))
                            throw std::runtime_error("Une des clés d'images fournis n'existe pas dans la séquence chute");

                // récupération des actions
                    if (!formConfigFileContent["actions-map"]) throw std::runtime_error("Il manque la map des actions");

                    auto actionsMap = formConfigFileContent["actions-map"].as<std::map<std::string, std::string> >();

                    for (auto &[actionName, configFilePath]: actionsMap) {
                        auto action = new CharacterAction();

                        action->actionName = actionName;
                        action->actionDescriptionFilePath = configFilePath;
                        action->actionDescription = YAML::LoadFile(this->dirPath + action->actionDescriptionFilePath);

                        // traitement des données de l'action
                        if (!this->manageActionVars(action)) throw std::runtime_error("Echec de la gestion de l'action");

                        formData->actionsMap[action->actionName] = action;
                }

            this->characterDatas->characterFormsMap[formName] = formData;

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement de la forme");
            TraceLog(LOG_ERROR,e.what() );
        }

        return false;
    }

    bool FileCharacter::manageActionVars(CharacterAction* action) noexcept{
        TraceLog(LOG_INFO,"Gestion des données d'une action");

        try{


            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de gestion des données d'une action");
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
                        this->dirPath + "/config/config.yaml",
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
