#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"

void delay_ms1(u16 ms)
{
	u16  i;
	u32  j;
	for(i=ms;i>0;i--)
	{
		for(j=5000;j>0;j--)
		;
	}
}
//����ʱ����target�궨��
int main(void)
{
		delay_init();
		USART1_Config();
		USART2_Config();
		USART3_Config();
		LED_GPIO_Config();
		KEY_GPIO_Config();
		USART2_Puts("123456");
		USART2_Puts("123456");
    TIM2_Config();
    TIM3_Config();
	//	Do_Usrat3_RFIDCmd(COMM_SELF_SEARCH_CARD);
		delay_ms(100);
    while(1){
			Execute_Host_Comm();
		}       
}




