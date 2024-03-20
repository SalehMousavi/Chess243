#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h> 

/***************************************************************************************************************************
 ******************************************************** FUNCTIONS ********************************************************
 ***************************************************************************************************************************/
void print_board(); 
void check_turn(); // this checks if the turn inputed by the user is valid, swaps turns if it is
void position_legal(); // this checks if the piece is at the start end locations are valid, if the destination is able to be 
                    // reached by the piece in one move, and if there are peices around it.
void obstructed_path(); // checks if the piece being moved has other pieces in its path, if so move is not legal unless its a knight
void if_checked(); // this function checks if a player is checked, if it is then only the moves that block the check are allowed or 
                    // if the kind moves out of the checked position and doesnt enter another checked postion
void check_blocker(); // this checks if the piece that is being moved is a check blocker, meaning if moving the piece to another 
                    // square would check the player, such pieces are illegal to move
void update_board(); // this function is called once the move has been cleared

/***************************************************************************************************************************
 ******************************************************** GLOBALS **********************************************************
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

char move [6] = {'P', 'a', '3', 'a', '4'}; // 3 characters (piece, x1, y1, x2, y2) + null terminator
char turn = 'w';
bool legal_move = false;


/***************************************************************************************************************************
 ******************************************************** MAIN *************************************************************
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
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != 0|| deltay != 0){ // if the move is not horizontal or vertical
                legal_move = false;
                return;
            }
        }
        if (move[0] == 'N' || move[0] == 'n'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (!(deltax == 2 && deltay == 1) || !(deltax == 1 && deltay == 2)){ // if the move is not L shaped
                legal_move = false;
                return;
            }
        }
        if (move[0] == 'B' || move[0] == 'b'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != deltay){ // if the move is not diagonal
                legal_move = false;
                return;
            }
        }
        if (move[0] == 'K' || move[0] == 'k'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != 1 || deltay != 1){ // move is not by 1 square
                legal_move = false;
                return;
            }
        }
        if (move[0] == 'Q' || move[0] == 'q'){
            int deltax = abs(move[1] - move[3]); // |x1 - x2|
            int deltay = abs(move[2] - move[4]); // |y1 - y2|
            if (deltax != deltay || deltax == 0 || deltay == 0){ // if move is not horitzontal, veritical, or diagonal
                legal_move = false;
                return;
            }
        }
        if (move[0] == 'P' || move[0] == 'p'){
            int deltax = move[3] - move[1]; // |x1 - x2| - cannot go backwards 
            int deltay = move[4] - move[2]; // |y1 - y2|

            if (move[0] == 'p'){ // WHITE pawn
                if (move[1] == 2 ){ // if it is a white pawn and it has not been moved
                    if (!(deltay == 1 || deltay == 2) && deltax != 0){ 
                        legal_move = false;
                        return;
                    }
                    else 
                        obstructed_path();
                }
                else {
                    if (!(deltay == 1) && deltax != 0){ // if not the the first move, then one 1 square moves allowed
                        legal_move = false;
                        return;
                    }
                    else 
                        obstructed_path();
                }
            }
            if (move[0] == 'P'){ // BLACK pawn
                if (move[1] == 7){ // if it is a black pawn and it has not been moved
                    if (!(deltay == -1 || deltay == -2) && deltax != 0){
                        legal_move = false;
                        return;
                    }
                    else 
                        obstructed_path();
                }
                else {
                    if (!(deltay == 1) && deltax != 0){ // if not the the first move, then one 1 square moves allowed
                        legal_move = false;
                        return;
                    }
                    else 
                        obstructed_path();
                }
            }
        }
    }
}

void obstructed_path(){
    int posx = move[1] - 1; // positions that we are checking
    int posy = move[3] - 1;

    int deltax = move[3] - move[1];
    int deltay = move[4] - move[2];

    int distancex = abs(deltax); // the distance of the path in the x direction
    int distancey = abs(deltay); // the distance in the y direction

    if (deltax > 0) // setting up the direction of movement
        deltax = 1;
    if (deltax < 0)
        deltax = -1;
    if (deltay > 0)
        deltay = 1;
    if (deltay < 0)
        deltay = -1;

   while (distancex != 0 && distancey != 0){
        if (Board[posx + deltax][posy + deltay] != 'o'){ // a piece is in the way, move not legal
            if (posx == move[3] && posy == move[4]) // if there is a piece at the destination, it is eliminated 
                update_board();
            posx += deltax;
            posy + deltay;
            legal_move = false;
            return;
        }
   }
}

void update_board(){
    Board[move[3] - 1][move[4] - 1] = move[0]; // move piece to the destination
    Board[move[1] - 1][move[2] - 1] = 'o'; // set the old square to empty
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


