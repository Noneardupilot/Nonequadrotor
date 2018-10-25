#ifndef __DEV_SOFT_IIC__H__
#define __DEV_SOFT_IIC__H__

#include "stm32f4xx.h"


#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define GPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define RCC_I2C_PORT 	RCC_AHB1Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define I2C_SCL_PIN		GPIO_Pin_10			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define I2C_SDA_PIN		GPIO_Pin_11			/* ���ӵ�SDA�����ߵ�GPIO */

/* �����дSCL��SDA�ĺ� */
#define I2C_SCL_1()  GPIO_PORT_I2C->BSRRL = I2C_SCL_PIN				/* SCL = 1 */
#define I2C_SCL_0()  GPIO_PORT_I2C->BSRRH = I2C_SCL_PIN				/* SCL = 0 */

#define I2C_SDA_1()  GPIO_PORT_I2C->BSRRL = I2C_SDA_PIN				/* SDA = 1 */
#define I2C_SDA_0()  GPIO_PORT_I2C->BSRRH = I2C_SDA_PIN				/* SDA = 0 */

#define I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
#define I2C_SCL_READ()  ((GPIO_PORT_I2C->IDR & I2C_SCL_PIN) != 0)	/* ��SCL����״̬ */

class DEV_SOFT_IIC
{
  public:
           void I2C_GpioInit(void);
           void I2C_Start(void);
           void I2C_Stop(void);
	         void I2C_Delay(void);
           void I2C_SendByte(uint8_t _ucByte);
           uint8_t I2C_ReadByte(void);
	         uint8_t I2C_ReadByte1(uint8_t ask);
           uint8_t I2C_WaitAck(void);
           void I2C_Ack(void);
           void I2C_NAck(void);
           uint8_t I2C_CheckDevice(uint8_t _Address);
	         uint8_t IIC_Write_1Byte(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
           uint8_t IIC2_Write_nByte(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t *pBuffer,uint8_t len);
	         uint8_t IIC_Read_nByte(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t len, uint8_t *buf);
          void IIC2_Test_RGBled(void);
};
extern DEV_SOFT_IIC IIC2;  //��������
#endif