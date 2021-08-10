#pragma once
#include <stdbool.h>
#include <stdint.h>

#define BOARD_WIDHT 16
#define BOARD_HEIGHT 10

// its useful for opposite directions to be negatives of one another
enum Direction { UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2, NO_DIR = 0 };

/*
struct TileLocation {
    int x, y;
};
*/

typedef struct tSnakeBody {
    int x, y;
    struct tSnakeBody *front, *behind; // if the front is null, then this is the body part immediately behind the head
} SnakeBody;

typedef struct tSnakeHead {
    int x, y;
    int snakeSize;
    enum Direction dir;
    struct tSnakeBody *behind;
} SnakeHead;

typedef struct {
    int x, y;
} Pokepuff;

extern SnakeHead *head;
extern Pokepuff *puff;

// only these need to be used outside gameLogic files

bool initGame(void);
int tickGame(enum Direction);
void cleanGame(void);

// these can be used, but not needed

void movePuff();
bool isSnekDead();
bool compareCoordsPuffHead(Pokepuff *, SnakeHead *);
bool compareCoordsPuffBody(Pokepuff *, SnakeBody *);
bool compareCoordsHeadBody(SnakeHead *, SnakeBody *);

