
char buffer[18];
int red, green, blue;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
    Serial.begin(9600);
    Serial.flush();
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop()
{
    if (Serial.available() > 0) {
        int index = 0;
        delay(100);
        int numChar = Serial.available();
        if (numChar > 15) {
            numChar = 15;
        }

        while (numChar--) {
            buffer[index++] = Serial.read();
        }

        splitString(buffer);
    }
}

void splitString(char *data)
{
    Serial.print("Data entered: ");
    Serial.println(data);
    char* parameter;
    parameter = strtok(data, " ,");

    while (parameter != NULL) {
        setLed(parameter);
        parameter = strtok(NULL, " ,");
    }

    for (int i = 0; i < 16; i++) {
        buffer[i] = '\0';
    }

    Serial.flush();
}


void setLed(char* data) {
    Serial.print(data);

    char color = data[0];
    if (color == 'r' || color == 'R') {
        int value = strtol(data + 1, NULL, 10);
        analogWrite(redPin, value);
        Serial.print("Red is set to: ");
        Serial.println(value);
    }

    if (color == 'g' || color == 'G') {
        int value = strtol(data + 1, NULL, 10);
        analogWrite(greenPin, value);
        Serial.print("Green is set to: ");
        Serial.println(value);
    }

    if (color == 'b' || color == 'B') {
        int value = strtol(data + 1, NULL, 10);
        analogWrite(bluePin, value);
        Serial.print("Blue is set to: ");
        Serial.println(value);
    }
}





