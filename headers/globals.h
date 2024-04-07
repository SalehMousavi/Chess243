#ifndef global
#include <stdbool.h>
#define global
#define HEIGHT 30
#define WIDTH 30
#define BLACK 0
#define WHITE 1
#define YELLOW 0xFFA0
#define BLUE 0x6D9D
#define Z 90
#define a 97
#define MOVEsound 0
#define CHECKsound 1
#define CAPTUREsound 2
volatile int gameOver = 0;
volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
volatile unsigned int mousex = 159;
volatile unsigned int mousey = 119;
volatile unsigned int mousePressed = 0;//for indicating if mouse was pressed
volatile unsigned int mouseBuffer;
volatile unsigned int undoMove = 0;
volatile unsigned int blackTime = (10*60)-1;
volatile unsigned int whiteTime = (10*60)-1;
volatile char colour = WHITE; 
int screenNum = 0; //0 starting screen 1 game
volatile int soundSampleIndex = 0;//index of sound array
volatile int soundType = MOVEsound;//type of sound being played

char potential_moves_board[8][8] = {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o'};  // this marks the potential moves
char stored_moves[8][8] = {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                                    'o'};  // this marks the potential moves

char move[4] = {'P', 'a', '3'};  // 5 characters (piece, x1, y1, x2, y2) + null terminator
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

char Board[8][8] = {
'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}; //8x8 gameboard global variable

#endif