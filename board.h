#ifndef BOARD_H
#define BOARD_H

#include "game.h"

void initboard(gast *game);
void printboard(gast *game);
int  isvalidmove(gast *game, int r, int c);
void placepin(gast *game, int r, int c);

#endif
