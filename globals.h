#ifndef global
#define global
#include <typedefs.h>
#include <numbers.h>
#include <pieces.h>

volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
char Board[8][8] = {
'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}; //8x8 gameboard global variable

number numberIcons[8] = {
    {
        .width = 10,
        .height = 23,
        .img = Num1
    },
    {
        .width = 10,
        .height = 18,
        .img = Num2
    },
    {
        .width = 10,
        .height = 18,
        .img = Num3
    },
    {
        .width = 10,
        .height = 16,
        .img = Num4
    },
    {
        .width = 10,
        .height = 19,
        .img = Num5
    },
    {
        .width = 10,
        .height = 17,
        .img = Num6
    },
    {
        .width = 10,
        .height = 17,
        .img = Num7
    },
    {
        .width = 10,
        .height = 17,
        .img = Num8
    }

};

gamepiece gameIcons[12] = {
    [BlackPawn] = {
        .type = 'P',
        .width = 25,
        .height = 30,
        .img = blackPawn,
        .imgW = blackPawnW
    },
    [BlackRook] = {
        .type = 'R',
        .width = 25,
        .height = 27,
        .img = blackRook,
        .imgW = blackRookW
    },
    [BlackKnight] = {
        .type = 'N',
        .width = 25,
        .height = 27,
        .img = blackKnight,
        .imgW = blackKnightW
    },
    [BlackBishop] = {
        .type = 'B',
        .width = 27,
        .height = 27,
        .img = blackBishop,
        .imgW = blackBishopW
    },
    [BlackQueen] = {
        .type = 'Q',
        .width = 29,
        .height = 27,
        .img = blackQueen,
        .imgW = blackQueenW
    },
    [BlackKing] = {
        .type = 'K',
        .width = 27,
        .height = 27,
        .img = blackKing,
        .imgW = blackKingW
    },
    [WhitePawn] = {
        .type = 'p',
        .width = 25,
        .height = 30,
        .img = whitePawn,
        .imgW = whitePawnW
    },
    [WhiteRook] = {
        .type = 'r',
        .width = 25,
        .height = 27,
        .img = whiteRook,
        .imgW = whiteRookW
    },
    [WhiteKnight] = {
        .type = 'n',
        .width = 25,
        .height = 27,
        .img = whiteKnight,
        .imgW = whiteKnightW
    },
    [WhiteBishop] = {
        .type = 'b',
        .width = 25,
        .height = 25,
        .img = whiteBishop,
        .imgW = whiteBishopW
    },
    [WhiteQueen] = {
        .type = 'q',
        .width = 25,
        .height = 23,
        .img = whiteQueen,
        .imgW = whiteQueenW
    },
    [WhiteKing] = {
        .type = 'k',
        .width = 25,
        .height = 25,
        .img = whiteKing,
        .imgW = whiteKingW
    }
};

#endif