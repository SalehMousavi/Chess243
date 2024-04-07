#include <globals.h>
#include <addressmap.h>

/***************************************************************************************************************************
 ******************************************************** BACKEND(CHESS LEGALITY) ****************************************************************
 ***************************************************************************************************************************/


void genPotentialMoves(int row, int col) {
  bool king_found = false;
  bool checked = false;
  for (int i = 0; i < 8 && !king_found; i++) {
    for (int j = 0; j < 8 && !king_found; j++) {
      if ((colour == WHITE && Board[i][j] == 'k') || (colour == BLACK && Board[i][j] == 'K')) {
        king_row = i;
        king_col = j;
        king_found = true; // Set the flag to indicate king is found
        potential_moves(Board[row][col], row, col);
        //print_potential_board();
        check_potential_moves(Board[row][col], row, col);
      }
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        stored_moves[i][j] = potential_moves_board[i][j];
        // store orignial potential moves board since it gets changed in check endgame
    }
  }
  //print_stored_moves();
}

bool check_endgame() {
  // if checked, check if the checking path can be blocked or if the checking
  // piece can be captured
  if(!is_checked(king_row, king_col)) {
    return false;
  }
  else if (Board[king_row][king_col] == 'k') {  // whites turn
    find_checking_piece();
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
  else if (Board[king_row][king_col] == 'K') {  // blacks turn
    find_checking_piece();
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
    //print_potential_board();
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (potential_moves_board[i][j] == 'x')
          return false;  // checking to see if the king has any place to go
      }
    }

    return true;  // game over
  }
}


void find_checking_piece() {
  int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
  int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

  if (Board[king_row][king_col] == 'k') {  // whites turn
    for (int i = 0; i < 8; i++) {
      if (king_row + dy[i] < 0 && king_row + dy[i] > 7 &&
          king_col + dx[i] < 0 && king_col + dx[i] > 7)
        continue;  // out of bounds
      if (Board[king_row + dy[i]][king_col + dx[i]] == 'N') {
        checking_piece = 'N';
        return;
      }
    }
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        for (int k = 1;
             (k < 8 && (king_row + k * i) < 8 && (king_row + k * j) >= 0 &&
              (king_col + k * i) < 8 && (king_col + k * j) >= 0);
             k++) {
          int posy = king_row + k * i;
          int posx = king_col + k * j;
          printf("%c \n", Board[posy][posx]);
          if (Board[posy][posx] > a && Board[posy][posx] != 'o')
            break;  // stop progressing when reaching our piece
          if (i == j || i == -j) {
            if (Board[posy][posx] == 'B') {
              checking_piece = 'B';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
            if (Board[posy][posx] == 'Q') {  // bishop or queen
              checking_piece = 'Q';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
          } else if (i == 0 || j == 0) {
            if (Board[posy][posx] == 'R') {
              checking_piece = 'R';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
            if (Board[posy][posx] == 'Q') {
              checking_piece = 'Q';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
          }
        }
      }
    }
  }

  if (Board[king_row][king_col] == 'K') {  // black turn
    for (int i = 0; i < 8; i++) {
      if (king_row + dy[i] < 0 && king_row + dy[i] > 7 &&
          king_col + dx[i] < 0 && king_col + dx[i] > 7)
        continue;  // out of bounds
      if (Board[king_row + dy[i]][king_col + dx[i]] == 'n') {
        checking_piece = 'n';
        return;
      }
    }
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        for (int k = 1;
             (k < 8 && (king_row + k * i) < 8 && (king_row + k * i) >= 0 &&
              (king_col + k * j) < 8 && (king_col + k * j) >= 0);
             k++) {
          int posy = king_row + k * i;
          int posx = king_col + k * j;
          if (Board[posy][posx] < Z)
            break;  // stop progressing when reaching our piece
          if (i == j || i == -j) {
            if (Board[posy][posx] == 'b') {
              checking_piece = 'b';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
            if (Board[posy][posx] == 'q') {  // bishop or queen
              checking_piece = 'q';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
          } else if (i == 0 || j == 0) {
            if (Board[posy][posx] == 'r') {
              checking_piece = 'r';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
            if (Board[posy][posx] == 'q') {
              checking_piece = 'q';
              checking_piece_row = posy;
              checking_piece_col = posx;
              return;
            }
          }
        }
      }
    }

  }
}

bool is_capturable(int row, int col) {  // give location of the checking piece
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Board[i][j] == 'k' || Board[i][j] == 'K' || Board[i][j] == 'o')
        continue;
      if (colour == BLACK && Board[i][j] > a) { // white turn
        // piece captured is black and looking for white pieces
        potential_moves(Board[i][j], i, j);  // find all potential moves for that piece
        if (potential_moves_board[row][col] == 'x')
          return true;

      } else if (colour == WHITE && Board[i][j] < Z) { // blacks turn
        // only check the potential moves for black pieces

        potential_moves(Board[i][j], i, j);  // find all potential moves for that piece
       if (potential_moves_board[row][col] == 'x')
          return true;
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

    /******************************************************** ROOKS ************************************************************/
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

    /******************************************************** KNIGHTS ************************************************************/
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


void check_potential_moves(char piece, int Prow, int Pcol) {  
  // call this only if the player is checked
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (potential_moves_board[i][j] == 'x') {
        char original_piece = Board[i][j];
        Board[i][j] = piece;
        Board[Prow][Pcol] = 'o'; // place move

        if (piece != 'k' && piece != 'K' && is_checked(king_row, king_col))
          potential_moves_board[i][j] = 'o'; // move not legal 
        else if ((piece == 'k' || piece == 'K') && is_checked(i, j)) // piece is not a king
          potential_moves_board[i][j] = 'o';

        Board[i][j] = original_piece; // restore the pieces
        Board[Prow][Pcol] = piece; 
      }
    }
  }
  // if not a check blocker or player is checked do nothing
}

void castling(){
  if (Board[king_row][king_col] == 'k'){
    if (!white_king_moved && !rw_rook_moved && Board[7][5] == 'o' && Board[7][6] == 'o'){
      castling_enable = true;
      potential_moves_board[7][6] = 'x'; }
    else if (!white_king_moved && !lw_rook_moved && Board[7][2] == 'o' && Board[7][3] == 'o' && Board[7][1] == 'o'){
      castling_enable = true;
      potential_moves_board[7][1] = 'x'; }
    else
      castling_enable = false;
  }
  else {
    if (!black_king_moved && !rb_rook_moved && Board[0][5] == 'o' && Board[0][6] == 'o'){
      castling_enable = true;
      potential_moves_board[0][6] = 'x'; }
    else if (!black_king_moved && !lb_rook_moved && Board[0][2] == 'o' && Board[0][3] == 'o' && Board[0][1] == 'o'){
      castling_enable = true;
      potential_moves_board[0][1] = 'x'; }
    else 
      castling_enable = false;
  }
}

bool is_checked(int row, int col) {  // give location of king
  int posy, posx;
  int kingColour = (Board[row][col] == 'K') ? BLACK : WHITE;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      for (int k = 1; k < 8; k++) {
        posy = row + (k * i);
        posx = col + (k * j);
        if (posy < 0 || posy > 7 || posx < 0 || posx > 7)
          break;
        else if(Board[posy][posx] != 'o') {
          if(kingColour == BLACK) {
            if (k == 1 && i == 1 && abs(j) == 1 && Board[posy][posx] == 'p')
              return true;
            else if (abs(i) == abs(j) && (Board[posy][posx] == 'q' || Board[posy][posx] == 'b'))
              // checking diagonal direction
              return true;

            else if ((abs(i) == 0 || abs(j) == 0) &&
                    (Board[posy][posx] == 'q' || Board[posy][posx] == 'r'))
              // checking horizontal and vertical direction
              return true;
            else if (((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)) &&
                Board[posy][posx] == 'n')
              // checking for knights around the king
              return true;
            else
              break;
          }
          else { // white
            if (k == 1 && i == -1 && abs(j) == 1 && Board[posy][posx] == 'P')
            return true;
            else if (abs(i) == abs(j) && (Board[posy][posx] == 'Q' || Board[posy][posx] == 'B'))
            // checking diagonal direction
              return true;

            else if ((abs(i) == 0 || abs(j) == 0) &&
                   (Board[posy][posx] == 'Q' || Board[posy][posx] == 'R'))
            // checking horizontal and vertical direction
              return true;
            else if (((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)) &&
              Board[posy][posx] == 'N')
            // checking for knights around the king
              return true;
            else 
              break;
          }
        }
      }
    }
  }
  return false;
}


void update_board(int posy, int posx, int row, int col) {
  /********************** EN PASSANT *********************/
  if (En_passant_enable && row == En_passant[0] && col == En_passant[1])
    Board[posy][posx -1] = 'o'; // elimintate piece
  
  else if (En_passant_enable && row == En_passant[2] && col == En_passant[3])
    Board[posy][posx +1] = 'o';

  /********************** CASTLING *********************/
   else if (castling_enable && col == 3 && Board[posy][posx] == 'k') {
    Board[7][4] = 'o';  // move the king
    Board[7][2] = 'k';
    Board[7][0] = 'o';
    Board[7][3] = 'r';
    white_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 6 && Board[posy][posx] == 'k') {
    Board[7][4] = 'o';  // move the king
    Board[7][6] = 'k';
    Board[7][7] = 'o';
    Board[7][5] = 'r';
    white_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 3 && Board[posy][posx] == 'K') {
    Board[0][4] = 'o';  // move the king
    Board[0][2] = 'K';
    Board[0][0] = 'o';
    Board[0][3] = 'R';
    black_king_moved = true;
    castling_enable = false;
  } else if (castling_enable && col == 6 && Board[posy][posx] == 'K') {
    Board[0][4] = 'o';  // move the king
    Board[0][6] = 'K';
    Board[0][7] = 'o';
    Board[7][5] = 'R';
    black_king_moved = true;
    castling_enable = false;
  }
  
  Board[row][col] = Board[posy][posx];// move piece to the destination
  Board[posy][posx] = 'o';  // set the orignal position to empty - 'o'
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

void print_stored_moves(){
  printf("  a b c d e f g h\n");
  for (int i = 0; i < 8; i++){
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", stored_moves[i][j]);
    }
    printf("\n");
  }
}

void checkLegality(int finalRow, int finalCol, char* moveLegal) {
   if(stored_moves[finalRow][finalCol] == 'x') {
    *moveLegal = 1;
   }
   else {
    *moveLegal = 0;
   }
    return;
}

void resetGame(){
  volatile unsigned int* LEDs = (int*) LED_BASE;
  char newBoard[8][8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
  'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
  'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
  'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
  'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
  'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
  'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
  'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Board[i][j] = newBoard[i][j];
    }
  }
  //reset the times;
  blackTime = (10*60)-1;
  whiteTime = (10*60)-1;
  if(colour == WHITE) {
    //black won
    *(LEDs) = (int)1;
  }
  else {
    *(LEDs) = (int)2;
  }
  screenNum = 0;

}
