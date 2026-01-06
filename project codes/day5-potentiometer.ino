const int potPin = A0;
const int ledPin = 9;   // MUST be a PWM pin (~)

int potValue = 0;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 1️⃣ Read potentiometer
  potValue = analogRead(potPin);

  // 2️⃣ Map ADC value (0–1023) → PWM (0–255)
  brightness = map(potValue, 0, 1023, 0, 255);

  // 3️⃣ CONTROL BRIGHTNESS 👇 (THIS LINE)
  analogWrite(ledPin, brightness);

  // 4️⃣ Debug output (optional but recommended)
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(10); // smooth updates
}
