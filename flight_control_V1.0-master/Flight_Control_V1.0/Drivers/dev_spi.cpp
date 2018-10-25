/******************************************************************************************************************
**头文件说明 ： spi驱动配置
**时      间 ： 2018-5-9
**作      者 ： 历小伟
**联系 方式  ： 15982962929
**备      注 ： SPI1配置读取IMU传感器
**                   PA5---SPI1_SCK
**                   PA6---SPI1_MISO
**                   PA7---SPI1_MOSI
**                   PC2---MPU_CS      ---MPU6000   PD15---MPU6000_DRDY
**                   PD7---BARO_CS     ---MS5611   
**                   PC13---GYRO_CS    ---L3GD20    PB0---GYRO_DRDY
**                   PC15---ACCEL_CS   ---LSM303D   PB1---MAG_DRDY  PB14---ACCEL_MAG
**              SPI2配置 用来读取FM25V01内存芯片
**                   PB13---SPI2_SCK
**                   PB14---SPI2_MISO
**                   PB15---SPI2_MOSI
**                   PD10---SPI2_CS      
**              SPI4配置外接的传感器数据
**                   PE2---SPI4_SCK
**                   PE4---SPI4_CS
**                   PE5---SPI4_MISO
**                   PE6---SPI4_CS  
******************************************************************************************************************/


/*=============================================================================================================
                                         头文件START
==============================================================================================================*/

#include "dev_spi.h"
#include "copter.h"

/*=============================================================================================================
                                         头文件START
==============================================================================================================*/
DEV_SPI Spi1;  //创建对象Spi1
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_SPI::SPI_Init(uint8_t SPIx)
**功    能 : SPI软件初始化配置
**输    入 : SPIx确定配置哪个SPI
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	

void DEV_SPI::SPI_Configure_Init(uint8_t SPIx)
{
   if(SPIx==Config_SPI1_DEVICE) //配置SPI1
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
				 
				 //SPI1 复用功能打开
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
				
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1 ,ENABLE);  //复位SPI1
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1 ,DISABLE);  //复位SPI1
				
				//配置SPI1
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
	 else if(SPIx==Config_SPI2_DEVICE)  //配置SPI2
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
				 
				 //SPI2 复用功能打开
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
	
				//配置SPI1
		 
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
	 else if(SPIx==Config_SPI4_DEVICE)//配置SPI4
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
				 
				 //SPI4复用功能打开
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
	
	      			
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4 ,ENABLE);  //复位SPI4
				RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4 ,DISABLE);  //复位SPI4
				//配置SPI4
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
**函数原型 : void DEV_SPI::SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**功    能 : SPI设置速度
**输    入 : SPI_BaudRatePrescaler：速度
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI1->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); //使能SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**功    能 : SPI1读写
**输    入 : SPIx确定配置哪个SPI
**输    出 : None
**备    注 : 
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
		
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
	SPI1Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//等待接收完一个byte  
  {
	  	  if((SPI1Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
    
}


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_SPI::SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**功    能 : SPI2设置速度
**输    入 : SPI_BaudRatePrescaler：速度
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI2->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI2,ENABLE); //使能SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**功    能 : SPI2读写
**输    入 : SPIx确定配置哪个SPI
**输    出 : None
**备    注 : 
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
		
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个byte  数据
	SPI2Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//等待接收完一个byte  
  {
	  	  if((SPI2Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据	
    
}


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_SPI::SPI4_SetSpeed(uint8_t SPI_BaudRatePrescaler)
**功    能 : SPI4设置速度
**输    入 : SPI_BaudRatePrescaler：速度
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_SPI::SPI4_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI4->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI4->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI4,ENABLE); //使能SPI1
} 


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : uint8_t DEV_SPI::SPI1_ReadWriteByte(uint8_t TxData)
**功    能 : SPI4读写
**输    入 : SPIx确定配置哪个SPI
**输    出 : None
**备    注 : 
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
		
	SPI_I2S_SendData(SPI4, TxData); //通过外设SPIx发送一个byte  数据
	SPI4Timeout=0xffff;	
  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_RXNE) == RESET)//等待接收完一个byte  
  {
	  	  if((SPI4Timeout--)==0)
			  return 1;
	} 
 
	return SPI_I2S_ReceiveData(SPI4); //返回通过SPIx最近接收的数据	
    
}


/**********************************************************************************************************************
*                                      file---end
**********************************************************************************************************************/

