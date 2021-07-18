#include "C:/Users/brian/Desktop/Flowmeter-Alert/library/pitches.h"

const int speaker = A3;

unsigned long lastTime = millis();
int currNote = 0;
bool playing = false;

const int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, END
};

// note durations: 8 = quarter note, 4 = 8th note, etc.
const int noteDurations[] = {       //duration of the notes
  2, 2, 2, 2, 1, 2, 2, 1, 2
};

const int speed=90;  //higher value, slower notes

void alarmCheck(bool alarm_state) {
  if (alarm_state) {
    if (playing) {
      int noteDuration = speed*noteDurations[currNote]; // set dur
      if ((millis() - lastTime) >= noteDuration) {
        if (melody[currNote + 1] == -1) { // reset vars and stop tone if playing ended
          playing = false; 
          currNote = 0;
          lastTime = millis();
          noTone(speaker);
        } else { // increment to next note
          currNote += 1;
          noteDuration = speed*noteDurations[currNote];
          lastTime = millis();
        }
      } else { // play tone
        tone(speaker, melody[currNote]); // this'll constantly send a freq to the pin i hope it doesnt lag
      }
    } else {
      lastTime = millis(); // keep time counter updated when alarm not playing
    }
  } else {
    lastTime = millis(); // keep time counter updated when alarm not playing
    noTone(speaker); // make sure to turn off if alarm is set to not play
  }
}