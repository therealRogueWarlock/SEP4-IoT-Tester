#pragma once
#include "../../fff/fff.h"

extern "C" {
#include "hih8120.h"
#include "portable.h"
}

DECLARE_FAKE_VALUE_FUNC(void*, pvPortMalloc, size_t);
DECLARE_FAKE_VOID_FUNC(vPortFree, void*)

DECLARE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
DECLARE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
DECLARE_FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
DECLARE_FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
DECLARE_FAKE_VALUE_FUNC(bool, hih8120_isReady);
DECLARE_FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);