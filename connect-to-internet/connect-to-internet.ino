/* project 46  - page 381*/


#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION  12

float tempC, tempF;
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

Server server(80);

void setup()
{
    Ethernet.begin(mac, ip);
    server.begin();

    sensors.begin();
    sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
    sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
}

void loop()
{
    sensors.requestTemperatures();

    Client client = server.available();
    if (client) {
        boolean BlankLine = true;

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                if ( c == '\n' && BlankLine ) {

                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html\n");
                    client.println("<html><head><meta http-equiv='refresh' content=5/>\n");
                    client.println("<title>Arduino Web Server</title></head>");
                    client.println("<body>")

                    client.println("<h1>Arduino Web Server</h1>")

                    getTemperature(insideThermometer);
                    client.println("<h3>Internal Temperature</h3>");
                    client.println("Temp C:");
                    client.println(tempC);
                    client.println("<br/>");
                    client.println("Temp F:");
                    client.println(tempF);
                    client.println("<br/>");

                    getTemperature(outsideThermometer);
                    client.println("<h3>External Temperature</h3>");
                    client.println("Temp C:");
                    client.println(tempC);
                    client.println("<br/>");
                    client.println("Temp F:");
                    client.println(tempF);
                    client.println("<br/>");

                    client.println("</body></html>")
                    break;
                }

                if ( c == '\n' ) {
                    BlankLine = true;
                }
                else if ( c != '\r' ) {
                    BlankLine = false;
                }
            }
        }

        delay(10);

        client.stop();
    }
}

void getTemperature(DeviceAddress deviceAddress)
{
    tempC = sensors.getTempC(deviceAddress);
    tempF = DallasTemperature::toFahrenheit(tempC);
}









