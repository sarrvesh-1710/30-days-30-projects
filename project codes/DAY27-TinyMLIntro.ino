const int lightPin = A0;
const int tempPin = A1;

const int LIGHT_THRESHOLD = 500;
const int TEMP_THRESHOLD = 25;

float readTemperature() {
  int raw = analogRead(tempPin);

  float resistance = 10000.0 * ((1023.0 / raw) - 1.0);

  float tempK = 1.0 / (
    (1.0 / 298.15) +
    (1.0 / 3950.0) * log(resistance / 10000.0)
  );

  float tempC = tempK - 273.15;
  return tempC;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  int lightVal = analogRead(lightPin);
  float tempC = readTemperature();

  bool isBright = lightVal > LIGHT_THRESHOLD;
  bool isWarm   = tempC > TEMP_THRESHOLD;

  Serial.print("Light: ");
  Serial.print(lightVal);
  Serial.print(" | Temp: ");
  Serial.print(tempC);
  Serial.print(" °C → ");

  if (!isWarm && !isBright) Serial.println("Cold & Dark");
  else if (!isWarm && isBright) Serial.println("Cold & Bright");
  else if (isWarm && !isBright) Serial.println("Warm & Dark");
  else Serial.println("Warm & Bright");

  delay(1000);
}