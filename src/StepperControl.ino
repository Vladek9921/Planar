/*
Управление двумя шаговыми приводами для ЗРУ_ЭМ_4450_Саранск
Модуль Mega_2560
*/

#include "Pins.h"
#include "Operational.h"
#include "Timers.h"

void setup()
{
    setPinMode();
    initObjects();
}

void loop()
{
    buttonsHandler();
    watchLogs();
}

ISR(TIMER2_A)
{
    stepperHandler();
}