
int rgbLen = 3;
int ledRgbPin[] = {9, 10, 11};
int veryCold[] = {0x21, 0x56, 0xf0};
int cold[] = {0x04,0x47,0xee};
int fine[] = {0x00, 0xc2, 0x16};
int hot[] = {0xfd, 0x00, 0x02};
int veryHot[] = {0xfb, 0x06, 0x03};



void setup() {

    for (int i = 0; i < rgbLen; i++) {
        pinMode(ledRgbPin[i], OUTPUT);
    }

}


void loop() {
    int sensor = analogRead(0);
    int temp = sensor * 0.09765625;

    if (temp < -10) {
        printColor(veryCold);
    } else if ( temp < 17) {
        printColor(cold);
    } else if (temp < 23) {
        printColor(fine);
    } else if ( temp <40) {
        printColor(hot);
    } else {
        printColor(veryHot);
    }

    delay(1000);
}

void printColor(int rgb[]) {
    for (int i = 0; i < rgbLen; i++) {
        analogWrite(ledRgbPin[i], rgb[i]);
    }
}

