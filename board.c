#include <stdio.h>
#include "board.h"

void initboard(gast *game) {
    for (int i = 1; i <= BOARD_SIZE; i++) {
        for (int j = 1; j <= BOARD_SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
}

void printboard(gast *game) {
    printf("\n     ");
    for (int j = 1; j <= BOARD_SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= BOARD_SIZE; i++) {
        printf("%2d | ", i);
        for (int j = 1; j <= BOARD_SIZE; j++) {
            char c = '.';
            if (game->board[i][j] == RED) { 
                 c = 'R';
            }
            else if (game->board[i][j] == BLACK) {
                c = 'B';
            }
            printf("%c  ", c);
        }
        printf("\n");
    }
    printf("\n");
}

int isvalidmove(gast *game, int r, int c) {

  
    if (r < 1 || r > BOARD_SIZE || c < 1 || c > BOARD_SIZE) {
        printf("Invalid move: sorry position is outside the board.\n");
        return 0;
    }

    
    if (game->board[r][c] != EMPTY) {
        printf("Invalid move: sorry that cell is already occupied.\n");
        return 0;
    }

    
    if ((r == 1 || r == BOARD_SIZE) && (c == 1 || c == BOARD_SIZE)) {
        printf("Invalid move: sorry pegs cannot be placed in the four corners.\n");
        return 0;
    }

   
    if (game->current == PLAYER_RED) {
        if (r == 1 || r == BOARD_SIZE) {
            printf("Invalid move: sorry RED cannot place pegs on rows 1 or %d.\n", BOARD_SIZE);
            return 0;
        }
    }

   
    if (game->current == PLAYER_BLACK) {
        if (c == 1 || c == BOARD_SIZE) {
            printf("Invalid move: sorry BLACK cannot place pegs on columns 1 or %d.\n", BOARD_SIZE);
            return 0;
        }
    }

    return 1;
}


void placepin(gast *game, int r, int c) {
  state color;

    if (game->current == PLAYER_RED) {
        color = RED;
    } else {
        color = BLACK;
    }

    game->board[r][c] = color;
    game->moveCount++;

    
    addedgesforpin(game, r, c);
}
