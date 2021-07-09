#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN         
const byte address[6] = "00001";

bool curr = false; // false if below threshold, true if above threshold
int threshold = 250;

void setup(){
  pinMode(A0, INPUT);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening(); 
}

void loop(){
  int photoValue = analogRead(A0);
  Serial.print(photoValue);
  Serial.print("\n");

  int val = threshold_check(photoValue);

  if (val != 0) {
    radio.write(&val, sizeof(val));
  }
  
  delay(1000); 
}

// return 1 if reading moved below threshold (from good to bad)
// return 0 if no change
// return -1 if reading moved above threshold (from bad to good)
int threshold_check(int reading) {
  if (curr && (reading > threshold)) {
    return -1; 
  } else if (!curr && (reading < threshold)) {
    return 1;
  }
  return 0;
}
