#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"
#include "FFF_mocksDeclarations.h"


extern "C" {
//form production code
#include "application.h"
#include "loraWan_up_link_handler.h"

//from test env
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
}

FAKE_VOID_FUNC(send_measurment, measurment_t*);

FAKE_VALUE_FUNC(uint16_t, co2_sensor_getCO2);

class ApplicationTest : public ::testing::Test {

protected:
	void SetUp()override {
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskDelayUntil);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(pvPortMalloc);
		RESET_FAKE(xTaskGetTickCount);

		RESET_FAKE(hih8120_isReady);
		RESET_FAKE(co2_sensor_getCO2);
		RESET_FAKE(send_measurment);
		RESET_FAKE(hih8120_getHumidityPercent_x10);
		RESET_FAKE(hih8120_getTemperature_x10);

		FFF_RESET_HISTORY();
	}
	void TearDown()override {}

};



TEST_F(ApplicationTest, application_initialize) {
	//Arrange
	EventGroupHandle_t readyGroup = xEventGroupCreate();
	EventGroupHandle_t startGroup = xEventGroupCreate();

	//Act
	application_initialize(1, readyGroup, startGroup);

	//Assert
	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}


TEST_F(ApplicationTest, application_task_init) {
	//Arrange

	//Act
	application_task_init();

	//Assert
	EXPECT_EQ(1, xTaskGetTickCount_fake.call_count);
}

TEST_F(ApplicationTest, application_task_run) {
	//Arrange
	hih8120_isReady_fake.return_val = 1;
	hih8120_getHumidityPercent_x10_fake.return_val = 50;
	hih8120_getTemperature_x10_fake.return_val = 23;
	co2_sensor_getCO2_fake.return_val = 850;
	pvPortMalloc_fake.return_val =(pMeasurment_t) malloc(sizeof(measurment_t));
	//Act
	application_task_run();

	//Assert
	EXPECT_EQ(1, xTaskDelayUntil_fake.call_count);
	EXPECT_LT(0, xEventGroupSetBits_fake.call_count);
	EXPECT_LT(0, xEventGroupWaitBits_fake.call_count);
	EXPECT_LT(0, vTaskDelay_fake.call_count);
	EXPECT_EQ(1, pvPortMalloc_fake.call_count);
	EXPECT_EQ(1, vPortFree_fake.call_count);
}