#include <IRremote.hpp>

const int IR_PIN = 2;
const int ledPin = 9;

enum SystemState { OFF, MODE1, MODE2 };
SystemState currentState = OFF;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;

    if (code == 0xBA45FF00) {        // POWER
      currentState = OFF;
    }
    else if (code == 0xB946FF00) {   // VOL+
      currentState = MODE1;
    }
    else if (code == 0xEA15FF00) {   // VOL-
      currentState = MODE2;
    }

    IrReceiver.resume();
  }

  switch (currentState) {
    case OFF:
      digitalWrite(ledPin, LOW);
      break;

    case MODE1:
      analogWrite(ledPin, 80);
      break;

    case MODE2:
      analogWrite(ledPin, 200);
      break;
  }
}
