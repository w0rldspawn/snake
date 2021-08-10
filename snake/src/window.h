#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#define WWIDTH  (1280)
#define WHEIGHT (800)

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void video_init(void);
void video_shutdown(void);