#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"

#define		SENSOR1_IO					GPIO_Pin_12
#define		SENSOR1_PORT				GPIOB
#define   SENSOR1_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR2_IO					GPIO_Pin_13
#define		SENSOR2_PORT				GPIOB
#define   SENSOR2_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR3_IO					GPIO_Pin_14
#define		SENSOR3_PORT				GPIOB
#define   SENSOR3_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR4_IO					GPIO_Pin_15
#define		SENSOR4_PORT				GPIOB
#define   SENSOR4_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR5_IO					GPIO_Pin_14
#define		SENSOR5_PORT				GPIOB
#define   SENSOR5_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR6_IO					GPIO_Pin_15
#define		SENSOR6_PORT				GPIOB
#define   SENSOR6_RCC					RCC_APB2Periph_GPIOB


#define   READ_SENSOR1_CHECK   			GPIO_ReadInputDataBit(SENSOR1_PORT,SENSOR1_IO)
#define   READ_SENSOR2_CHECK  			GPIO_ReadInputDataBit(SENSOR2_PORT,SENSOR2_IO)
#define   READ_SENSOR3_CHECK   			GPIO_ReadInputDataBit(SENSOR3_PORT,SENSOR3_IO)
#define   READ_SENSOR4_CHECK  			GPIO_ReadInputDataBit(SENSOR4_PORT,SENSOR4_IO)
#define   READ_SENSOR5_CHECK   			GPIO_ReadInputDataBit(SENSOR5_PORT,SENSOR5_IO)
#define   READ_SENSOR6_CHECK  			GPIO_ReadInputDataBit(SENSOR6_PORT,SENSOR6_IO)


void SENSOR_GPIO_Config(void);




#endif




