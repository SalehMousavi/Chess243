#include <addressmap.h>
#include <globals.h>

void setupMouse() {
	volatile int* PS2_ptr = (int *)PS2_BASE; 
	*(PS2_ptr) = 0xFF;
	*(PS2_ptr+1) = 1; //enable interrupt
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

void mouse_ISR() {
	volatile int* PS2_ptr = (int *)PS2_BASE; 
	int PS2_data, RVALID;
	volatile int* LEDs = (int *)LED_BASE;
	char byte1, byte2, byte3;
    byte1 = (char)((mouseBuffer & 0xFF0000) >> 16);
    byte2 = (char)((mouseBuffer & 0xFF00) >> 8);
    byte3 = (char) (mouseBuffer & 0xFF);

	PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port 
	RVALID = PS2_data & 0x8000; // extract the RVALID field
	if (RVALID) {
	/* shift the next data byte into the display */
		byte1 = (char)byte2;
		byte2 = (char)byte3;
		byte3 = (char)(PS2_data & 0x0FF);
		*(LEDs) = ((int)(byte2) & 0x0FF);
		HEX_PS2(byte1, byte2,  byte3);
		*(LEDs) = ((int)(byte1) & 0xFFF);
		if ((byte2 == (char)0xAA) && (byte3 == (char)0x00)) // mouse inserted; initialize sending of data 
			*(PS2_ptr) = 0xF4;
		else if(byte1 == 0x8 || byte1 == 0x18 || byte1 == 0x28 || byte1 == 0x38) {
			if((mousex != 319 || byte2 < 0 )&&(mousex != 0 || byte2 > 0)) {
				mousex += byte2;
			}
			if((mousey != 239 || byte3 > 0 )&&(mousey != 0 || byte3 < 0)) {
				mousey -= byte3;
			}
			mouseBuffer = 0;
		}
		else if(byte1 == 0x9 || byte1 == 0x19 || byte1 == 0x29 || byte1 == 0x39) {
			if((mousex != 319 || byte2 < 0 )&&(mousex != 0 || byte2 > 0)) {
				mousex += byte2;
			}
			if((mousey != 239 || byte3 > 0 )&&(mousey != 0 || byte3 < 0)) {
				mousey -= byte3;
			}
			mousePressed = 1;
			*(PS2_ptr+1) = 0;
			mouseBuffer = 0;
			//move has been selected
		}
		else if(byte1 == 0xA || byte1 == 0x1A || byte1 == 0x2A || byte1 == 0x3A) {
			mousePressed = 1;
			mouseBuffer = 0;
			*(PS2_ptr+1) = 0;
			undoMove = 1;

		}	//for checking if right clicker is pressed in that case reset their move
		else {
			mouseBuffer = ((byte1&0xFF) << 16) + ((byte2&0xFF) << 8) + (byte3&0xFF);
		}
	}
	return;
}