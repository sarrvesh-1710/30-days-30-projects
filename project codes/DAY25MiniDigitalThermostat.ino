const int tempPin = A0;
const int controlPin = 9;

const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMPERATURE = 25.0;  // °C
const float BETA_COEFFICIENT = 3950.0;   // common value

const float setPoint = 28.0;
const float Kp = 15.0;

void setup() {
  Serial.begin(9600);
  pinMode(controlPin, OUTPUT);
}

void loop() {
  int adc = analogRead(tempPin);

  float resistance = SERIES_RESISTOR / ((1023.0 / adc) - 1.0);

  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;  
  steinhart = log(steinhart);                   
  steinhart /= BETA_COEFFICIENT;                
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  float temperature = steinhart;

  float error = setPoint - temperature;
  int controlSignal = Kp * error;
  controlSignal = constrain(controlSignal, 0, 255);

  analogWrite(controlPin, controlSignal);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Control: ");
  Serial.println(controlSignal);

  delay(500);
}
