void mouse_ISR();
void plot_pixel(int, int, short int);
void drawPiece(int, int, char);
void drawMouse();
void drawBoard();
void map(int, int, int*, int*);
void the_reset(void) __attribute__((section(".reset")));