#include <globals.h>

void getMove(int* MoveRow, int* MoveCol) {
   *(MoveCol) = (int)((mousex - 39) / WIDTH);
   *(MoveRow) = (int)(mousey / HEIGHT);
   return;
}