#include <Arduino.h>
#include <WiFi.h>
#include <WifiUdp.h>

#include "network.h"
#include "config.h"

// EspUdpNetwork::EspUdpNetwork() {
// }

void EspUdpNetwork::connectToWifi(const char* ssid, const char* wifiPassword, uint16_t glovePort) {
    
    WiFi.config(LOCAL_IP, GATEWAY, SUBNET);

    Serial.println("Connecting to Wifi...");
    WiFi.begin(ssid, wifiPassword);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wifi connection established on IP address: ");
    Serial.print(WiFi.localIP());
    udpConnection.begin(glovePort);
}

void EspUdpNetwork::parseIncomingPacket(uint8_t* outputMotorIntensities, int arraySize) {
    packetSize = udpConnection.parsePacket();
    if (packetSize == sizeof(HapticMotorPacket)) {
        udpConnection.read((char*)&incomingPacket, sizeof(HapticMotorPacket));

        if (incomingPacket.header == 0x03BF) {
            Serial.println("Packet received");
            for (int i = 0; i < arraySize; i++) {
                outputMotorIntensities[i] = incomingPacket.motorIntensities[i];
            }
        }
    }
}