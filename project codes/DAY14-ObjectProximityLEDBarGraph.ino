const int trig = 9;
const int echo = 10;
int led[] = {2,3,4,5};

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  for (int i = 0; i<4; i++){
    pinMode(led[i], OUTPUT);
  }

  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2;
}


void loop() {
  long distance = getDistance();

  for (int i = 0; i < 4; i++) {
    digitalWrite(led[i], LOW);
  }

  if (distance < 40) digitalWrite(led[0], HIGH);
  if (distance < 30) digitalWrite(led[1], HIGH);
  if (distance < 20) digitalWrite(led[2], HIGH);
  if (distance < 10) digitalWrite(led[3], HIGH);

  delay(100);
}

