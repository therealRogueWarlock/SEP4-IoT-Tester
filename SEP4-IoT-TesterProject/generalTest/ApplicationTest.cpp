#include "gtest/gtest.h"
#include "GoogleTestDemo/VIAFreeRTOSTest/FreeRTOS_FFF_MocksDeclaration.h"


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


class ApplicationTest : public ::testing::Test {

protected:
	void SetUp()override {
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskDelayUntil);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(pvPortMalloc);

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
	EXPECT_EQ(application_task_handler, xTaskCreate_fake.arg0_val);
	EXPECT_EQ("Application", xTaskCreate_fake.arg1_val);

	//Assert
	EXPECT_EQ(1, xTaskCreate_fake.call_count);
}



