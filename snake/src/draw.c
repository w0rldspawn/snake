#include "draw.h"
#include "window.h"

#include <SDL2/SDL_image.h>

#include <string.h>



void clearScreen() {

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    return;
}

void renderSnylkeon() {

}