#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>


#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN);
char dataReceived[10];
bool newData = false;


int photo1 = A0;
int photo2 = A1;

int laser1 = A3;
int laser2 = A4;

int waitTime = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  Serial.begin(9600);

  radio.begin();                  //Starting the Wireless communication
  printf_begin();
//  check_radio();
//  analogWrite(laser1,255);
//  analogWrite(laser2,255);
}

void test_photoresistor(String whichResistor){
  if (whichResistor.equals("BOTH") || whichResistor.equals("TOP")){
    Serial.println("Testing Photoresistors");
    Serial.println("Uncovered top resistor: " + String(analogRead(photo1)));
    Serial.println("Please shine laser on top resistor");
    analogWrite(laser1, 255);
    delay(waitTime);
    Serial.println("Laser'd top resistor: " + String(analogRead(photo1)));
    analogWrite(laser1, 0);
    delay(waitTime);
    Serial.println("");
  }
  if (whichResistor.equals("BOTH") || whichResistor.equals("BOTTOM")){
    Serial.println("Uncovered bottom resistor: " + String(analogRead(photo2)));
    Serial.println("Please shine laser on top resistor");
    analogWrite(laser2, 255);
    delay(waitTime);
    Serial.println("Laser'd bottom resistor: " + String(analogRead(photo2)));
    analogWrite(laser2, 0);
    delay(waitTime);
    Serial.println("");
  }
}

void check_radio(){
  radio.printDetails();
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.setDataRate( RF24_250KBPS );
  radio.printDetails();
  delay(waitTime);
}

void loop() {
  test_photoresistor("TOP");
  
}
