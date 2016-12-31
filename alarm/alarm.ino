
float sinVal;
int toneVal;
const int TONE_PIN = 8;

void setup()
{
    pinMode(TONE_PIN, OUTPUT);
}


void loop()
{
    for (int i = 0; i < 180; i++) {
        sinVal = sin(x * (PI / 180));
        toneVal = 2000 + int(sinVal * 1000);
        tone(TONE_PIN, toneVal);
        delay(2);
    }
}


