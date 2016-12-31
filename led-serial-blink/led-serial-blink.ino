
char buffer[4];
int bufferLen = sizeof(buffer) / sizeof(tune[0]);
const int LED_PIN = 10;


void setup()
{
    Serial.begin(9600);
    Serial.flush();

    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    if (Serial.available() > 0) {
        delay(100);
        int numChar = Serial.available();
        if (numChar > bufferLen) {
            numChar = bufferLen;
        }

        int index = 0;
        while(numChar--) {
            buffer[index++] = Serial.read();
        }

        setLed(buffer);
    }
}


void setLed(char *data)
{
    Serial.print("Data entered: ");
    Serial.println(data);

    int value = strtol(data, NULL, 10);
    value = map(value, 0, 1000, 0, 255);
    analogWrite(LED_PIN, value);

    for (int i = 0; i < bufferLen; i++) {
      data[i] = '\0';
    }

    Serial.print("Led is write to: ");
    Serial.println(value);
    Serial.flush();
}


