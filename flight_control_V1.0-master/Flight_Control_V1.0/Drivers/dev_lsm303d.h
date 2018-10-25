#ifndef __DEV_LSM303D_H__
#define __DEV_LSM303D_H__
#include "stm32f4xx.h"



#define WHO_I_AM               0X49
#define LSM303D_TEMP_OUT_L     0X05
#define LSM303D_TEMP_OUT_H     0X06

#define LSM303D_STATUS_M       0X07

#define LSM303DLHC_OUT_X_L_M   0X08
#define LSM303DLHC_OUT_X_H_M   0X09

#define LSM303DLHC_OUT_Y_L_M   0X0A
#define LSM303DLHC_OUT_Y_H_M   0X0B

#define LSM303DLHC_OUT_Z_L_M   0X0C
#define LSM303DLHC_OUT_Z_H_M   0X0D

#define LSM303D_WHO_AM_I       0X0F


#define LSM303D_INT_CTRL_M     0X12
#define LSM303D_SRC_M          0X13

#define LSM303D_INT_THS_L_M    0X14
#define LSM303D_INT_THS_H_M    0X15



#define LSM303D_OFFSET_X_L_M   0X16
#define LSM303D_OFFSET_X_H_M   0X17
#define LSM303D_OFFSET_Y_L_M   0X18
#define LSM303D_OFFSET_Y_H_M   0X19
#define LSM303D_OFFSET_Z_L_M   0X1A
#define LSM303D_OFFSET_Z_H_M   0X1B


#define REFERENCE_X            0X1C
#define REFERENCE_Y            0X1D
#define REFERENCE_Z            0X1E

#define LSM303D_CTRL0          0X1F
#define LSM303D_CTRL1          0X20
#define LSM303D_CTRL2          0X21
#define LSM303D_CTRL3          0X22
#define LSM303D_CTRL4          0X23
#define LSM303D_CTRL5          0X24
#define LSM303D_CTRL6          0X25
#define LSM303D_CTRL7          0X26

#define LSM303D_STATUS_A       0X27

#define LSM303D_OUT_X_L_A      0X28
#define LSM303D_OUT_X_H_A      0X29

#define LSM303D_OUT_Y_L_A      0X2A
#define LSM303D_OUT_Y_H_A      0X2B

#define LSM303D_OUT_Z_L_A      0X2C
#define LSM303D_OUT_Z_H_A      0X2D


#define LSM303D_FIFO_CTRL      0X2E
#define LSM303D_FIFO_SRC       0X2F

#define LSM303D_IG_CFG1        0X30
#define LSM303D_IG_SRC1        0X31

#define LSM303D_IG_THS1        0X32
#define LSM303D_IG_DUR1        0X33

#define LSM303D_IG_CFG2        0X34
#define LSM303D_IG_SRC2        0X35


#define LSM303D_IG_THS2        0X36
#define LSM303D_IG_DUR2        0X37

#define LSM303D_CLICK_CFG      0X38
#define LSM303D_CLICK_SRC      0X39
#define LSM303D_CLICK_THS      0X3A

#define LSM303D_TIME_LIMIT     0X3B
#define LSM303D_TIME_LATENCY   0X3C
#define LSM303D_TIME_WINDOW    0X3D

#define LSM303D_Act_THS        0X3E
#define LSM303D_Act_DUR        0X3F


//定义地磁灵敏度,可以参考数据手册

#define LSM303D_FS_2_GA        0X00
#define LSM303D_M_SENSITIVITY_XY_2_1GA       0.08
#define LSM303D_M_SENSITIVITY_Z_2_1GA        0.08

#define LSM303D_FS_4_GA       0x20
#define LSM303D_M_SENSITIVITY_XY_4_1GA       0.16
#define LSM303D_M_SENSITIVITY_Z_4_1GA        0.16

#define LSM303D_FS_8_GA       0x40
#define LSM303D_M_SENSITIVITY_XY_8_1GA       0.32
#define LSM303D_M_SENSITIVITY_Z_8_1GA        0.32

#define LSM303D_FS_12_GA       0x60
#define LSM303D_M_SENSITIVITY_XY_12_1GA       0.479
#define LSM303D_M_SENSITIVITY_Z_12_1GA        0.479





#define LSM303D_FULLSCALE_2G  ((uint8_t)0x00)
#define LSM303D_FULLSCALE_4G  ((uint8_t)0x10)
#define LSM303D_FULLSCALE_8G  ((uint8_t)0x20)
#define LSM303D_FULLSCALE_16G  ((uint8_t)0x30)

#define LSM303D_Acc_Sensitivity_2g  (float)  1
#define LSM303D_Acc_Sensitivity_4g  (float)  2
#define LSM303D_Acc_Sensitivity_8g  (float)  4
#define LSM303D_Acc_Sensitivity_16g  (float) 12





//定义地磁灵敏度,可以参考数据手册
class DEV_LSM303D
{
    public:
		
					typedef struct LSM303D_Acc_Init
					{
						int  Power_Mode;
						int  AccOutput_DataRate;
						int  Axes_Enable;
						int  AccFull_Scale;
						int  BlockData_Update;
						int  Endianness;
						int  High_Resolution;
					}LSM303D_Acc_InitTypeDef;
     			typedef struct LSM303D_Mag_Init
					{
						int  Temperature_Sensor;
						int  MagOutput_DataRate;
						int  MagFull_Scale;
						int  Working_Mode;
					}LSM303D_Mag_InitTypeDef;
					
					int LSM303D_Init(LSM303D_Acc_InitTypeDef *LSM303D_Acc_InitStruct,LSM303D_Mag_InitTypeDef *LSM303D_InitStruct);
					void LSM303D_Get_Sensor_Data(float *mag_data,float *acc_data);
					uint8_t LSM303D_SPI_ReadWriteByte(uint8_t TxData);
					uint8_t LSM303D_Write_Reg(uint8_t reg,uint8_t value);
					uint8_t LSM303D_Read_Reg(uint8_t reg);
					
					void LSM303D_AccInit(LSM303D_Acc_InitTypeDef *LSM303D_Acc_InitStruct);
					void LSM303D_MagInit(LSM303D_Mag_InitTypeDef *LSM303D_InitStruct);
          void LSM303D_Read_Addr_Data(uint8_t regAddr,uint8_t *pBuffer,uint8_t len);
          void LSM303D_ReadMag_Data(float *pfData);  
          void LSM303D_ReadAcc_Data(float *pfData);   	
          void LSM303D_Caloffset_Mag(float *pfData);					
};












#endif