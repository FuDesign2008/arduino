
const int POT_PIN = 0;
const int TRANSISTOR_PIN = 9;
int potValue = 0;

void setup()
{
    pinMode(TRANSISTOR_PIN, OUTPUT);
}

void loop()
{
    potValue = analogRead(POT_PIN) / 4;
    analogWrite(TRANSISTOR_PIN, potValue);
}


