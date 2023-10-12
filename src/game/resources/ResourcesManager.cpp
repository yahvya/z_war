//
// Created by devel on 07/10/2023.
//

#include <string>
#include "ResourcesManager.hpp"
#include "yaml-cpp/yaml.h"
#include "raylib.h"

namespace Game::Resource {
    // initialisation des constantes statiques
    const char* ResourcesManager::APP_CONFIG_FILE_PATH = "./app.yaml";
    const char* ResourcesManager::FONTS_DIR_PATH = "fonts/";
    const char* ResourcesManager::CONFIG_DIR_PATH = "config/";

    ResourcesManager::ResourcesManager() : gameGlobalResources{new GameGlobalResource()},gameRequiredResources{nullptr} {}

    bool ResourcesManager::loadGlobalResources() noexcept{
        try {
            // chargement du fichier de configuration global app.yaml
                auto fileContent = YAML::LoadFile(ResourcesManager::APP_CONFIG_FILE_PATH);

            // récupération des valeurs de configuration
                this->gameGlobalResources->appName = fileContent["appname"].as<std::string>();
                this->gameGlobalResources->resourcesDirPath = fileContent["resources-path"].as<std::string>();
                this->gameGlobalResources->appIconPath = fileContent["iconPath"].as<std::string>();
                this->gameGlobalResources->currentVersion = fileContent["version"].as<int>();
                this->gameGlobalResources->basicNormalFontSize = fileContent["basic-font-size"].as<float>();
                this->gameGlobalResources->basicLargerFontSize = fileContent["basic-font-larger-size"].as<float>();
                this->gameGlobalResources->specialNormalFontSize = fileContent["special-font-size"].as<float>();
                this->gameGlobalResources->specialLargerFontSize = fileContent["special-font-larger-size"].as<float>();
                this->gameGlobalResources->fps = fileContent["fps"].as<int>();
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

                TraceLog(LOG_INFO,"Chargement du fichier ressources app.yaml");

            return true;
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement du fichier de configuration (app.yaml) ) ou des fichiers de polices");
            TraceLog(LOG_ERROR,e.what());
        }

        return false;
    }

    void ResourcesManager::loadRequiredResources() noexcept{
        try{
            // lancement du thread de chargement
                this->requiredResourcesLoadingThread = new std::thread([this](){ this->loadRequiredResources(true); });
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des ressources requises");
            TraceLog(LOG_ERROR,e.what() );

            this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, false);
        }
    }

    bool ResourcesManager::getSuccessfullyLoadRequiredResources() noexcept{
        return this->gameRequiredResources != nullptr;
    }

    void ResourcesManager::loadRequiredResources(bool fromThread) noexcept {
        try{
            // récupération des données du fichier de configuration
                auto playerConfigFileContent = YAML::LoadFile(
                    std::string(this->gameGlobalResources->resourcesDirPath) + ResourcesManager::CONFIG_DIR_PATH + "player/config.yaml"
                );


            // configuration joueur
                auto playerConfig = new PlayerConfigDatas();

                playerConfig->name = playerConfigFileContent["name"].as<std::string>();
                playerConfig->fname = playerConfigFileContent["fname"].as<std::string>();
                playerConfig->birth = playerConfigFileContent["birth"].as<std::string>();
                playerConfig->joinDate = playerConfigFileContent["join-date"].as<std::string>();
                playerConfig->isConfigured = !playerConfig->name.empty() && !playerConfig->fname.empty() && !playerConfig->birth.empty() && !playerConfig->joinDate.empty();

            // configuration song
                auto songConfig = new SongConfigDatas();

                songConfig->generalSongPercent = playerConfigFileContent["game-general-song-percent"].as<float>();
                songConfig->gameSongPercent = playerConfigFileContent["game-game-song-percent"].as<float>();
                songConfig->hitSongPercent = playerConfigFileContent["game-hit-song-percent"].as<float>();
                songConfig->generalActionSongPercent = playerConfigFileContent["game-general-action-song-percent"].as<float>();

            // sauvegarde des ressources
                this->gameRequiredResources = new GameRequiredResource(playerConfig,songConfig);

            TraceLog(LOG_INFO,"Fin de chargement des ressources requises");

            // notificaiton d'évenement de fin de chargement
                this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, true);
        }
        catch(std::exception& e){
            TraceLog(LOG_ERROR,"Echec de chargement des ressources requises");
            TraceLog(LOG_ERROR,e.what());

            this->notifyObservers(ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES, false);
        }

    }

    GameRequiredResource* ResourcesManager::getGameRequiredResources() noexcept{
        return this->gameRequiredResources;
    }

    GameGlobalResource* ResourcesManager::getGameGlobalResources() noexcept{
        return this->gameGlobalResources;
    }
}