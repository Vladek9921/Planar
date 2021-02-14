#ifndef STEPPER_DRIVER

#define STEPPER_DRIVER

#include <Arduino.h>
#include "Timers.h"

class StepperDriver
{
private:
    uint8_t pinDir;
    uint8_t pinStep;
    uint8_t stepsPerRotation;
    uint32_t timeOneStep = 0;
    bool direction;
    long int steps;
    uint32_t speed;

public:
    StepperDriver(uint8_t pinDirection, uint8_t pinStep, uint8_t stepsPerRotate)
    {
        this->pinDir = pinDirection;
        this->pinStep = pinStep;
        this->stepsPerRotation = stepsPerRotate;
    }

    void handler()
    {
        // if (steps != 0)
        // {
        //     if (timeOneStep + speed < millis())
        //     {
        //         digitalWrite(pinStep, !digitalRead(pinStep));
        //         timeOneStep = millis();
        //         steps--;
        //     }
        // }
        if (this->steps != 0)
        {
            this->steps--;
            digitalWrite(this->pinStep, !digitalRead(this->pinStep));
        }
        Serial.println("sdfasfdasdf");
    }

    void move(long int steps, bool direction, uint32_t speed)
    {
        if (direction == true)
        {
            digitalWrite(pinDir, HIGH);
        }
        if (direction == false)
        {
            digitalWrite(pinDir, LOW);
        }
        this->speed = speed;
        this->steps = steps;
    }

    void begin()
    {
        Timer2.setFrequency(1);
        Timer2.enableISR(CHANNEL_A);
    }
};

#endif