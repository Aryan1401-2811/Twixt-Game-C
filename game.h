#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 24
#define MAX_EDGES 1000

typedef enum { 
    EMPTY, RED, BLACK 
} state;
typedef enum { 
    PLAYER_RED, PLAYER_BLACK 
} player;

typedef struct connection {
    int r1, c1;
    int r2, c2;
    player owner;   
} connection;

typedef struct {
    state board[BOARD_SIZE + 1][BOARD_SIZE + 1]; 
    player current;
    connection edges[MAX_EDGES];
    int edgeCount;
    int moveCount;
} gast;


void initgame(gast *game);
void switchplayer(gast *game);


state checkwinner(gast *game);


void addedgesforpin(gast *game, int r, int c);
void printedges(gast *game);
#endif
