const int buzzerPin = 9;

const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;

void setup() {
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (digitalRead(btn1)) {
    tone(buzzerPin, 262);  // C
  }
  else if (digitalRead(btn2)) {
    tone(buzzerPin, 330);  // E
  }
  else if (digitalRead(btn3)) {
    tone(buzzerPin, 392);  // G
  }
  else {
    noTone(buzzerPin);
  }
}
