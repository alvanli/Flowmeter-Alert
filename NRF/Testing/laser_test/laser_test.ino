int laser1 = 6; // with A0
int laser2 = 5; // with A1

void setup() {
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
}

void loop() {
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
}
