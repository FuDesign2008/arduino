/* project 45 */


#define lockPin 7
#define speakerPin 9
#define tx 3
#define rx 2
#define unlockLength 2000

#include <SoftwareSerial.h>

SoftwareSerial rfidReader = SoftwareSerial(rx, tx);

int users = 3

char* cards[] = {
    "3D00768B53",
    "3D0051C27",
    "3D0029E6BF"
};

char* names[] = {
    "Tom Smith",
    "Dick Jones",
    "Harry Roberts"
};


void setup()
{
    pinMode(lockPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);
    digitalWrite(lockPin, LOW);
    Serial.begin(9600);
    rfidReader.begin(9600);
}


void loop()
{
    char cardNum[10];
    byte cardBytes[6];
    int index = 0;
    byte byteIn = 0;
    byte lastByte = 0;
    byte checksum = 0;

    if (rfidReader.read() == 2) {
        while(index < 12) {
            byteIn = rfidReader.read();
            if (byteIn == 1 || byteIn == 2 || byteIn == 10 || byteIn == 13 ) {
                return;
            }

            if (index < 10) {
                cardNum[index] = byteIn;
            }

            if (byteIn >= '0' && byteIn <= '9') {
                byteIn -= '0';
            } else if ( byteIn >= 'A' && byteIn <= 'F') {
                byteIn = (byteIn + 10) - 'A';
            }

            if ( (index & 1) == 1 ) {
                cardBytes[index/2] = (byteIn | (lastByte << 4));
            }

            if ( index == 12 ) {
                cardNum[10] = '\0';
            }
        }

        Serial.println(cardNum);

        int cardIndex = checkCard(cardNum);

        if (cardIndex >= 0 && cardBytes[5] == checksum) {
            Serial.println("Card validated");
            Serial.println("User: ");
            Serial.println(names[cardIndex]);
            unlock();
            Serial.println();
        }
        else {
            Serial.println("Card INVALID");
            tone(speakerPin, 250, 250);
            delay(250);
            tone(speakerPin, 150, 250);
            Serial.println();
        }
    }
}


int checkCard(char cardNum[10]) {
    for (int i = 0; i < users; i++) {
        if (strcmp(cardNum, cards[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void unlock() {
    tone(speakerPin, 1000, 500);
    digitalWrite(lockPin, HIGH);
    delay(unlockLength);
    digitalWrite(lockPin, LOW);
}









