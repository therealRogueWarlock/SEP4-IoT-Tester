#pragma once


#ifndef HIH8120_H_
#define HIH8120_H_
#include <stdbool.h>


typedef enum hih8120_driverReturnCodes {
	HIH8120_OK	/**< Everything went well */
	, HIH8120_OUT_OF_HEAP /**< Not enough heap to initialise the driver */
	, HIH8120_DRIVER_NOT_INITIALISED /**< Driver must be initialise before use */
	, HIH8120_TWI_BUSY /**< The two wire/I2C interface is busy */
} hih8120_driverReturnCode_t;


hih8120_driverReturnCode_t hih8120_initialise(void);

hih8120_driverReturnCode_t hih8120_destroy(void);

bool hih8120_isReady(void);

hih8120_driverReturnCode_t hih8120_wakeup(void);

hih8120_driverReturnCode_t hih8120_measure(void);

uint16_t hih8120_getHumidityPercent_x10(void);

int16_t hih8120_getTemperature_x10(void);

float hih8120_getHumidity(void);


float hih8120_getTemperature(void);

#endif /* HIH8120_H_ */