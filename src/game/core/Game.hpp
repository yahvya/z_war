//
// Created by devel on 03/10/2023.
//

#ifndef Z_WAR_GAME_HPP
#define Z_WAR_GAME_HPP

#include "../resources/ResourcesManager.hpp"
#include "../pattern/observer/ClassicObserver.hpp"

using namespace Game::Resource;
using namespace Game::Pattern::Observer;

namespace Game::Core {
    class Game : public ClassicObserver{
        public:
            /**
             * lance le jeux
             * @return bool si le jeux est bien lancé
             */
            bool launch() noexcept;

            /**
             *
             * @return le gestionnaire de ressources
             */
            ResourcesManager* getResourcesManager() noexcept;

        private:
            /**
             * gestionnaire de ressources
             */
             ResourcesManager* resourcesManager;

            /**
             * nombre de tentatives à refaire (global dans le programme) dessin
             */
            static const int GLOBAL_COUNT_OF_RETRY_FOR_DRAW;
    };
}

#endif //Z_WAR_GAME_HPP
