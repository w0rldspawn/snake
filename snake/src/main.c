#include "gameLogic.h"
#include "window.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // sdl likes to redefine main

#define gameSpeed 500 // the game ticks every 500ms

int main(int argc, char *argv[]) {
    video_init();
    uint32_t lastTick = SDL_GetTicks();
    int tickBucket = 0;
    SDL_KeyCode lastArrow = 0;

    while (1) {
        uint32_t currentTick = SDL_GetTicks();
        int deltaTime = currentTick - lastTick;

        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_KEYDOWN:
                printf("Key down\n");
                SDL_KeyCode key = e.key.keysym.sym;
                if (key == SDLK_LEFT) {
                    lastArrow = key;
                }
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
            enum Direction d = NO_DIR;
            switch (lastArrow) {
            case SDLK_UP:
                d = UP;
                break;
            case SDLK_DOWN:
                d = DOWN;
                break;
            case SDLK_RIGHT:
                d = RIGHT;
                break;
            case SDLK_LEFT:
                d = LEFT;
                break;
            }
            tickGame(d);
        }

        nextFramePls();
        lastTick = currentTick;
    }

    video_shutdown();
    return 0;
}