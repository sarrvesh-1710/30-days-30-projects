#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 6

MFRC522 rfid(SS_PIN, RST_PIN);

bool systemOn = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);
  Serial.println("Scan RFID card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.println(uid);

  // Example authorized UID (replace with yours)
  if (uid == "165c252") {
    systemOn = !systemOn;
    digitalWrite(LED_PIN, systemOn ? HIGH : LOW);
    Serial.println(systemOn ? "System ON" : "System OFF");
  } else {
    Serial.println("Access Denied");
  }

  rfid.PICC_HaltA();
}
