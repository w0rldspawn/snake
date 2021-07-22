#include <stdio.h>
#include <SDL2/SDL.h>
#undef main // sdl likes to redefine main

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	puts("hello sylveon");
	return 0;
}