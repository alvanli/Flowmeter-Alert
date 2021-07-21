int calib_photores(int photoPin, int cycles, int laser, int t) {
  float sumDim;
  float sumBright;
  // Ambient light
  analogWrite(laser, 0);
  for (int i = 0; i < cycles; i++) {
    sumDim += analogRead(photoPin) / cycles;
    delay(500);
  }
  // Laser light
  analogWrite(laser, 255);
  for (int i = 0; i < cycles; i++) {
    sumBright += analogRead(photoPin) / cycles;
    delay(500);
  }
  analogWrite(laser, 0);
  int threshold = int((sumDim + 4 * sumBright) / 5);
  return threshold;
}

// NOT USING THIS RN
void eval_threshold(int photoPin, int laser, int threshold) {
  int reading = 0;
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      reading = analogRead(photoPin);
      if (reading > threshold) {
        Serial.println("Check " + String(i) + ": Good");
      } else {
        Serial.println("Check " + String(i) + ": Bad");
      }
    } else {
      analogWrite(laser, 255);
      reading = analogRead(photoPin);
      if (reading < threshold) {
        Serial.println("Check " + String(i) + ": Good");
      } else {
        Serial.println("Check " + String(i) + ": Bad");
      }
      analogWrite(laser, 0);
    }
    delay(200);
  }
}

// return -1 if reading moved below threshold (from bad to good)
// return 0 if no change
// return 1 if reading moved above threshold (from good to bad)
int threshold_check(int reading, bool blocked, int threshold) {
  if (!blocked && (reading > threshold)) {
    return 1; 
  } else if (blocked && (reading < threshold)) {
    return -1;
  }
  return 0;
}

// 1 = ball too high, -1 = ball too low, 0 = ball in middle
int getBallLocation(int res1, int res2) {
  if (res1 == 1){
    return 1;
  } else if (res2 == 1){
    return -1;
  }
  return 0;
}