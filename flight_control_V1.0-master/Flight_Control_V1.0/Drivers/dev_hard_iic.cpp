/******************************************************************************************************************
**ͷ�ļ�˵�� �� Ӳ��iic��������
**ʱ      �� �� 2018-5-16
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע ��������ɿ���ʹ��
******************************************************************************************************************/


/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

#include "dev_hard_iic.h"
#include "copter.h"

/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/
static unsigned int ulTimeOut_Time=0xffff;
unsigned int  I2C_Err=0;

DEV_HARD_IIC  Hard_IIC2;
/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_HARD_IIC::IIC_Hard_Init(void)
**��    �� : Ӳ��IIC��ʼ��
**��    �� : None
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_HARD_IIC::I2C_Hard_Init(void)
{
 	//�ȶ���ṹ��
	GPIO_InitTypeDef	 GPIO_InitStructure;
  I2C_InitTypeDef    I2C_InitStructure;
	RCC_ClocksTypeDef  rcc_clocks;
	//Ҫ���˶�Ӧ��gpio��ʱ�ӻ��������������ʱ�ӣ�Ȼ�������üĴ����ſ��ԣ�����������濪ʱ���Ⱥ�û��Ӱ�죬����ʵ�����棬Ҫ�ȿ�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	//ʹ��AHB1�����GPIOB��ʱ��,I2C2��PB_10 SCL��PB_11 SDA����ĸ���	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2 ,ENABLE);  //����iic2ʱ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 ,ENABLE);  //��λIIC2ʱ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 ,DISABLE);  //��λIIC2ʱ��
	
	//ʹ�ܶ˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 	//ѡ��PB_10 ��SCL����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //���ģʽΪ���ÿ�©���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ܽ�Ƶ��Ϊ50MHZ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);				 //��ʼ��GPIOB�Ĵ���
	
	//����ӳ��,��Ҫ�ֿ�����
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_I2C2);
	//����I2C2��ģʽ
	I2C_DeInit(I2C2);
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;     
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  /*����CCR�Ĵ����ģ�ռ�ձ�  ����ģʽ��0:Tlow/Thigh = 2��1:Tlow/Thigh = 16/9 */
	I2C_InitStructure.I2C_OwnAddress1 = 0xA0 ;         /*��仰˵����stm32��Ϊ�ӻ���ʱ�����ĵ�ַ�����û�����ӻ�����������ֵ*/
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;        /*Ӧ��ʹ�� */
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; /* */
	I2C_InitStructure.I2C_ClockSpeed = 100000;          /*I2C��ʱ��Ƶ��400kHz ������I2C����ʱ�ӵ�Ƶ��*/
	I2C_Init(I2C2,&I2C_InitStructure);
	I2C_Cmd(I2C2, ENABLE);	//ʹ��I2C
	RCC_GetClocksFreq(&rcc_clocks);
	ulTimeOut_Time=(rcc_clocks.SYSCLK_Frequency/10000);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_HARD_IIC::IIC_Hard_Init(void)
**��    �� : Ӳ��IIC��ʼ��
**��    �� : None
**��    �� : None
**��    ע : 
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
**����ԭ�� : void DEV_HARD_IIC::IIC_Hard_Init(void)
**��    �� : Ӳ��IIC��ʼ��
**��    �� : None
**��    �� : None
**��    ע : 
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
**����ԭ�� : void DEV_HARD_IIC::Hard_IIC_Test_RGBled(void)
**��    �� : Ӳ��IIC����
**��    �� : None
**��    �� : None
**��    ע : 
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

