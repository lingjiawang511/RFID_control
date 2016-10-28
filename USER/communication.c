#include"HeadType.h"
/********************全局变量定义****************/

//=====================命令======================
unsigned char static ComSet[]={0x03, COMM_CONTROL_ANTENNA, 0x03};
 //设置打开天线和关闭自动循卡
unsigned char static ComSearchCard[]={0x03,COMM_MIFARE_SEARCH_CARD, 0x00};
//寻卡后读出卡号
unsigned char static cReadBlock[]={0x0A,COMM_READ_BLOCK, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//读块No.3第1扇区的密码和控制字
unsigned char static ComReadBlock3[]={0x0A,COMM_READ_BLOCK,0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//读块No.1
unsigned char static ComReadBlock1[]={0x0A,COMM_READ_BLOCK,0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//写块No.1
unsigned char static ComWriteBlock1[]={0X1A,COMM_WRITE_BLOCK, 
	   								0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
       								0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
       								0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

//初始化钱包No.5 的值为0x12345678
unsigned char static ComIntiPurse5[]={0x0E,COMM_INIT_PURSE, 
	                                0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 
									0x00, 0x00, 0x00, 0x00};
								    //0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};

//读钱包的值No.5
unsigned char static ComReadPurse5[]={0x0A,COMM_READ_PURSE,
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//读钱包的值No.6
unsigned char static ComReadPurse6[]={0x0A,COMM_READ_PURSE,
									0x00, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//钱包值加2	    
unsigned char static ComIncrPurse5[]={0x0E,COMM_INC_VALUE, 
	   								0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
									0x02, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//钱包值减1
unsigned char static ComDecrPurse5[]={0x0E,COMM_DEC_VALUE, 
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
									0x01, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//钱包备份
unsigned char static ComBakPurse56[]={0x0B,COMM_BAK_PURSE, 
	   								0x00, 0x05, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//卡片休眠
unsigned char static ComHaltCard[]={0x02,COMM_CARD_HALT,0x09};  
//设置模块空闲睡眠模式
unsigned char static ComHaltMCU[]={0x02,COMM_SET_MCU_IDLE,0x03};	
unsigned char static ComSelfSearchCard[]={0x02,COMM_SELF_SEARCH_CARD,0x0E};

static u8 check_xor_sum(u8 len,u8 *pdata){
	u8 checksum=0;
		while(len)
	{
	  checksum ^= (*pdata);
	  pdata++;
	  len--;
	}

	return checksum;
}
static void Usart2_Send_RFIDCmd(unsigned char len,unsigned char *pdata)
{
		u8 i;
		Usart2_Control_Data.tx_count = 0;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;
		for(i=0;i<len;i++){
			Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = *pdata++;
		}
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = check_xor_sum(len,&Usart2_Control_Data.txbuf[2]);
  	Usart2_Control_Data.tx_index = 0;
		USART_SendData(USART2,Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index++]);
	
}

static void Usart3_Send_RFIDCmd(unsigned char len,unsigned char *pdata)
{
		u8 i;
		Usart3_Control_Data.tx_count = 0;
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = 0x00;
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = 0x00;
		for(i=0;i<len;i++){
			Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = *pdata++;
		}
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = check_xor_sum(len,pdata);
  	Usart3_Control_Data.tx_index = 0;
		USART_SendData(USART3,Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_index++]);
	
}

void Do_Usrat2_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //设置模块空闲睡眠模式
		Usart2_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://模块天线控制、自动寻卡设置
		Usart2_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-A寻卡
		Usart2_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //读块
		Usart2_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://写块
		Usart2_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //初始化钱包
		Usart2_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://读取钱包
		Usart2_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);break ;
	case COMM_INC_VALUE://充值
		Usart2_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //扣款
		Usart2_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //备份钱包值
		Usart2_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://卡休眠
		Usart2_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart2_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}
	
}


void Do_Usrat3_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //设置模块空闲睡眠模式
		Usart3_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://模块天线控制、自动寻卡设置
		Usart3_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-A寻卡
		Usart3_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //读块
		Usart3_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://写块
		Usart3_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //初始化钱包
		Usart3_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://读取钱包
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse6);break ;
	case COMM_INC_VALUE://充值
		Usart3_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //扣款
		Usart3_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //备份钱包值
		Usart3_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://卡休眠
		Usart3_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart3_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}
	
}
