#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct  {
    SDL_Texture *head;
    SDL_Texture *body;
    SDL_Texture *curve;
} tSnyl;

extern tSnyl *texSnylkeon;
extern SDL_Texture *texPuff;

void loadSnylkeonTextures(void);
SDL_Texture *loadTexture(char *path);