#include "gameLogic.h"
#include <stdint.h>
#include <stdlib.h>

bool compareCoords(Pokepuff *, SnakeHead *);
bool compareCoords(Pokepuff *, SnakeBody *);
bool compareCoords(SnakeHead *, SnakeBody *);

typedef struct {
    int x, y;
    int snakeSize;
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
// initialises the snek with size 3
int initSnake() {
    // 16x10 board, it'll start almost in the middle
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
bool compareCoords(Pokepuff *p, SnakeHead *sh) {
    if (p->x == sh->x && p->y == sh->y)
        return true;
    return false;
}
bool compareCoords(Pokepuff *p, SnakeBody *sb) {
    if (p->x == sb->x && p->y == sb->y)
        return true;
    return false;
}
bool compareCoords(SnakeHead *sh, SnakeBody *sb) {
    if (sh->x == sb->x && sh->y == sb->y)
        return true;
    return false;
}
// returns 0 if everything's normal, 1 if the snek dies, 2 if the snek wins
int tickGame(enum Direction directionToGo) {
    // if it tries to go backwards it doesnt change direction
    if (directionToGo == -head->dir) {
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

    bool willEatPuff = compareCoords(puff, head);
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
            prevBody->behind = newBody;
            newBody->x = prevX;
            newBody->y = prevY;
            head->snakeSize++;
        }
    }
}

bool isSnekDead() {
    if (head->x < 0 || BOARD_WIDHT <= head->x)
        return true;
    if (head->y < 0 || BOARD_HEIGHT <= head->y)
        return true;
    SnakeBody *tBody = head->behind;
    while (tBody) {
        if (compareCoords(head, tBody)) {
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

