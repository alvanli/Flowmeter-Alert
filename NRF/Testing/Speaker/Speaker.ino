#include "pitches.h"



int speed=90;  //higher value, slower notes
void setup() {

  Serial.begin(9600);

}

int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, NOTE_DS3, NOTE_AS4, NOTE_G4, END
};

// note durations: 8 = quarter note, 4 = 8th note, etc.
int noteDurations[] = {       //duration of the notes
  2, 2, 2, 2, 1, 2, 2, 1, 2
};

void playAlarm(){
  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {
    int noteDuration = speed*noteDurations[thisNote];
    tone(3, melody[thisNote],noteDuration*.95);
    Serial.println(melody[thisNote]);
    
    delay(noteDuration);
    
    noTone(3);
  }
}

void loop() {
// no need to repeat the melody.
}
