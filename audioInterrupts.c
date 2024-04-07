#include <addressmap.h>
#include <control_macros.h>
#include <globals.h>
#include <pieces.h>
#include <typedefs.h>

//so whenever you enter this ISR write a sample
void audio_ISR() {
    audio* const audio_ptr = (audio*)0xFF203040;
    while(audio_ptr->wsrc != 0) {
      if (soundType == MOVEsound){
          audio_ptr -> ldata = move_left[soundSampleIndex];
          audio_ptr -> rdata = move_right[soundSampleIndex];
          soundSampleIndex ++;
          if (soundSampleIndex == MoveSongSize)
              disableAudio();
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
}

void enableAudio() {//enable interrupts for audio 
    volatile audio*  audioPtr = (int*) AUDIO_BASE;
    audioPtr->control = 0b10;//reset fifo
}

void disableAudio() {
    volatile audio*  audioPtr = (int*) AUDIO_BASE;
    audioPtr->control = 0;//reset fifo
    soundSampleIndex = 0;
}

void resetAudio() {
    volatile audio*  audioPtr = (int*) AUDIO_BASE;
    audioPtr->control = 0b1100;//reset fifo
    audioPtr->control = 0;
    soundSampleIndex = 0;
}
