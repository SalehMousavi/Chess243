#ifndef types
#define types
enum icon{
    BlackPawn,
    BlackRook,
    BlackKnight,
    BlackBishop,
    BlackQueen,
    BlackKing,
    WhitePawn,
    WhiteRook,
    WhiteKnight,
    WhiteBishop,
    WhiteQueen,
    WhiteKing
};

typedef struct numbers {//struct to hold the image of each number
    short int width;
    short int height;
    const unsigned short int* img;
}number;


typedef struct piece {//struct to hold the image of each icon, one with white background another with black
    char type;
    short int width;
    short int height;
    const unsigned short int* img;
    const unsigned short int* imgW;
}gamepiece;

#endif