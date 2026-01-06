const int motor = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motor, 80); // Low
  delay(2000);

  analogWrite(motor, 150); // Medium
  delay(2000);

  analogWrite(motor, 255); // Full speed
  delay(2000);

  analogWrite(motor, 0);
  delay(2000);
}
