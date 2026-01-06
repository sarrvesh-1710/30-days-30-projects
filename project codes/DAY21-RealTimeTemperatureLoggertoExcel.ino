const int tempPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Time(ms),Temperature(C)");
}

void loop() {
  int raw = analogRead(tempPin);
  float voltage = raw * (5.0 / 1023.0);

  // Adjust if using a different sensor
  float temperatureC = (voltage - 0.5) * 100;

  Serial.print(millis());
  Serial.print(",");
  Serial.println(temperatureC);

  delay(1000); // 1 sample per second
}
