#include "Arduino.h"
#include "Pins.h"

void setPinMode()
{
    pinMode(PIN_DIR_LEFT, OUTPUT);
    pinMode(PIN_DIR_RIGHT, OUTPUT);
    pinMode(PIN_STEP_LEFT, OUTPUT);
    pinMode(PIN_STEP_RIGHT, OUTPUT);
    pinMode(PIN_BUTTON_STEP_LEFT, INPUT);
    pinMode(PIN_BUTTON_STEP_RIGHT, INPUT);
    pinMode(PIN_BUTTON_HOME_LEFT, INPUT);
    pinMode(PIN_BUTTON_HOME_RIGHT, INPUT);
    pinMode(PIN_ENDSTOP_LEFT, INPUT);
    pinMode(PIN_ENDSTOP_RIGHT, INPUT);
    pinMode(PIN_BUTTON_PUSHER, INPUT);
}
