const int thermistorPin = A0;
const float R0 = 10000.0;     // 10kΩ resistor
const float BETA = 3950.0;    // Typical thermistor value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(thermistorPin);
  float voltage = adcValue * (5.0 / 1023.0);

  float resistance = R0 * (5.0 / voltage - 1.0);

  float tempK = 1.0 / ( (1.0 / 298.15) + (1.0 / BETA) * log(resistance / R0) );
  float tempC = tempK - 273.15;

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  delay(1000);
}