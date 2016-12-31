
byte ledPin[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int ledLength = 10;
int ledDelay = 65;
int currentLed = 0;
int direction = 1;
unsigned long changeTime;

void setup() {
    for (int x = 0; x<10; x++) {
        pinMode(ledPin[x], OUTPUT);
    }

    changeTime = millis();
}


void loop() {

    if ((millis() - changeTime) > ledDelay) {
        changeLed();
        changeTime = millis();
    }

}

void changeLed() {
    for (int i = 0; i < ledLength; i++) {
        digitalWrite(ledPin[i], LOW);
    }
    digitalWrite(ledPin[currentLed], HIGH);

    if (currentLed == 0) {
        direction = 1;
    } else (currentLed == 9) {
        direction = -1;
    }

    currentLed += direction;

}

