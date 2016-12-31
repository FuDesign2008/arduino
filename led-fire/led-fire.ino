
byte ledPins[] = {9, 10, 11};
byte lenPinsLength = 3;

void setup()
{
    for (int i = 0; i < lenPinsLength; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop()
{
    for (int i = 0; i < lenPinsLength; i++) {
        analogWrite(ledPins[i], random(120) + 135);
    }

    delay(random(100));
}


