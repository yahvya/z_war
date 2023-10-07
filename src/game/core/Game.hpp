//
// Created by devel on 03/10/2023.
//

#ifndef Z_WAR_GAME_HPP
#define Z_WAR_GAME_HPP

#include "../resources/ResourcesLoader.hpp"

using namespace Game::Resource;

namespace Game::Core {
    class Game {
        public:
            /**
             * lance le jeux
             * @return bool si le jeux est bien lancé
             */
            bool launch() noexcept;

        private:
            /**
             * ressources globales de l'application
             */
            GameGlobalResource* appGlobalRessources;
    };
}

#endif //Z_WAR_GAME_HPP
