#ifndef __DEV_SPI_H__
#define __DEV_SPI_H__

#include "stm32f4xx.h"


class DEV_SPI
{
  public:
		     void SPI_Configure_Init(uint8_t SPIx);
         void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler);
	       uint8_t SPI1_ReadWriteByte(uint8_t TxData);
	
	       void SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler);
	       uint8_t SPI2_ReadWriteByte(uint8_t TxData);
	
	       void SPI4_SetSpeed(uint8_t SPI_BaudRatePrescaler);
	       uint8_t SPI4_ReadWriteByte(uint8_t TxData);
  private:
		     enum
        {
					Config_SPI1_DEVICE=1,
					Config_SPI2_DEVICE=2,
					Config_SPI4_DEVICE=4
        };


};

extern DEV_SPI Spi1;  //创建对象Spi1
#endif