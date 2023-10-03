//
// Created by devel on 03/10/2023.
//

#include "Game.h"
#include "raylib.h"

namespace Game {
    namespace Core {
        bool Game::launch() {
            InitWindow(300,300,"test");
            while(!WindowShouldClose() ){
                BeginDrawing();
                ClearBackground(WHITE);
                EndDrawing();
            }
            CloseWindow();

            return true;
        }
    } // Game
} // Core