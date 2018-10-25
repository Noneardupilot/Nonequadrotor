/******************************************************************************************************************
**头文件说明 ： L3GD20驱动配置
**时      间 ： 2018-4-30
**作      者 ： 历小伟
**联系 方式  ： 15982962929
**备      注 ：
******************************************************************************************************************/


/*=============================================================================================================
                                         头文件START
==============================================================================================================*/

#include "dev_l3gd20.h"
#include "copter.h"

/*=============================================================================================================
                                         头文件START
==============================================================================================================*/

/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : int DEV_L3GD20::L3GD20_Init(L3GD20_InitTypeDef *L3GD20_InitStruct)
**功    能 : 初始化
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	

int DEV_L3GD20::L3GD20_Init(L3GD20_InitTypeDef *L3GD20_InitStruct)
{
  bool success=0;
	if(L3GD20_SPI_ReadWriteByte(L3GD20_WHO_AM_I_ADDR)==L3GD20_ADDR)
	{
	  success=1;
	}
	else
	{
	  success=0;
	}
	if(success)
	{
	  L3GD20_Init_Configure(L3GD20_InitStruct);
		return 1;
	}
	else
	{
	 return 0;
	}

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_L3GD20::L3GD20_Init_Configure(L3GD20_InitTypeDef *L3GD20_InitStruct)
**功    能 : 配置管脚
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_L3GD20::L3GD20_Init_Configure(L3GD20_InitTypeDef *L3GD20_InitStruct)
{
	L3GD20_InitTypeDef L3GD20_InitStructure;
  uint8_t ctrl1 = 0x00, ctrl4 = 0x00;
  
  L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;             //???0x08
  L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1; //???0x00
  L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;      //???0x07
  L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4; //???0x30
  L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous; //???0x00
  L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB; //???0x00
  L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500;       //???0x10
            
  ctrl1 |= (uint8_t) (L3GD20_InitStruct->Power_Mode | L3GD20_InitStruct->Output_DataRate | \
                    L3GD20_InitStruct->Axes_Enable | L3GD20_InitStruct->Band_Width);
  
  ctrl4 |= (uint8_t) (L3GD20_InitStruct->BlockData_Update | L3GD20_InitStruct->Endianness | \
                    L3GD20_InitStruct->Full_Scale);                
  
  L3GD20_Write(&ctrl1, L3GD20_ADDR_CTRL_REG1, 1);
  
  
  L3GD20_Write(&ctrl4, L3GD20_ADDR_CTRL_REG4, 1);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_L3GD20::L3GD20_Gyro_ReadAngRate(float *pfdata)
**功    能 : 
**输    入 : 
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_L3GD20::L3GD20_Gyro_ReadAngRate(float *pfdata)
{
  uint8_t tmpbuffer[6] ={0};
  int16_t RawData[3] = {0};
  uint8_t tmpreg = 0;
  float sensitivity = 0;
  int i =0;
 
  L3GD20_Read(&tmpreg,L3GD20_ADDR_CTRL_REG4,1);
  L3GD20_Read(tmpbuffer,L3GD20_ADDR_OUT_X_L,6);
  
   
  if(!(tmpreg & 0x40))
  {
    for(i=0; i<3; i++)
    {
      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
    }
  }
  else
  {
    for(i=0; i<3; i++)
    {
      RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1]);
    }
  }
  
  switch(tmpreg & 0x30)
  {
  case 0x00:
    sensitivity=L3GD20_Sensitivity_250dps;//L3G_Sensitivity_500dps=360/pi
    break;
    
  case 0x10:
    sensitivity=L3GD20_Sensitivity_500dps;  //L3G_Sensitivity_500dps=180/pi=57.1429
    break;
    
  case 0x20:
    sensitivity=L3GD20_Sensitivity_2000dps;//L3G_Sensitivity_500dps=1/4*180/pi
    break;
  }
  
  for(i=0; i<3; i++)
  {
    pfdata[i]=(float)RawData[i]/sensitivity; //????????
  }
}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : uint8_t DEV_L3GD20::L3GD20_SPI_ReadWriteByte(uint8_t TxData)
**功    能 : 
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_L3GD20::L3GD20_SPI_ReadWriteByte(uint8_t TxData)
{
  Spi1.SPI1_ReadWriteByte(TxData);
}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : uint8_t DEV_L3GD20::L3GD20_Write_Reg(uint8_t reg,uint8_t value)
**功    能 : 
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_L3GD20::L3GD20_Write(uint8_t *pBuffer,uint8_t WriteAddr,uint16_t NumByteToWrite)
{
	if(NumByteToWrite>0x01)
	{
	 WriteAddr|=(uint8_t)MULTIPLEBYTE_CMD;
	}

  Sensor.Sensor_Cs_Enable(L3GD20,ENABLE);
	L3GD20_SPI_ReadWriteByte(WriteAddr);
	while(NumByteToWrite>=0x01)
	{
	  L3GD20_SPI_ReadWriteByte(*pBuffer);
		NumByteToWrite--;
		pBuffer++;
	
	}
	Sensor.Sensor_Cs_Enable(L3GD20,DISABLE);

}

/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void   DEV_L3GD20::L3GD20_FilterConfig(L3GD20_InitTypeDef *L3GD20_InitStruct)
**功    能 : 
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/
void   DEV_L3GD20::L3GD20_FilterConfig(L3GD20_FilterConfigTypeDef *L3GD20_FilterStruct)
{
	 L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;
   uint8_t tmpreg;
  
  L3GD20_Read(&tmpreg, L3GD20_ADDR_CTRL_REG2, 1);
  tmpreg &= 0xC0;
  L3GD20_FilterStructure.HighPassFilter_Mode_Selection =0x00;  //???0x00
  L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = 0x00;      //???0x00
  
  tmpreg |= (uint8_t) (L3GD20_FilterStruct->HighPassFilter_Mode_Selection |\
                      L3GD20_FilterStruct->HighPassFilter_CutOff_Frequency);                             
 
  
  L3GD20_Write(&tmpreg, L3GD20_ADDR_CTRL_REG2, 1);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void   DEV_L3GD20::L3GD20_FilterCmd(uint8_t HighPassFilterState)
**功    能 : 
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void   DEV_L3GD20::L3GD20_FilterCmd(uint8_t HighPassFilterState)
{
	uint8_t tmpreg;
  L3GD20_Read(&tmpreg, L3GD20_ADDR_CTRL_REG5, 1);             
  tmpreg &= 0xEF;
  tmpreg |= HighPassFilterState; 
  L3GD20_Write(&tmpreg, L3GD20_ADDR_CTRL_REG5, 1);

}
/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_L3GD20::L3GD20_Read(uint8_t *pBuffer,uint8_t regAddr,uint16_t NumByteToRead)
**功    能 : 
**输    入 : 
**输    出 : 
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_L3GD20::L3GD20_Read(uint8_t *pBuffer,uint8_t ReadAddr,uint16_t NumByteToRead)
{
  	if(NumByteToRead>0x01)
	{
	 ReadAddr|=(uint8_t)(READWRITE_CMD|MULTIPLEBYTE_CMD);
	}
	else
	{
	  ReadAddr|=(uint8_t)READWRITE_CMD;
	}

  Sensor.Sensor_Cs_Enable(L3GD20,ENABLE);
	L3GD20_SPI_ReadWriteByte(ReadAddr);
	while(NumByteToRead>0x00)
	{
	  *pBuffer=L3GD20_SPI_ReadWriteByte(DUMMY_BYTE);
		NumByteToRead--;
		pBuffer++;
	
	}
	Sensor.Sensor_Cs_Enable(L3GD20,DISABLE);
}

/**************************************************************************************************************
*                                      file---end
***************************************************************************************************************/