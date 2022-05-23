#pragma once

typedef enum
{
	ser_USART0 = 0,
	ser_USART1,
	ser_USART2,
	ser_USART3
} serial_comPort_t;


void mh_z19_initialise(uint16_t);

void mh_z19_injectCallBack(void*);
