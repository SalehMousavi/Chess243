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
    if ((byte2 == (char)0xAA) && (byte3 == (char)0x00)){
      // mouse inserted; initialize sending of data 
      *(PS2_ptr) = 0xF4;
      mouseCount = 0;
      return;
    }
		if(mouseCount == 3) {
			if(byte1 == 0x8 || byte1 == 0x18 || byte1 == 0x28 || byte1 == 0x38) {
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
			mouseCount = 1;
			
		}
		else {
			mouseBuffer = ((byte1&0xFF) << 16) + ((byte2&0xFF) << 8) + (byte3&0xFF);
			mouseCount++;
		}
	}
	return;
}
