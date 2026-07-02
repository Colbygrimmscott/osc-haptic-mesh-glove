#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WifiUdp.h>

#include "config.h"
#include "private.h"
#include "network/network.h"
#include "controller/controller.h"


Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(PWM_ADDR_1);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(PWM_ADDR_2);

const unsigned long interval = 50;
unsigned long prevTime = 0;

EspUdpNetwork espUdpConnection;
gloveController controllerObj = gloveController(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_BTN, PIN_BTN_A, PIN_BTN_B);

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

    controllerObj.initializePins();

    Serial.println("----------");
    delay(500);
}


void loop() {
    uint8_t hapticMotorCount = 30;
    uint8_t hapticMotorIntensities[hapticMotorCount] = {0};

    espUdpConnection.parseIncomingPacket(hapticMotorIntensities, hapticMotorCount);
    espUdpConnection.sendControlPacket(controllerObj);

    uint16_t hapticMotorPWMVals[hapticMotorCount];

    for (uint8_t i = 0; i < hapticMotorCount; i++) {
        unsigned long currTime = millis();
        while (currTime - prevTime < interval) {
            currTime = millis();
        }
        prevTime = currTime;
        hapticMotorPWMVals[i] = map(hapticMotorIntensities[i], 0, 255, 0, 4095);
        pwm1.setPWM(1, 0, hapticMotorPWMVals[i]);
        Serial.println("Setting haptic motor values:");
    }
    
    // for (uint8_t i = 0; i < hapticMotorCount; i++) {
    //     unsigned long currTime = millis();
    //     if (currTime - prevTime >= interval) {
    //         prevTime = currTime;
    //         hapticMotorPWMVals[i] = map(hapticMotorIntensities[i], 0, 255, 0, 4095);
    //         pwm1.setPWM(1, 0, hapticMotorPWMVals[i]);
    //         Serial.println("Setting haptic motor values:");
    //     }
    // }
}