#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"
DEFINE_FFF_GLOBALS

extern "C" {
#include "temp_hum_sensor.h"
#include "hih8120.h"
#include "FreeRTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

}

FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(bool, hih8120_isReady);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);


class TempHumSensorTest : public ::testing::Test {
protected:
	void SetUp()override {
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(vTaskDelay);

		RESET_FAKE(hih8120_initialise);
		RESET_FAKE(hih8120_wakeup);
		RESET_FAKE(hih8120_getHumidityPercent_x10);
		RESET_FAKE(hih8120_getTemperature_x10);
		RESET_FAKE(hih8120_isReady);
		RESET_FAKE(hih8120_measure);
		FFF_RESET_HISTORY();
	}
	void TearDown()override {}

};



TEST_F(TempHumSensorTest, TestInit) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}