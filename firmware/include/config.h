#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define PWM objects using I2C address
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

// Define pinout for joystick and buttons
extern int joyStickX = 4;
extern int joyStickY = 5;
extern int joyStickButton = 6;
extern int buttonBot = 7;
extern int buttonTop = 8;