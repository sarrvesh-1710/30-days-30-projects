#define LED_PIN 8
#define BUTTON_PIN 7

byte lastButtonState;
byte ledState = LOW;

unsigned long lastTimeButtonStateChanged = 0;
unsigned long debounceDuration = 50; // milliseconds

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // internal pull-up

  lastButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  if (millis() - lastTimeButtonStateChanged >= debounceDuration) {

    byte buttonState = digitalRead(BUTTON_PIN);

    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;

      // Button pressed (LOW because of INPUT_PULLUP)
      if (buttonState == LOW) {
        ledState = !ledState;   // toggle LED
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
}
