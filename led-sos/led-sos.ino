
int ledPin = 10;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int x=0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  delay(250);

  for (int x=0; x<3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  delay(250);

  for (int x=0; x<3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  delay(5000);
}
