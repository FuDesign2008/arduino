
int ledPin = 10;

void setup()
{
    pinMode(ledPin, OUTPUT);
}


void loop()
{
    for (int i = 0; i < 180; i++) {
        float sinVal = sin(i * (PI/180));
        int ledVal = int(sinVal * 255);
        analogWrite(ledPin, ledVal);
        delay(100);
    }

    digitalWrite(ledPin, LOW);
    delay(5000);
}


