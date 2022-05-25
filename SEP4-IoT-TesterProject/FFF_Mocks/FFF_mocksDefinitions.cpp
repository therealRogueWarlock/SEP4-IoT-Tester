#pragma once
#include "FFF_mocksDeclarations.h"


DEFINE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
DEFINE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
DEFINE_FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
DEFINE_FAKE_VALUE_FUNC(bool, hih8120_isReady);
DEFINE_FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
DEFINE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);