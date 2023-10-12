//
// Created by devel on 10/10/2023.
//

#include "SceneBackground.hpp"

namespace Game::Scene::Background::Background{
    SceneBackground::SceneBackground(Game::Core::Game* linkedGame) : linkedGame(linkedGame) {}

    YAML::Node SceneBackground::getColorConfig() noexcept{
        return this->colorConfig;
    }

    Color SceneBackground::getColorFromConfig(const char* colorKey) noexcept{
        try {
            if (this->colorConfig[colorKey]) {
                auto colorDatas = this->colorConfig[colorKey].as<std::array<int,4> >();

                return Color(colorDatas[0],colorDatas[1],colorDatas[2],colorDatas[3]);
            }
        }
        catch(std::exception& e){
            TraceLog(LOG_INFO,"Une erreur s'est produite lors de la récupération de la couleur");
            TraceLog(LOG_INFO,e.what() );
        }

        return Color(0, 0, 0, 255);
    }
}