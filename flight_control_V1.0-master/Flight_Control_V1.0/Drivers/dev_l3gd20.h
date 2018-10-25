#ifndef __DEV_L3GD20_H__
#define __DEV_L3GD20_H__


#include "stm32f4xx.h"




/* SPI protocol address bits */
#define READWRITE_CMD				((uint8_t)0x80)
#define MULTIPLEBYTE_CMD		((uint8_t)0x40)
#define DUMMY_BYTE				  ((uint8_t)0x00)

/* register addresses */
#define L3GD20_ADDR			0xD4

#define L3GD20_WHO_AM_I_ADDR			0x0F

#define L3GD20_ADDR_CTRL_REG1			0x20
#define L3GD20_ADDR_CTRL_REG2			0x21
#define L3GD20_ADDR_CTRL_REG3			0x22
#define L3GD20_ADDR_CTRL_REG4			0x23
#define L3GD20_ADDR_CTRL_REG5			0x24
#define L3GD20_ADDR_REFERENCE			0x25
#define L3GD20_ADDR_OUT_TEMP			0x26
#define L3GD20_ADDR_STATUS_REG			0x27
#define L3GD20_ADDR_OUT_X_L			0x28
#define L3GD20_ADDR_OUT_X_H			0x29
#define L3GD20_ADDR_OUT_Y_L			0x2A
#define L3GD20_ADDR_OUT_Y_H			0x2B
#define L3GD20_ADDR_OUT_Z_L			0x2C
#define L3GD20_ADDR_OUT_Z_H			0x2D
#define L3GD20_ADDR_FIFO_CTRL_REG		0x2E
#define L3GD20_ADDR_FIFO_SRC_REG		0x2F
#define L3GD20_ADDR_INT1_CFG			0x30
#define L3GD20_ADDR_INT1_SRC			0x31
#define L3GD20_ADDR_INT1_TSH_XH		0x32
#define L3GD20_ADDR_INT1_TSH_XL		0x33
#define L3GD20_ADDR_INT1_TSH_YH		0x34
#define L3GD20_ADDR_INT1_TSH_YL		0x35
#define L3GD20_ADDR_INT1_TSH_ZH		0x36
#define L3GD20_ADDR_INT1_TSH_ZL		0x37
#define L3GD20_ADDR_INT1_DURATION		0x38

#define L3GD20_MODE_ACTIVE 		                      (0x08)
#define L3GD20_OUTPUT_DATARATE_1			              (0x00)
#define L3GD20_AXES_ENABLE		                      (0x07)
#define L3GD20_BANDWIDTH_4			                    (0x30)
#define L3GD20_BlockDataUpdate_Continous			      (0x00)
#define L3GD20_BLE_LSB			                        (0x00)
#define L3GD20_FULLSCALE_500			                  (0x10)



#define L3GD20_Sensitivity_250dps            (float)114.285f
#define L3GD20_Sensitivity_500dps            (float)57.1429f
#define L3GD20_Sensitivity_2000dps           (float)14.285f




class DEV_L3GD20
{
    public:
		
					typedef struct 
					{
						int  Power_Mode;
						int  Output_DataRate;
						int  Axes_Enable;
						int  Band_Width;
						int  BlockData_Update;
						int  Endianness;
						int  Full_Scale;
					}L3GD20_InitTypeDef;
					
     			typedef struct 
					{
						uint8_t HighPassFilter_Mode_Selection;
						uint8_t HighPassFilter_CutOff_Frequency;
					}L3GD20_FilterConfigTypeDef;
					
					int L3GD20_Init(L3GD20_InitTypeDef *L3GD20_InitStruct);
		      void L3GD20_Init_Configure(L3GD20_InitTypeDef *L3GD20_InitStruct);
					void L3GD20_Gyro_ReadAngRate(float *pfdata);
					uint8_t L3GD20_SPI_ReadWriteByte(uint8_t TxData);
					uint8_t L3GD20_Write(uint8_t *pBuffer,uint8_t WriteAddr,uint16_t NumByteToWrite);
					void   L3GD20_FilterConfig(L3GD20_FilterConfigTypeDef *L3GD20_FilterStruct);
					void   L3GD20_FilterCmd(uint8_t HighPassFilterState);
					void L3GD20_Read(uint8_t *pBuffer,uint8_t ReadAddr,uint16_t NumByteToRead);
};









#endif
