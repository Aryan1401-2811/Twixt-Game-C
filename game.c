#include<stdio.h>
#include "game.h"



static int max(int a, int b) { 
    if(a>b){
        return a;
    }
    else{
    return b;
    }
}


static int orientation(int r1, int c1, int r2, int c2, int r3, int c3) {
    long x1 = c1, y1 = r1;
    long x2 = c2, y2 = r2;
    long x3 = c3, y3 = r3;

    long val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);

    if (val == 0) return 0;
   if (val > 0) {
    return 1;   
} else {
    return 2;   
}

}

static int onsegment(int r1, int c1, int r2, int c2, int r3, int c3) {
    long x1 = c1, y1 = r1;
    long x2 = c2, y2 = r2;
    long x3 = c3, y3 = r3;

    return x2 <= max(x1, x3) && x2 >= (x1 < x3 ? x1 : x3) &&
           y2 <= max(y1, y3) && y2 >= (y1 < y3 ? y1 : y3);
}


static int edgesintersect(const connection *a, const connection *b) {
 
    if ((a->r1 == b->r1 && a->c1 == b->c1) || (a->r1 == b->r2 && a->c1 == b->c2) || (a->r2 == b->r1 && a->c2 == b->c1) ||(a->r2 == b->r2 && a->c2 == b->c2)) {
        return 0;
    }

    int o1 = orientation(a->r1, a->c1, a->r2, a->c2, b->r1, b->c1);
    int o2 = orientation(a->r1, a->c1, a->r2, a->c2, b->r2, b->c2);
    int o3 = orientation(b->r1, b->c1, b->r2, b->c2, a->r1, a->c1);
    int o4 = orientation(b->r1, b->c1, b->r2, b->c2, a->r2, a->c2);

  
    if (o1 != o2 && o3 != o4) return 1;

 
    if (o1 == 0 && onsegment(a->r1, a->c1, b->r1, b->c1, a->r2, a->c2)) {
    return 1;
}

if (o2 == 0 && onsegment(a->r1, a->c1, b->r2, b->c2, a->r2, a->c2)) {
    return 1;
}

if (o3 == 0 && onsegment(b->r1, b->c1, a->r1, a->c1, b->r2, b->c2)) {
    return 1;
}

if (o4 == 0 && onsegment(b->r1, b->c1, a->r2, a->c2, b->r2, b->c2)) {
    return 1;
}

    return 0;
}


static int addEdge(gast *game, int r1, int c1, int r2, int c2, player owner) {
    if (game->edgeCount >= MAX_EDGES) return 0;

  
    for (int i = 0; i < game->edgeCount; ++i) {
        connection *e = &game->edges[i];
        if (e->owner == owner && ((e->r1 == r1 && e->c1 == c1 && e->r2 == r2 && e->c2 == c2) || (e->r1 == r2 && e->c1 == c2 && e->r2 == r1 && e->c2 == c1))) {
            
            return 0;
        }
    }

    connection newEdge;
    newEdge.r1 = r1;
    newEdge.c1 = c1;
    newEdge.r2 = r2;
    newEdge.c2 = c2;
    newEdge.owner = owner;

  
    for (int i = 0; i < game->edgeCount; ++i) {
        if (edgesintersect(&newEdge, &game->edges[i])) {
           
            return -1;
        }
    }

    game->edges[game->edgeCount++] = newEdge;
    return 1;
}



typedef struct Node{ 
    int r, c; 
} Node;

static int hasPath(gast *game, player p1) {
    int visited[BOARD_SIZE + 1][BOARD_SIZE + 1] = {0};
    Node queue[(BOARD_SIZE + 1) * (BOARD_SIZE + 1)];
    int head = 0, tail = 0;

   state color;

if (p1 == PLAYER_RED) {
    color = RED;
} else {
    color = BLACK;
}



    if (p1 == PLAYER_RED) {
        int c = 1;
        for (int r = 1; r <= BOARD_SIZE; ++r) {
            if (game->board[r][c] == color) {
                visited[r][c] = 1;
               Node temp;
                temp.r = r;
                temp.c = c;

                queue[tail] = temp;
                tail++;

            }
        }
    } else { 
        int r = 1;
        for (int c = 1; c <= BOARD_SIZE; ++c) {
            if (game->board[r][c] == color) {
                visited[r][c] = 1;
                Node temp;
                temp.r = r;
                temp.c = c;

                queue[tail] = temp;
                tail++;

            }
        }
    }

    
    while (head < tail) {
        Node cur = queue[head++];

      
        if (p1 == PLAYER_RED) {
            if (cur.c == BOARD_SIZE) {
                return 1;
            }
        } else {
            if (cur.r == BOARD_SIZE) {
                return 1;
            }
        }

        for (int i = 0; i < game->edgeCount; ++i) {
            connection *e = &game->edges[i];
            if (e->owner != p1) {
                continue;
            }

            int nr, nc;
            if (e->r1 == cur.r && e->c1 == cur.c) {
                nr = e->r2; 
                nc = e->c2;
            } else if (e->r2 == cur.r && e->c2 == cur.c) {
                nr = e->r1; 
                nc = e->c1;
            } else {
                continue;
            }

            if (visited[nr][nc]==0) {
                visited[nr][nc] = 1;
               Node temp;
                temp.r = nr;
                temp.c = nc;

                queue[tail] = temp;
                tail++;

            }
        }
    }

    return 0;
}



void initgame(gast *game) {
    for (int i = 0; i <= BOARD_SIZE; ++i) {
        for (int j = 0; j <= BOARD_SIZE; ++j) {
            game->board[i][j] = EMPTY;
        }
    }
    game->current   = PLAYER_RED;
    game->edgeCount = 0;
    game->moveCount = 0;
}

void switchplayer(gast *game) {
   if (game->current == PLAYER_RED) {
    game->current = PLAYER_BLACK;
} else {
    game->current = PLAYER_RED;
}

}

state checkwinner(gast *game) {
    if (hasPath(game, PLAYER_RED))  {
        return RED;
    } 
    if (hasPath(game, PLAYER_BLACK)) {
        return BLACK;
    }
    return EMPTY;
}

void addedgesforpin(gast *game, int r, int c) {
    state me = game->board[r][c];
    if (me == EMPTY) {
        return;
    }

   player owner;

if (me == RED) {
    owner = PLAYER_RED;
} else {
    owner = PLAYER_BLACK;
}

if (r - 2 >= 1 && c - 1 >= 1) {
    if (game->board[r - 2][c - 1] == me) {

        int res = addEdge(game, r, c, r - 2, c - 1, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r - 2, c - 1);
        }
    }
}


if (r - 2 >= 1 && c + 1 <= BOARD_SIZE) {
    if (game->board[r - 2][c + 1] == me) {

        int res = addEdge(game, r, c, r - 2, c + 1, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r - 2, c + 1);
        }
    }
}


if (r - 1 >= 1 && c - 2 >= 1) {
    if (game->board[r - 1][c - 2] == me) {

        int res = addEdge(game, r, c, r - 1, c - 2, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r - 1, c - 2);
        }
    }
}


if (r - 1 >= 1 && c + 2 <= BOARD_SIZE) {
    if (game->board[r - 1][c + 2] == me) {

        int res = addEdge(game, r, c, r - 1, c + 2, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r - 1, c + 2);
        }
    }
}


if (r + 1 <= BOARD_SIZE && c - 2 >= 1) {
    if (game->board[r + 1][c - 2] == me) {

        int res = addEdge(game, r, c, r + 1, c - 2, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r + 1, c - 2);
        }
    }
}


if (r + 1 <= BOARD_SIZE && c + 2 <= BOARD_SIZE) {
    if (game->board[r + 1][c + 2] == me) {

        int res = addEdge(game, r, c, r + 1, c + 2, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r + 1, c + 2);
        }
    }
}


if (r + 2 <= BOARD_SIZE && c - 1 >= 1) {
    if (game->board[r + 2][c - 1] == me) {

        int res = addEdge(game, r, c, r + 2, c - 1, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r + 2, c - 1);
        }
    }
}


if (r + 2 <= BOARD_SIZE && c + 1 <= BOARD_SIZE) {
    if (game->board[r + 2][c + 1] == me) {

        int res = addEdge(game, r, c, r + 2, c + 1, owner);

        if (res == -1) {
            char ownerChar;
            if (owner == PLAYER_RED) {
                ownerChar = 'R';
            } else {
                ownerChar = 'B';
            }
            printf("Link rejected for %c: (%d,%d) <-> (%d,%d) would cross an existing link.\n",
                   ownerChar, r, c, r + 2, c + 1);
        }
    }
}

}

void printedges(gast *game) {
    printf("\nCurrent Links (Edges):\n");
    if (game->edgeCount == 0) {
        printf("  No links yet.\n\n");
        return;
    }

    for (int i = 0; i < game->edgeCount; i++) {
        connection *e = &game->edges[i];
        char owner;

        if (e->owner == PLAYER_RED) {
            owner = 'R';
        } else {
            owner = 'B';
        }

        printf("  %c: (%d,%d) <--> (%d,%d)\n",owner, e->r1, e->c1, e->r2, e->c2);
    }
    printf("\n");
}
