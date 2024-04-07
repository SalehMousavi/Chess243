#include <addressmap.h>
#include <control_macros.h>

void audio_ISR() {
    //so whenever you enter this ISR write a sample
}

void enableAudio() {//enable interrupts for audio 
    volatile unsigned int* audioPtr = (int*) AUDIO_BASE;
    *(audioPtr) = 0x2;
}

void resetAudio() {
    volatile unsigned int* audioPtr = (int*) AUDIO_BASE;
    *(audioPtr) = 0x8;//reset fifo
}