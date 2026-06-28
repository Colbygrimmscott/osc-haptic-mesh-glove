#include <Arduino.h>

#include "controller.h"


gloveController::gloveController(uint8_t pinX, uint8_t pinY, uint8_t pinJoyBtn, uint8_t pinBtnA, uint8_t pinBtnB)
    : joyStickXPin(pinX), joyStickYPin(pinY), joyStickButtonPin(pinJoyBtn), buttonAPin(pinBtnA), buttonBPin(pinBtnB) {}

void gloveController::initializePins() {
    pinMode(joyStickXPin, INPUT);
    pinMode(joyStickYPin, INPUT);
    pinMode(joyStickButtonPin, INPUT_PULLUP);
    pinMode(buttonAPin, INPUT_PULLUP);
    pinMode(buttonBPin, INPUT_PULLUP);

}


void gloveController::getControllerVals(GloveControlPacket &packet) {
    packet.joyStickXVal = analogRead(joyStickXPin);
    packet.joyStickYVal = analogRead(joyStickYPin);
    packet.joyStickButtonVal = digitalRead(joyStickButtonPin);
    packet.buttonAVal = digitalRead(buttonAPin);
    packet.buttonBVal = digitalRead(buttonBPin);
}