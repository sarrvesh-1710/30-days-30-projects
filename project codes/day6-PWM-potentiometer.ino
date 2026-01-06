const int ledPin = 9;
const int potPin = A0;




void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 900, 0, 225);
  analogWrite(ledPin, brightness);           // PWM output
  delay(10);
}
