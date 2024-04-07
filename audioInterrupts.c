#include <addressmap.h>
#include <control_macros.h>
#include <globals.h>
#include <pieces.h>
#include <typedefs.h>

//so whenever you enter this ISR write a sample
void audio_ISR() {
    const audio*  audio_ptr = (audio*)0xFF203040;

    if (soundType == MOVEsound){
        audio_ptr -> ldata = move_left[soundSampleIndex];
        audio_ptr -> rdata = move_right[soundSampleIndex];
        soundSampleIndex ++;

        if (soundSampleIndex == MoveSongSize)
            resetAudio();
    }
    else if (soundType == CAPTUREsound){
        audio_ptr -> ldata = capture_left[soundSampleIndex];
        audio_ptr -> rdata = capture_right[soundSampleIndex];
        soundSampleIndex++;

        if (soundSampleIndex == CaptureSongSize)
            disableAudio();
    }
    else if(soundType == CHECKsound){
        audio_ptr -> ldata = check_left[soundSampleIndex];
        audio_ptr -> rdata = check_right[soundSampleIndex];
        soundSampleIndex++;

        if (soundSampleIndex == CheckSongSize)
            disableAudio();
    }
}

void enableAudio() {//enable interrupts for audio 
    volatile unsigned int* audioPtr = (int*) AUDIO_BASE;
    *(audioPtr) = 0x2;
}

void disableAudio() {
    *(audioPtr) = 0;
    soundSampleIndex = 0;
}

void resetAudio() {
    volatile unsigned int* audioPtr = (int*) AUDIO_BASE;
    *(audioPtr) = 0x8;//reset fifo
    soundSampleIndex = 0;
}
