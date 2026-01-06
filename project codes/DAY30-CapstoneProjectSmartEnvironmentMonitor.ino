#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo ventServo;

/* ----- PINS ----- */
const int tempPin = A0;
const int lightPin = A1;
const int buzzerPin = A2;

const int redLED = 2;
const int greenLED = 3;
const int blueLED = 4;

const int motorPin = 5;
const int servoPin = 6;

const int trigPin = 7;
const int echoPin = 8;

/* ----- SYSTEM STATES ----- */
enum SystemState { LOCKED, IDLE, ACTIVE, ALERT };
SystemState state = LOCKED;

/* ----- AUTHORIZED RFID UID (REPLACE WITH YOURS) ----- */
byte authorizedUID[4] = {0x16, 0x5C, 0x25,0x02};

/* ----- SETUP ----- */
void setup() {
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  ventServo.attach(servoPin);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("System Booted - LOCKED");
}

/* ----- MAIN LOOP ----- */
void loop() {
  float temperature = readTemperature();
  int lightLevel = analogRead(lightPin);
  long distance = readDistance();

  checkRFID();

  if (state != LOCKED) {
    if (lightLevel > 500) state = ALERT;
    else if (distance < 30) state = ACTIVE;
    else state = IDLE;
  }

  updateOutputs(lightLevel);

  logData(temperature, lightLevel, distance);

  delay(500);
}

/* ----- SENSOR FUNCTIONS ----- */
float readTemperature() {
  int raw = analogRead(tempPin);
  float voltage = raw * (5.0 / 1023.0);
  return (voltage - 0.5) * 100.0;
}

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

/* ----- RFID CHECK ----- */
void checkRFID() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  bool authorized = true;
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      authorized = false;
      break;
    }
  }

  if (authorized) {
    state = IDLE;
    Serial.println("RFID Authorized");
  } else {
    state = LOCKED;
    Serial.println("RFID Denied");
  }

  rfid.PICC_HaltA();
}

/* ----- OUTPUT CONTROL ----- */
void updateOutputs(int light) {
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(buzzerPin, LOW);

  if (state == LOCKED) {
    digitalWrite(redLED, HIGH);
    ventServo.write(0);
    analogWrite(motorPin, 0);
  }

  else if (state == IDLE) {
    digitalWrite(blueLED, HIGH);
    ventServo.write(20);
    analogWrite(motorPin, 0);
  }

  else if (state == ACTIVE) {
    digitalWrite(greenLED, HIGH);
    ventServo.write(60);
    analogWrite(motorPin, 120);
  }

  else if (state == ALERT) {
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    ventServo.write(90);

    int pwm = map(light, 500, 1023, 100, 255);
    pwm = constrain(pwm, 0, 255);
    analogWrite(motorPin, pwm);
  }
}

/* ----- SERIAL LOGGER ----- */
void logData(float temp, int light, long dist) {
  Serial.print("STATE:");
  Serial.print(state);
  Serial.print(",TEMP:");
  Serial.print(temp);
  Serial.print(",LIGHT:");
  Serial.print(light);
  Serial.print(",DIST:");
  Serial.println(dist);
}
