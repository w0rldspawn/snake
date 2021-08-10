#include "gameLogic.h"
#include "window.h"
#include "input.h"
#include "draw.h"
#include "texture.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // sdl likes to redefine main

#define gameSpeed 350 // the game ticks every X ms

int getFrameTime();

int main(int argc, char *argv[]) {
    video_init();
    if (initGame()) {
        printf("ERROR: FAILED TO INITIALIZE GAME");
        exit(1);
    }
    
    loadSnylkeonTextures();

    int tickBucket = 0;
    SDL_KeyCode lastArrow = 0;

    int red = 0;

    while (1) {
        int deltaTime = getFrameTime();

        processInput(&lastArrow);

        tickBucket += deltaTime;
        if (tickBucket >= gameSpeed) {
            tickBucket -= gameSpeed;

            printf("Game tick: %d\n", tickGame(mapSDLArrow(lastArrow)));
        }

        // RENDERING

        clearScreen();

        renderGame();

        SDL_RenderPresent(renderer);

    }

    video_shutdown();
    return 0;
}


int getFrameTime() {
    static uint32_t lastTick;
    static uint32_t currentTick;

    static bool firstFrame = true;
    if (firstFrame) {
        lastTick = SDL_GetTicks();
        firstFrame = false;
    }

    currentTick = SDL_GetTicks();
    int deltaTime = currentTick - lastTick;
    lastTick = currentTick;

    return deltaTime;
}

