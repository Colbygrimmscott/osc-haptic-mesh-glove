#pragma once
#include <WiFi.h>
#include "private.h"

// Define wi-fi credentials (UNCOMMENT)
// const char* SSID = "ENTER_WIFI_SSID";
// const char* WIFI_PASS = "ENTER_WIFI_PASSWORD";

const IPAddress LOCAL_IP(192, 168, 4, 48);
const IPAddress GATEWAY(192, 168, 1, 1);
const IPAddress SUBNET(255, 255, 255, 0);

// Define ports for UDP connection
const uint16_t LOCAL_PORT = 4242;
const uint16_t REMOTE_PORT = 4243;

// Define PWM I2C addresses
constexpr int PWM_ADDR_1 = 0x40;
constexpr int PWM_ADDR_2 = 0x41;


// Define pinout for joystick and buttons
const uint8_t PIN_JOYSTICK_X = 1;
const uint8_t PIN_JOYSTICK_Y = 2;
const uint8_t PIN_JOYSTICK_BTN = 4;
const uint8_t PIN_BTN_A = 6;
const uint8_t PIN_BTN_B = 7;

