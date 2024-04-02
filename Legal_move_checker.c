#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Z 90
#define a 97

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
bool is_check_blocker (char piece, int row, int col);
void piece_is_check_blocker(char piece, int dy, int dx, int row, int col);
// if the piece is a check blocker the moves are limited and must be calculated differently

void potential_moves_indirection(char piece, int dy, int dx, int row, int col);
// finds the potnetial moves in a specific direction;

void check_potential_moves(char piece); // checks if the potential moves are correct

void find_checking_piece ();

bool is_capturable (int row, int col);

/***************************************************************************************************************************
 ******************************************************** GLOBALS *************************************************************
 ***************************************************************************************************************************/
char Board[8][8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 
                    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'b', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'P', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'p', 'o', 'o', 'o', 'o', 'o', 
                    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
                    'q', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
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
char turn = 'b';
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

int king_row;
int king_col;

char checking_piece; // for finding the checking piece
int checking_piece_row;
int checking_piece_col;

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
    
    if (turn == 'b'){ // correcting the potential moves
    for (int i =0; i<8; i++){
      for (int j =0; j<8; j++){
        if (Board[i][j] == 'k'){
          king_row = i;
          king_col = j;

          potential_moves(move[0], row, col);  // calculating potential moves
          print_potential_board();

          if (is_checked(i, j))
            goto found_white_king;
          goto out;
        }
      }
    }
    found_white_king:
      printf("White king is checked\n");
      find_checking_piece();
      check_potential_moves('p');
      
    }
    else { // black turn
      for (int i =0; i<8; i++){
        for (int j =0; j<8; j++){
          if (Board[i][j] == 'K'){
            king_row = i;
            king_col = j;

            potential_moves(move[0], row, col);  // calculating potential moves
            print_potential_board();

            if (is_checked(i, j))
              goto found_king;
            goto out;
          }
        }
      }
      found_king:
      printf("Black king is checked \n");
      find_checking_piece();
      check_potential_moves('P');  
    }
    out: 

    print_potential_board();  // drawing potential moves

    if (check_endgame()){
      printf("Game over, %c wins\n", turn);
      break;
    }


    printf("Enter move: ");  // choosing the move
    scanf("%3s", move);

    update_board(row, col);  // pass location of the piece as argument
    print_board();

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
  // if checked, check if the checking path can be blocked or if the checking piece can be captured
  if (is_checked(king_row, king_col)){
    find_checking_piece();
    if (Board[king_row][king_col]== 'k'){ // whites turn
        if (is_capturable(checking_piece_row, checking_piece_col))
          return false; // checking piece can be captured 
        int dy = king_row - checking_piece_row;
        int dx = king_col - checking_piece_col;

      if (dx != 0)
        dx = (dx < 0) ? -1 : 1;
      if (dy != 0)
        dy = (dy < 0) ? -1 : 1;

      for (int k=1; (k<8 && king_row+k*dy < 8 && king_row+k*dy >= 0 
      && king_col+k*dx < 8 && king_col+k*dx >= 0); k++){
        int posy = king_row+k*dy;
        int posx = king_col+k*dx;
        if (is_capturable(posy, posx))
          return false; // checking path can be blocked
      }
      return true; // game over
    
    }
    if (Board[king_row][king_col]== 'K'){ // blacks turn
          if (is_capturable(checking_piece_row, checking_piece_col))
            return false; // checking piece can be captured 
          int dy = king_row - checking_piece_row;
          int dx = king_col - checking_piece_col;

        if (dx != 0)
          dx = (dx < 0) ? -1 : 1;
        if (dy != 0)
          dy = (dy < 0) ? -1 : 1;

        for (int k=1; (k<8 && (king_row+k*dy) < 8 && (king_row+k*dy) >= 0 
        && (king_col+k*dx) < 8 && (king_col+k*dx) >= 0); k++){
          int posy = king_row+k*dy;
          int posx = king_col+k*dx;
          if (is_capturable(posy, posx))
            return false; // checking path can be blocked
        }
        return true; // game over
      
    }
  }
  return false; // if its not checked return false
}

bool is_capturable (int row, int col){
  for(int i =0; i<8; i++){
    for (int j=0; j<8; j++){
      if (Board[i][j] > a && Board[i][j] != 'o'){
        potential_moves(Board[i][j], i, j); // find all potential moves for that piece
        for(int k =0; k<8; k++){
          for (int l=0; l<8; l++){
            if (potential_moves_board[k][l] == 'x' && row == k && col == l)
              return true;
          }
        }
      }
      else if (Board[i][j] < Z){
        potential_moves(Board[i][j], i, j); // find all potential moves for that piece
        for(int k =0; k<8; k++){
          for (int l=0; l<8; l++){
            if (potential_moves_board[k][l] == 'x' && row == k && col == l)
              return true;
          }
        }
      }
    }
  }
  return false;
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
      if (Board[row - 1][col] == 'o' && !is_check_blocker(piece, row, col)) {  // if there is no piece in front
        potential_moves_board[row - 1][col] =
            'x';  // mark the potential moves for that piece with x
        if (row == 6 && Board[row-2][col] == 'o')
          potential_moves_board[row - 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row - 1][col - 1] < Z && Board[row - 1][col - 1] != 'K')  
        potential_moves_board[row - 1][col - 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row - 1][col + 1] < Z && Board[row - 1][col + 1] != 'K')
        potential_moves_board[row - 1][col + 1] = 'x';

      // En Passant
      if (Board[row][col-1] < Z && Board[row][col - 1] == 'P'){
        potential_moves_board[row - 1][col - 1] = 'x';

        En_passant_enable = true;
        En_passant[0] = row;
        En_passant[1] = col; // store location of En Passant pawn
      }
      if (Board[row][col+1] < Z && Board[row][col + 1] == 'P'){
        potential_moves_board[row - 1][col + 1] = 'x';
        
        En_passant_enable = true;
        En_passant[2] = row;
        En_passant[3] = col; // store location of En Passant pawn
      }

      break;

    case 'P':
      if (Board[row + 1][col] == 'o' && !is_check_blocker(piece, row, col)) {  // if there is no piece in front
        potential_moves_board[row + 1][col] = 'x';
        if (row == 1 && Board[row+2][col] == 'o')
          potential_moves_board[row + 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row + 1][col + 1] > a && Board[row + 1][col + 1] != 'o')  
        potential_moves_board[row + 1][col + 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row + 1][col - 1] > a && Board[row + 1][col - 1] != 'o')
        potential_moves_board[row + 1][col - 1] = 'x';
      break;

    /******************************************************** ROOKS ***********************************************************/
    case 'r':
    case 'R':

    for (int i = -1; i<2; i++){
      for (int j = -1; j<2; j++){
        if (i == j || i == -j) // skip all diagonal directions
          continue;
        if (is_check_blocker(piece, row, col)){
          piece_is_check_blocker(piece, -1, -1, row, col);
          continue;
        }        
        potential_moves_indirection(piece, i, j, row, col);
      }
    }
    
    break;

    /******************************************************** KNIGHTS ***********************************************************/
    case 'n':
      
      for (int i=0; (i< 8 && !is_check_blocker(piece, row, col)); i++){
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
      
        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 && ((col + dx[i]) < 8) ))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' || Board[row + dy[i]][col + dx[i]] < Z)          
          potential_moves_board [row + dy[i]][col + dx[i]] = 'x';
      }

    break;

    case 'N':
      for (int i=0; (i< 8 && !is_check_blocker(piece, row, col)); i++){
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 && (col + dx[i]) < 8))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' || Board[row + dy[i]][col + dx[i]] > a)
          potential_moves_board [row + dy[i]][col + dx[i]] = 'x';
      }

    break;

    /******************************************************** BISHOPS ***********************************************************/
    case 'b':
    case 'B':
    for (int i = -1; i<2; i++){
      for (int j = -1; j<2; j++){
        if (i == 0 || j==0) // skip all horizontal and vertical 
          continue;
        if (is_check_blocker(piece, row, col)){
          piece_is_check_blocker(piece, -1, -1, row, col);
          continue;
        }        
        potential_moves_indirection(piece, i, j, row, col);
      }
    }
    break;

    /******************************************************** QUEENS **********************************************************/
    case 'q':
    case 'Q':
    for (int i = -1; i<2; i++){
      for (int j = -1; j<2; j++){
        if (i == 0 && j==0)
          continue;
        if (is_check_blocker(piece, row, col)){
          piece_is_check_blocker(piece, i, j, row, col);
          continue;
        }        
        potential_moves_indirection(piece, i, j, row, col);
      }
    }
    break;

    /******************************************************** KINGS **********************************************************/
    case 'k':
      for (int i=-1; i< 2; i++){
        for (int j = -1; j<2; j++){
          if ((row+i) >= 0 || (row+i) < 8 || (col+j) >= 0 || (col+j) < 8){
            if (Board[row+i][col+j] == 'o' || Board[row+i][col+j] < Z)
              potential_moves_board[row+i][col+j] = 'x';
          }
        }
      }
      break;

    case 'K':
      for (int i=-1; i< 2; i++){
        for (int j = -1; j<2; j++){
          if ((row+i) >= 0 || (row+i) < 8 || (col+j) >= 0 || (col+j) < 8){
            if (Board[row+i][col+j] == 'o' || Board[row+i][col+j] > a)
              potential_moves_board[row+i][col+j] = 'x';
          }
        }
      }
    break; 

  }
}



void piece_is_check_blocker(char piece, int dy, int dx, int row, int col){
  if (is_check_blocker(piece, row+dy, col+dx) || is_check_blocker(piece, row-dy, col-dx)){
    // the checking piece is in this direction 
    for (int k = 1; row + (k*dy) < 8 && row + (k*dy) >= 0 && col + (k*dx) < 8 && col + (k*dx) >=0; k++) {
      int posy = row + (k*dy);
      int posx = col + (k*dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] > a && Board[posy][posx] != 'o') {
        break;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';  
        break;    // Stop after capturing
      }
    }

    for (int k = 1; row - (k*dy) < 8 && row - (k*dy) >= 0 && col - (k*dx) < 8 && col - (k*dx) >=0; k++) {
      int posy = row - (k*dy);
      int posx = col - (k*dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] > a && Board[posy][posx] != 'o') {
        break;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';  
        break;    // Stop after capturing
      }
      
    }
  }
}

void potential_moves_indirection(char piece, int dy, int dx, int row, int col){
  if (piece > a){
    for (int k = 1; row + (k*dy) < 8 && row + (k*dy) >= 0 && col + (k*dx) < 8 && col + (k*dx) >=0; k++) { 
      int posy = row + (k*dy);
      int posx = col + (k*dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] > a) {
        return;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';  
        return;    // Stop after capturing
      }
      
    }
  }
  else if (piece < Z){
    for (int k = 1; row + (k*dy) < 8 && row + (k*dy) >= 0 && col + (k*dx) < 8 && col + (k*dx) >=0; k++) { 
      int posy = row + (k*dy);
      int posx = col + (k*dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] < Z) {
        return;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';  
        return;    // Stop after capturing
      }
      
    }
  }
}


void check_potential_moves(char piece) { // call this only if the player is checked
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (potential_moves_board[i][j] == 'x'){
              if (is_check_blocker(piece, i, j) || Board[i][j] == checking_piece)
                continue;
              potential_moves_board[i][j] = 'o'; 
            }
        }
    }
}

bool is_check_blocker (char piece, int row, int col){
  
  if (Board[king_row][king_col] == 'k' && piece > a){
    // found the king
    int dy = row - king_row; // distance away from the piece
    int dx = col - king_col;

    if (dx == 0 || dy == 0 || dx == dy || dx == -dy){
      if (dx != 0)
        dx = (dx < 0) ? -1 : 1;
      if (dy != 0)
        dy = (dy < 0) ? -1 : 1;

      for (int k = 0; (k < 8 && (king_row + k*dy)<8 && (king_row + k*dy)>= 0 
      && (king_col + k*dx)<8 && (king_col + k*dx) >= 0); k++){
        int posy = king_row + k*dy;
        int posx = king_col + k*dx;
        if(posy != row && posx != col && Board[posy][posx] > a && Board[posy][posx] != 'o')
          return false; // another piece already blocks it
      }

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
  else if (Board[king_row][king_col] == 'K' && piece < Z){
    // found the king
    int dy = row - king_row; // distance away from the piece
    int dx = col - king_col;

    for (int k = 1; (k < 8 && (king_row + k*dy)<8 && (king_row + k*dy)>= 0 
      && (king_col + k*dx)<8 && (king_col + k*dx) >= 0); k++){
        int posy = king_row + k*dy;
        int posx = king_col + k*dx;
        if(posy != row && posx != col && Board[posy][posx] < Z)
          return false; // another piece already blocks it
      }

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

void find_checking_piece (){
  int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
  int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

  if(Board[king_row][king_col] == 'k'){ // whites turn
    for (int i = 0; i<8; i++){
      if (Board[dx[i]][dy[i]] == 'N'){
        checking_piece = 'N';
        return;
      }
    }
    for (int i=-1; i<2; i++){
      for (int j=-1; j<2; j++){
        for (int k = 1; (k < 8 && (king_row + k*i)<8 && (king_row + k*j)>= 0 
        && (king_col + k*i)<8 && (king_col + k*j) >= 0); k++){
          int posy = king_row + k*i;
          int posx = king_col + k*j;
          if (Board[posy][posy] > a && Board[posy][posy] != 'o')
            break; // stop progressing when reaching our piece
          if (dx == i || dx == -j){
            if (Board[posy][posx] == 'B'){
              checking_piece = 'B'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }
            if (Board[posy][posx] == 'Q'){ // bishop or queen
              checking_piece = 'Q'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }
          }
          else if (dx == 0 || dy == 0){
            if (Board[posy][posx] == 'R'){
              checking_piece = 'R'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; } 
            if (Board[posy][posx] == 'Q'){
              checking_piece = 'Q'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }         
          }
        }
      }
    }
  }

  if(Board[king_row][king_col] == 'K'){ // whites turn
    for (int i = 0; i<8; i++){
      if (Board[dx[i]][dy[i]] == 'n'){
        checking_piece = 'n';
        return;
      }
    }
    for (int i=-1; i<2; i++){
      for (int j=-1; j<2; j++){
        for (int k = 1; (k < 8 && (king_row + k*i)<8 && (king_row + k*i)>= 0 
        && (king_col + k*j)<8 && (king_col + k*j) >= 0); k++){
          int posy = king_row + k*i;
          int posx = king_col + k*j;
          if (Board[posy][posx] < Z)
            break; // stop progressing when reaching our piece
          if (i == j || i == -j){
            if (Board[posy][posx] == 'b'){
              checking_piece = 'b'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }
            if (Board[posy][posx] == 'q'){ // bishop or queen
              checking_piece = 'q';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }
          }
          else if (i == 0 || j == 0){
            if (Board[posy][posx] == 'r'){
              checking_piece = 'r'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }
            if (Board[posy][posx] == 'q'){
              checking_piece = 'q'; 
              checking_piece_row = posy;
              checking_piece_col = posx;
              return; }       
          }
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

        if (Board[row][col] > a){ // white piece
          if (Board[posy][posx] > a && Board[posy][posx] != 'o') // blocked by our piece
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
          if (Board[posy][posx] < Z && Board[posy][posy] != 'o') // blocked by our piece
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
