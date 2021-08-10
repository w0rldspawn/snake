#include "draw.h"
#include "window.h"


#include "texture.h"
#include "gameLogic.h"
#include <string.h>

#include <SDL2/SDL_image.h>

#ifdef EZRA
uint8_t ribbonColors[4][3] = {
    { 255, 225, 140 }, // cyan
    { 64,  64,  64  }, // blue
    { 195, 122, 245 }, // pink
    { 255, 255, 255 }, // white
};
#else
uint8_t ribbonColors[4][3] = {
    { 133, 207, 244 }, // cyan
    { 100, 123, 177 }, // blue
    { 246, 153, 172 }, // pink
    { 255, 255, 255 }, // white
};
#endif

void clearScreen() {

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    return;
}

void renderGame() {
    renderTile(texPuff, puff->x, puff->y);
    renderTile(texSnylkeon->head, head->x, head->y);

    SnakeBody *tBody = head->behind;
    int i = 0;
    SDL_SetTextureColorMod(texSnylkeon->head,
        ribbonColors[i][0], ribbonColors[i][1], ribbonColors[i][2]);
    while (tBody) {
        // divide by 3 because 3 rgb values
        if (i < (sizeof(ribbonColors) / 3) - 1) {
            ++i;
        }
        SDL_SetTextureColorMod(texSnylkeon->body,
            ribbonColors[i][0], ribbonColors[i][1], ribbonColors[i][2]);
        renderTile(texSnylkeon->body, tBody->x, tBody->y);
        tBody = tBody->behind;
    }

    return;
}

void renderTile(SDL_Texture *tex, int x, int y) {
    
    SDL_Rect dest;

    dest.x = x * 80;
    dest.y = y * 80;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    double angle = 0;
    SnakeBody *tBody = head;
    if (tBody->x < tBody->behind->x)
        angle = 270;
    if (tBody->x > tBody->behind->x)
        angle = 90;
    if (tBody->y < tBody->behind->y)
        angle = 0;
    if (tBody->y > tBody->behind->y)
        angle = 180;

    SDL_RenderCopyEx(renderer, tex, NULL, &dest, angle, NULL, SDL_FLIP_NONE);

    return;
}