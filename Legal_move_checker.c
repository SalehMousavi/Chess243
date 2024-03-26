#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************
 ******************************************************** FUNCTIONS
 ***********************************************************
 ***************************************************************************************************************************/
void print_board();
void print_potential_board();
void check_turn();      // this checks if the turn inputed by the user is valid,
                        // swaps turns if it is
void position_legal();  // this checks if the piece is at the start end
                        // locations are valid, if the destination is able to be
                        // reached by the piece in one move, and if there are
                        // peices around it.
void obstructed_path();  // checks if the piece being moved has other pieces in
                         // its path, if so move is not legal unless its a
                         // knight
bool is_checked(int row, int col);  // this function checks if a player is checked, if it is
                    // then only the moves that block the check are allowed or
                    // if the kind moves out of the checked position and doesnt
                    // enter another checked postion

void update_board(
    int posy,
    int posx);  // this function is called once the move has been cleared
void potential_moves(char piece, int row, int col);

bool check_endgame();
bool is_check_blocker (int row, int col);

/***************************************************************************************************************************
 ******************************************************** GLOBALS*************************************************************
 ***************************************************************************************************************************/
char Board[8][8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 
                    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'q', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'o', 'R', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'p', 'p', 'p', 'p', 'o', 'p', 'p', 'p', 
                    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
// capital resembles black pieces and lower case resembles white pieces

char potential_moves_board[8][8] = {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o'};  // this marks the potential moves

char move[4] = {'P', 'a',
                '3'};  // 5 characters (piece, x1, y1, x2, y2) + null terminator
char turn = 'w';
bool legal_move = true;

int En_passant[3]; // marks the location of En Passant pawn
bool En_passant_enable = false;

bool rw_rook_moved = false;
bool lw_rook_moved = false;
bool rb_rook_moved = false;
bool lb_rook_moved = false;
bool white_king_moved = false;
bool black_king_moved = false;

bool castling_enable = false;

int wk_moves = 0; // used to determien end game
int bk_moves = 0;

/***************************************************************************************************************************
 ******************************************************** MAIN ****************************************************************
 ***************************************************************************************************************************/

int main() {
  char termination[] = "000";

  print_board();
  printf("Enter piece: ");
  scanf("%3s", move);

  while (strcmp(move, termination) != 0) {
    check_turn();
    if (!legal_move) {  // reset if wrong turn
      printf("Enter piece: ");
      scanf("%3s", move);
      legal_move = true;
      continue;
    }

    legal_move = true;  // assume move is legal until proven it is not

    int col = move[1] - 'a';
    int row = move[2] - '1';
    potential_moves(move[0], row, col);  // calculating potential moves

    print_potential_board();  // drawing potential moves

    printf("Enter move: ");  // choosing the move
    scanf("%3s", move);

    update_board(row, col);  // pass location of the piece as argument
    print_board();


    if (turn == 'b'){
      if (is_checked(0, 4)){
        printf("Black king is checked");
        legal_move = false;
      }
    }
    else {
      if (is_checked(7, 4)){
        printf("White king is checked");
        legal_move = false;
      }
    }
    if (!legal_move) {  // if the move was not legal dont switch turns, keep
                        // taking inputs until move is legal
      if (turn == 'w')
        turn = 'b';
      else
        turn = 'w';
    }

    printf("Enter piece: ");
    scanf("%3s", move);
  }
}

void check_turn() {
  if (turn == 'w' && (move[0] == 'p' || move[0] == 'r' || move[0] == 'n' ||
                      move[0] == 'b' || move[0] == 'k' || move[0] == 'q')) {
    // it is white's turn and white is making a move
    turn = 'b';  // switch turns
  } else if (turn == 'b' &&
             (move[0] == 'P' || move[0] == 'R' || move[0] == 'N' ||
              move[0] == 'B' || move[0] == 'K' || move[0] == 'Q')) {
    // black's turn and black is making a move
    turn = 'w';  // switch turns
  } else {
    printf("Wrong turn\n");  // not their turn
    legal_move = false;
  }
}

bool check_endgame(){
  int row;
  int col;
  for(int i =0; i<8; i++){
    for (int j=0; j<8; j++){
      if (turn == 'b' && Board[i][j] == 'k'){
        row = i;
        col = j; // found the king
        potential_moves('k', row, col);
        if (is_checked(row, col) && wk_moves == 0){ // white check mate
          printf("Black wins \n");
          return true;
        }
        if (!is_checked(row, col) && wk_moves == 0){ // draw
          printf("Draw \n");
          return true;
        }
      }
      else if (turn == 'w' && Board[i][j] == 'K'){
        row = i;
        col = j;
        potential_moves('K', row, col);
        if (is_checked(row, col) && bk_moves == 0){ // white check mate
          printf("White wins \n");
          return true;
        }
        if (!is_checked(row, col) && bk_moves == 0){ // draw
          printf("Draw \n");
          return true;
        }
      }
    }
  }
}

/*********************************************************************************************
 **************************************** POTENTIAL MOVES *************************************
 *********************************************************************************************/

void potential_moves(char piece, int row, int col) {
  for (int i = 0; i < 8; i++) {  // erasing old potential moves
    for (int j = 0; j < 8; j++) {
      if (potential_moves_board[i][j] == 'x') 
        potential_moves_board[i][j] = 'o';
    }
  }
  if (Board[row][col] !=
      piece)  // if the piece is not there, no potential moves
    return;

  switch (piece) {
    /******************************************************** PAWNS ***********************************************************/
    case 'p':
      if (Board[row - 1][col] == 'o' && !is_check_blocker(row, col)) {  // if there is no piece in front
        potential_moves_board[row - 1][col] =
            'x';  // mark the potential moves for that piece with x
        if (row == 6 && Board[row-2][col] == 'o')
          potential_moves_board[row - 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row - 1][col - 1] < 90 && Board[row - 1][col - 1] != 'K')  
        potential_moves_board[row - 1][col - 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row - 1][col + 1] < 90 && Board[row - 1][col + 1] != 'K')
        potential_moves_board[row - 1][col + 1] = 'x';

      // En Passant
      if (Board[row][col-1] < 90 && Board[row][col - 1] == 'P'){
        potential_moves_board[row - 1][col - 1] = 'x';

        En_passant_enable = true;
        En_passant[0] = row;
        En_passant[1] = col; // store location of En Passant pawn
      }
      if (Board[row][col+1] < 90 && Board[row][col + 1] == 'P'){
        potential_moves_board[row - 1][col + 1] = 'x';
        
        En_passant_enable = true;
        En_passant[2] = row;
        En_passant[3] = col; // store location of En Passant pawn
      }

      break;

    case 'P':
      if (Board[row + 1][col] == 'o' && !is_check_blocker(row, col)) {  // if there is no piece in front
        potential_moves_board[row + 1][col] = 'x';
        if (row == 1 && Board[row+2][col] == 'o')
          potential_moves_board[row + 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row + 1][col + 1] > 122)  
        potential_moves_board[row + 1][col + 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row + 1][col - 1] > 122)
        potential_moves_board[row + 1][col - 1] = 'x';
      break;

    /******************************************************** ROOKS ***********************************************************/
    case 'r':
    // vertically up
      for (int i = row + 1; (i < 8 && !is_check_blocker(row, col)); i++) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] > 97)
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check vertically down
      for (int i = row - 1; (i >= 0 && !is_check_blocker(row, col)); i--) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] > 97)
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally right
      for (int i = col + 1; (i < 8 && !is_check_blocker(row, col)); i++) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] > 97) {
          if (col == 0 && Board[row][i] == 'k' && !lw_rook_moved && !white_king_moved){
            potential_moves_board[row][i-1] = 'x';
            castling_enable = true;
          }
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally left
      for (int i = col - 1; (i >= 0 && !is_check_blocker(row, col)); i--) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] > 97) {
          if (col == 7 && Board[row][i] == 'k' && !rw_rook_moved && !white_king_moved){
            potential_moves_board[row][i+1] = 'x';
            castling_enable = true;
          }
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }
      break;

    case 'R':
      // vertically up
      for (int i = row + 1; (i < 8 && !is_check_blocker(row, col)); i++) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] < 90)
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check vertically down
      for (int i = row - 1; (i >= 0 && !is_check_blocker(row, col)); i--) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] < 90)
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally right
      for (int i = col + 1; (i < 8 && !is_check_blocker(row, col)); i++) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] < 90) {
          if (col == 0 && Board[row][i] == 'K' && !lb_rook_moved && !black_king_moved){
            potential_moves_board[row][i-1] = 'x';
            castling_enable = true;
          }
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally left
      for (int i = col - 1; (i >= 0 && !is_check_blocker(row, col)); i--) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] < 90) {
          if (col == 7 && Board[row][i] == 'k' && !rb_rook_moved && !black_king_moved){
            potential_moves_board[row][i+1] = 'x';
            castling_enable = true;
          }
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }
      break;

    /******************************************************** KNIGHTS ***********************************************************/
    case 'n':
      
      for (int i=0; (i< 8 && !is_check_blocker(row, col)); i++){
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
      
        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 && ((col + dx[i]) < 8) ))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' || Board[row + dy[i]][col + dx[i]] < 90)          
          potential_moves_board [row + dy[i]][col + dx[i]] = 'x';
      }

    break;

    case 'N':
      for (int i=0; (i< 8 && !is_check_blocker(row, col)); i++){
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 && (col + dx[i]) < 8))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' || Board[row + dy[i]][col + dx[i]] > 97)
          potential_moves_board [row + dy[i]][col + dx[i]] = 'x';
      }

    break;

    /******************************************************** BISHOPS ***********************************************************/
    case 'b':
      // up right
      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col + i] == 'o') {
          potential_moves_board[row + i][col + i] = 'x';
        } else if (Board[row + i][col + i] >= 'a' &&
                   Board[row + i][col + i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col + i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // up left
      for (int i = 1; row + i < 8 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col - i] == 'o') {
          potential_moves_board[row + i][col - i] = 'x';
        } else if (Board[row + i][col - i] >= 'a' &&
                   Board[row + i][col - i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col - i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // Check diagonally down and right
      for (int i = 1; row - i >= 0 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col + i] == 'o') {
          potential_moves_board[row - i][col + i] = 'x';
        } else if (Board[row - i][col + i] >= 'a' &&
                   Board[row - i][col + i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col + i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // Check diagonally down and left
      for (int i = 1; row - i >= 0 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col - i] == 'o') {
          potential_moves_board[row - i][col - i] = 'x';
        } else if (Board[row - i][col - i] >= 'a' &&
                   Board[row - i][col - i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col - i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }
      break;

    case 'B':
      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col + i] == 'o') {
          potential_moves_board[row + i][col + i] = 'x';
        } else if (Board[row + i][col + i] >= 'A' &&
                   Board[row + i][col + i] <= 'Z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col + i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // Check diagonally up and left
      for (int i = 1; row + i < 8 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col - i] == 'o') {
          potential_moves_board[row + i][col - i] = 'x';
        } else if (Board[row + i][col - i] >= 'A' &&
                   Board[row + i][col - i] <= 'Z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col - i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // Check diagonally down and right
      for (int i = 1; row - i >= 0 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col + i] == 'o') {
          potential_moves_board[row - i][col + i] = 'x';
        } else if (Board[row - i][col + i] >= 'A' &&
                   Board[row - i][col + i] <= 'Z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col + i] =
              'x';  // Capture opponent's piece
          break;    // Stop after capturing
        }
      }

      // Check diagonally down and left
      for (int i = 1; row - i >= 0 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col - i] == 'o')
          potential_moves_board[row - i][col - i] = 'x';
        else if (Board[row - i][col - i] >= 'A' &&
                 Board[row - i][col - i] <= 'Z')
          break;  // stop going in that direction once we reach our own piece
        else {
          potential_moves_board[row - i][col - i] =
              'x';  // Capture opponent's piece
          break;    // break after capturing one of their peices
        }
      } 


      break;

    /******************************************************** QUEENS **********************************************************/
    case 'q':

    // HORIZONTAL AND VERTICAL 

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // UP
        if (Board[row - i][col] == 'o') {
          potential_moves_board[row - i][col] = 'x';
        } else if (Board[row - i][col] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // DOWN
        if (Board[row + i][col] == 'o') {
          potential_moves_board[row + i][col] = 'x';
        } else if (Board[row + i][col] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // RIGHT
        if (Board[row][col + i] == 'o') {
          potential_moves_board[row][col + i] = 'x';
        } else if (Board[row - i][col] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // LEFT
        if (Board[row][col - i] == 'o') {
          potential_moves_board[row][col - i] = 'x';
        } else if (Board[row][col - i] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // DIAGONALS
      // diagonal up right
      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col + i] == 'o') {
          potential_moves_board[row + i][col + i] = 'x';
        } else if (Board[row + i][col + i] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonal up left
      for (int i = 1; row + i < 8 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col - i] == 'o') {
          potential_moves_board[row + i][col - i] = 'x';
        } else if (Board[row + i][col - i] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonally down right
      for (int i = 1; row - i >= 0 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col + i] == 'o') {
          potential_moves_board[row - i][col + i] = 'x';
        } else if (Board[row - i][col + i] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonally down  left
      for (int i = 1; row - i >= 0 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col - i] == 'o') {
          potential_moves_board[row - i][col - i] = 'x';
        } else if (Board[row - i][col - i] > 97) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }

    break;

    case 'Q':
     // HORIZONTAL AND VERTICAL 

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // UP
        if (Board[row - i][col] == 'o') {
          potential_moves_board[row - i][col] = 'x';
        } else if (Board[row - i][col] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // DOWN
        if (Board[row + i][col] == 'o') {
          potential_moves_board[row + i][col] = 'x';
        } else if (Board[row + i][col] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // RIGHT
        if (Board[row][col + i] == 'o') {
          potential_moves_board[row][col + i] = 'x';
        } else if (Board[row - i][col] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) { // LEFT
        if (Board[row][col - i] == 'o') {
          potential_moves_board[row][col - i] = 'x';
        } else if (Board[row][col - i] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // DIAGONALS

      // diagonal up right
      for (int i = 1; row + i < 8 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col + i] == 'o') {
          potential_moves_board[row + i][col + i] = 'x';
        } else if (Board[row + i][col + i] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonal up left
      for (int i = 1; row + i < 8 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row + i][col - i] == 'o') {
          potential_moves_board[row + i][col - i] = 'x';
        } else if (Board[row + i][col - i] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row + i][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonally down right
      for (int i = 1; row - i >= 0 && col + i < 8 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col + i] == 'o') {
          potential_moves_board[row - i][col + i] = 'x';
        } else if (Board[row - i][col + i] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col + i] = 'x';  
          break;    // Stop after capturing
        }
      }

      // diagonally down  left
      for (int i = 1; row - i >= 0 && col - i >= 0 && !is_check_blocker(row, col); i++) {
        if (Board[row - i][col - i] == 'o') {
          potential_moves_board[row - i][col - i] = 'x';
        } else if (Board[row - i][col - i] < 90) {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row - i][col - i] = 'x';  
          break;    // Stop after capturing
        }
      }
    break;

    /******************************************************** KINGS **********************************************************/
    case 'k':
      for (int i=-1; i< 2; i++){
        for (int j = -1; j<2; j++){
          if ((row+i) >= 0 || (row+i) < 8 || (col+j) >= 0 || (col+j) < 8){
            if (Board[row+i][col+j] == 'o' || Board[row+i][col+j] < 90)
              potential_moves_board[row+i][col+j] = 'x';
          }
        }
      }
      break;

    case 'K':
      for (int i=-1; i< 2; i++){
        for (int j = -1; j<2; j++){
          if ((row+i) >= 0 || (row+i) < 8 || (col+j) >= 0 || (col+j) < 8){
            if (Board[row+i][col+j] == 'o' || Board[row+i][col+j] > 97)
              potential_moves_board[row+i][col+j] = 'x';
          }
        }
      }
    break; 

  }
}

// void potential_check_blocker ()

bool is_check_blocker (int row, int col){
  if (Board[row][col] > 97){ // white piece
    for (int i = 0; i <8; i++){
      for (int j = 0; j<8; j++){
        if (Board[i][j] == 'k' && Board[row][col] > 97){
          // found the king
          int dy = row - i; // distance away from the piece
          int dx = col - j;

          if (dx == 0 || dy == 0 || dx == dy || dx == -dy){
            dy = (dy < 0) ? -1 : 1;
            dx = (dx < 0) ? -1 : 1;
            for (int k = 0; (k < 8 && (row + k*dy)<8 && (row + k*dy)>= 0 
            && (col + k*dx)<8 && (col + k*dx) >= 0); k++){
              int posy = row + k*dy;
              int posx = col + k*dx;
              if ((dx == dy || dx == -dy) && 
              (Board[posy][posx] == 'B' || Board[posy][posx] == 'Q')){ // bishop or queen
                return true;
              }
              else if ((dx == 0 || dy == 0) && 
              (Board[posy][posx] == 'R' || Board[posy][posx] == 'Q')){
                return true;
              }
              

            }
            return false;
          } 
          // not in the path to block a check
          return false;
        }
        else if (Board[i][j] == 'K' && Board[row][col] < 90){
          // found the king
          int dy = i - row; // distance away from the piece
          int dx = j - col;

          if (dx == 0 || dy == 0 || dx == dy || dx == -dy){
            dy = (dy < 0) ? -1 : 1;
            dx = (dx < 0) ? -1 : 1;
            for (int k = 1; (k < 8 && (row + k*dy)<8 && (row + k*dy)>= 0 
            && (col + k*dx)<8 && (col + k*dx) >= 0); k++){
              int posy = row + k*dy;
              int posx = col + k*dx;
              if ((dx == dy || dx == -dy) && 
              (Board[posy][posx] == 'b' || Board[posy][posx] == 'q')){ // bishop or queen
                return true;
              }
              else if ((dx == 0 || dy == 0) && 
              (Board[posy][posx] == 'r' || Board[posy][posx] == 'q')){
                return true;
              }
            }
            return false;
          }
          return false;
        }
      }
    }

  }
}




bool is_checked(int row, int col){
  for (int i=-1; i<2 ; i++){
    for (int j=-1; j<2; j++){
      for (int k = 1; j<8; k++){
          int posy = row + (k*i);
          int posx = col + (k*j);

        if (posy < 0 || posy > 7 || posx < 0 || posx > 7)
          break; // stop proceeding if we are out of boands

        if (Board[row][col] > 97){ // white piece
          if (Board[posy][posx] > 97) // blocked by our piece
            break;

          if (abs(i) == 1 && abs(j) == 1 && 
            ((k == 1 && Board[posy][posx] == 'P') || Board[posy][posx] == 'Q'
            || Board[posy][posx] == 'B'))
            // checking diagonal direction
            return true;

          else if ((abs(i) == 0 || abs(j) == 0) && 
            (Board[posy][posx] == 'Q'|| Board[posy][posx] == 'R'))
            // checking horizontal and vertical direction
            return true;
          if (((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)) && 
            Board[posy][posx] == 'N')
            // checking for knights around the king
            return true;
        } 
        else { // black piece
          if (Board[posy][posx] < 90) // blocked by our piece
            break;

          if (abs(i) == 1 && abs(j) == 1 && 
            ((k == 1 && Board[posy][posx] == 'p') || Board[posy][posx] == 'q'
            || Board[posy][posx] == 'b'))
            // checking diagonal direction
            return true;

          else if ((abs(i) == 0 || abs(j) == 0) && 
            (Board[posy][posx] == 'q'|| Board[posy][posx] == 'r'))
            // checking horizontal and vertical direction
            return true;
          if (((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)) && 
            Board[posy][posx] == 'n')
            // checking for knights around the king
            return true;        
        }
        
      }
    }
  }
  return false;
}

void update_board(int posy, int posx) {
  int row = move[2] - '1';
  int col = move[1] - 'a';
  if (potential_moves_board[row][col] !=
      'x') {  // move is not one of the potential moves not legal
    printf("move not legal\n");
    legal_move = false;
    return;
  }
   /********************** EN PASSANT *********************/
  else if (En_passant_enable && row == En_passant[0] && col == En_passant[1])
    Board[posy][posx -1] = 'o'; // elimintate piece
  
  else if (En_passant_enable && row == En_passant[2] && col == En_passant[3])
    Board[posy][posx +1] = 'o';

  /********************** CASTLING *********************/
  else if(castling_enable && col == 3 && move[0] == 'r'){
    Board[7][4] = 'o'; // move the king
    Board[7][2] = 'k';  
    white_king_moved = true;
    castling_enable = false;
  }
  else if(castling_enable && col == 5 && move[0] == 'r' ){
    Board[7][4] = 'o'; // move the king
    Board[7][6] = 'k';  
    white_king_moved = true;
    castling_enable = false;
  }
  else if(castling_enable && col == 3 && move[0] == 'R'){
    Board[0][4] = 'o'; // move the king
    Board[0][2] = 'K';  
    black_king_moved = true;
    castling_enable = false;
  }
  else if(castling_enable && col == 5 && move[0] == 'R'){
    Board[0][4] = 'o'; // move the king
    Board[0][2] = 'K';  
    black_king_moved = true;
    castling_enable = false;
  }
  
  Board[row][col] = move[0];// move piece to the destination
  Board[posy][posx] = 'o';  // set the orignal position to empty - 'o'
}

void print_board() {
  printf("  a b c d e f g h\n");
  for (int i = 0; i < 8; i++) {
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", Board[i][j]);
    }
    printf("\n");
  }
}

void print_potential_board() {
  printf("  a b c d e f g h\n");
  for (int i = 0; i < 8; i++){
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", potential_moves_board[i][j]);
    }
    printf("\n");
  }
}
