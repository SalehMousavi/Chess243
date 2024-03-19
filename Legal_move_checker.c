#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h> 

/***************************************************************************************************************************
 ******************************************************** FUNCTIONS ***********************************************************
 ***************************************************************************************************************************/
void print_board(); 
void check_turn(); // this checks if the turn inputed by the user is valid, swaps turns if it is
void position_legal(); // this checks if the piece is at the start end locations are valid, if the destination is able to be 
                    // reached by the piece in one move, and if there are peices around it.
void is_L_shaped(); // checks if the move entered for a knight is L shaped

/***************************************************************************************************************************
 ******************************************************** GLOBALS ***********************************************************
 ***************************************************************************************************************************/
char Board[8][8] = {
'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 
'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}; // capital letters resemble black pieces and lower case letter resemble white pieces

char move [6] = {'P', 'A', '3'}; // 3 characters (piece, x1, y1, x2, y2) + null terminator
char turn = 'w';
bool legal_move = false;


/***************************************************************************************************************************
 ******************************************************** MAIN ***********************************************************
 ***************************************************************************************************************************/

void main(){

    while (move != '00000'){

        printf ("Enter move: ");
        scanf("%5s", move);
        printf ("you entered: %s\n", move);

        check_turn();
        position_legal();

        print_board(); 

    }
}

void check_turn(){
    if (move[0] != turn){
        printf("Wrong turn");
        legal_move = false;
    }
    else {
        if (turn == 'w')
            turn = 'b';
        else 
            turn = 'w';

        legal_move = true;
    }
}

void position_legal(){
    if (legal_move == true ){

        if (move[0] == 'R' || move[0]=='r'){
            if (move[1] != move[3] || move[2] != move[4]) // if the move is not horizontal or diagronal
                legal_move = false;
        }
        if (move[0] == 'K' || move[0] == 'k'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|

            if (!(deltax == 2 && deltay == 1) || !(deltax == 1 && deltay == 2))
                legal_move = false;
        }
        if (move[0] == 'B' || move[0] == 'b'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|

            if (deltax != deltay)
                legal_move = false;
        }
        if (move[0] == 'K' || move[0] == 'k'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != 1 || deltay != 1)
                legal_move = false;
        }
        if (move[0] == 'Q' || move[0] == 'q'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != deltay || deltax == 0 || deltay == 0)
                legal_move = false;
        }
        if (move[0] == 'P' || move[0] == 'p'){
            int deltax = move[3] - move[1]; // |x1 - x2| - cannot go backwards 
            int deltay = move[4] - move[2]; // |y1 - y2|

            if (move[0] == 'p' && move[1] == 2){ // if it is a white pawn and it has not been moved
                if (!(deltay == 1 || deltay == 2) && deltax != 0)
                    legal_move = false;
            }
            if (move[0] == 'P' && move[1] == 7){ // if it is a black pawn and it has not been moved
                if (!(deltay == -1 || deltay == -2) && deltax != 0)
                    legal_move = false;
            }
        }

        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
            
            }
        }
    }
}

void print_board(){
    printf("  a b c d e f g\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", Board[i][j]);
        }
        printf("\n");
    }
}


