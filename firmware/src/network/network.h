#pragma once
#include <WifiUdp.h>
#include "controller/controller.h"

/**
 * Custom packet struct for deciphering incoming haptic motor control packets from PC server
 */
struct __attribute__((__packed__)) HapticMotorPacket {
    uint16_t header;                ///< Identifying header used to verify packet target.
    uint8_t motorIntensities[30];   ///< Array of 30 motor intensities.
};

/**
 * Custom packet struct for sending controller data to PC server.
 */
struct __attribute__((__packed__)) GloveControlPacket {
    uint16_t header;                ///< Identifying header used to verify packet target.
    uint16_t joyStickXVal;          ///< X value of joystick
    uint16_t joyStickYVal;          ///< Y value of joystick
    uint8_t joyStickButtonVal;      ///< State of joystick button
    uint8_t buttonBotVal;           ///< State of bottom button
    uint8_t buttonTopVal;           ///< State of top button
};


/**
 * Manages UDP network connection and packet parsing
 */
class EspUdpNetwork {

private:
    HapticMotorPacket incomingPacket;   ///< Stores most recent packet.
    WiFiUDP udpConnection;              ///< Used to initialize and connect to the internet using UDP.
    int packetSize;                     ///< Stores the size of most recent packet.
    gloveController gloveControllerObj;

public:
//  EspUdpNetwork();

    /**
     * Attempts to connect to Wi-Fi network when passed SSID and password credentials.
     * Establishes UDP listener when given a port number.
     */
    void connectToWifi(const char* ssid, const char* wifiPassword, uint16_t glovePort);

    /**
     * Parses incoming packets and verifies the header is correct.
     * Copies data for motor intensities into an array passed as input
     */
    void parseIncomingPacket(uint8_t* outputMotorIntensities, int arraySize);

    void sendControlPacket()
};