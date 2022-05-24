#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "co2_sensor.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
}

FAKE_VOID_FUNC(mh_z19_initialise, uint16_t);
FAKE_VOID_FUNC(mh_z19_injectCallBack, void*);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);



class CO2SensorTest : public ::testing::Test {
protected:
	void SetUp()override {
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xEventGroupWaitBits);


		RESET_FAKE(mh_z19_initialise);
		RESET_FAKE(mh_z19_injectCallBack);
		RESET_FAKE(mh_z19_takeMeassuring);

		FFF_RESET_HISTORY();
	}
	void TearDown()override {}

};


TEST_F(CO2SensorTest, co2_Sensor_initilizeCall) {
	//Arrange
	EventGroupHandle_t readyGroup = xEventGroupCreate();
	EventGroupHandle_t startGroup = xEventGroupCreate();

	//Act
	co2_sensor_initialize(1, readyGroup, startGroup);

	//Assert
	EXPECT_EQ(1, mh_z19_injectCallBack_fake.call_count);
	EXPECT_EQ(1, mh_z19_initialise_fake.call_count);
	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}


TEST_F(CO2SensorTest, _co2_sensor_task_init) {
	//Arrange
	//Act
	//Assert

	FAIL();
}

TEST_F(CO2SensorTest, _co2_sensor_task_runNco2_wakeup_and_measure) {
	//Arrange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;

	//Act
	_co2_sensor_task_run();

	//Assert
	EXPECT_EQ(1, mh_z19_takeMeassuring_fake.call_count);
	EXPECT_EQ(1, xEventGroupWaitBits_fake.call_count);
	ASSERT_LT(1, vTaskDelay_fake.call_count);
}