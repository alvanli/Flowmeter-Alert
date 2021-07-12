#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

bool tooHigh = false;
bool tooLow = false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop(){
  if (radio.available()){              //Looking for the data.
    int res1 = 0;
    int res2 = 0; //Saving the incoming data
    radio.read(&res1, sizeof(res1));    //Reading the data
    radio.read(&res2, sizeof(res2)); 
    Serial.println("res 1: " + String(res1));
    Serial.println("res 2: " + String(res2));
    getBallLocation(res1, res2);
    Serial.println("Too high?: " + String(tooHigh));
    Serial.println("Too low?: " + String(tooLow));
    if (!tooHigh && !tooLow) {
      Serial.println("Ball is in the center");
    }
    if (tooHigh && tooLow){
      Serial.println("ERROR: ball is too high and too low at the same time");
    }
  }
  delay(5);
}

void getBallLocation(int res1, int res2) {
  if (res1 == 1){
    tooHigh = true;
  }
  if (res2 == 1){
    tooLow = true;
  }
  if (res1 == -1){
    tooHigh = false;
  }
  if (res2 == -1){
    tooLow = false;
  }
}
