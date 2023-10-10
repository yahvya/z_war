//
// Created by devel on 07/10/2023.
//

#ifndef Z_WAR_LOADINGSCENE_HPP
#define Z_WAR_LOADINGSCENE_HPP

#include "../scene/BaseScene.hpp"

using namespace Game::Scene::Scene;

namespace Game::Scene::GameScene {

    /**
     * page de chargement
     */
    class LoadingScene : public BaseScene {
        public:
            explicit LoadingScene(Core::Game *linkedGame);

            /**
             * dessine la fenêtre (redéfinis la configuration de la fenêtre)
             * @attention méthode bloquante se débloque à l'appel de la fonction stopDrawing
             * @param countOfRetry nombre de tentatives en cas d'échec
             * @return si le dessin à réussi
             */
            bool draw(int countOfRetry) noexcept override;

            bool configWindow() noexcept override;
    };

}

#endif //Z_WAR_LOADINGSCENE_HPP
