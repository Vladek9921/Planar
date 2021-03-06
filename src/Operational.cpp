#include "Arduino.h"
#include "Operational.h"
#include "Pins.h"
#include "Debounce.h"
#include "StepperLib/AccelStepper.h"

short stepFirstLeft = 150;
short stepFirstRight = stepFirstLeft;
short stepMainLeft = 100;                 // перемещение левой кассеты на одно нажатие кнопки
short stepMainRight = stepMainLeft;       // перемещение правой кассеты на одно нажатие кнопки
short stepReboundLeft = 200;              // отскок от исходного левой кассеты в первую позицию
short stepReboundRight = stepReboundLeft; // отскок от исходного правой кассеты в первую позицию
int stepToHome = -500;
short accelerateDefault = 500;
short speedForStep = 10000;
short speedForHoming = 1000;
short maxCountOfStepsLeft = 6;
short maxCountOfStepsRight = maxCountOfStepsLeft;
unsigned long int coordinateStepperLeft = 0;

unsigned wait_time_micros = 0;
short counterStepsLeft = 0;
short counterStepsRight = 0;
bool isPressedBtnStepLeft = false;
bool isPressedBtnStepRight = false;
bool isPressedBtnHomeLeft = false;
bool isPressedBtnHomeRight = false;
bool isPressedBtnPusher = false;
bool isHomeLeft = false;
bool isHomeRight = false;
bool isPressedEncoderLeft = false;
bool isPressedEncoderRight = false;
bool canStepLeft = true; //false;
bool canStepRight = false;

void carriageStep();
void carriageHome();

Button btnStepLeft(PIN_BUTTON_STEP_LEFT);
Button btnStepRight(PIN_BUTTON_STEP_RIGHT);
Button btnHomeLeft(PIN_BUTTON_HOME_LEFT);
Button btnHomeRight(PIN_BUTTON_HOME_RIGHT);
Button btnPusher(PIN_BUTTON_PUSHER);
Button btnEndstopLeft(PIN_ENDSTOP_LEFT);
Button btnEndstopRight(PIN_ENDSTOP_RIGHT);
AccelStepper stepperLeft(AccelStepper::DRIVER, PIN_STEP_LEFT, PIN_DIR_LEFT);

void initObjects()
{
    Serial.begin(9600);
    btnStepLeft.begin();
    btnStepRight.begin();
    btnHomeLeft.begin();
    btnHomeRight.begin();
    btnPusher.begin();
    btnEndstopLeft.begin();
    btnEndstopRight.begin();
    stepperLeft.setMaxSpeed(speedForStep);
    stepperLeft.setAcceleration(2000.0);
}

void buttonsHandler()
{
    btnStepLeft.read();
    btnStepRight.read();
    btnHomeLeft.read();
    btnHomeRight.read();
    btnPusher.read();
    btnEndstopLeft.read();
    btnEndstopRight.read();

    if (btnStepLeft.wasPressed())
    {
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }
}

void stepperHandler()
{
    // stepperLeft.moveTo(coordinateStepperLeft);
    // stepperLeft.setSpeed(speedForStep);
}

void carriageHandler()
{
    carriageStep();
    carriageHome();
}

void carriageStep()
{
    if (canStepLeft == true)
    {
        if (btnStepLeft.wasPressed())
        {
            if (counterStepsLeft == 0)
            {
                coordinateStepperLeft += stepFirstLeft;
                counterStepsLeft++;
            }
            else //if (counterStepsLeft < maxCountOfStepsLeft)
            {
                coordinateStepperLeft += stepMainLeft;
                stepperLeft.runToNewPosition(coordinateStepperLeft);
                counterStepsLeft++;
                if (counterStepsLeft == maxCountOfStepsLeft)
                {
                    //canStepLeft = false;
                }
            }
        }
    }
}

void carriageHome()
{
    if (btnHomeLeft.wasPressed())
    {
        coordinateStepperLeft = 0;
        counterStepsLeft = 0;
    }

    // if (side == LEFT)
    // {
    //     if (isPressedEncoderLeft == false &&
    //         isHomeLeft == false)
    //     {
    //         stepperLeft.startMove(stepToHome);
    //     }
    //     else
    //     {
    //         if (isHomeLeft == false)
    //         {
    //             stepperRight.stop();
    //             isHomeLeft = true;
    //             stepperLeft.move(stepReboundLeft);
    //         }
    //     }
    // }
}

// if (digitalRead(2) == LOW &&
//     digitalRead(12) == LOW &&
//     digitalRead(6) == LOW) // если нажата кнопка левого мотора и датчик выталкивателя в исходном, кассета в исходном
// {
//     digitalWrite(8, HIGH);         //  записываем направление вращения левого мотора (вперед)
//     for (int d = 1; d <= 150; d++) // ведем счет шагов
//     {
//         digitalWrite(9, HIGH); // начинаем перемещение левой каретки
//         delayMicroseconds(100);
//         digitalWrite(9, LOW);   // формируем тактовую последовательность
//         delayMicroseconds(100); // отскок от исходного выполнен
//     }
//     delay(1000);
// }
// else if (digitalRead(2) == LOW &&
//          digitalRead(12) == LOW &&
//          digitalRead(6) == HIGH) // если нажата кнопка левого мотора и датчик выталкивателя в исходном, кассета не в исходном
// {
//     digitalWrite(8, HIGH);          //  записываем направление вращения левого мотора (вперед)
//     for (int d = 1; d <= 2805; d++) // ведем счет шагов
//     {
//         digitalWrite(9, HIGH); // начинаем перемещение левой каретки
//         delayMicroseconds(100);
//         digitalWrite(9, LOW);   // формируем тактовую последовательность
//         delayMicroseconds(100); // кассета сдигается на шаг вперед
//     }
//     delay(200);
// }

// //////////////////////////////
// if (digitalRead(4) == LOW &&
//     digitalRead(12) == LOW &&
//     digitalRead(7) == LOW) // если нажата кнопка левого мотора и датчик выталкивателя в исходном, кассета в исходном
// {
//     digitalWrite(10, HIGH);        //  записываем направление вращения левого мотора (вперед)
//     for (int d = 1; d <= 150; d++) // ведем счет шагов
//     {
//         digitalWrite(11, HIGH); // начинаем перемещение левой каретки
//         delayMicroseconds(100);
//         digitalWrite(11, LOW);  // формируем тактовую последовательность
//         delayMicroseconds(100); // отскок от исходного выполнен
//     }
//     delay(1000);
// }
// else if (digitalRead(4) == LOW &&
//          digitalRead(12) == LOW &&
//          digitalRead(7) == HIGH) // если нажата кнопка левого мотора и датчик выталкивателя в исходном, кассета не в исходном
// {
//     digitalWrite(10, HIGH);         //  записываем направление вращения левого мотора (вперед)
//     for (int d = 1; d <= 2805; d++) // ведем счет шагов
//     {
//         digitalWrite(11, HIGH); // начинаем перемещение левой каретки
//         delayMicroseconds(100);
//         digitalWrite(11, LOW);  // формируем тактовую последовательность
//         delayMicroseconds(100); // кассета сдигается на шаг вперед
//     }
//     delay(200);
// }
// //////////////////////////////////
// if (digitalRead(3) == LOW &&
//     digitalRead(12) == LOW &&
//     digitalRead(6) == HIGH) // если нажата кнопка исходного левого мотора и датчик выталкивателя в исходном, кассета не в исходном
// {
//     if (buttonDownPressedLeft == false)
//     {
//         buttonDownPressedLeft = true;
//         digitalWrite(8, LOW); //  записываем направление вращения левого мотора (назад к исходному)
//     }
// }

// if (digitalRead(5) == LOW &&
//     digitalRead(12) == LOW &&
//     digitalRead(7) == HIGH) // если нажата кнопка исходного левого мотора и датчик выталкивателя в исходном, кассета не в исходном
// {
//     if (buttonDownPressedRight == false)
//     {
//         buttonDownPressedRight = true;
//         digitalWrite(10, LOW); //  записываем направление вращения левого мотора (назад к исходному)
//     }
// }

// caretkaReturnLeft();
// caretkaOtskokLeft();
// caretkaReturnRight();
// caretkaOtskokRight();
// //Serial.println(digitalRead(7));

// void caretkaReturnLeft()
// {
//     if (buttonDownPressedLeft == true)
//     {
//         if (digitalRead(6) == HIGH)
//         {
//             digitalWrite(9, HIGH); // начинаем перемещение левой каретки
//             delayMicroseconds(100);
//             digitalWrite(9, LOW);   // формируем тактовую последовательность
//             delayMicroseconds(100); // кассета сдигается на шаг
//         }
//         else
//         {
//             isHomeLeft = true;
//             buttonDownPressedLeft = false;
//             digitalWrite(9, LOW); //остановка в исходном
//             delay(500);
//             digitalWrite(8, HIGH); //  записываем направление вращения левого мотора (вперед)
//         }
//     }
// }

// void caretkaOtskokLeft()
// {
//     if (isHomeLeft == true)
//     {
//         for (int d = 1; d <= 200; d++)
//         {
//             digitalWrite(9, HIGH); // начинаем перемещение левой каретки
//             delayMicroseconds(400);
//             digitalWrite(9, LOW);   // формируем тактовую последовательность
//             delayMicroseconds(400); // отскок от исходного выполнено
//             if (d == 200)
//             {
//                 isHomeLeft = false;
//             }
//         }
//     }
// }

// void caretkaReturnRight()
// {
//     if (buttonDownPressedRight == true)
//     {
//         if (digitalRead(7) == HIGH)
//         {
//             digitalWrite(11, HIGH); // начинаем перемещение левой каретки
//             delayMicroseconds(100);
//             digitalWrite(11, LOW);  // формируем тактовую последовательность
//             delayMicroseconds(100); // кассета сдигается на шаг
//         }
//         else
//         {
//             isHomeRight = true;
//             buttonDownPressedRight = false;
//             digitalWrite(11, LOW); //остановка в исходном
//             delay(500);
//             digitalWrite(10, HIGH); //  записываем направление вращения левого мотора (вперед)
//         }
//     }
// }

// void caretkaOtskokRight()
// {
//     if (isHomeRight == true)
//     {
//         for (int d = 1; d <= 200; d++)
//         {
//             digitalWrite(11, HIGH); // начинаем перемещение левой каретки
//             delayMicroseconds(400);
//             digitalWrite(11, LOW);  // формируем тактовую последовательность
//             delayMicroseconds(400); // отскок от исходного выполнено
//             if (d == 200)
//             {
//                 isHomeRight = false;
//             }
//         }
//     }
// }

unsigned long timeLogs = 0;

void watchLogs()
{
    // Serial.print("Left STEP drv: ");
    // Serial.println(digitalRead(PIN_STEP_LEFT));
    if (timeLogs + 2000 < millis())
    {
        timeLogs = millis();
        Serial.print("Left STEP btn: ");
        Serial.println(digitalRead(PIN_BUTTON_STEP_LEFT));
        Serial.print("Left HOME btn: ");
        Serial.println(digitalRead(PIN_BUTTON_HOME_LEFT));
        Serial.print("Left STEP drv: ");
        Serial.println(digitalRead(PIN_STEP_LEFT));
        Serial.print("Left DIR  drv: ");
        Serial.println(digitalRead(PIN_DIR_LEFT));
        Serial.print("Pusher button: ");
        Serial.println(btnPusher.isPressed());
        Serial.print("counterStepsL: ");
        Serial.println(counterStepsLeft);
        Serial.print("coorginateLeft: ");
        Serial.println(coordinateStepperLeft);
        Serial.println("/////////////////");
    }
}