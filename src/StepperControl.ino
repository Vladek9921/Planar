/*
Управление двумя шаговыми приводами для ЗРУ_ЭМ_4450_Саранск
Модуль Mega_2560
*/

#include "Pins.h"
#include "Operational.h"

void setup()
{
    setPinMode();
    initObjects();
}

void loop()
{
    buttonsHandler();
    stepperHandler();
    watchLogs();
}