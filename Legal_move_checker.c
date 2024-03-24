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
void if_checked();  // this function checks if a player is checked, if it is
                    // then only the moves that block the check are allowed or
                    // if the kind moves out of the checked position and doesnt
                    // enter another checked postion
void check_blocker();  // this checks if the piece that is being moved is a
                       // check blocker, meaning if moving the piece to another
                       // square would check the player, such pieces are illegal
                       // to move

void update_board(
    int posy,
    int posx);  // this function is called once the move has been cleared
void potential_moves(char piece, int row, int col);

/***************************************************************************************************************************
 ******************************************************** GLOBALS*************************************************************
 ***************************************************************************************************************************/
char Board[8][8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 'P', 'P', 'P',
                    'P', 'P', 'P', 'P', 'P', 'o', 'o', 'o', 'o', 'o', 'o',
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                    'o', 'o', 'o', 'o', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                    'p', 'r', 'n', 'b', 'q', 'k', 'b', 'n', '0'};
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

bool rw_rook_moved = false;
bool lw_rook_moved = false;
bool rb_rook_moved = false;
bool lb_rook_moved = false;
bool white_king_moved = false;
bool black_king_moved = false;

/***************************************************************************************************************************
 ******************************************************** MAIN
 ****************************************************************
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
     * **********************************************************/
    case 'p':
      if (Board[row - 1][col] == 'o') {  // if there is no piece in front
        potential_moves_board[row - 1][col] =
            'x';  // mark the potential moves for that piece with x
        if (row == 6)
          potential_moves_board[row - 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row - 1][col - 1] <
          90)  // corresponds to capital Z, if its a black piece on that square
        potential_moves_board[row - 1][col - 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row - 1][col + 1] < 90)
        potential_moves_board[row - 1][col + 1] = 'x';

      break;

    case 'P':
      if (Board[row + 1][col] == 'o') {  // if there is no piece in front
        potential_moves_board[row + 1][col] = 'x';
        if (row == 1)
          potential_moves_board[row + 2][col] =
              'x';  // if its the first move, then two moves is available
      }
      if (Board[row + 1][col + 1] >
          122)  // lower case z, if white piece on that square
        potential_moves_board[row + 1][col + 1] =
            'x';  // if there are pieces on the diagonals of the pawn they can
                  // be eliminated
      if (Board[row + 1][col - 1] > 122)
        potential_moves_board[row + 1][col - 1] = 'x';
      break;

    /******************************************************** ROOKS
     * **********************************************************/
    case 'r':
      for (int i = row + 1; i < 8; i++) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] >= 'a' && Board[i][col] <= 'z')
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check vertically down
      for (int i = row - 1; i >= 0; i--) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] >= 'a' && Board[i][col] <= 'z')
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally right
      for (int i = col + 1; i < 8; i++) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] >= 'a' && Board[row][i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally left
      for (int i = col - 1; i >= 0; i--) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] >= 'a' && Board[row][i] <= 'z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }
      break;

    case 'R':
      for (int i = row + 1; i < 8; i++) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] >= 'A' && Board[i][col] <= 'Z')
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check vertically down
      for (int i = row - 1; i >= 0; i--) {
        if (Board[i][col] == 'o')
          potential_moves_board[i][col] = 'x';
        else if (Board[i][col] >= 'A' && Board[i][col] <= 'Z')
          break;  // Stop at own piece
        else {
          potential_moves_board[i][col] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally right
      for (int i = col + 1; i < 8; i++) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] >= 'A' && Board[row][i] <= 'Z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }

      // Check horizontally left
      for (int i = col - 1; i >= 0; i--) {
        if (Board[row][i] == 'o') {
          potential_moves_board[row][i] = 'x';
        } else if (Board[row][i] >= 'A' && Board[row][i] <= 'Z') {
          break;  // Stop at own piece
        } else {
          potential_moves_board[row][i] = 'x';  // Capture opponent's piece
          break;                                // Stop after capturing
        }
      }
      break;

    /******************************************************** KNIGHTS ***********************************************************/
    case 'n':
      if (Board[row - 2][col - 1] == 'o' || Board[row - 2][col - 1] < 90)
        potential_moves_board[row-2][col-1] = 'x';
      if (Board[row-1][col-2] == 'o' || Board[row-1][col-2] < 90) // checking every possible 8 potnetial moves for a knight
        potential_moves_board[row-1][col-2] = 'x';
      if (Board[row+1][col-2] == 'o' || Board[row+1][col-2] < 90)
        potential_moves_board[row+1][col-2] = 'x';
      if (Board[row+2][col-1] == 'o' || Board[row+2][col-1] < 90)
        potential_moves_board[row+2][col-1] = 'x';
      if(Board[row+2][col+1] == 'o' || Board[row+2][col+1] < 90)
        potential_moves_board[row+2][col+1] = 'x';
      if (Board[row+1][col+2] == 'o' || Board[row+1][col-2] < 90)
        potential_moves_board[row+1][col+2] = 'x';
      if (Board[row+1][col+2] == 'o' || Board[row+1][col-2] < 90)
        potential_moves_board[row+1][col+2] = 'x';
      if (Board[row-1][col+2] == 'o' || Board[row-1][col-2] < 90)
        potential_moves_board[row-1][col+2] = 'x';
      if (Board[row-2][col+1] == 'o' || Board[row-2][col+1] < 90)
        potential_moves_board[row-2][col+1] = 'x';
        
    break;

    case 'N':
      if (Board[row - 2][col - 1] == 'o' || Board[row - 2][col - 1] > 97)
        potential_moves_board[row-2][col-1] = 'x';
      if (Board[row-1][col-2] == 'o' || Board[row-1][col-2] > 97) // checking every possible 8 potnetial moves for a knight
        potential_moves_board[row-1][col-2] = 'x';
      if (Board[row+1][col-2] == 'o' || Board[row+1][col-2] > 97)
        potential_moves_board[row+1][col-2] = 'x';
      if (Board[row+2][col-1] == 'o' || Board[row+2][col-1] > 97)
        potential_moves_board[row+2][col-1] = 'x';
      if(Board[row+2][col+1] == 'o' || Board[row+2][col+1] > 97)
        potential_moves_board[row+2][col+1] = 'x';
      if (Board[row+1][col+2] == 'o' || Board[row+1][col-2] > 97)
        potential_moves_board[row+1][col+2] = 'x';
      if (Board[row+1][col+2] == 'o' || Board[row+1][col-2] > 97)
        potential_moves_board[row+1][col+2] = 'x';
      if (Board[row-1][col+2] == 'o' || Board[row-1][col-2] > 97)
        potential_moves_board[row-1][col+2] = 'x';
      if (Board[row-2][col+1] == 'o' || Board[row-2][col+1] > 97)
        potential_moves_board[row-2][col+1] = 'x';

    break;

    /******************************************************** BISHOPS
     * **********************************************************/
    case 'b':
      for (int i = 1; row + i < 8 && col + i < 8; i++) {
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

      // Check diagonally up and left
      for (int i = 1; row + i < 8 && col - i >= 0; i++) {
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
      for (int i = 1; row - i >= 0 && col + i < 8; i++) {
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
      for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
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
      for (int i = 1; row + i < 8 && col + i < 8; i++) {
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
      for (int i = 1; row + i < 8 && col - i >= 0; i++) {
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
      for (int i = 1; row - i >= 0 && col + i < 8; i++) {
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
      for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
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

    /******************************************************** QUEENS
     * **********************************************************/
    case 'q':

      break;
    case 'Q':

      break;

    /******************************************************** KINGS
     * **********************************************************/
    case 'k':

      break;
    case 'K':
  }
}

void position_legal() {
  if (legal_move == true) {
    if (move[0] == 'R' || move[0] == 'r') {
      int deltax = abs(move[1] - move[3]);  // |x1 - x2|
      int deltay = abs(move[2] - move[4]);  // |y1 - y2|
      if (deltax == 0 ||
          deltay == 0)  // if the move is not horizontal or vertical
        obstructed_path();
      else {
        legal_move = false;
        return;
      }
    }
    if (move[0] == 'N' || move[0] == 'n') {
      int deltax = abs(move[1] - move[3]);  // |x1 - x2|
      int deltay = abs(move[2] - move[4]);  // |y1 - y2|
      if (!(deltax == 2 && deltay == 1) ||
          !(deltax == 1 && deltay == 2)) {  // if the move is not L shaped
        legal_move = false;
        return;
      }
    }
    if (move[0] == 'B' || move[0] == 'b') {
      int deltax = abs(move[1] - move[3]);  // |x1 - x2|
      int deltay = abs(move[2] - move[4]);  // |y1 - y2|
      if (deltax != deltay) {               // if the move is not diagonal
        legal_move = false;
        return;
      }
    }
    if (move[0] == 'K' || move[0] == 'k') {
      int deltax = abs(move[1] - move[3]);  // |x1 - x2|
      int deltay = abs(move[2] - move[4]);  // |y1 - y2|
      if (deltax != 1 || deltay != 1) {     // move is not by 1 square
        legal_move = false;
        return;
      }
    }
    if (move[0] == 'Q' || move[0] == 'q') {
      int deltax = abs(move[1] - move[3]);  // |x1 - x2|
      int deltay = abs(move[2] - move[4]);  // |y1 - y2|
      if (deltax != deltay || deltax == 0 ||
          deltay == 0) {  // if move is not horitzontal, veritical, or diagonal
        legal_move = false;
        return;
      }
    }
    if (move[0] == 'P' || move[0] == 'p') {
      int deltax = move[3] - move[1];  // |x1 - x2| - cannot go backwards
      int deltay = move[4] - move[2];  // |y1 - y2|

      if (move[0] == 'p') {  // WHITE pawn
        if (move[2] ==
            '7') {  // if it is a white pawn and it has not been moved
          if (!(deltay == 1 || deltay == 2) && deltax != 0) {
            legal_move = false;
            return;
          } else
            obstructed_path();
        } else {
          if (!(deltay == 1) &&
              deltax != 0) {  // if deltay is not 1 and deltax is not zero
            legal_move = false;
            return;
          } else
            obstructed_path();
        }
      }
      if (move[0] == 'P') {  // BLACK pawn
        if (move[1] == 7) {  // if it is a black pawn and it has not been moved
          if (!(deltay == -1 || deltay == -2) && deltax != 0) {
            legal_move = false;
            return;
          } else
            obstructed_path();
        } else {
          if (!(deltay == 1) &&
              deltax != 0) {  // if not the the first move, then one 1 square
                              // moves allowed
            legal_move = false;
            return;
          } else
            obstructed_path();
        }
      }
    }
  }
}

void obstructed_path() {
  int posx = move[1] - 'a';  // positions that we are checking
  int posy = move[2] - '1';

  int deltax = move[3] - move[1];
  int deltay = move[4] - move[2];

  int destinationx = posx + deltax;
  int destinationy = posy + deltay;

  int distancex = abs(deltax);  // the distance of the path in the x direction
  int distancey = abs(deltay);  // the distance in the y direction

  if (deltax > 0)  // setting up the direction of movement
    deltax = 1;
  if (deltax < 0) deltax = -1;
  if (deltay > 0) deltay = 1;
  if (deltay < 0) deltay = -1;

  while (distancex != posx && destinationy != posy) {
    if (Board[posy + deltay][posx + deltax] !=
        'o') {  // posy is the row, posx is the column of the array
      // a piece is in the way, move not legal
      // printf("%c", Board[posx + deltax][posy + deltay]);
      if ((posx + deltay) == destinationx && (posy + deltax) == destinationy) {
        // if the next square is the destination, and a piece is there then it
        // is eliminated
        update_board(destinationx, destinationy);
        return;
      }
      legal_move = false;
      return;
    } else {
      posx += deltax;
      posy += deltay;
    }
  }
  update_board(destinationx, destinationy);
}

void update_board(int posy, int posx) {
  if (potential_moves_board[(move[2] - '1')][(move[1] - 'a')] !=
      'x') {  // move is not one of the potential moves not legal
    printf("move not legal\n");
    legal_move = false;
    return;
  }

  Board[(move[2] - '1')][(move[1] - 'a')] =
      move[0];              // move piece to the destination
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
  for (int i = 0; i < 8; i++) {
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", potential_moves_board[i][j]);
    }
    printf("\n");
  }
}
