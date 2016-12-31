
float rgb1[3];
float rgb2[3];
float inc[3];

int red, green, blue;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
    randomSeed(analogRead(0));

    for (int i = 0; i < 3; i++) {
        rgb1[i] = 0;
        rgb2[i] = random(256);
    }
}


void loop()
{
    randomSeed(analogRead(0));

    for (int i = 0; i < 3; i++) {
        inc[i] = (rgb1[i] - rgb2[i]) / 256;
    }

    for (int i = 0; i < 256; i++) {
        red = int(rgb1[0]);
        green = int(rgb1[1]);
        blue = int(rgb1[2]);

        analogWrite(redPin, red);
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
        delay(100);

        for (int j = 0; j < 3; j++) {
            rgb1[j] -= inc[j];
        }
    }

    for (int i = 0; i < 3; i++) {
        rgb2[i] = random(556) - 300;
        rgb2[i] = constrain(rgb2[i], 0, 255);
        delay(1000);
    }
}

