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
bool is_checked(int row,
                int col);  // this function checks if a player is checked, if it
                           // is then only the moves that block the check are
                           // allowed or if the kind moves out of the checked
                           // position and doesnt enter another checked postion

void update_board(
    int posy,
    int posx);  // this function is called once the move has been cleared
void potential_moves(char piece, int row, int col);

bool check_endgame();
// if the piece is a check blocker the moves are limited and must be calculated
// differently

void potential_moves_indirection(char piece, int dy, int dx, int row, int col);
// finds the potnetial moves in a specific direction;

void check_potential_moves(char piece, int Prow, int Pcol);  
// checks if the potential moves are correct

bool is_capturable(int row, int col);
void castling();

/***************************************************************************************************************************
 ******************************************************** GLOBALS
 **************************************************************
 ***************************************************************************************************************************/
char Board[8][8] = {'R', 'N', 'B', 'o', 'K', 'B', 'N', 'R', 
                    'P', 'P', 'P', 'P', 'o', 'o', 'o', 'P', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 
                    'p', 'p', 'p', 'q', 'p', 'p', 'p', 'p', 
                    'q', 'n', 'b', 'o', 'k', 'o', 'o', 'r' };
// capital resembles black pieces and lower case resembles white pieces

char potential_moves_board[8][8] = {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o'};  // this marks the potential moves

char stored_moves[8][8];

char move[4] = {'P', 'a',
                '3'};  // 5 characters (piece, x1, y1, x2, y2) + null terminator
char turn = 'b';
bool legal_move = true;

int En_passant[3];  // marks the location of En Passant pawn
bool En_passant_enable = false;

bool rw_rook_moved = false;
bool lw_rook_moved = false;
bool rb_rook_moved = false;
bool lb_rook_moved = false;
bool white_king_moved = false;
bool black_king_moved = false;

bool castling_enable = false;

int wk_moves = 0;  // used to determien end game
int bk_moves = 0;

int king_row;
int king_col;

char checking_piece;  // for finding the checking piece
int checking_piece_row;
int checking_piece_col;

/***************************************************************************************************************************
 ******************************************************** MAIN
 *****************************************************************
 ***************************************************************************************************************************/

int main() {
  char termination[] = "000";

  print_board();
  printf("Enter piece: ");
  scanf("%3s", move);
  bool king_found = false;
  bool checked = false;

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
    king_found = false;

    for (int i = 0; i < 8 && !king_found; i++) {
      for (int j = 0; j < 8 && !king_found; j++) {
        if (turn == 'b' && Board[i][j] == 'k') {
          king_row = i;
          king_col = j;
          king_found = true;

          potential_moves(move[0], row, col);
          print_potential_board();
          check_potential_moves(move[0], row, col);   
        } 
        else if (turn == 'w' && Board[i][j] == 'K') {
          king_row = i;
          king_col = j;
          king_found = true;

          potential_moves(move[0], row, col);
          print_potential_board();
          check_potential_moves(move[0], row, col);
        }
      }
    }

    print_potential_board();  // drawing potential moves
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        stored_moves[i][j] = potential_moves_board[i][j];
        // store orignial potential moves board since it gets changed in check
        // endgame
      }
    }

    if (checked && check_endgame()) {
      printf("Game over, %c wins\n", turn);
      break;
    }

    printf("Enter move: ");  // choosing the move
    scanf("%3s", move);

    update_board(row, col);  // pass location of the piece as argument
    print_board();

    if (!legal_move) turn = (turn == 'w') ? 'b' : 'w';

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

bool check_endgame() {
  // if checked, check if the checking path can be blocked or if the checking
  // piece can be captured
  if (Board[king_row][king_col] == 'k') {  // whites turn
    
    if (is_capturable(checking_piece_row, checking_piece_col))
      return false;  // checking piece can be captured
    int dy = checking_piece_row - king_row;
    int dx = checking_piece_col - king_col;

    if (dx != 0) dx = (dx < 0) ? -1 : 1;
    if (dy != 0) dy = (dy < 0) ? -1 : 1;

    for (int k = 1;
          (k < 8 && king_row + k * dy < 8 && king_row + k * dy >= 0 &&
          king_col + k * dx < 8 && king_col + k * dx >= 0);
          k++) {
      int posy = king_row + k * dy;
      int posx = king_col + k * dx;
      if (is_capturable(posy, posx))
        return false;  // checking path can be blocked
    }
    potential_moves('k', king_row, king_col);
    check_potential_moves('k', king_row, king_col);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (potential_moves_board[i][j] == 'x')
          return false;  // checking to see if the king has any place to go
      }
    }

    return true;  // game over
  }
  if (Board[king_row][king_col] == 'K') {  // blacks turn
    if (is_capturable(checking_piece_row, checking_piece_col))
      return false;  // checking piece can be captured
    int dy = checking_piece_row - king_row;
    int dx = checking_piece_col - king_col;

    if (dx != 0) dx = (dx < 0) ? -1 : 1;
    if (dy != 0) dy = (dy < 0) ? -1 : 1;

    for (int k = 1;
          (k < 8 && (king_row + k * dy) < 8 && (king_row + k * dy) >= 0 &&
          (king_col + k * dx) < 8 && (king_col + k * dx) >= 0);
          k++) {
      int posy = king_row + k * dy;
      int posx = king_col + k * dx;
      if (is_capturable(posy, posx))
        return false;  // checking path can be blocked
    }

    potential_moves('K', king_row, king_col);
    check_potential_moves('K', king_row, king_col);
    print_potential_board();
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (potential_moves_board[i][j] == 'x')
          return false;  // checking to see if the king has any place to go
      }
    }

    return true;  // game over
  }
}

bool is_capturable(int row, int col) {  // give location of the checking piece
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Board[row][col] < Z && Board[i][j] > a && Board[i][j] != 'o') {
        // piece captured is black and looking for white pieces

        potential_moves(Board[i][j], i,
                        j);  // find all potential moves for that piece
        for (int k = 0; k < 8; k++) {
          for (int l = 0; l < 8; l++) {  // search through the potential moves
            if (potential_moves_board[k][l] == 'x' && row == k && col == l)
              return true;
          }
        }
      } else if (Board[row][col] > a && Board[i][j] < Z) {
        // piece captured is white and looking for black pieces

        potential_moves(Board[i][j], i,
                        j);  // find all potential moves for that piece
        for (int k = 0; k < 8; k++) {
          for (int l = 0; l < 8; l++) {
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
 **************************************** POTENTIAL MOVES
 **************************************
 *********************************************************************************************/

void potential_moves(char piece, int row, int col) {
  for (int i = 0; i < 8; i++) {  // erasing old potential moves
    for (int j = 0; j < 8; j++) {
      if (potential_moves_board[i][j] == 'x') potential_moves_board[i][j] = 'o';
    }
  }
  if (Board[row][col] !=
      piece)  // if the piece is not there, no potential moves
    return;

  switch (piece) {
    /******************************************************** PAWNS
     * ***********************************************************/
    case 'p':
      if (Board[row - 1][col] == 'o') {  // if there is no piece in front
        potential_moves_board[row - 1][col] =
            'x';  // mark the potential moves for that piece with x
        if (row == 6 && Board[row - 2][col] == 'o')
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
      if (Board[row][col - 1] < Z && Board[row][col - 1] == 'P') {
        potential_moves_board[row - 1][col - 1] = 'x';

        En_passant_enable = true;
        En_passant[0] = row;
        En_passant[1] = col;  // store location of En Passant pawn
      }
      if (Board[row][col + 1] < Z && Board[row][col + 1] == 'P') {
        potential_moves_board[row - 1][col + 1] = 'x';

        En_passant_enable = true;
        En_passant[2] = row;
        En_passant[3] = col;  // store location of En Passant pawn
      }

      break;

    case 'P':
      if (Board[row + 1][col] == 'o') {  // if there is no piece in front
        potential_moves_board[row + 1][col] = 'x';
        if (row == 1 && Board[row + 2][col] == 'o')
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

    /******************************************************** ROOKS
     * ***********************************************************/
    case 'r':
    case 'R':

      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          if (i == j || i == -j)  // skip all diagonal directions
            continue;
          potential_moves_indirection(piece, i, j, row, col);
        }
      }

      break;

    /******************************************************** KNIGHTS
     * ***********************************************************/
    case 'n':

      for (int i = 0; (i < 8); i++) {
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 &&
              ((col + dx[i]) < 8)))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' ||
            Board[row + dy[i]][col + dx[i]] < Z)
          potential_moves_board[row + dy[i]][col + dx[i]] = 'x';
      }

      break;

    case 'N':
      for (int i = 0; (i < 8); i++) {
        int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

        if (!((row + dy[i]) >= 0 && (row + dy[i]) < 8 && (col + dx[i]) >= 0 &&
              (col + dx[i]) < 8))
          continue;
        if (Board[row + dy[i]][col + dx[i]] == 'o' ||
            Board[row + dy[i]][col + dx[i]] > a)
          potential_moves_board[row + dy[i]][col + dx[i]] = 'x';
      }

      break;

    /******************************************************** BISHOPS
     * ***********************************************************/
    case 'b':
    case 'B':
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          if (i == 0 || j == 0)  // skip all horizontal and vertical
            continue;
          potential_moves_indirection(piece, i, j, row, col);
        }
      }
      break;

    /******************************************************** QUEENS
     ***********************************************************/
    case 'q':
    case 'Q':
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          if (i == 0 && j == 0) continue;
          potential_moves_indirection(piece, i, j, row, col);
        }
      } 
      break;

    /******************************************************** KINGS
     * **********************************************************/
    case 'k':
      for (int i = -1; i < 2 && (row + i) >= 0 && (row + i) < 8; i++) {
        for (int j = -1; j < 2 && (col + j) >= 0 && (col + j) < 8; j++) {
          if ((row + i) < 0 || (row + i) > 7  || (col + j) < 0 || (col + j) > 8)
            continue;
          if ((Board[row + i][col + j] < Z) || Board[row + i][col + j] == 'o')
            potential_moves_board[row + i][col + j] = 'x';
        }
      }
      castling();
      break;

    case 'K':
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          if ((row + i) < 0 || (row + i) > 7  || (col + j) < 0 || (col + j) > 8)
            continue;
          if (Board[row + i][col + j] > a)
            potential_moves_board[row + i][col + j] = 'x';
        }
      }
      castling();
      break;
  }
}




void castling(){
  if (Board[king_row][king_col] == 'k'){
    if (!white_king_moved && !rw_rook_moved){
      castling_enable = true;
      potential_moves_board[7][6] = 'x'; }
    else if (!white_king_moved && !lw_rook_moved){
      castling_enable = true;
      potential_moves_board[7][1] = 'x'; }
    else
      castling_enable = false;
  }
  else {
    if (!black_king_moved && !rb_rook_moved){
      castling_enable = true;
      potential_moves_board[0][6] = 'x'; }
    else if (!black_king_moved && !lb_rook_moved){
      castling_enable = true;
      potential_moves_board[0][1] = 'x'; }
    else 
      castling_enable = false;
  }
}

void potential_moves_indirection(char piece, int dy, int dx, int row, int col) {
  if (piece > a) {
    for (int k = 1; row + (k * dy) < 8 && row + (k * dy) >= 0 &&
                    col + (k * dx) < 8 && col + (k * dx) >= 0;
         k++) {
      int posy = row + (k * dy);
      int posx = col + (k * dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] > a) {
        return;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';
        return;  // Stop after capturing
      }
    }
  } else if (piece < Z) {
    for (int k = 1; row + (k * dy) < 8 && row + (k * dy) >= 0 &&
                    col + (k * dx) < 8 && col + (k * dx) >= 0;
         k++) {
      int posy = row + (k * dy);
      int posx = col + (k * dx);

      if (Board[posy][posx] == 'o') {
        potential_moves_board[posy][posx] = 'x';
      } else if (Board[posy][posx] < Z) {
        return;  // Stop at own piece
      } else {
        potential_moves_board[posy][posx] = 'x';
        return;  // Stop after capturing
      }
    }
  }
}

void check_potential_moves(char piece, int Prow, int Pcol) {  
  // call this only if the player is checked
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (potential_moves_board[i][j] == 'x') {
        char original_piece = Board[i][j];
        Board[i][j] = piece;
        Board[Prow][Pcol] = 'o'; // place move

        if (is_checked(king_row, king_col))
          potential_moves_board[i][j] = 'o'; // move not legal 

        Board[i][j] = original_piece; // restore the pieces
        Board[Prow][Pcol] = piece; 
      }
    }
  }
  // if not a check blocker or player is checked do nothing
}



bool is_checked(int row, int col) {  // give location of king
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      for (int k = 1; k < 8; k++) {
        int posy = row + (k * i);
        int posx = col + (k * j);

        if (posy < 0 || posy > 7 || posx < 0 || posx > 7)
          break;  // stop proceeding if we are out of boands

        if (Board[row][col] > a) {  // white piece
          if (Board[posy][posx] > a &&
              Board[posy][posx] != 'o')  // blocked by our piece
            break;

          if (abs(i) == 1 && abs(j) == 1 &&
              ((k == 1 && Board[posy][posx] == 'P') ||
               Board[posy][posx] == 'Q' || Board[posy][posx] == 'B'))
            // checking diagonal direction
            return true;

          else if ((abs(i) == 0 || abs(j) == 0) &&
                   (Board[posy][posx] == 'Q' || Board[posy][posx] == 'R'))
            // checking horizontal and vertical direction
            return true;
          if (((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)) &&
              Board[posy][posx] == 'N')
            // checking for knights around the king
            return true;
        } else {                      // black piece
          if (Board[posy][posx] < Z)  // blocked by our piece
            break;
          if (abs(i) == 1 && abs(j) == 1 &&
              ((k == 1 && Board[posy][posx] == 'p') ||
               Board[posy][posx] == 'q' || Board[posy][posx] == 'b'))
            // checking diagonal direction
            return true;

          else if ((abs(i) == 0 || abs(j) == 0) &&
                   (Board[posy][posx] == 'q' || Board[posy][posx] == 'r'))
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
  if (stored_moves[row][col] !=
      'x') {  // move is not one of the potential moves not legal
    printf("move not legal\n");
    legal_move = false;
    return;
  }
  /********************** EN PASSANT *********************/
  else if (En_passant_enable && row == En_passant[0] && col == En_passant[1])
    Board[posy][posx - 1] = 'o';  // elimintate piece

  else if (En_passant_enable && row == En_passant[2] && col == En_passant[3])
    Board[posy][posx + 1] = 'o';

  /********************** CASTLING *********************/
  else if (castling_enable && col == 3 && move[0] == 'k') {
    Board[7][4] = 'o';  // move the king
    Board[7][2] = 'k';
    Board[7][0] = 'o';
    Board[7][3] = 'r';
    white_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 6 && move[0] == 'k') {
    Board[7][4] = 'o';  // move the king
    Board[7][6] = 'k';
    Board[7][7] = 'o';
    Board[7][5] = 'r';
    white_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 3 && move[0] == 'K') {
    Board[0][4] = 'o';  // move the king
    Board[0][2] = 'K';
    Board[0][0] = 'o';
    Board[0][3] = 'R';
    black_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 6 && move[0] == 'K') {
    Board[0][4] = 'o';  // move the king
    Board[0][6] = 'K';
    Board[0][7] = 'o';
    Board[0][5] = 'R';
    black_king_moved = true;
    castling_enable = false;
  }

  Board[row][col] = move[0];  // move piece to the destination
  Board[posy][posx] = 'o';    // set the orignal position to empty - 'o'
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
  for (int i = 0; i < 8; i++) {
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", potential_moves_board[i][j]);
    }
    printf("\n");
  }
}
