const int ldrPin = A0;
const int ledPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightValue = analogRead(ldrPin);
  int brightness = map(lightValue, 0, 1023, 255, 0);
  brightness = constrain(brightness, 0, 255);

  analogWrite(ledPin, brightness);

  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print(" Brightness: ");
  Serial.println(brightness);

  delay(100);
}
