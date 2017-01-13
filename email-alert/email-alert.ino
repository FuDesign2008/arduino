/* project 48 - page 360 */


#include <Ethernet.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define time 10000
#define emailInterval 60
#define HighThreshold 28
#define LowThreshold 10

#define  ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 12


float tempC, tempF;
char message1[35], message2[35];
char subject[] = "ARDUINO: TEMPERATURE ALERT!!\0";
unsigned long lastMessage;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer = { 0x28, 0x44, 0x12, 0xC2, 0x03, 0x00, 0x00, 0x92 };


byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xF7, 0x38 };
byte ip[] = { 192,168,0, 104 };
byte server[] = { 10, 254, 30, 60 }; // Mail server address. Change this to your own mail servers IP.


EthernetClient client;

void sendMail(char subject[], char message1[], char message2, float temp) {
    Serial.println("connecting...");

    if (client.connect(server, 25)) {
        Serial.println("connected");

        client.println("EHLO MYSERVER");
        delay(time);

        client.println("AUTH LOGIN");
        delay(time);

        client.println("lcbWNybbWl2JttnRzLmNvrZSbQ==");
        delay(time);
        client.println("GV0yVGbjLlnZ2VEw");
        delay(time);
        client.println("MAIL FROM:<sales@earthshineelectronics.com>");
        delay(time);
        client.println("RCPT TO:<fred@crunchytoad.com>");
        delay(time);
        client.println("DATA");
        delay(time);
        client.println("From: < sales@earthshineelectronics.com >");
        delay(time);
        client.println("To: < fred@crunchytoad.com >");
        delay(time);
        client.print("SUBJECT: ");
        client.println(subject);
        delay(time);
        delay(time);
        client.println();
        delay(time);
        client.println(message1);
        delay(time);
        client.println(message2);
        delay(time);
        client.print("Temperature: ");
        client.println(temp);
        delay(time);
        client.println(".");
        delay(time);
        client.println("QUIT");
        delay(time);

        Serial.println("Email sent.");
        lastMessage = millis();

    } else {
        Serial.println("Connection failed");
    }
}

void checkMail() {
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }

    if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
    }
}

void getTemperature(deviceAddress) {
    tempC = sensors.getTempC(deviceAddress);
    tempF = DallasTemperature::toFahrenheit(tempC);
}



void setup()
{
    Serial.begin(9600);
    lastMessage = 0;
    Ethernet.begin(mac, ip);

    sensors.begin();
    sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);

    delay(1000);
}

void alert(boolean isHigh) {

    if (isHigh) {
        Serial.println("High Threshold Exceeded");
        char message1[] = "Temperature Sensor\0";
        char message2[] = "High Threshold Exceeded\0";
    } else {
        Serial.println("Low Threshold Exceeded");
        char message1[] = "Temperature Sensor\0";
        char message2[] = "Low Threshold Exceeded\0";
    }

    sendMail(subject, message1, message2, tempC);
}

void loop()
{
    sensors.requestTemperatures();
    getTemperature(insideThermometer);
    Serial.println(tempC);

    if (millis() > (lastMessage + emailInterval * 1000)) {
        if (tempC >= HighThreshold) {
            alert(true);
        } else if (tempC <= LowThreshold) {
            alert(false);
        }
    }

    if (client.available()) {
        checkEmail();
    }
}







