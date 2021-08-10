#include "draw.h"
#include "window.h"

#include "gameLogic.h"
#include "texture.h"
#include <string.h>

#include <SDL2/SDL_image.h>

#ifdef EZRA
uint8_t ribbonColors[4][3] = {
    {255, 225, 140}, // cyan
    {64, 64, 64},    // blue
    {195, 122, 245}, // pink
    {255, 255, 255}, // white
};
#else
uint8_t ribbonColors[4][3] = {
    {133, 207, 244}, // cyan
    {100, 123, 177}, // blue
    {246, 153, 172}, // pink
    {255, 255, 255}, // white
};
#endif

void clearScreen() {

	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
	SDL_RenderClear(renderer);

	return;
}

void renderGame() {
	renderTile(texPuff, puff->x, puff->y, UP);
	renderTile(texSnylkeon->head, head->x, head->y, head->dir);
	SnakeBody *prevBody = (SnakeBody *)head;
	SnakeBody *tBody = head->behind;
	SnakeBody *nextBody = tBody->behind;
	int i = 0;
	SDL_SetTextureColorMod(texSnylkeon->head, ribbonColors[i][0], ribbonColors[i][1], ribbonColors[i][2]);

	enum Direction dir = NO_DIR;
	while (tBody) {
		// divide by 3 because 3 rgb values
		if (i < (sizeof(ribbonColors) / 3) - 1) {
			++i;
		}

		SDL_Texture *tex = texSnylkeon->body;
		if (nextBody == NULL) {
			if (tBody->x == prevBody->x) {
				dir = UP;
			} else {
				dir = RIGHT;
			}
		} else if (prevBody->x == nextBody->x) {
			dir = UP;
		} else if (prevBody->y == nextBody->y) {
			dir = RIGHT;
		} else {
			tex = texSnylkeon->curve;
			int bigy = (prevBody->y > nextBody->y) ? prevBody->y : nextBody->y;
			int bigx = (prevBody->x > nextBody->x) ? prevBody->x : nextBody->x;

			if (bigy > tBody->y) {
				if (bigx > tBody->x) {
					dir = LEFT;
				} else {
					dir = UP;
				}
			} else {
				if (bigx > tBody->x) {
					dir = DOWN;
				} else {
					dir = RIGHT;
				}
			}
		}
		SDL_SetTextureColorMod(tex, ribbonColors[i][0], ribbonColors[i][1], ribbonColors[i][2]);
		renderTile(tex, tBody->x, tBody->y, dir);
		prevBody = tBody;
		tBody = nextBody;
		if (nextBody) {
			nextBody = nextBody->behind;
		}
	}

	return;
}

void renderTile(SDL_Texture *tex, int x, int y, enum Direction dir) {

	SDL_Rect dest;

	dest.x = x * 80;
	dest.y = y * 80;
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	double angle = 0;

	if (dir == LEFT)
		angle = 270.0;
	else if (dir == RIGHT)
		angle = 90.0;
	else if (dir == UP)
		angle = 0.0;
	else
		angle = 180.0;

	SDL_RenderCopyEx(renderer, tex, NULL, &dest, angle, NULL, SDL_FLIP_NONE);

	return;
}