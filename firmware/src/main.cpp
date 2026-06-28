#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WifiUdp.h>

#include "config.h"
#include "private.h"
#include "network/network.h"


Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(PWM_ADDR_1);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(PWM_ADDR_2);


EspUdpNetwork espUdpConnection;

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


// Initial setup when turned on
void setup() {
    Wire.begin();
    Serial.begin(115200);
    delay(5000);

    espUdpConnection.connectToWifi(SSID, WIFI_PASS, LOCAL_PORT);

    Serial.println("Serial Device Scan Test:");
    int numDevices = 0;
    scanSerialDevices(&numDevices);

    pwm1.begin();
    pwm1.setPWMFreq(200);

    Serial.println("----------");
    delay(500);
}


void loop() {
    uint8_t hapticMotorCount = 30;
    uint8_t hapticMotorIntensities[hapticMotorCount];

    espUdpConnection.parseIncomingPacket(hapticMotorIntensities, hapticMotorCount);
}