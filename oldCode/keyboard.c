#include <addressmap.h>

char keyboardInput(void) {
/* Declare volatile pointers to I/O registers (volatile means that IO load
       and store instructions will be used to access these pointer locations,
       instead of regular memory loads and stores) */
	volatile int* PS2_ptr = (int *)PS2_BASE; 
	volatile int* LEDs = (int *)LED_BASE;
	*(LEDs) = 0;
	int PS2_data, RVALID;
	unsigned char byte1 = 0, byte2 = 0, byte3 = 0;
    unsigned char input;
	// PS/2 mouse needs to be reset (must be already plugged in)
	*(PS2_ptr) = 0xFF; // reset
	while (1) {
		PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port 
		RVALID = PS2_data & 0x8000; // extract the RVALID field
		if (RVALID) {
		/* shift the next data byte into the display */
			byte1 = byte2;
			byte2 = byte3;
			byte3 = PS2_data & 0xFF;
            input = decode(byte1, byte2, byte3);
			if ((byte2 == (char)0xAA) && (byte3 == (char)0x00)) // mouse inserted; initialize sending of data 
				*(PS2_ptr) = 0xF4;
		}
	}
}
enum characterindex {
    A,
    B,
    C, 
    D, 
    E,
    F,
    G,
    H,
    characters
};

unsigned char characterCodes [characters][2] = {
    [A] = {"1C"},
    [B] = {"32"},
    [C] = {"21"},
    [D] = {"23"},
    [E] = {"24"},
    [F] = {"2B"},
    [G] = {"34"},
    [H] = {"33"}
};

char decode(byte1, byte2, byte3) {

}