int posState = 0;
int prevTrigger = 0; // 1 is top, -1 is bottom

int calib_photores(int photoPin, int cycles, int laser, int t) {
  float sumDim;
  float sumBright;
  // Ambient light
  analogWrite(laser, 0);
  for (int i = 0; i < cycles; i++) {
    sumDim += analogRead(photoPin) / cycles;
    delay(200);
  }
  // Laser light
  analogWrite(laser, 255);
  for (int i = 0; i < cycles; i++) {
    sumBright += analogRead(photoPin) / cycles;
    delay(200);
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

// 1 = ball too high, -1 = ball too low, 0 = ball in middle
int getBallLocation(int res1, int res2, int thresh1, int thresh2) {
  bool topTriggered = res1 < thresh1;
  bool bottomTriggered = res2 < thresh2;
  Serial.println("thresh1-2 "+ String(thresh1) + " " + String(thresh2));
  Serial.println("top-bottom-" + String(topTriggered) + " " + String(bottomTriggered));
  if (topTriggered) return 1;
  if (bottomTriggered) return -1;
  return 0;
  /**
  
  int currTrigger = 0;
  if (topTriggered){
    currTrigger = 1;
  }else if (bottomTriggered){
    currTrigger = -1;
  }else{
    currTrigger = 0;
  }
  if (currTrigger != prevTrigger && currTrigger != 0){
    if (topTriggered && posState == 0){
      posState = 1;
    }else if (topTriggered && posState == 1){
      posState = 0;
    }else if (bottomTriggered && posState == 0){
      posState = -1;
    }else if (bottomTriggered && posState == -1){
      posState = 0;
    }
  }
  return posState;
  **/
}