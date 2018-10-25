/******************************************************************************************************************
**头文件说明 ： 硬件iic驱动配置
**时      间 ： 2018-5-16
**作      者 ： 历小伟
**联系 方式  ： 15982962929
**备      注 ：测试完成可以使用
******************************************************************************************************************/


/*=============================================================================================================
                                         头文件START
==============================================================================================================*/

#include "dev_hard_iic.h"
#include "copter.h"

/*=============================================================================================================
                                         头文件START
==============================================================================================================*/
static unsigned int ulTimeOut_Time=0xffff;
unsigned int  I2C_Err=0;

DEV_HARD_IIC  Hard_IIC2;
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_HARD_IIC::IIC_Hard_Init(void)
**功    能 : 硬件IIC初始化
**输    入 : None
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_HARD_IIC::I2C_Hard_Init(void)
{
 	//先定义结构体
	GPIO_InitTypeDef	 GPIO_InitStructure;
  I2C_InitTypeDef    I2C_InitStructure;
	RCC_ClocksTypeDef  rcc_clocks;
	//要开了对应的gpio的时钟还有其他的外设的时钟，然后你配置寄存器才可以，软件仿真里面开时钟先后没有影响，但是实物里面，要先开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	//使能AHB1外设的GPIOB的时钟,I2C2是PB_10 SCL，PB_11 SDA上面的复用	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2 ,ENABLE);  //开启iic2时钟
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 ,ENABLE);  //复位IIC2时钟
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 ,DISABLE);  //复位IIC2时钟
	
	//使能端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 	//选择PB_10 是SCL引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //输出模式为复用开漏输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //管脚频率为50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);				 //初始化GPIOB寄存器
	
	//打开重映射,需要分开设置
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C2);
	//配置I2C2的模式
	I2C_DeInit(I2C2);
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;     
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  /*设置CCR寄存器的，占空比  快速模式下0:Tlow/Thigh = 2；1:Tlow/Thigh = 16/9 */
	I2C_InitStructure.I2C_OwnAddress1 = 0xA0 ;         /*这句话说的是stm32作为从机的时候它的地址，如果没有做从机不用理会这个值*/
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;        /*应答使能 */
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; /* */
	I2C_InitStructure.I2C_ClockSpeed = 100000;          /*I2C的时钟频率400kHz ，不是I2C输入时钟的频率*/
	I2C_Init(I2C2,&I2C_InitStructure);
	I2C_Cmd(I2C2, ENABLE);	//使能I2C
	RCC_GetClocksFreq(&rcc_clocks);
	ulTimeOut_Time=(rcc_clocks.SYSCLK_Frequency/10000);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_HARD_IIC::IIC_Hard_Init(void)
**功    能 : 硬件IIC初始化
**输    入 : None
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_HARD_IIC::I2C_WriteBytes(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t Reg_addr,uint8_t*pBuffer,uint8_t len)
{
  uint8_t tmr;
  uint8_t i;
	I2C_GenerateSTART(I2Cx,ENABLE);
	
	tmr=ulTimeOut_Time;
  while((--tmr)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
	
  I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
	
	tmr=ulTimeOut_Time;
  while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));  
  
  I2C_SendData(I2Cx,Reg_addr);  
  tmr=ulTimeOut_Time;
  while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)));  
  for(i=0;i<len;i++)
	{
	  I2C_SendData(I2Cx,*pBuffer); 
		tmr=ulTimeOut_Time;
		while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)));  
		pBuffer++;
	}
	I2C_GenerateSTOP(I2Cx,ENABLE);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_HARD_IIC::IIC_Hard_Init(void)
**功    能 : 硬件IIC初始化
**输    入 : None
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	

uint8_t DEV_HARD_IIC::I2C_ReadOneByte(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t Reg_addr)
{ 
	uint8_t readout;
  uint32_t tmr;
	tmr=ulTimeOut_Time;
	while((--tmr)&&(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)));
	if(tmr==0)I2C_Err=1;
	
	I2C_GenerateSTART(I2Cx,ENABLE);
	
	tmr=ulTimeOut_Time;
  while((--tmr)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
	if(tmr==0)I2C_Err=1;	
	
  I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
	
	tmr=ulTimeOut_Time;
  while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));  
	
  if(tmr==0)I2C_Err=1;	
  I2C_SendData(I2Cx,Reg_addr);  
	
  tmr=ulTimeOut_Time;
	
  while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)));  
	if(tmr==0)I2C_Err=1;	
	
	I2C_GenerateSTART(I2Cx,ENABLE);
	tmr=ulTimeOut_Time;
	while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT)));
	if(tmr==0)I2C_Err=1;	
	
	I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Receiver);
	tmr=ulTimeOut_Time;
	while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));
	if(tmr==0)I2C_Err=1;	
	I2C_AcknowledgeConfig(I2Cx,DISABLE);
	I2C_GenerateSTOP(I2Cx,ENABLE);
	tmr=ulTimeOut_Time;
	while((--tmr)&&(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED)));
	if(tmr==0)I2C_Err=1;	
	
	readout=I2C_ReceiveData(I2Cx);
  I2C_AcknowledgeConfig(I2Cx,ENABLE);
	return readout;
 
}


/*=======================================================================================================================*/
/*=======================================================================================================================*
**函数原型 : void DEV_HARD_IIC::Hard_IIC_Test_RGBled(void)
**功    能 : 硬件IIC测试
**输    入 : None
**输    出 : None
**备    注 : 
**=====================================================================================================================*/
/*=====================================================================================================================*/	
void DEV_HARD_IIC::Hard_IIC_Test_RGBled(void)
{
	I2C_WriteBytes(I2C2,DEV_RGBLED_Driver_Write_ADDR,0x01,&DEV_RGBLED_Color_Index[0][0],4);
	System_set.delay_ms(500); 
  I2C_WriteBytes(I2C2,DEV_RGBLED_Driver_Write_ADDR,0x01,&DEV_RGBLED_Color_Index[1][0],4);
	System_set.delay_ms(500); 
	I2C_WriteBytes(I2C2,DEV_RGBLED_Driver_Write_ADDR,0x01,&DEV_RGBLED_Color_Index[2][0],4);
	System_set.delay_ms(500); 
  I2C_WriteBytes(I2C2,DEV_RGBLED_Driver_Write_ADDR,0x01,&DEV_RGBLED_Color_Index[3][0],4);
	System_set.delay_ms(500); 

}

/**************************************************************************************************************************
*                                      file---end
**************************************************************************************************************************/

