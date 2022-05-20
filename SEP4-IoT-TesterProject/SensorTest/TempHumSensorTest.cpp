#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "temp_hum_sensor.h"
#include "hih8120.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
}

FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(bool, hih8120_isReady);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VOID_FUNC(temp_hum_sensor_wentWRONG);

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

		RESET_FAKE(temp_hum_sensor_wentWRONG);
		
		FFF_RESET_HISTORY();
	}
	void TearDown()override {}

};



TEST_F(TempHumSensorTest, temp_hum_initilizeCall) {
	//Arrange
	EventGroupHandle_t readyGroup = xEventGroupCreate();
	EventGroupHandle_t startGroup = xEventGroupCreate();

	//Act
	temp_hum_sensor_initialize(1,readyGroup,startGroup);


	//Assert
	EXPECT_EQ(1, hih8120_initialise_fake.call_count);
	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}

TEST_F(TempHumSensorTest, temp_hum_sensor_task_initCall) {
	temp_hum_sensor_task_init();
	FAIL();
}

TEST_F(TempHumSensorTest, temp_hum_sensor_task_runCall) {
	temp_hum_sensor_task_run();
	


	//Assert
	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
	EXPECT_EQ(1, hih8120_measure_fake.call_count);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
}


TEST_F(TempHumSensorTest, temp_hum_sensor_task_runCallStatusNotOk) {
	
	hih8120_measure_fake.return_val = HIH8120_TWI_BUSY;

	temp_hum_sensor_task_run();

	
	//Assert
	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
	EXPECT_EQ(1, hih8120_measure_fake.call_count);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
}


TEST_F(TempHumSensorTest, temp_hum_getTemperatureCall) {
	//Arrange
	int16_t testTempValue = 100;
	hih8120_isReady_fake.return_val = 1;
	hih8120_getTemperature_x10_fake.return_val = testTempValue;

	//Act
	int16_t temp = temp_hum_getTemperature();

	//Assert
	EXPECT_EQ(testTempValue, temp);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
	EXPECT_EQ(1, hih8120_getTemperature_x10_fake.call_count);
}

TEST_F(TempHumSensorTest, temp_hum_getHumidityCall) {
	//Arrange
	uint16_t testHumValue = 100;
	hih8120_isReady_fake.return_val = 1;
	hih8120_getHumidityPercent_x10_fake.return_val = testHumValue;

	//Act
	uint16_t hum = temp_hum_getHumidity();

	//Assert
	EXPECT_EQ(testHumValue, hum);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
	EXPECT_EQ(1, hih8120_getHumidityPercent_x10_fake.call_count);

}