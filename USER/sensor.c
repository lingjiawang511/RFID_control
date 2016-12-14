#include"HeadType.h"


//=============================================================================
//函数名称: LOCK_GPIO_Config
//功能概要:LOCK灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void SENSOR_GPIO_Config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//SENSOR1状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR1_PORT, &GPIO_InitStructure);

	//SENSOR2状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR2_PORT, &GPIO_InitStructure);
	//SENSOR3状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR3_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR3_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR3_PORT, &GPIO_InitStructure);
	//SENSOR4状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR4_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR4_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR4_PORT, &GPIO_InitStructure);
	//SENSOR5状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR5_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR5_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR5_PORT, &GPIO_InitStructure);
	//SENSOR6状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR6_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR6_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR6_PORT, &GPIO_InitStructure);
	

}



















