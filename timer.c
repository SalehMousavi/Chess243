#include <globals.h>
#include <addressmap.h>
void setupTimer();
void HEX_PS2(char b1, char b2, char b3);
void TIMER_ISR();
void displayTime();



void setupTimer() {//puts 1 second back on the timer
    volatile int * interval_timer_ptr = (int *)TIMER_BASE;
    *(interval_timer_ptr) = 0; // clear the interrupt
    int counter = 100000000; // 1/(50 MHz) x (2500000) = 50 msec
    *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
    *(interval_timer_ptr + 1) = 0x7;//turn on start and CONT

}

void HEX_PS2(char b1, char b2, char b3) {
	volatile int * HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE; 
	volatile int * HEX5_HEX4_ptr = (int *)HEX5_HEX4_BASE;
	unsigned char seven_seg_decode_table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
	0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; 
	unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0}; 
	unsigned int shift_buffer, nibble;
	unsigned char code;
	int i;
	shift_buffer = ((b1&0xFF) << 16) | ((b2&0xFF) << 8) | (b3&0xFF); 
	for (i = 0; i < 6; ++i) {
		nibble = shift_buffer & 0x0000000F; // character is in rightmost nibble 
		code = seven_seg_decode_table[nibble];
		hex_segs[i] = code;
		shift_buffer = shift_buffer >> 4;
	}
    /* drive the hex displays */
	*(HEX3_HEX0_ptr) = *(int *)(hex_segs);
	*(HEX5_HEX4_ptr) = *(int *)(hex_segs + 4); 
}

void timer_ISR() {
    volatile int * interval_timer_ptr = (int *)TIMER_BASE;
    *(interval_timer_ptr) = 0; // clear the interrupt
    if(screenNum == 0) {
		return;
	}
	if(colour == WHITE){
        if(whiteTime == 0) {
			whiteTime = 60*10;
			gameOver = 1;
		}
		whiteTime -= 1;
    }
    else {
		if(blackTime == 0) {
			blackTime = 60*10;
			gameOver = 1;
		}
        blackTime -= 1;
    }
    displayTime();
}

void displayTime() {
    int minutes, secondsTens, seconds;
	if(colour == WHITE) {
		minutes = whiteTime / 60;
		secondsTens = (whiteTime - (minutes*60)) / 10;
		seconds = (whiteTime - (minutes*60) - (secondsTens*10));
	}
	else {
		minutes = blackTime / 60;
		secondsTens = (blackTime - (minutes*60)) / 10;
		seconds = (blackTime - (minutes*60) - (secondsTens*10));
	}
    char byte1, byte2, byte3;
    byte1 = ((minutes&0xF));
    byte2 = ((secondsTens & 0xF) << 4) | (seconds&0xF);
	byte3 = 0;
    HEX_PS2(byte1, byte2, byte3);
    return;
}
