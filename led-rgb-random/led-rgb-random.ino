
/*int redPin = 10;*/
/*int bluePin = 9;*/
/*int greenPin = 8;*/

int ledPins[] = {10, 9, 8};
int ledLen = 3;

void setup()
{
    /*Serial.begin(9600);*/
    randomSeed(analogRead(0));

    for (int i = 0; i < ledLen; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

}

void loop()
{
    for (int i = 0; i < ledLen; i++) {
        int value = random(0, 256);
        analogWrite(ledPins[i], value);
    }

    delay(100);
}


