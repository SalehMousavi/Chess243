#include <pieces.h>
#include <numbers.h>
#include <typedefs.h>
#include <globals.h>

void main(void)
{
    short int moveRow, moveCol;
    char startedMove = 0;
    char startingRow, startingCol;
    char finalRow, finalCol;
    char moveLegal = 0;
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
	char colour = WHITE; 
    setupMouse();
    setupInterrupts();
    while (1)
    {   
        //draw board
		clear_screen();
        drawBoard();
        drawPieces();
        if(startedMove == 1) {
            drawSelection(startingRow, startingCol);
        }
        drawMouse();
        if(mousePressed) {
            getMove(&moveRow, &moveCol); //get the move position
            checkMove(moveRow,moveCol,colour, &moveValid, startedMove); //check if there is a piece in that postion if just starting move
            if(moveValid == 1 && startedMove == 0) {
                startingRow = moveRow;
                startingCol = moveCol;
                startedMove = 1;
            }
            else if(moveValid == 1 && startedMove == 1 && undoMove != 1) {
                finalRow = moveRow;
                finalCol = moveCol;
                checkLegality(startingRow, startingCol, finalRow, finalCol, &moveLegal);
                if(moveLegal) {
                    movePiece(startingRow, startingCol, finalRow, finalCol);
                    colour = colour == WHITE? BLACK: WHITE;//change colour
                    startedMove = 0;
                }
                else {
                    startedMove = 1;
                }
            }
            else if(undoMove == 1 && startedMove == 1) {
                startedMove = 0;
                undoMove = 1;
            }
            mousePressed = 0;
            setupMouse();//enable interrupts from mouse
        }//make sure to enable interrupts for mouse after
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
		pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    	
	}
}