#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WifiUdp.h>

#include "config.h"
#include "private.h"


WiFiUDP udp;
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(pwm1Address);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(pwm2Address);

struct __attribute__((__packed__)) HapticMotorPacket {
    uint16_t header;
    uint8_t motorPwmVals[30];
};

HapticMotorPacket incomingPacket;


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

    delay(100);

    WiFi.begin(ssid, wifiPassword);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wifi connection established on IP address: ");
    Serial.print(WiFi.localIP());
    udp.begin(glovePort);

    Serial.println("16 channel PWM test");
    int numDevices = 0;
    scanSerialDevices(&numDevices);

    pwm1.begin();
    pwm1.setPWMFreq(200);

    Serial.println("----------");
    delay(500);
}


void loop() {
    int packetSize = udp.parsePacket();
    if (packetSize == sizeof(HapticMotorPacket)) {
        udp.read((char*)&incomingPacket, sizeof(HapticMotorPacket));

        if (incomingPacket.header == 0x03BF) {
            Serial.println("Packet received");
        }
    }
}