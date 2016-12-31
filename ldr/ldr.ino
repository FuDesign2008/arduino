
const int PIEZO_PIN = 8;
const int LDR_PIN = 0;
int ldrValue  = 0;

void setup()
{
    // do nothing
}


void loop()
{
    ldrValue = analogRead(LDR_PIN);
    tone(PIEZO_PIN, 1000);
    delay(25);
    noTone(PIEZO_PIN);
    delay(ldrValue);
}

