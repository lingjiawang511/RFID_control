#include"HeadType.h"


//=============================================================================
//��������: LOCK_GPIO_Config
//���ܸ�Ҫ:LOCK����������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
void SENSOR_GPIO_Config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//SENSOR1״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR1_PORT, &GPIO_InitStructure);

	//SENSOR2״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR2_PORT, &GPIO_InitStructure);
	//SENSOR3״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR3_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR3_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR3_PORT, &GPIO_InitStructure);
	//SENSOR4״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR4_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR4_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR4_PORT, &GPIO_InitStructure);
	//SENSOR5״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR5_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR5_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR5_PORT, &GPIO_InitStructure);
	//SENSOR6״̬��������ź�
	RCC_APB2PeriphClockCmd(SENSOR6_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR6_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR6_PORT, &GPIO_InitStructure);
	

}



















