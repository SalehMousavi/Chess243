#include <pieces.h>
#include <numbers.h>
#include <typedefs.h>
#include <globals.h>
#include <addressmap.h>

void main(void)
{
  short int moveRow, moveCol;
  char startedMove = 0;
  char startingRow, startingCol;
  char finalRow, finalCol;
  char moveLegal = 0;
  volatile unsigned int* LEDs = (int*) LED_BASE;
  *(LEDs) = (int)2;
  
  /* set front pixel buffer to Buffer 1 */
  *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = (int) *pixel_ctrl_ptr;
  clear_screen(); // pixel_buffer_start points to the pixel buffer
  char moveValid = 0;
  /* set back pixel buffer to Buffer 2 */
  *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
  pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
  clear_screen(); // pixel_buffer_start points to the pixel buffer
  setupMouse();
  setupTimer();
  setupInterrupts();
  
  while (1) {   
      //draw board
    switch(screenNum){
      case 0: {
        drawStartingScreen();
        drawWinner();
        if(mousePressed) {
          screenNum = 1;
          mousePressed = 0;
          setupMouse();
        }
        break;
      }
      case 1: {
        clear_screen();
        drawBoard();
        drawPieces();
        if(startedMove == 1) {
          drawSelection(startingRow, startingCol, YELLOW);
          for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
              if(stored_moves[i][j] == 'x') {
                drawSelection(i, j, BLUE);
              }
            }
          }
        }
        drawMouse();
        if(mousePressed) {
            getMove(&moveRow, &moveCol); //get the move position
            checkMove(moveRow,moveCol,colour, &moveValid, startedMove); //check if there is a piece in that postion if just starting move
            if(moveValid == 1 && startedMove == 0) {
                startingRow = moveRow;
                startingCol = moveCol;
                startedMove = 1;
                genPotentialMoves(moveRow, moveCol);
            }
            else if(moveValid == 1 && startedMove == 1 && undoMove != 1) {
                finalRow = moveRow;
                finalCol = moveCol;
                checkLegality(finalRow, finalCol, &moveLegal);
                if(moveLegal) {
                  update_board(startingRow, startingCol, finalRow, finalCol);
                  colour = colour == WHITE? BLACK: WHITE;//change colour
                  printf("%d",check_endgame());
                  if(check_endgame() == true) {
                    gameOver = 1;
                    printf("Game is over");
                  }
                  startedMove = 0;
                }
                else {
                  startedMove = 1;
                }
            }
            else if(undoMove == 1 && startedMove == 1) {
                startedMove = 0;
                undoMove = 0;
            }
            mousePressed = 0;
            setupMouse();//enable interrupts from mouse
        }
        if(gameOver == 1) {
          resetGame();
        }
        break;
      }
    }
    //make sure to enable interrupts for mouse after
    wait_for_vsync(); // swap front and back buffers on VGA vertical sync
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer	
	}
}