#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define PWM I2C addresses
constexpr int pwm1Address = 0x40;
constexpr int pwm2Address = 0x41;


// Define pinout for joystick and buttons
constexpr int joyStickX = 4;
constexpr int joyStickY = 5;
constexpr int joyStickButton = 6;
constexpr int buttonBot = 7;
constexpr int buttonTop = 8;

// Define glove port for UDP connection
constexpr int glovePort = 4242;