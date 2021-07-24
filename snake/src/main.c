#include <stdio.h>
#include "window.h"

#include <SDL2/SDL.h>
#undef main // sdl likes to redefine main

int
main(int argc, char *argv[])
{
	video_init();

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_KEYDOWN:
				printf("Key down\n");
				break;
			case SDL_KEYUP:
				printf("Key up\n");
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}

	video_shutdown();
	return 0;
}