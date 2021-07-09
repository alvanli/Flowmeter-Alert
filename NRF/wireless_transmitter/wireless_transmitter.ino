#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN         
const byte address[6] = "00001";  //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

void setup() {
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop(){
  int curr_time = millis();
  radio.write(&curr_time, sizeof(curr_time)); //Sending the message to receiver
  delay(1000);
}
