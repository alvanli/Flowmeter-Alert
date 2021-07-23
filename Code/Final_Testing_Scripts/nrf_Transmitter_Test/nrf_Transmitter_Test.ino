#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";
long pos = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening(); 

}

void loop() {
  pos += 1;
  radio.write(&pos, sizeof(pos));
  Serial.println("transmitted,"+String(pos)+","+String(millis()));
  delay(5);
}
