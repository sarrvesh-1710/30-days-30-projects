#include <Servo.h>

Servo panServo;

void setup() {
  // put your setup code here, to run once:
  panServo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Sweep left to right 
  for (int pos = 45; pos <= 135; pos += 2) {
    panServo.write(pos);
    delay(30);
  }

  // Sweep right to left
  for(int pos = 135; pos >= 45; pos -= 2){
    panServo.write(pos);
    delay(30);
  }
}
