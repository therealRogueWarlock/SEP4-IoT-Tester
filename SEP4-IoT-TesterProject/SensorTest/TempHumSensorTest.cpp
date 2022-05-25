#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"
#include "FFF_mocksDeclarations.h"

extern "C" {
#include "temp_hum_sensor.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
}



class TempHumSensorTest : public ::testing::Test {
protected:
	void SetUp()override {
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xEventGroupCreate);
		RESET_FAKE(xTaskGetTickCount);


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
	//Arrange
	//Act
	temp_hum_sensor_task_init();

	//Assert
	FAIL();
}

TEST_F(TempHumSensorTest, temp_hum_sensor_task_runCall) {
	//Arrange
	//Act
	temp_hum_sensor_task_run();

	//Assert
	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
	EXPECT_EQ(1, hih8120_measure_fake.call_count);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
}


TEST_F(TempHumSensorTest, temp_hum_sensor_task_runCallStatusNotOk) {
	//Arrange
	hih8120_measure_fake.return_val = HIH8120_TWI_BUSY;

	//Act
	temp_hum_sensor_task_run();

	
	//Assert
	EXPECT_EQ(1, hih8120_wakeup_fake.call_count);
	EXPECT_EQ(1, hih8120_measure_fake.call_count);
	EXPECT_EQ(1, hih8120_isReady_fake.call_count);
	EXPECT_EQ(false, hih8120_isReady());
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