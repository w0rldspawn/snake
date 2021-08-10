#pragma once

#include <SDL2/SDL.h>

void clearScreen(void);
void renderGame(void);
void renderTile(SDL_Texture *tex, int x, int y, enum Direction dir);