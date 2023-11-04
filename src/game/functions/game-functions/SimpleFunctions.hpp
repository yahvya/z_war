//
// Created by devel on 04/11/2023.
//

#ifndef Z_WAR_SIMPLEFUNCTIONS_HPP
#define Z_WAR_SIMPLEFUNCTIONS_HPP

#include "../functions/GameFunction.hpp"

using namespace Game::Functions::Functions;

namespace Game::Functions::GameFunctions{
    /**
     * liste d'implémentation de fonction simples
     */
    class SimpleFunctions : GameFunction{
        protected:
            /**
             * enregistre les fonctions simples
             */
            static void registerFunctions();

            friend void GameFunction::registerFunctions();
    };
}



#endif //Z_WAR_SIMPLEFUNCTIONS_HPP
