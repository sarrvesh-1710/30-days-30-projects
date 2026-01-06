const int trigPin = 9;
const int echoPin = 8;
const int ledPin = 6;

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int d1 = readDistance();
  delay(50);
  int d2 = readDistance();
  delay(50);
  int d3 = readDistance();

  Serial.print("Readings: ");
  Serial.print(d1); Serial.print(", ");
  Serial.print(d2); Serial.print(", ");
  Serial.println(d3);

  if (d1 - d3 > 15) {
    Serial.println("Gesture: SWIPE IN");
    digitalWrite(ledPin, HIGH);
  }
  else if (d3 - d1 > 15) {
    Serial.println("Gesture: SWIPE OUT");
    digitalWrite(ledPin, LOW);
  }
  else {
    Serial.println("Gesture: NONE");
  }

  delay(300);
}
