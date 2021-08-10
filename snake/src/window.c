#include "window.h"

#define WPOS (SDL_WINDOWPOS_CENTERED)
#define WFLAGS (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)

SDL_Window *window;
SDL_Renderer *renderer;
static SDL_GLContext *context;

// TODO: use fatal() for errors
static void video_init_sdl(void) {

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetSwapInterval(1); /* force vsync */
	atexit(SDL_Quit);
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		printf("SDL_INIT_VIDEO failed: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("Snylkeon", WPOS, WPOS, WWIDTH, WHEIGHT, WFLAGS);
	if (window == NULL) {
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, context);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		exit(1);
	}
}

// TODO: use glew or just sdl drawing functions
static void video_init_gl(void) {

	/*int status = gl3wInit();
	if (status != 0) {
		printf("video_init_gl failed: %d\n", status);
		exit(1);
	}*/
}

void video_init(void) {

	video_init_sdl();
	video_init_gl();
#ifndef NDEBUG
	puts("video_init");
#endif
}

void video_shutdown(void) {

	SDL_DestroyWindow(window);
}