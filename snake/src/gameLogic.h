#pragma once
#include <stdbool.h>

#define BOARD_WIDHT 16
#define BOARD_HEIGHT 10

int initGame();
int initSnake();
int initPuff();
int tickGame(enum Direction);
void movePuff();
bool isSnekDead();
void cleanGame();

struct TileLocation {
    int x, y;
};

// its useful for opposite directions to be negatives of one another
enum Direction { UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2 };