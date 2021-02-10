#include "Arduino.h"
#include "Operational.h"
#include "Pins.h"
#include "Debounce.h"
#include "StepperDriver.h"

short stepFirstLeft = 150;
short stepFirstRight = stepFirstLeft;
short stepMainLeft = 100;                 // перемещение левой кассеты на одно нажатие кнопки
short stepMainRight = stepMainLeft;       // перемещение правой кассеты на одно нажатие кнопки
short stepReboundLeft = 200;              // отскок от исходного левой кассеты в первую позицию
short stepReboundRight = stepReboundLeft; // отскок от исходного правой кассеты в первую позицию
int stepToHome = -500;
short accelerateDefault = 500;
short speedForStep = 1000;
short speedForHoming = 1000;
short maxCountOfStepsLeft = 6;
short maxCountOfStepsRight = maxCountOfStepsLeft;

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

Button btnStepLeftDeb(PIN_BUTTON_STEP_LEFT);
Button btnStepRightDeb(PIN_BUTTON_STEP_RIGHT);
Button btnHomeLeftDeb(PIN_BUTTON_HOME_LEFT);
Button btnHomeRightDeb(PIN_BUTTON_HOME_RIGHT);
Button btnPusherDeb(PIN_BUTTON_PUSHER);
Button btnEndstopLeft(PIN_ENDSTOP_LEFT);
Button btnEndstopRight(PIN_ENDSTOP_RIGHT);
SpeedyStepper stepperLeft;

void initObjects()
{
    Serial.begin(9600);
    btnStepLeftDeb.begin();
    btnStepRightDeb.begin();
    btnHomeLeftDeb.begin();
    btnHomeRightDeb.begin();
    btnPusherDeb.begin();
    btnEndstopLeft.begin();
    btnEndstopRight.begin();
    stepperLeft.connectToPins(PIN_STEP_LEFT, PIN_DIR_LEFT);
    stepperLeft.setSpeedInStepsPerSecond(1000);
    stepperLeft.setAccelerationInStepsPerSecondPerSecond(accelerateDefault);
}

void buttonsHandler()
{
    btnStepLeftDeb.read();
    btnStepRightDeb.read();
    btnHomeLeftDeb.read();
    btnHomeRightDeb.read();
    btnPusherDeb.read();
    btnEndstopLeft.read();
    btnEndstopRight.read();
}

void stepperHandler()
{
    // if (btnPusherDeb.isPressed())
    // {
        carriageStep();
        carriageHome();
    //}
}

void carriageStep()
{
    if (canStepLeft == true)
    {
        if (btnStepLeftDeb.wasPressed())
        {
            if (counterStepsLeft == 0)
            {
                stepperLeft.setSpeedInStepsPerSecond(speedForStep);
                stepperLeft.moveRelativeInSteps(stepFirstLeft);
                counterStepsLeft++;
            }
            else if (counterStepsLeft < maxCountOfStepsLeft)
            {
                stepperLeft.setSpeedInStepsPerSecond(speedForStep);
                stepperLeft.moveRelativeInSteps(stepMainLeft);
                counterStepsLeft++;
                if (counterStepsLeft == maxCountOfStepsLeft)
                {
                    canStepLeft = false;
                }
            }
            else
            {
                stepperLeft.setupStop();
            }
        }
    }
}

void carriageHome()
{
    if (btnHomeLeftDeb.wasPressed())
    {
        stepperLeft.setSpeedInStepsPerSecond(speedForHoming);
        stepperLeft.moveRelativeInSteps(stepToHome);
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
        Serial.println(btnPusherDeb.isPressed());
        Serial.print("counterStepsL: ");
        Serial.println(counterStepsLeft);
        Serial.println("/////////////////");
    }
}