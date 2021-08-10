#include "draw.h"
#include "window.h"


#include "texture.h"
#include "gameLogic.h"
#include <string.h>

#include <SDL2/SDL_image.h>



void clearScreen() {

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    return;
}

void renderGame() {
    renderTile(texPuff, puff->x, puff->y);
    renderTile(texSnylkeon->head, head->x, head->y);

    SnakeBody *tBody = head->behind;
    while (tBody) {
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

    SDL_RenderCopy(renderer, tex, NULL, &dest);

    return;
}