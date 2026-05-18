#include <stdio.h>
#include <string.h>
#include "game.h"
#include "board.h"
int flagggg=0;
void printHelp() {
   if(flagggg==0){
    printf("\n");
    printf(" Players will take turns placing pins on the board.\n");
    printf(" Red targets LEFT → RIGHT.\n");
    printf(" Black targets TOP → BOTTOM.\n");
    printf(" If two pins of the same color are a knight move apart,\n");
    printf("  an edge is automatically created.\n");
    printf(" Edges may not intersect other edges.\n");
    printf(" First player to complete a connection wins.\n");
    printf("\n\n");
    flagggg=1;
   }

    printf("Commands:\n");
    printf("  r c   -> place a pin at row r, column c\n");
    printf("  help  -> show command menu\n");
    printf("  quit  -> exit game\n");
}

int main() {
    gast game;
    initgame(&game);
    initboard(&game);

    char input[50];
    int r, c;

    printHelp();

    while (1) {
        printboard(&game);

        if (game.current == PLAYER_RED){
            printf("RED's turn.   Enter move (r c): ");
        }
        else{
            printf("BLACK's turn. Enter move (r c): ");
        }

        if (!fgets(input, sizeof(input), stdin)) {
            break; 
        }

        if (strncmp(input, "quit", 4) == 0) {
            break;
        }

        if (strncmp(input, "help", 4) == 0) {
            printHelp();
            continue;
        }

        if (sscanf(input, "%d %d", &r, &c) != 2) {
            printf("Invalid input: Use r c\n");
            continue;
        }

        if (isvalidmove(&game, r, c)==0) {
            printf("Invalid move! Try again.\n");
            continue;
        }

       
        placepin(&game, r, c);
        printedges(&game);
     
        state winner = checkwinner(&game);
        if (winner == RED) {
            printboard(&game);
            printf("RED wins by connecting left to right\n");
            break;
        } 
        else if (winner == BLACK) {
            printboard(&game);
            printf("BLACK wins by connecting top to bottom\n");
            break;
        }

      
        switchplayer(&game);
    }

    return 0;
}
