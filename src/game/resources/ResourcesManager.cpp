//
// Created by devel on 07/10/2023.
//

#include <iostream>
#include <string>
#include "ResourcesManager.hpp"
#include "yaml-cpp/yaml.h"
#include<chrono>
namespace Game::Resource {
    // initialisation des constantes statiques
    const char* ResourcesManager::APP_CONFIG_FILE_PATH = "./app.yaml";
    const char* ResourcesManager::FONTS_DIR_PATH = "fonts/";

    ResourcesManager::ResourcesManager() : gameGlobalResources{new GameGlobalResource()} {}

    bool ResourcesManager::loadGlobalResources() noexcept{
        try {
            // chargement du fichier de configuration global app.yaml
            auto fileContent = YAML::LoadFile(ResourcesManager::APP_CONFIG_FILE_PATH);

            // récupération des valeurs de configuration

            this->gameGlobalResources->appName = fileContent["appname"].as<std::string>().c_str();
            this->gameGlobalResources->resourcesDirPath = fileContent["resources-path"].as<std::string>();
            this->gameGlobalResources->currentVersion = fileContent["version"].as<int>();
            this->gameGlobalResources->basicNormalFontSize = fileContent["basic-font-size"].as<float>();
            this->gameGlobalResources->basicLargerFontSize = fileContent["basic-font-larger-size"].as<float>();
            this->gameGlobalResources->specialNormalFontSize = fileContent["special-font-size"].as<float>();
            this->gameGlobalResources->specialLargerFontSize = fileContent["special-font-larger-size"].as<float>();
            this->gameGlobalResources->creators = fileContent["-creators"].as<std::vector<YAML::Node> >();

            // chargements des fichiers de polices d'écriture

            auto basicFont = LoadFont(
            (std::string(this->gameGlobalResources->resourcesDirPath) + ResourcesManager::FONTS_DIR_PATH + "normal.ttf").c_str()
            );

            if (!IsFontReady(basicFont) ) throw std::runtime_error("Echec de chargement de la police normale");

            auto specialFont = LoadFont(
            (std::string(this->gameGlobalResources->resourcesDirPath) + ResourcesManager::FONTS_DIR_PATH + "special.ttf").c_str()
            );

            if(!IsFontReady(specialFont) ) throw std::runtime_error("Echec de chargement de la police spéciale");

            this->gameGlobalResources->basicTextFont = basicFont;
            this->gameGlobalResources->specialTextFont = specialFont;

            // réussite du chargement des ressources
            this->gameGlobalResources->isLoaded = true;

            std::wcout << "(Chargement du fichier ressources app.yaml)" << std::endl;

            return true;
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de chargement du fichier de configuration (app.yaml) ) ou des fichiers de polices " << std::endl;
            std::wcerr << "(Erreur : " << e.what() <<  ")" << std::endl;
        }

        return false;
    }

    void ResourcesManager::loadRequiredResources() noexcept{
        try{
            // lancement du thread de chargement
            this->requiredResourcesLoadingThread = new std::thread([this](){ this->loadRequiredResources(true); });
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de chargement des ressources requises)" << std::endl;
            std::wcerr << "(Erreur" << e.what() <<  ")" << std::endl;
            this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, false);
        }
    }

    bool ResourcesManager::getSuccessfullyLoadRequiredResources() noexcept{
        return true;
    }

    void ResourcesManager::loadRequiredResources(bool fromThread) noexcept {
        try{
            std::this_thread::sleep_for(std::chrono::seconds(2) );

            this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, true);
        }
        catch(std::exception& e){
            std::wcerr << "(Echec de chargement des ressources requises)" << std::endl;
            std::wcerr << "(Erreur" << e.what() <<  ")" << std::endl;
            this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, false);
        }

    }
}