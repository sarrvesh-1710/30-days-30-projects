const int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

int notes[] = {262, 294, 330, 349, 392, 440, 494};

void loop() {
  for (int i = 0; i < 7; i++) {
    tone(8, notes[i]);
    delay(300);
  }
  noTone(8);
  delay(1000);
}
