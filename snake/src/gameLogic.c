
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define BOARD_WIDHT 16
#define BOARD_HEIGHT 10

int initGame();
int initSnake();
int initPuff();
int tickGame(enum Direction);
void movePuff();
bool compareCoords(Pokepuff *, SnakeHead *);
bool compareCoords(Pokepuff *, SnakeBody *);


struct TileLocation {
    int x, y;
};

// its useful for opposite directions to be negatives of one another
enum Direction { UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2 };

typedef struct {
    int x, y;
    enum Direction dir;
    SnakeBody *behind;
} SnakeHead;

typedef struct {
    int x, y;
    SnakeBody *front, *behind; // if the front is null, then this is the body part immediately behind the head
} SnakeBody;

typedef struct {
    int x, y;
} Pokepuff;

SnakeHead *head = NULL;
Pokepuff *puff = NULL;


// prepared the initial conditions for the game
int initGame() {
    
    if (!initSnake() || !initPuff()) {
        return 1;
    }
    return 0;
}
// initialises the snek
int initSnake() {
    // 16x10 board, it'll start almost in the middle
    head = (SnakeHead *)malloc(sizeof(SnakeHead));
    if (head == NULL) {
        printf("ERROR: MEMORY ALLOCATION FAILED");
        return 1;
    }
    head->x = BOARD_WIDHT;
    head->y = BOARD_HEIGHT;
    head->dir = LEFT;
    head->behind = NULL;

    return 0;
}
// initialises the pokepuff
int initPuff() {
    puff = (Pokepuff *)malloc(sizeof(Pokepuff));
    if (puff == NULL) {
        printf("ERROR: MEMORY ALLOCATION FAILED");
        return 1;
    }

    movePuff();

    return 0;
}
// changes the puff coords until it is in an empty tile
void movePuff() {
    bool puffIsInTheRightPlace;
    do {
  
        puff->x = rand() % BOARD_WIDHT;
        puff->y = rand() % BOARD_HEIGHT;

        puffIsInTheRightPlace = true;

        if (compareCoords(puff, head)) {
            puffIsInTheRightPlace = false;
            continue;
        }
        SnakeBody *tBody = head->behind;
        while (tBody) {
            if (compareCoords(puff, tBody)) {
                puffIsInTheRightPlace = false;
                break;
            }
            tBody = tBody->behind;
        }
    } while (!puffIsInTheRightPlace);
}
// return true if they are in the same tile
bool compareCoords(Pokepuff* p, SnakeHead *sh) {
    if (p->x == sh->x && p->y == sh->y)
        return true;
    return false;
}
bool compareCoords(Pokepuff *p, SnakeBody *sb) {
    if (p->x == sb->x && p->y == sb->y)
        return true;
    return false;
}
// returns 0 if everything's normal, 1 if the snek dies, 2 if the snek wins
int tickGame(enum Direction directionToGo) {
    // if it tries to go backwards it doesnt change direction
    if (directionToGo == -head->dir) {
        directionToGo = head->dir;
    }
    switch (directionToGo) {
    case UP:
        break;
    case DOWN:
        break;
    case LEFT:
        break;
    case RIGHT:
        break;
    default:
        break;
    }
}
