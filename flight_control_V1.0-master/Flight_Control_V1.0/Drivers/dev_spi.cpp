/******************************************************************************************************************
**ͷ�ļ�˵�� �� spi��������
**ʱ      �� �� 2018-5-9
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע �� SPI1���ö�ȡIMU������
**                   PA5---SPI1_SCK
**                   PA6---SPI1_MISO
**                   PA7---SPI1_MOSI
**                   PC2---MPU_CS      ---MPU6000   PD15---MPU6000_DRDY
**                   PD7---BARO_CS     ---MS5611   
**                   PC13---GYRO_CS    ---L3GD20    PB0---GYRO_DRDY
**                   PC15---ACCEL_CS   ---LSM303D   PB1---MAG_DRDY  PB14---ACCEL_MAG
**              SPI2���� ������ȡFM25V01�ڴ�оƬ
**                   PB13---SPI2_SCK
**                   PB14---SPI2_MISO
**                   PB15---SPI2_MOSI
**                   PD10---SPI2_CS      
**              SPI4������ӵĴ���������
**                   PE2---SPI4_SCK
**                   PE4---SPI4_CS
**                   PE5---SPI4_MISO
**                   PE6---SPI4_CS  
******************************************************************************************************************/


/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

#include "dev_spi.h"
#include "copter.h"

/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/
DEV_SPI Spi1;  //��������Spi1
/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI_Init(uint8_t SPIx)
**��    �� : SPI�����ʼ������
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	

void DEV_SPI::SPI_Configure_Init(uint8_t SPIx)
{
   if(SPIx==Config_SPI1_DEVICE) //����SPI1
	 {
				GPIO_InitTypeDef GPIO_InitStructure;
				SPI_InitTypeDef  SPI_InitStructure;

				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

				GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				 
				 //SPI1 ���ù��ܴ�
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
			

				//flash SPI1 CS----PC2-PC13-PC15
				GPIO_InitStructure.GPIO_Pin= GPIO_Pin_2|GPIO_Pin_13|GPIO_Pin_15;  //
				GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_OUT ;   
				GPIO_InitStructure.GPIO_OType           = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd            = GPIO_PuPd_UP;
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				GPIO_SetBits(GPIOC, GPIO_Pin_2|GPIO_Pin_13|GPIO_Pin_15);	
				//PD7	
				GPIO_InitStructure.GPIO_Pin= GPIO_Pin_7;  //
				GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_OUT ;   
				GPIO_InitStructure.GPIO_OType           = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd            = GPIO_PuPd_UP;
				GPIO_Init(GPIOD, &GPIO_InitStructure);
				GPIO_SetBits(GPIOD, GPIO_Pin_7);	
				
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1 ,ENABLE);  //��λSPI1
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1 ,DISABLE);  //��λSPI1
				
				//����SPI1
				SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
				SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
				SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
				SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
				SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
				SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
				SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
				SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
				SPI_InitStructure.SPI_CRCPolynomial     = 7;
				SPI_Init(SPI1, &SPI_InitStructure);
				SPI_Cmd(SPI1, ENABLE);
				SPI1_ReadWriteByte(0xff);
				SPI1_SetSpeed(SPI_BaudRatePrescaler_4);
	 }
	 else if(SPIx==Config_SPI2_DEVICE)  //����SPI2
	 {
				GPIO_InitTypeDef GPIO_InitStructure;
				SPI_InitTypeDef  SPI_InitStructure;

				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

				GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				 
				 //SPI2 ���ù��ܴ�
				GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
				GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
				GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
			

				//SPI2 CS----PD10
				GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;  //
				GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_OUT ;   
				GPIO_InitStructure.GPIO_OType           = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd            = GPIO_PuPd_NOPULL;
				GPIO_Init(GPIOD, &GPIO_InitStructure);
				GPIO_SetBits(GPIOD, GPIO_Pin_10);	
	
				//����SPI1
		 
				SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
				SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
				SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
				SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
				SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
				SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
				SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
				SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
				SPI_InitStructure.SPI_CRCPolynomial     = 7;
				SPI_Init(SPI2, &SPI_InitStructure);
				SPI_Cmd(SPI2, ENABLE);
				SPI2_ReadWriteByte(0xff);
				SPI2_SetSpeed(SPI_BaudRatePrescaler_4);
	 
	 
	 }
	 else if(SPIx==Config_SPI4_DEVICE)//����SPI4
	 {
	      GPIO_InitTypeDef GPIO_InitStructure;
				SPI_InitTypeDef  SPI_InitStructure;

				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);

				GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6;
				GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
				 
				 //SPI4���ù��ܴ�
				GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
				GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_SPI4);
				GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);
			

				//SPI4 CS----PD10
				GPIO_InitStructure.GPIO_Pin= GPIO_Pin_4;  //
				GPIO_InitStructure.GPIO_Mode            = GPIO_Mode_OUT ;   
				GPIO_InitStructure.GPIO_OType           = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed           = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd            = GPIO_PuPd_NOPULL;
				GPIO_Init(GPIOE, &GPIO_InitStructure);
				GPIO_SetBits(GPIOE, GPIO_Pin_4);	
	
	      			
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4 ,ENABLE);  //��λSPI4
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4 ,DISABLE);  //��λSPI4
				//����SPI4
				SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
				SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
				SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
				SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
				SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
				SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
				SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
				SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
				SPI_InitStructure.SPI_CRCPolynomial     = 7;
				SPI_Init(SPI4, &SPI_InitStructure);
				SPI_Cmd(SPI4, ENABLE);
				SPI4_ReadWriteByte(0xff);
				SPI4_SetSpeed(SPI_BaudRatePrescaler_4);
	 }
}


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**��    �� : SPI�����ٶ�
**��    �� : SPI_BaudRatePrescaler���ٶ�
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI1->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI1,ENABLE); //ʹ��SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**��    �� : SPI1��д
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
{		 			 
  int SPI1Timeout=0xffff;
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  {
	  if((SPI1Timeout--)==0)
			return 1;
	
	}
		
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ��byte  ����
	SPI1Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//�ȴ�������һ��byte  
  {
	  	  if((SPI1Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
    
}


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**��    �� : SPI2�����ٶ�
**��    �� : SPI_BaudRatePrescaler���ٶ�
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI2->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI2,ENABLE); //ʹ��SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**��    �� : SPI2��д
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_SPI::SPI2_ReadWriteByte(uint8_t TxData)
{		 			 
  int SPI2Timeout=0xffff;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
  {
	  if((SPI2Timeout--)==0)
			return 1;
	
	}
		
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ��byte  ����
	SPI2Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//�ȴ�������һ��byte  
  {
	  	  if((SPI2Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����	
    
}


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI4_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**��    �� : SPI4�����ٶ�
**��    �� : SPI_BaudRatePrescaler���ٶ�
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI4_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI4->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI4->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI4,ENABLE); //ʹ��SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**��    �� : SPI4��д
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_SPI::SPI4_ReadWriteByte(uint8_t TxData)
{		 			 
  int SPI4Timeout=0xffff;
  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET)
  {
	  if((SPI4Timeout--)==0)
			return 1;
	
	}
		
	SPI_I2S_SendData(SPI4, TxData); //ͨ������SPIx����һ��byte  ����
	SPI4Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_RXNE) == RESET)//�ȴ�������һ��byte  
  {
	  	  if((SPI4Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI4); //����ͨ��SPIx������յ�����	
    
}


/**********************************************************************************************************************
*                                      file---end
**********************************************************************************************************************/

