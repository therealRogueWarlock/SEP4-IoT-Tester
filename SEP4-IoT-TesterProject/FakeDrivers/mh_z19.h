#pragma once

typedef enum
{
	ser_USART0 = 0,
	ser_USART1,
	ser_USART2,
	ser_USART3
} serial_comPort_t;


typedef enum
{
	MHZ19_OK 	/**< Everything went well */
	, MHZ19_NO_MEASSURING_AVAILABLE /**< No results are received from the sensor */
	, MHZ19_NO_SERIAL /**< No serial driver is specified */
	, MHZ19_PPM_MUST_BE_GT_999 /**< Span calibration is only allowed from ppm >= 1000 */
} mh_z19_returnCode_t;

void mh_z19_initialise(uint16_t);

void mh_z19_injectCallBack(void*);

mh_z19_returnCode_t mh_z19_takeMeassuring();