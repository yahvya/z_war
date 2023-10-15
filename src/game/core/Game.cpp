//
// Created by devel on 03/10/2023.
//

#include <iostream>
#include <future>
#include "Game.hpp"
#include "raylib.h"
#include "../scene/game-scene/LoadingScene.hpp"

using namespace Game::Scene::GameScene;

namespace Game::Core {
    // initalisation des constantes statiques
    const int Game::GLOBAL_COUNT_OF_RETRY_FOR_DRAW = 5;

    bool Game::launch() noexcept{
        // configuration de lancement raylib (pour permettre le chargement des ressources préliminaires)
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(0,0,"Configuration");

        this->resourcesManager = new ResourcesManager();

        // chargement des ressources préliminaires

        if(!this->resourcesManager->loadGlobalResources() ){
            TraceLog(LOG_ERROR,"Echec de chargement du fichier des ressources de l'application");

            CloseWindow();

            return false;
        }

        auto loadingScene = new LoadingScene(this);

        // branchement sur la fin de chargement chargement des ressources requises au reste du fonctionnement
        this->resourcesManager->registerObserver(
            ResourcesManager::ResourcesManagerObservableEvents::END_OF_LOADING_APP_RESSOURCES,
            new ClassicObservable::ObserverDatasContainer(
                this,
                [this,&loadingScene](ClassicObservable* resourceManager,std::any eventData){ /*loadingScene->stopDrawing();*/ }
            )
        );

        TraceLog(LOG_INFO,"Lancement du chargement de ressource");

        this->resourcesManager->loadRequiredResources();

        // affichage de la page de chargement en attendant le chargement des ressources
        loadingScene->draw(Game::GLOBAL_COUNT_OF_RETRY_FOR_DRAW);

        // vérification de la réussite du chargement des ressources

        // lancement du jeux

        CloseWindow();

        return true;
    }

    ResourcesManager* Game::getResourcesManager() noexcept{
        return this->resourcesManager;
    }
}