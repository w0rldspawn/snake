
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_WIDHT 16
#define BOARD_HEIGHT 10

struct TileLocation {
    int x, y;
};

// its useful for opposite directions to be negatives of one another
enum Direction { UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2, NO_DIR = 0 };

typedef struct tSnakeBody {
    int x, y;
    struct tSnakeBody *front, *behind; // if the front is null, then this is the body part immediately behind the head
} SnakeBody;

typedef struct tSnakeHead{
    int x, y;
    int snakeSize;
    enum Direction dir;
    struct tSnakeBody *behind;
} SnakeHead;


typedef struct {
    int x, y;
} Pokepuff;

int initGame();
int initSnake();
int initPuff();
int tickGame(enum Direction);
void movePuff();
bool compareCoordsPuffHead(Pokepuff *, SnakeHead *);
bool compareCoordsPuffBody(Pokepuff *, SnakeBody *);
bool compareCoordsHeadBody(SnakeHead *, SnakeBody *);
bool isSnekDead();
void cleanGame();

SnakeHead *head = NULL;
Pokepuff *puff = NULL;

// prepared the initial conditions for the game
int initGame() {

    if (!initSnake() || !initPuff()) {
        return 1;
    }
    return 0;
}
// initialises the snek with size 3
int initSnake() {
    head = (SnakeHead *)malloc(sizeof(SnakeHead));
    if (head == NULL) {
        printf("ERROR: MEMORY ALLOCATION FAILED");
        return 1;
    }
    head->x = BOARD_WIDHT / 2;
    head->y = BOARD_HEIGHT / 2;
    head->snakeSize = 3;
    head->dir = LEFT;
    SnakeBody *body1 = (SnakeBody *)malloc(sizeof(SnakeBody));
    if (body1 == NULL) {
        printf("ERROR: MEMORY ALLOCATION FAILED");
        return 1;
    }
    head->behind = body1;
    body1->x = BOARD_WIDHT / 2 + 1;
    body1->y = BOARD_HEIGHT / 2;
    body1->front = NULL;
    SnakeBody *body2 = (SnakeBody *)malloc(sizeof(SnakeBody));
    if (body2 == NULL) {
        printf("ERROR: MEMORY ALLOCATION FAILED");
        return 1;
    }
    body1->behind = body2;
    body2->x = BOARD_WIDHT / 2 + 2;
    body2->y = BOARD_HEIGHT / 2;
    body2->front = body1;

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

        if (compareCoordsPuffHead(puff, head)) {
            puffIsInTheRightPlace = false;
            continue;
        }
        SnakeBody *tBody = head->behind;
        while (tBody) {
            if (compareCoordsPuffBody(puff, tBody)) {
                puffIsInTheRightPlace = false;
                break;
            }
            tBody = tBody->behind;
        }
    } while (!puffIsInTheRightPlace);
}
// return true if they are in the same tile
bool compareCoordsPuffHead(Pokepuff *p, SnakeHead *sh) {
    if (p->x == sh->x && p->y == sh->y)
        return true;
    return false;
}
bool compareCoordsPuffBody(Pokepuff *p, SnakeBody *sb) {
    if (p->x == sb->x && p->y == sb->y)
        return true;
    return false;
}
bool compareCoordsHeadBody(SnakeHead *sh, SnakeBody *sb) {
    if (sh->x == sb->x && sh->y == sb->y)
        return true;
    return false;
}
// returns 0 if everything's normal, 1 if the snek dies, 2 if the snek wins, -1 if error
int tickGame(enum Direction directionToGo) {
    // if it tries to go backwards it doesnt change direction
    // and if theres no direction, it stays in the same direction it was going before
    if (directionToGo == -head->dir || directionToGo == NO_DIR) {
        directionToGo = head->dir;
    }
    int prevX = head->x;
    int prevY = head->y;
    switch (directionToGo) {
    case UP:
        head->y++;
        break;
    case DOWN:
        head->y--;
        break;
    case LEFT:
        head->x--;
        break;
    case RIGHT:
        head->y++;
        break;
    }
    if (isSnekDead()) {
        head->x = prevX; // in case you need to render
        head->y = prevY; // the snek after death
        return 1;
    }
    head->dir = directionToGo;

    bool willEatPuff = compareCoordsPuffHead(puff, head);
    if (willEatPuff)
        movePuff();

    // moving the body
    SnakeBody *tBody = head->behind;
    while (tBody) {
        int auxX = tBody->x;
        int auxY = tBody->y;
        tBody->x = prevX;
        tBody->y = prevY;
        prevX = auxX;
        prevX = auxY;
        SnakeBody *prevBody = tBody;
        tBody = tBody->behind;
        if (!tBody && willEatPuff) {
            SnakeBody *newBody = (SnakeBody *)malloc(sizeof(SnakeBody));
            if (newBody == NULL) {
                printf("ERROR: MEMORY ALLOCATION FAILED");
                return -1;
            }
            prevBody->behind = newBody;
            newBody->x = prevX;
            newBody->y = prevY;
            head->snakeSize++;
        }
    }
    if (head->snakeSize == BOARD_WIDHT * BOARD_HEIGHT) {
        return 2;
    }
    return 0;
}

bool isSnekDead() {
    if (head->x < 0 || BOARD_WIDHT <= head->x)
        return true;
    if (head->y < 0 || BOARD_HEIGHT <= head->y)
        return true;
    SnakeBody *tBody = head->behind;
    while (tBody) {
        if (compareCoordsHeadBody(head, tBody)) {
            return true;
        }
        tBody = tBody->behind;
    }
    return false;
}
// frees everything
void cleanGame() {
    free(puff);
    SnakeBody *tBody = head->behind;
    free(head);
    while (tBody->behind) {
        tBody = tBody->behind;
        free(tBody->front);
    }
    free(tBody);
}

