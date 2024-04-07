
#include <globals.h>
#include <typedefs.h>
#include <pieces.h>
#include <numbers.h>
#include <addressmap.h>

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

    /*x = 20;
    for (int i = 0; i < 8; i++) {
        for (int m = 0; m < numberIcons[i].width; m++) {
            for (int k = 0; k < numberIcons[i].height; k++) {
                plot_pixel(x+m, (i*HEIGHT)+k+10, numberIcons[i].img[(k*numberIcons[i].width) + m]);
            }   
        }
    }*/
}

void drawMouse() {
	if(mousey > 239 || mousey < 0) {
		mousey = 119;
	}
	else if(mousex > 319 || mousex < 0) {
		mousex = 159;
	}
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            plot_pixel(mousex+i, mousey+j, 0x025F);
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
  x += (WIDTH - gameIcons[iconNum].width)/2;
  y += (HEIGHT - gameIcons[iconNum].height)/2;
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

void drawSelection(int Row, int Col, short int boxColour) {
  //draw top bars
  int x = 39 + Col*WIDTH;
  int y = Row*HEIGHT;
  //draw top bars
  for (int i = 0; i < WIDTH; i++) {
      plot_pixel(x+i, y, boxColour);
      plot_pixel(x+i, y+HEIGHT-1, boxColour);
  }
  //draw side bars
  for (int i = 0; i < HEIGHT; i++) {
      plot_pixel(x, y+i, boxColour);
      plot_pixel(x+WIDTH-1, y+i, boxColour);
  }
  return;
}

void drawStartingScreen() {
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 240; j++) {
            plot_pixel(i, j, chessloadingscreen[(j*(320))+i]);
        }
    }
}

void drawWinner() {
  volatile unsigned int* LEDs = (int*) LED_BASE;
  for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 29; j++) {
          if(*LEDs == (int)1 && blackWins[(j*(120))+i] != (short int)0) {
            plot_pixel(i+100, j+100, blackWins[(j*(120))+i]);
          }
          else if(*LEDs == (int)2 && whiteWins[(j*(120))+i] != (short int)0) {
            plot_pixel(i+100, j+100, whiteWins[(j*(120))+i]);
          }
        }
    }
}
