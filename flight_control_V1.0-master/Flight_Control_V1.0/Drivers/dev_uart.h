#ifndef  __DEV_UART__H__
#define  __DEV_UART__H__




#include "stm32f4xx.h"


class DEV_UART
{
  public:
		     void Uart_Init(uint8_t uartx,uint32_t BaudRate);
	       void Usart2_IRQ(void);
	       void Usart2_Send(unsigned char *DataToSend ,u8 data_num);
		     void Usart3_IRQ(void);
	       void Usart3_Send(unsigned char *DataToSend ,u8 data_num);
		     void Usart4_IRQ(void);
	       void Usart4_Send(unsigned char *DataToSend ,u8 data_num);
	
         uint8_t UART2_TxBuffer[256];
         uint8_t UART2_TxCounter;
         uint8_t UART2_count; 
         uint8_t UART2_Rx_Buf[256];	//串口接收缓存
	
	       uint8_t UART3_TxBuffer[256];
         uint8_t UART3_TxCounter;
         uint8_t UART3_count; 
         uint8_t UART3_Rx_Buf[256];	//串口接收缓存
	
	       uint8_t UART4_TxBuffer[256];
         uint8_t UART4_TxCounter;
         uint8_t UART4_count; 
         uint8_t UART4_Rx_Buf[256];	//串口接收缓存
  private:
		     enum
        {
					Config_UART1_DEVICE=1,
					Config_UART2_DEVICE=2,
					Config_UART3_DEVICE=3,
					Config_UART4_DEVICE=4,
					Config_UART5_DEVICE=5,
					Config_UART6_DEVICE=6,
					Config_UART7_DEVICE=7,
					Config_UART8_DEVICE=8,
        };


};









#endif