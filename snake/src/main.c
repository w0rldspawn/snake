#include "window.h"
#include "gameLogic.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // sdl likes to redefine main

#define gameSpeed 500 // the game ticks every 500ms

int main(int argc, char *argv[])
{
    video_init();
    uint32_t lastTick = SDL_GetTicks();
    int tickBucket = 0;

    while (1) {
        uint32_t currentTick = SDL_GetTicks();
        int deltaTime = currentTick - lastTick;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_KEYDOWN:
                printf("Key down\n");
                break;
            case SDL_KEYUP:
                printf("Key up\n");
                break;
            case SDL_QUIT:
                exit(0);
            }
        }

        tickBucket += deltaTime;
        if (tickBucket >= gameSpeed) {
            tickBucket -= gameSpeed;
            // tickGame();
        }

        nextFramePls();
        lastTick = currentTick;
    }

    video_shutdown();
    return 0;
}