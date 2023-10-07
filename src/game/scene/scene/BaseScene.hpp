//
// Created by devel on 07/10/2023.
//

#ifndef Z_WAR_BASESCENE_HPP
#define Z_WAR_BASESCENE_HPP

#include "../../pattern/observer/ClassicObserver.hpp"
#include "../../core/Game.hpp"


using namespace Game::Pattern::Observer;

namespace Game::Scene::Scene{

    /**
     * interface de scène de jeux
     */
    class BaseScene : public ClassicObserver {
        public:
            explicit BaseScene(Game::Core::Game* linkedGame);

            /**
             * dessine la scène
             * @param countOfRetry nombre de tentatives si echec de dessin
             * @return si le dessin réussi
             */
            virtual bool draw(int countOfRetry) noexcept = 0;

        protected:
            /**
             * le jeux lié à la scène
             */
            Game::Core::Game* linkedGame;
    };

}

#endif //Z_WAR_BASESCENE_HPP

