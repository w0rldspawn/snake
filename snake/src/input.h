#pragma once
#include <SDL2/SDL.h>
#include "gameLogic.h"

void processInput(SDL_KeyCode *);
enum Direction mapSDLArrow(SDL_KeyCode);