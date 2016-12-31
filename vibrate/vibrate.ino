const int LED_PIN = 9;
const int PIEZO_PIN = 5;
const int THRESHOLD = 120;
int sensorValue = 0;
float ledHighlight = 0;

void setup()
{
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);

    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
}


void loop()
{
    sensorValue = analogRead(PIEZO_PIN);
    if (sensorValue >= THRESHOLD) {
        ledHighlight = 255;
    }
    analogWrite(LED_PIN, int(ledHighlight));
    ledHighlight -= 0.05;
    if (ledHighlight <=0) {
        ledHighlight = 0;
    }
}

