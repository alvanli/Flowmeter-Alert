#include "C:/DATA/Git/Flowmeter-Alert/Code/library/pitches.h"

int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, END
};

boolean alarm_state = true;

unsigned long lastTime = 0;
int currNote = 0;
bool playing = false;

int noteDurations[] = {       //duration of the notes
  2, 2, 2, 2, 1, 2, 2, 1, 2
};

int speed=90; 
int SPEAKER_PIN = A3;

// Does alarm stuff - check time, play, and stop
void alarmCheck() {
  if (alarm_state) {
    if (playing) {
      int noteDuration = speed*noteDurations[currNote]; // set dur
      if ((millis() - lastTime) >= noteDuration) {
        if (melody[currNote + 1] == -1) { // reset vars and stop tone if playing ended
          playing = false; 
          currNote = 0;
          lastTime = millis();
          noTone(SPEAKER_PIN);
        } else { // increment to next note
          currNote += 1;
          noteDuration = speed*noteDurations[currNote];
          lastTime = millis();
        }
      } else { // play tone
        tone(SPEAKER_PIN, melody[currNote]); // this'll constantly send a freq to the pin i hope it doesnt lag
      }
    } else {
      lastTime = millis(); // keep time counter updated when alarm not playing
    }
  } else {
    lastTime = millis(); // keep time counter updated when alarm not playing
    noTone(SPEAKER_PIN); // make sure to turn off if alarm is set to not play
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(SPEAKER_PIN, OUTPUT);
  tone(SPEAKER_PIN, NOTE_G4, 2*90*.95);
  delay(5000);
  noTone(SPEAKER_PIN);
}

int raaa = 0;
void loop() {
  raaa ++ ;
  Serial.println("hey"+String(raaa));
  playing = true;
  alarmCheck();
}
