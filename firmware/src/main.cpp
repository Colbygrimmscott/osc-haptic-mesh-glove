#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "config.h"

// Initial setup when turned on
void setup() {
    Wire.begin();
    Serial.begin(115200);
    while (!Serial) delay(10);
    Serial.println("16 channel PWM test");
}

// Scan for I2C devices and output through serial, returns number of devices connected.
void scanSerialDevices(int *numDevices) {
    byte error, address, prevAddress;
    prevAddress = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            Serial.println(address, HEX);
            prevAddress = address;
            (*numDevices)++;
        }
        else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            Serial.println(address, HEX);
        }
    }

    if (*numDevices == 0) {
        Serial.println("No I2C devices found\n");
    }
}



void loop() {
    int numDevices = 0;
    scanSerialDevices(&numDevices);

    Serial.println("----------");
    delay(500);
}