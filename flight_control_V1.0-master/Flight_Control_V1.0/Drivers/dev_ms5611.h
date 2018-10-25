#ifndef __DEV_MS5611_H__
#define __DEV_MS5611_H__
#include "stm32f4xx.h"



//#define USE_IIC_MS5611   //采用IIC驱动MS5611
#define USE_SPI_MS5611   //采用SPI驱动MS5611
#define MS5611_PROM_REG_COUNT 6 // number of registers in the PROM
#define MS5611_PROM_REG_SIZE 2 // size in bytes of a prom registry.
#define BARO_CAL_CNT 200          //TEMP=2000+dt*c6/2^23
#define MS5611_ADDR             0x77   //0xee //

#define MS5611_CMD_RESET               0x1E // ADC reset command
#define MS5611_CMD_ADC_READ            0x00 // ADC read command
#define MS5611_CMD_ADC_CONV            0x40 // ADC conversion command
#define MS5611_CMD_ADC_D1              0x00 // ADC D1 conversion
#define MS5611_CMD_ADC_D2              0x10 // ADC D2 conversion
#define MS5611_D2 0x50

#define MS5611_CMD_ADC_256             0x00 // ADC OSR=256
#define MS5611_CMD_ADC_512             0x02 // ADC OSR=512
#define MS5611_CMD_ADC_1024            0x04 // ADC OSR=1024
#define MS5611_CMD_ADC_2048            0x06 // ADC OSR=2048
#define MS5611_CMD_ADC_4096            0x08 // ADC OSR=4096
#define MS5611_CMD_PROM_RD             0xA0 // Prom read command
#define MS5611_PROM_BASE_ADDR 0xA2
#define MS5611_PROM_NB                 8
#define MS5611_OSR							0x08	//CMD_ADC_4096

// Self test parameters. Only checks that values are sane
#define MS5611_ST_PRESS_MAX   (1100.0f) //mbar
#define MS5611_ST_PRESS_MIN   (450.0f)  //mbar
#define MS5611_ST_TEMP_MAX    (60.0f)   //degree celcius
#define MS5611_ST_TEMP_MIN    (-20.0f)  //degree celcius
#define EXTRA_PRECISION      5 // trick to add more precision to the pressure and temp readings
#define MS5611_D1D2_SIZE 3
#define PRESSURE_PER_TEMP 3 

class DEV_MS5611
{
	public:
		

	
	      //IIC函数配置
				void IIC_MS5611_Reset(void);
				uint8_t IIC_MS5611_Read_Prom(void);
				void IIC_MS5611_Read_Adc_Temperature(void);
				void IIC_MS5611_Read_Adc_Pressure(void);
				void IIC_MS5611_Start_Temperature(void);
				void IIC_MS5611_Start_Press(void);
				void IIC_MS5611_Init(void);
				int  IIC_MS5611_Update(void);

				void IIC_MS5611_BaroAltCalculate(void);
				int32_t IIC_MS5611_Get_BaroAlt(void);
				double IIC_Calculator_Ms5611_Alititude(int32_t MS5611_baroAlt);

        uint32_t ms5611_ut;              // 静态温度测量结果
				uint32_t ms5611_up;             // 静态压力测量结果
				uint16_t ms5611_prom[MS5611_PROM_NB];  // on-chip ROM
				uint8_t temp_rxbuf[3],press_rxbuf[3];
	      int32_t baroAlt,baroAltOld;
   

        //SPI函数配置
        uint8_t SPI_MS5611_Init(void);

				//返回值:0，成功;1，失败	
				uint8_t SPI_MS5611_SelfTest(void);

				uint8_t SPI_MS5611_EvaluateSelfTest(float min, float max, float value, char* string);

				float SPI_MS5611_GetPressure(uint8_t osr);
				float SPI_MS5611_CalcPressure(int32_t rawPress, int32_t dT);
				float SPI_MS5611_GetTemperature(uint8_t osr);
				float SPI_MS5611_CalcTemp(int32_t deltaT);
				int32_t SPI_MS5611_GetDeltaTemp(uint8_t osr);
				int32_t SPI_MS5611_CalcDeltaTemp(int32_t rawTemp);
				int32_t SPI_MS5611_RawPressure(uint8_t osr);
				int32_t SPI_MS5611_RawTemperature(uint8_t osr);

				uint8_t SPI_MS5611_ReadPROM(void);

				void SPI_MS5611_StartConversion(uint8_t command);
				int32_t SPI_MS5611_GetConversion(uint8_t command);


				void  SPI_MS5611_GetData(float* pressure, float* temperature, float* asl);
				float SPI_MS5611_PressureToAltitude(float* pressure);
        int32_t  _TEMP;
	      int64_t  _OFF;
	      int64_t  _SENS;

        typedef struct
				{
					uint16_t psens;
					uint16_t off;
					uint16_t tcs;
					uint16_t tco;
					uint16_t tref;
					uint16_t tsens;
				} CalReg;
        
        uint32_t lastPresConv;
        uint32_t lastTempConv;
        int32_t  tempCache;
				
};

extern DEV_MS5611::CalReg   calReg;








#endif