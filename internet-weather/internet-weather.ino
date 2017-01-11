/* project 47 - Page 391 */

#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SHARE_FEED_ID 10722
#define UPDATE_INTERVAL 10000
#define RESET_INTERVAL 10000
#define PACHUBE_API_KEY "xxffssdds"

#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer = {
    0x10,
    0x7A,
    0x3B,
    0xA9,
    0x01,
    0x08,
    0x00,
    0xBF
};


DeviceAddress outsideThermometer = {
    0x10,
    0xCD,
    0x39,
    0xA9,
    0x01,
    0x08,
    0x00,
    0xBE
};

byte mac[] = { 0x48, 0xC2, 0xA1, 0xF3, 0x8D, 0xB7 };
byte ip[] = {192, 168, 0, 104};
byte remoteServer[] = {173, 203, 98, 29}

Client localClient(remoteServer, 80);

unsigned int interval;
char buff[64];
int pointer = 0;
char pachube_data[70];
char *found;
boolean ready_to_update = true;
boolean reading_pachube = false;
boolean request_pause = false;
boolean found_content = false;
unsigned long last_connect;
int content_length;
int tempC, tempF, etempC, etempF;

void setupEthernet() {

    resetEthernetShield();
    delay(500);
    interval = UPDATE_INTERVAL;
    Serial.println("setup complete");
}

void clean_buffer() {
    pointer = 0;
    memset(buff, 0, sizeof(buff));
}

void resetEthernetShield() {
    Serial.println("reset ethernet");
    Ethernet.begin(mac, ip);
}

void pachube_out () {
    getTemperatures();

    if (millis() < last_connect) {
        last_connect = millis();
    }

    if (request_pause) {
        if ((millis () - last_connect) > interval) {
            ready_to_update = true;
            reading_pachube = false;
            request_pause = false;
        }
    }

    if (ready_to_update) {
        Serial.println("Connecting ....");

        if (localClient.connect()) {
            sprintf(pachube_data, "%d, %d, %d, %d", tempC, tempF, etempC, etempF);
            Serial.print("Sending: ");
            Serial.println(pachube_data);
            content_length = strlen(pachube_data);

            Serial.println("Updating.");
            localClient.print("PUT /v1/feeds");
            localClient.print(SHARE_FEED_ID);
            localClient.print(".csv HTTP/1.1\nHost:api.pachube.com\nX-Pachube ApiKey: ");
            localClient.print(PACHUBE_API_KEY);
            localClient.print("\nUser-Agent: Beginning Arduino - Project 47");
            localClient.print("\nContent-Type: text/csv\nContent-Length: ");
            localClient.print(content_length);
            localClient.print("\nConnection: close\n\n");
            localClient.print(pachube_data);
            localClient.print("\n");

            ready_to_update = false;
            reading_pachube = true;
            request_pause = false;
            interval = UPDATE_INTERVAL;
        }
        else {
            Serial.print("connection failed");
            ready_to_update = false;
            reading_pachube = false;
            request_pause = true;
            last_connect = millis();
            interval = RESET_INTERVAL;
            setupEthernet();
        }
    }

    while (reading_pachube) {
        while (localClient.available()) {
            checkForResponse();
        }
        if (!localClient.connected) {
            disconnect_pachube();
        }
    }
}

void disconnect_pachube() {
    Serial.println("disconnecting. \n =========== \n\n");
    localClient.stop();
    ready_to_update = false;
    reading_pachube = false;
    request_pause = true;
    last_connect = millis();
    resetEthernetShield();
}

void checkForResponse{
    char c = localClient.read();
    buff[pointer] = c;

    if (pointer < 64) {
        pointer++;
    }

    if ( c == '\n' ) {
        found = strstr(buff, "200 OK");
        buff[pointer] = 0;
        clean_buffer();
    }
}

void getTemperatures() {
    sensors.requestTemperatures();
    tempC = sensors.getTempC(insideThermometer);
    tempF = DallasTemperature::toFahrenheit(tempC);
    etempC = sensors.getTempC(outsideThermometer);
    etempF = DallasTemperature::toFahrenheit(etempC);
}


void setup()
{
    Serial.begin(57600);
    setupEthernet();
    sensors.begin();
    sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
    sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
}

void loop()
{
    pachube_out();
}







