#ifndef global
#define global
volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
volatile unsigned int mousex = 159;
volatile unsigned int mousey = 119;
volatile unsigned int mousePressed = 0;//for indicating if mouse was pressed
volatile unsigned int mouseBuffer;
volatile unsigned int undoMove = 0;
#define HEIGHT 30
#define WIDTH 30
#define BLACK 0
#define WHITE 1
#define YELLOW 0xFFA0
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