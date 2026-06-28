#pragma once
#include <WiFi.h>

// Define wi-fi credentials (UNCOMMENT)
// const char* ssid = "ENTER_WIFI_SSID";
// const char* wifiPassword = "ENTER_WIFI_PASSWORD";

const IPAddress localIP(192, 168, 4, 48);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

// Define glove port for UDP connection
const uint16_t glovePort = 4242;

// Define PWM I2C addresses
constexpr int pwm1Address = 0x40;
constexpr int pwm2Address = 0x41;


// Define pinout for joystick and buttons
constexpr int joyStickX = 4;
constexpr int joyStickY = 5;
constexpr int joyStickButton = 6;
constexpr int buttonBot = 7;
constexpr int buttonTop = 8;

