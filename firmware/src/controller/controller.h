#pragma once
#include "network/network.h"

class gloveController {
private:

    const uint8_t joyStickXPin;         ///< Pin of joystick X-value
    const uint8_t joyStickYPin;         ///< Pin of joystick Y-value
    const uint8_t joyStickButtonPin;    ///< Pin of joystick button
    const uint8_t buttonAPin;         ///< Pin of bottom button
    const uint8_t buttonBPin;         ///< Pin of top button

public:
    gloveController(uint8_t pinX, uint8_t pinY, uint8_t pinJoyBtn, uint8_t pinBtnA, uint8_t pinBtnB);
    void initializePins();
    void getControllerVals(GloveControlPacket &packet);
};