/***************************************************************************************************************************
******************************************************** FUNCTIONS***********************************************************
***************************************************************************************************************************/
#ifndef functiondef
#define functiondef
void main(void);
void interrupt_handler(void); 
void setupMouse();
void setupInterrupts(); 
void movePiece(int startingRow, int startingCol, int finalRow, int finalCol);
void checkLegality(int finalRow, int finalCol, char* moveLegal);
void checkMove(short int moveRow, short int moveCol, char colour, char* moveValid, char startedMove);
void getMove(short int* moveRow, short int* moveCol);
void mouse_ISR(void);
void setupTimer();
void HEX_PS2(char b1, char b2, char b3);
void genPotentialMoves(int row, int col);
void resetGame();
void drawStartingScreen();
void timer_ISR();
void displayTime();
void drawWinner();
void check_turn();      // this checks if the turn inputed by the user is valid,
                // swaps turns if it is
void position_legal();  // this checks if the piece is at the start end
                        // locations are valid, if the destination is able to be
                        // reached by the piece in one move, and if there are
                        // peices around it.
bool is_checked(int row, int col);  // this function checks if a player is checked, if it is
                    // then only the moves that block the check are allowed or
                    // if the kind moves out of the checked position and doesnt
                    // enter another checked postion
void update_board(int posy, int posx, int row, int col);  // this function is called once the move has been cleared
void potential_moves(char piece, int row, int col);

bool check_endgame();

void potential_moves_indirection(char piece, int dy, int dx, int row, int col);
// finds the potnetial moves in a specific direction;

void check_potential_moves(char piece, int Prow, int Pcol); // checks if the potential moves are correct

void castling();

bool is_capturable (int row, int col);

void print_potential_board();
void print_stored_moves();

#endif