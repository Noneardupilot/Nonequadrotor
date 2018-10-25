/******************************************************************************************************************
**ͷ�ļ�˵�� �� ���������ļ�����
**ʱ      �� �� 2018-5-9
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע �� Serial4----UART8
**              Serial5----UART7
**              FMU-IO---UART6(PC6---UART6_TX  PC7---UART6_RX)---------�����ʵ�ָ�IO��ͨ�ŵ�
**              Serial3----UART4(PA0---UART4_TX PA1---UART4_RX )
**              Serial2----UART3(PD8---UART3_TX PD9---UART3_RX )
**              Serial1----UART2(PD5---UART2_TX PD6---UART2_RX )----���ӵ���վ
******************************************************************************************************************/


/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

#include "dev_uart.h"
#include "copter.h"

/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

/*********************************************����2����*****************************************************************************************************
                                             ����2��������
***********************************************************************************************************************************************************/

/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart2_Init(uint32_t BaudRate)
**��    �� : LED��ʼ��
**��    �� : None
**��    �� : None
**��    ע : PD5--UART2-TX
             PD6--UART2-RX
**====================================================================================================*/
/*====================================================================================================*/

void DEV_UART::Uart_Init(uint8_t uartx,uint32_t BaudRate)
{
	if(uartx==Config_UART1_DEVICE)
	{
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

			GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART2);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART2);
			
			//PA9---USART1 Tx   PA10---USART1 Rx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
			GPIO_Init(GPIOA, &GPIO_InitStructure); 

			
			//����USART1
			//�жϱ�������
			USART_InitStructure.USART_BaudRate = BaudRate;               //������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
			USART_InitStructure.USART_StopBits = USART_StopBits_1;   //1��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ�������Ʋ�ʹ��
			USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��
			USART_Init(USART1, &USART_InitStructure);
      USART_Cmd(USART1, ENABLE); 

			//ʹ��USART1�����ж�
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			//�ж����ȼ�����
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	
	
	}
	else if(uartx==Config_UART2_DEVICE) //��������
	{   
			USART_InitTypeDef USART_InitStructure;
			USART_ClockInitTypeDef USART_ClockInitStruct;
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	
			
			//�ж����ȼ�����
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	

			
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
			
			//PD5---USART2 Tx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
			GPIO_Init(GPIOD, &GPIO_InitStructure); 
			//PD6---USART2 Rx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
			GPIO_Init(GPIOD, &GPIO_InitStructure); 
			
			//����USART2
			//�жϱ�������
			USART_InitStructure.USART_BaudRate = BaudRate;               //������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
			USART_InitStructure.USART_StopBits = USART_StopBits_1;   //1��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ�������Ʋ�ʹ��
			USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��

			USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
			USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  
			USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  
			USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; 
			
			USART_Init(USART2, &USART_InitStructure);
			USART_ClockInit(USART2, &USART_ClockInitStruct);

			//ʹ��USART2�����ж�
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			//ʹ��USART2
			USART_Cmd(USART2, ENABLE); 
	
	}
		else if(uartx==Config_UART3_DEVICE)//uart3----ͨ��Э��
	{
			USART_InitTypeDef USART_InitStructure;
			USART_ClockInitTypeDef USART_ClockInitStruct;
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	
			
			//�ж����ȼ�����
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	

			
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
			
			//PD8---USART3 Tx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
			GPIO_Init(GPIOD, &GPIO_InitStructure); 
			//PD9---USART3 Rx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
			GPIO_Init(GPIOD, &GPIO_InitStructure); 
			
			//����USART3
			//�жϱ�������
			USART_InitStructure.USART_BaudRate = BaudRate;               //������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
			USART_InitStructure.USART_StopBits = USART_StopBits_1;   //1��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ�������Ʋ�ʹ��
			USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��

			USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
			USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  
			USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  
			USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; 
			
			USART_Init(USART3, &USART_InitStructure);
			USART_ClockInit(USART3, &USART_ClockInitStruct);

			//ʹ��USART3�����ж�
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			//ʹ��USART3
			USART_Cmd(USART3, ENABLE); 
	}
		else if(uartx==Config_UART4_DEVICE) //Uart4---GPS
	{
	    USART_InitTypeDef USART_InitStructure;
			USART_ClockInitTypeDef USART_ClockInitStruct;
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	
			
			//�ж����ȼ�����
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	

			
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
			
			//PA0---UART4 Tx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
			GPIO_Init(GPIOA, &GPIO_InitStructure); 
			//PA1---UART4 Rx
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
			GPIO_Init(GPIOA, &GPIO_InitStructure); 
			
			//����USART4
			//�жϱ�������
			USART_InitStructure.USART_BaudRate = BaudRate;               //������
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
			USART_InitStructure.USART_StopBits = USART_StopBits_1;   //1��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ�������Ʋ�ʹ��
			USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��

			USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
			USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  
			USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  
			USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; 
			
			USART_Init(UART4, &USART_InitStructure);
			USART_ClockInit(UART4, &USART_ClockInitStruct);

			//ʹ��USART4�����ж�
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			//ʹ��USART4
			USART_Cmd(UART4, ENABLE); 
	}
		else if(uartx==Config_UART5_DEVICE)
	{
		
	
	}
		else if(uartx==Config_UART6_DEVICE)
	{
	
	}
		else if(uartx==Config_UART7_DEVICE)
	{
	
	}
		else if(uartx==Config_UART8_DEVICE)
	{
	
	}

}

/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart2_IRQ(void)
**��    �� : UART2�жϷ�����
**��    �� : None
**��    �� : None
**��    ע : PD5--UART2-TX
             PD6--UART2-RX
**====================================================================================================*/
/*====================================================================================================*/
void DEV_UART::Usart2_IRQ(void)
{
	u8 com_data;
	
	if(USART2->SR & USART_SR_ORE)//ORE�ж�
	{
		com_data = USART2->DR;
	}

  //�����ж�
	if( USART_GetITStatus(USART2,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//����жϱ�־

		com_data = USART2->DR;
		Protocol.Communicate_DT_Data_Receive_Prepare(com_data); //�����ⲿ�ж�
	}
	//����(������λ)
	if( USART_GetITStatus(USART2,USART_IT_TXE ) )
	{
				
		USART2->DR = UART2_TxBuffer[UART2_TxCounter++]; //дDR����жϱ�־       
		if(UART2_TxCounter == UART2_count)
		{
			USART2->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE(�����ж�)�ж�
		}

	}
}


/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart2_Send(unsigned char *DataToSend ,u8 data_num)
**��    �� : UART2����
**��    �� : None
**��    �� : None
**��    ע : PD5--UART2-TX
             PD6--UART2-RX
**====================================================================================================*/
/*====================================================================================================*/
void DEV_UART::Usart2_Send(unsigned char *DataToSend ,u8 data_num)
{
  u8 i;
	for(i=0;i<data_num;i++)
	{
		UART2_TxBuffer[UART2_count++] = *(DataToSend+i);
	}

	if(!(USART2->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}

}



/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart3_IRQ(void)
**��    �� : UART2�жϷ�����
**��    �� : None
**��    �� : None
**��    ע :
**====================================================================================================*/
/*====================================================================================================*/

void DEV_UART::Usart3_IRQ(void)
{
	u8 com_data;
	
  //�����ж�
	if( USART_GetITStatus(USART3,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//����жϱ�־

		com_data = USART3->DR;
		//Ultrasonic_Get_distance(com_data);  //�����жϣ���ȡ����������

	}
	//����(������λ)
	if( USART_GetITStatus(USART3,USART_IT_TXE ) )
	{
				
		USART3->DR = UART3_TxBuffer[UART3_TxCounter++]; //дDR����жϱ�־       
		if(UART3_TxCounter == UART3_count)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE(�����ж�)�ж�
		}

	}
}


/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart3_Send(unsigned char *DataToSend ,u8 data_num)
**��    �� : UART1����
**��    �� : None
**��    �� : None
**��    ע : 
**====================================================================================================*/
/*====================================================================================================*/
void DEV_UART::Usart3_Send(unsigned char *DataToSend ,u8 data_num)
{
  u8 i;
	for(i=0;i<data_num;i++)
	{
		UART3_TxBuffer[UART3_count++] = *(DataToSend+i);
	}

	if(!(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}

}

/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void Usart4_IRQ(void)
**��    �� : UART2�жϷ�����
**��    �� : None
**��    �� : None
**��    ע :
**====================================================================================================*/
/*====================================================================================================*/

void DEV_UART::Usart4_IRQ(void)
{
	u8 com_data;
	
  //�����ж�
	if( USART_GetITStatus(UART4,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//����жϱ�־

		com_data = UART4->DR;
		//Ultrasonic_Get_distance(com_data);  //�����жϣ���ȡ����������

	}
	//����(������λ)
	if( USART_GetITStatus(UART4,USART_IT_TXE ) )
	{
				
		UART4->DR = UART4_TxBuffer[UART4_TxCounter++]; //дDR����жϱ�־       
		if(UART4_TxCounter == UART4_count)
		{
			UART4->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE(�����ж�)�ж�
		}

	}
}


/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : void DEV_UART::Usart4_Send(unsigned char *DataToSend ,u8 data_num)
**��    �� : UART4����
**��    �� : None
**��    �� : None
**��    ע : 
**====================================================================================================*/
/*====================================================================================================*/
void DEV_UART::Usart4_Send(unsigned char *DataToSend ,u8 data_num)
{
  u8 i;
	for(i=0;i<data_num;i++)
	{
		UART4_TxBuffer[UART4_count++] = *(DataToSend+i);
	}

	if(!(UART4->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(UART4, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}

}



/**********************************************************************************************************
*                                      file---end
**********************************************************************************************************/