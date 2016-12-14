#include"HeadType.h"

#define LOCK_SHORT_TIME 		20
#define LOCK_LONG_TIME			300
u8 Lock1_State;
u8 Lock2_State;
u8 Lock3_State;
u8 Lock4_State;
u16 lock1_time;
u16 lock2_time;
u16 lock3_time;
u16 lock4_time;

u8 Check_State;
//=============================================================================
//函数名称: LOCK_GPIO_Config
//功能概要:LOCK灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void LOCK_GPIO_Config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	//LOCK1开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_PORT, &GPIO_InitStructure);
	//LOCK2开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_PORT, &GPIO_InitStructure);
		//LOCK3开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK3_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK3_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK3_PORT, &GPIO_InitStructure);
	//LOCK4开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK4_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK4_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK4_PORT, &GPIO_InitStructure);
	
	//LOCK1状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK1_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_CHECK_PORT, &GPIO_InitStructure);
	//LOCK2状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK2_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_CHECK_PORT, &GPIO_InitStructure);
	//LOCK3状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK3_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK3_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK3_CHECK_PORT, &GPIO_InitStructure);
	//LOCK4状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK4_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK4_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK4_CHECK_PORT, &GPIO_InitStructure);	
	
	//LOCK1开锁指示灯1
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT1_PORT, &GPIO_InitStructure);
	
	//LOCK1开锁指示灯2,这个现在是灯的亮度调节IO
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT2_PORT, &GPIO_InitStructure);

//	//LOCK2开锁指示灯1
//	RCC_APB2PeriphClockCmd(LOCK2_LIGHT1_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT1_IO;			 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(LOCK2_LIGHT1_PORT, &GPIO_InitStructure);

//	//LOCK2开锁指示灯1
//	RCC_APB2PeriphClockCmd(LOCK2_LIGHT2_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT2_IO;			 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(LOCK2_LIGHT2_PORT, &GPIO_InitStructure);
	
	
	LOCK1_LIGHT_OFF();
//	LOCK2_LIGHT_OFF();
	LOCK1_OFF;
	LOCK2_OFF;
}

//锁的控制和检测分开，因为所的控制需要控制灯，并且人工关锁的时候要自动关灯，但是锁的状态改变需要上传给PC
static void Lock_control_12(void )
{
	 static u8 lock1_triggerstate;
	 static u16 lock1_timercount;
	 static u8 lock2_triggerstate;
	 static u16 lock2_timercount;
	 //LOCK1
	 if(Lock1_State == 1){	
			if(READ_LOCK1_CHECK == READLOW){   //锁是关的，才打开，不然没有意义
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK1_OFF;
						Lock1_State = 2;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else if(Lock1_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK1_CHECK == READHIGH){
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
//						LOCK1_LIGHT_OFF();//关灯
						LOCK1_OFF;
						Lock1_State = 0;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else{
				lock1_triggerstate = 0;
				lock1_timercount = 0;
	 }
	 	 //LOCK2
	 if(Lock2_State == 1){
			if(READ_LOCK2_CHECK == READLOW){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
					  LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK2_OFF;
						Lock2_State = 2;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else if(Lock2_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK2_CHECK == READHIGH){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_OFF();//关灯
//				  	LOCK1_LIGHT_OFF();//关灯
						LOCK2_OFF;
						Lock2_State = 0;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else{
				lock2_triggerstate = 0;
				lock2_timercount = 0;
	 }
	 
	 if(Lock1_State > 0){   //最长开锁时间，如果锁是开的，上位机让MCU开锁，超时后状态复位
			 lock1_time--;
			 if(lock1_time <= 0){
				 LOCK1_OFF;
				 lock1_time = LOCK_TIME;
			}
	}
	if(Lock2_State > 0){
			 lock2_time--;
			 if(lock2_time <= 0){
				 LOCK2_OFF;
				 lock2_time = LOCK_TIME;
			}
	}
}
//锁的控制和检测分开，因为所的控制需要控制灯，并且人工关锁的时候要自动关灯，但是锁的状态改变需要上传给PC
static void Lock_control_34(void )
{
	 static u8 lock3_triggerstate;
	 static u16 lock3_timercount;
	 static u8 lock4_triggerstate;
	 static u16 lock4_timercount;
	 //LOCK1
	 if(Lock3_State == 1){	
			if(READ_LOCK3_CHECK == READLOW){
				if(lock3_triggerstate == 0){
					lock3_triggerstate = 1;
				}else{
					lock3_timercount++;
				}
				if(lock3_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK3_OFF;
						Lock3_State = 2;
						lock3_triggerstate = 0;
						lock3_timercount = 0;
				}
			}
	 }else if(Lock3_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK3_CHECK == READHIGH){
				if(lock3_triggerstate == 0){
					lock3_triggerstate = 1;
				}else{
					lock3_timercount++;
				}
				if(lock3_timercount >= LOCK_SHORT_TIME){
//						LOCK1_LIGHT_OFF();//关灯
						LOCK3_OFF;
						Lock3_State = 0;
						lock3_triggerstate = 0;
						lock3_timercount = 0;
				}
			}
	 }else{
				lock3_triggerstate = 0;
				lock3_timercount = 0;
	 }
	 	 //LOCK4
	 if(Lock4_State == 1){
			if(READ_LOCK4_CHECK == READLOW){
				if(lock4_triggerstate == 0){
					lock4_triggerstate = 1;
				}else{
					lock4_timercount++;
				}
				if(lock4_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
					  LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK4_OFF;
						Lock4_State = 2;
						lock4_triggerstate = 0;
						lock4_timercount = 0;
				}
			}
	 }else if(Lock4_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK4_CHECK == READHIGH){
				if(lock4_triggerstate == 0){
					lock4_triggerstate = 1;
				}else{
					lock4_timercount++;
				}
				if(lock4_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_OFF();//关灯
//				  	LOCK1_LIGHT_OFF();//关灯
						LOCK4_OFF;
						Lock4_State = 0;
						lock4_triggerstate = 0;
						lock4_timercount = 0;
				}
			}
	 }else{
				lock4_triggerstate = 0;
				lock4_timercount = 0;
	 }
	 
	 if(Lock3_State > 0){
			 lock3_time--;
			 if(lock3_time <= 0){
				 LOCK3_OFF;
				 lock3_time = LOCK_TIME;
			}
	}
	if(Lock4_State > 0){
			 lock4_time--;
			 if(lock4_time <= 0){
				 LOCK4_OFF;
				 lock4_time = LOCK_TIME;
			}
	}
}

//必须在定时器中调用此函数
void Lock_control(void )
{
	Lock_control_12();
	Lock_control_34();
	if((Lock1_State > 0)||(Lock2_State > 0)||(Lock3_State > 0)||(Lock4_State > 0)){
		 LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
	}else{//四个锁都是关的状态，自动关灯
		LOCK1_LIGHT_OFF();//关灯
	}
}













