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
}







