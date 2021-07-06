void setup(){
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop(){
  int photoValue = analogRead(A0);
  Serial.print(photoValue);
  Serial.print("\n");
  delay(1000); 
}
