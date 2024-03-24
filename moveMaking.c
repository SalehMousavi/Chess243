#include <globals.h>

void getMove(short int* moveRow, short int* moveCol) {
   mousex = (int) (mousex & 0x1FF);
   mousey = (int) (mousey & 0xFF);
   printf("Mousex: %d, Mousey: %d\n", mousex, mousey);
   *moveCol = (short int)((mousex - 39) / WIDTH);
   *moveRow = (short int)(mousey / HEIGHT);
   printf("MouseR: %d, MouseC: %d\n", *moveRow, *moveCol);
   return;
}

void checkMove(short int moveRow, short int moveCol, char colour, char* moveValid, char startedMove) {
    if(startedMove == 0) {//selecting a starting position for move
        switch(colour) {
            case BLACK: {
                if(Board[moveRow][moveCol] > 'A' && Board[moveRow][moveCol] < 'Z' && Board[moveRow][moveCol] != 'o') {
                    *(moveValid) = 1;
                }
                else {
                    *(moveValid) = 0;
                }
                break;
            }

            case WHITE: {
                if(Board[moveRow][moveCol] > 'a' && Board[moveRow][moveCol] < 'z' && Board[moveRow][moveCol] != 'o') {
                    *(moveValid) = 1;
                }
                else {
                    *(moveValid) = 0;
                }
                break;
            }
        }
    }
    else {//already selected starting position
        switch(colour) {
            case BLACK: {
                if(Board[moveRow][moveCol] > 'a' && Board[moveRow][moveCol] < 'z') {
                    *(moveValid) = 1;
                }
                else {
                    *(moveValid) = 0;
                }
                break;
            }

            case WHITE: {
                if((Board[moveRow][moveCol] > 'A' && Board[moveRow][moveCol] < 'Z') || Board[moveRow][moveCol] == 'o') {
                    *(moveValid) = 1;
                }
                else {
                    *(moveValid) = 0;
                }
                break;
            }
        }
    }
    
    return;
}

void checkLegality(int startingRow, int startingCol, int finalRow, int finalCol, char* moveLegal) {
    *moveLegal = 1;
    return;
}

void movePiece(int startingRow, int startingCol, int finalRow, int finalCol) {
    Board[finalRow][finalCol] = Board[startingRow][startingCol];
    Board[startingRow][startingCol] = 'o';
    return;
}