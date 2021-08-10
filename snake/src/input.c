#include "input.h"

void processInput(SDL_KeyCode *lastArrow) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_KEYDOWN:
            printf("Key down\n");
            SDL_KeyCode key = e.key.keysym.sym;
            if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT) {
                *lastArrow = key;
            } else if (key == SDLK_ESCAPE) {
                exit(0);
            }
            break;
        case SDL_KEYUP:
            printf("Key up\n");
            break;
        case SDL_QUIT:
            exit(0);
        }
    }

    return;
}

enum Direction mapSDLArrow(SDL_KeyCode lastArrow) {
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
    return d;
}

