const int sensorPin = A0;
unsigned long lastLogTime = 0;
const unsigned long logInterval = 1000; // 1s

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  if (currentTime - lastLogTime >= logInterval) {
    lastLogTime = currentTime;

    int raw = analogRead(sensorPin);
    float voltage = raw * (5.0/1023.0);

    Serial.print("Time(ms): ");
    Serial.print(currentTime);
    Serial.print(" | Raw: ");
    Serial.print(raw);
    Serial.print(" | Voltage: ");
    Serial.println(voltage, 2);
  }
}
