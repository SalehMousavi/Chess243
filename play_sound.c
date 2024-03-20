#include <stdio.h>
#include <stdlib.h>

typedef struct audio_reg {
  volatile int control;
  volatile char rarc;
  volatile char ralc;
  volatile char wsrc;
  volatile char wslc;
  volatile int ldata;
  volatile int rdata;
} audio;

void main() {
    audio * const audio_ptr = (audio*)0xFF203040;
    audio_ptr->control = 0b1100;  // set control register to 1100 to clear input and output fifos
    audio_ptr->control = 0x0; // set to zero to allow samples to flow into the fifos

    for (int i = 0; i < sizeof(audio_data); i++) {
        while (audio_ptr->wslc == 0); // loop if no empty output fifo, wait until there is empty ones
        audio_ptr -> ldata = audio_data[i];
        audio_ptr -> rdata = audio_data[i];
        i++;
    }

    // printf("%i", sizeof(audio_data));
} 

