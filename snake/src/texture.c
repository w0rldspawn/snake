
#include "texture.h"
#include "window.h"

tSnyl *texSnylkeon;
SDL_Texture *texPuff;

void loadSnylkeonTextures() {

	IMG_Init(IMG_INIT_PNG);

	texSnylkeon = (tSnyl *) malloc(sizeof(tSnyl));
	if (texSnylkeon == NULL) {
		printf("ERROR: MEMORY ALLOCATION FAILED");
		exit(1);
	}

	texSnylkeon->head = loadTexture("sprites/snylkeon/head.png");
	texSnylkeon->body = loadTexture("sprites/snylkeon/body.png");
	texSnylkeon->curve = loadTexture("sprites/snylkeon/curve.png");
	texPuff = loadTexture("sprites/snylkeon/puff.png");

	return;
}

SDL_Texture *loadTexture(char *path) {
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	} else {
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}