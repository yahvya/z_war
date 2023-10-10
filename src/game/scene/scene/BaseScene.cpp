//
// Created by devel on 07/10/2023.
//

#include "BaseScene.hpp"
#include "raylib.h"

namespace Game::Scene::Scene {
    // intiation constantes
    const int BaseScene::MIN_FPS = 25;
    const int BaseScene::MAX_FPS = 100;
    const int BaseScene::DEFAULT_FPS = 60;

    BaseScene::BaseScene(Game::Core::Game* linkedGame) : linkedGame(linkedGame),isDrawing(true) { }

    BaseScene* BaseScene::stopDrawing() noexcept{
        std::lock_guard<std::mutex> lockGuard(this->accessLocker);
            this->isDrawing = false;

        return this;
    }

    BaseScene* BaseScene::initSceneTransition() noexcept{
        return this;
    }

    bool BaseScene::configWindow() noexcept{
        try {
            SetWindowSize(this->width, this->height);
            SetWindowTitle((std::string(this->windowName) + this->linkedGame->getResourcesManager()->getGameGlobalResources()->appName).c_str() );
            this->setFps();

            return true;
        }
        catch(std::exception&){}

        return false;
    }

    BaseScene* BaseScene::centerWindow(){
        auto monitor = GetCurrentMonitor();

        SetWindowPosition(
            (GetMonitorWidth(monitor) - this->width) / 2,
            (GetMonitorHeight(monitor) - this->width) / 2
        );

        return this;
    }

    BaseScene* BaseScene::setFps(){
        int gameFpsConfig = this->linkedGame->getResourcesManager()->getGameGlobalResources()->fps;

        SetTargetFPS(gameFpsConfig <= BaseScene::MAX_FPS && gameFpsConfig >= BaseScene::MIN_FPS ? gameFpsConfig : BaseScene::DEFAULT_FPS);

        return this;
    }

    BaseScene* BaseScene::setFps(int fps){
        SetTargetFPS(fps);

        return this;
    }
}