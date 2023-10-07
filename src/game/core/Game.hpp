//
// Created by devel on 03/10/2023.
//

#ifndef Z_WAR_GAME_HPP
#define Z_WAR_GAME_HPP

namespace Game::Core {
    class Game {
        public:
            /**
             * lance le jeux
             * @return bool si le jeux est bien lancé
             */
            bool launch() noexcept;
    };
}

#endif //Z_WAR_GAME_HPP
