//
// Created by devel on 04/11/2023.
//

#include "SimpleFunctions.hpp"
#include "raylib.h"

namespace Game::Functions::GameFunctions{
    bool sayHello(GameFunction::FunctionData,GameFunction::FunctionRequiredGlobalData,std::vector<GameFunction::FunctionData>*){
        return true;
    }

    void SimpleFunctions::registerFunctions(){
        TraceLog(LOG_INFO,"Enregistrement des fonctions simples");

        GameFunction::gameFunctionsMap.insert({"HELLO",sayHello});
    }
}