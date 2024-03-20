#define HEIGHT 30
#define WIDTH 30
#include <globals.h>
#include <typedefs.h>
#include <pieces.h>
#include <numbers.h>

volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;

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

void drawBoard() {
    int x, y;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map(i, j, &x, &y);
            for (int m = 0; m < WIDTH; m++) {
                for (int k = 0; k < HEIGHT; k++) {
                    if((i+j) & 0b1) {
                        plot_pixel(x+m, y+k, 0x0);
                    }
                    else {
                        plot_pixel(x+m, y+k, 0xFFFF);
                    }
                }   
            }
        }
    }
    x = 20;
    for (int i = 0; i < 8; i++) {
        for (int m = 0; m < numberIcons[i].width; m++) {
            for (int k = 0; k < numberIcons[i].height; k++) {
                plot_pixel(x+m, (i*HEIGHT)+k+10, numberIcons[i].img[(k*numberIcons[i].width) + m]);
            }   
        }
    }
}

void wait_for_vsync() {
    *(pixel_ctrl_ptr) = 1;
    int status = (*(pixel_ctrl_ptr +3)) & 0b1;
    //poll status
    while(status) {
        status = (*(pixel_ctrl_ptr +3)) & 0b1;
    }
    //ready to swap
    //swap buffers
}

void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel(x,y,0);
        }
    }
    return;
}

void drawPieces() {
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            drawPiece(i, j, Board[i][j]);
        }
    }
}

//maps rows and columns to top left pixel location
void map(int row, int col, int* x, int* y) {//rows from 0 to 7 and 
    *y = row * HEIGHT;
    *x = 39 + col * WIDTH;
}

void drawPiece(int row, int col, char piece) {
    int x, y, background;
    enum icon iconNum;
    
    map(row, col, &x, &y);
    switch (piece)
    {
    case 'o':
        return;
    break;
    case 'P':
        iconNum = BlackPawn;
    break;
    case 'R':
        iconNum = BlackRook;
    break;
    case 'N':
        iconNum = BlackKnight;
    break;
    case 'B':
        iconNum = BlackBishop;
    break;
    case 'Q':
        iconNum = BlackQueen;
    break;
    case 'K':
        iconNum = BlackKing; 
    break;
    case 'p':
        iconNum = WhitePawn;
    break;
    case 'r':
        iconNum = WhiteRook;
    break;
    case 'n':
        iconNum = WhiteKnight;
    break;
    case 'b':
        iconNum = WhiteBishop;
    break;
    case 'q':
        iconNum = WhiteQueen;
    break;
    case 'k':
        iconNum = WhiteKing; 
    break;
    }
    background = (row + col) & 0b1; //background 1 == white
    for (int i = 0; i < gameIcons[iconNum].width; i++) {
        for(int j = 0; j < gameIcons[iconNum].height; j++) {
            if(background == 0) {
                plot_pixel(x+i, y+j,gameIcons[iconNum].imgW[((j*(gameIcons[iconNum].width))+i)]);
            }
			else {
				plot_pixel(x+i, y+j,gameIcons[iconNum].img[((j*(gameIcons[iconNum].width))+i)]);
			}
        }
    }
}

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
	if(y < 240 && y >= 0 && x >= 0 && x < 320) {
		one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
		*one_pixel_address = line_color;
	}     
}