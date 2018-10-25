#ifndef __DEV_HARD_IIC_H__
#define __DEV_HARD_IIC_H__

#include "stm32f4xx.h"

class DEV_HARD_IIC
{
  public:
		void I2C_Hard_Init(void);
	  void Hard_IIC_Test_RGBled(void);
	  void I2C_WriteBytes(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t Reg_addr,uint8_t*pBuffer,uint8_t len);
    uint8_t I2C_ReadOneByte(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t Reg_addr);
};
extern DEV_HARD_IIC  Hard_IIC2;

#endif