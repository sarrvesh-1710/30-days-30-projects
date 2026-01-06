const int lightPin = A0;
const int alarmPin = 8;


void setup() {
  // put your setup code here, to run once:
  pinMode(alarmPin, OUTPUT);
  Serial.begin(9600);
}

const int threshold = 400;

void loop() {
  int lightValue = analogRead(lightPin);

  if (lightValue < threshold) {
    digitalWrite(alarmPin, HIGH);  // Alarm ON
  } else {
    digitalWrite(alarmPin, LOW);   // Alarm OFF
  }

  delay(100);
}