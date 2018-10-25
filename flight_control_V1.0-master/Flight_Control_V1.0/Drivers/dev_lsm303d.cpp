/******************************************************************************************************************
**ͷ�ļ�˵�� �� LSM303D��������
**ʱ      �� �� 2018-4-30
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע ��
******************************************************************************************************************/


/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

#include "dev_lsm303d.h"
#include "copter.h"

/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/



/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI_Init(uint8_t SPIx)
**��    �� : SPI�����ʼ������
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	

int DEV_LSM303D::LSM303D_Init(LSM303D_Acc_InitTypeDef *LSM303D_Acc_InitStruct,LSM303D_Mag_InitTypeDef *LSM303D_InitStruct)
{
  bool success=(LSM303D_Read_Reg(LSM303D_WHO_AM_I)==WHO_I_AM);
	if(success)
	{
	  LSM303D_AccInit(LSM303D_Acc_InitStruct);
		LSM303D_MagInit(LSM303D_InitStruct);
		return 1;
	}
	else
	{
	 return 0;
	}



}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI_Init(uint8_t SPIx)
**��    �� : SPI�����ʼ������
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_Get_Sensor_Data(float *mag_data,float *acc_data)
{
  LSM303D_ReadMag_Data(mag_data);
  LSM303D_ReadAcc_Data(acc_data);
}
/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_LSM303D::LSM303D_SPI_ReadWriteByte(uint8_t TxData)
**��    �� : SPI��д����
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_LSM303D::LSM303D_SPI_ReadWriteByte(uint8_t TxData)
{
  Spi1.SPI1_ReadWriteByte(TxData); 
}
/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_LSM303D::LSM303D_Write_Reg(uint8_t reg,uint8_t value)
**��    �� : д�Ĵ���
**��    �� : 
**��    �� : 
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_LSM303D::LSM303D_Write_Reg(uint8_t reg,uint8_t value)
{
  uint8_t status;
  Sensor.Sensor_Cs_Enable(LSM303D,ENABLE);
	status=LSM303D_SPI_ReadWriteByte(reg);
	LSM303D_SPI_ReadWriteByte(value);
	Sensor.Sensor_Cs_Enable(LSM303D,DISABLE);
	return(status);
}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : uint8_t DEV_LSM303D::LSM303D_Read_Reg(uint8_t reg)
**��    �� : ���Ĵ���
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
uint8_t DEV_LSM303D::LSM303D_Read_Reg(uint8_t reg)
{
  uint8_t reg_val;
  Sensor.Sensor_Cs_Enable(LSM303D,ENABLE);
  LSM303D_SPI_ReadWriteByte(reg|0x80);
	reg_val=LSM303D_SPI_ReadWriteByte(0xff);
	Sensor.Sensor_Cs_Enable(LSM303D,DISABLE);
	return(reg_val);


}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_LSM303D::LSM303D_AccInit(LSM303D_Acc_InitTypeDef *LSM303D_Acc_InitStruct)
**��    �� : ���ٶ����ݳ�ʼ��
**��    �� : 
**��    �� : 
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_AccInit(LSM303D_Acc_InitTypeDef *LSM303D_Acc_InitStruct)
{
  uint8_t ctrl1 = 0x00, ctrl4 = 0x00;
  LSM303D_Acc_InitTypeDef LSM303D_Acc_InitStructure;
  LSM303D_Acc_InitStructure.Power_Mode = 0; 
  LSM303D_Acc_InitStructure.AccOutput_DataRate = 0x40; 
  LSM303D_Acc_InitStructure.Axes_Enable= 0x07;  
  LSM303D_Acc_InitStructure.AccFull_Scale = 0x00;  
  LSM303D_Acc_InitStructure.BlockData_Update = 0; 
  LSM303D_Acc_InitStructure.Endianness=0;  
  LSM303D_Acc_InitStructure.High_Resolution=0x08;    

  if(LSM303D_Acc_InitStruct)
	{
	
	  ctrl1 |= (uint8_t) (LSM303D_Acc_InitStruct->Power_Mode | LSM303D_Acc_InitStruct->AccOutput_DataRate | LSM303D_Acc_InitStruct->Axes_Enable);
    ctrl4 |= (uint8_t) (LSM303D_Acc_InitStruct->BlockData_Update | LSM303D_Acc_InitStruct->Endianness | \
                    LSM303D_Acc_InitStruct->AccFull_Scale|LSM303D_Acc_InitStruct->High_Resolution);   
	}
	else
	{
	  ctrl1 |= (uint8_t) (LSM303D_Acc_InitStruct->Power_Mode | LSM303D_Acc_InitStruct->AccOutput_DataRate | LSM303D_Acc_InitStruct->Axes_Enable);
    ctrl4 |= (uint8_t) (LSM303D_Acc_InitStruct->BlockData_Update | LSM303D_Acc_InitStruct->Endianness | \
                    LSM303D_Acc_InitStruct->AccFull_Scale|LSM303D_Acc_InitStruct->High_Resolution);  
	}
	
   LSM303D_Write_Reg(LSM303D_CTRL1,ctrl1);            
   LSM303D_Write_Reg(LSM303D_CTRL4,ctrl4);     


}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_LSM303D::LSM303D_MagInit(LSM303D_Mag_InitTypeDef *LSM303D_InitStruct)
**��    �� : �ش����ݳ�ʼ��
**��    �� : 
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_MagInit(LSM303D_Mag_InitTypeDef *LSM303D_InitStruct)
{
  uint8_t cra_regm = 0x00, crb_regm = 0x00, mr_regm = 0x00;
  LSM303D_Mag_InitTypeDef  LSM303D_InitStructure;
  LSM303D_InitStructure.Temperature_Sensor = 0; 
  LSM303D_InitStructure.MagOutput_DataRate =0x10 ;    //???0x14
  LSM303D_InitStructure.MagFull_Scale = 0x40;    //???0xE0
  LSM303D_InitStructure.Working_Mode = 0;    //???0x00
  if(LSM303D_InitStruct)
	{
	  cra_regm |= (uint8_t) (LSM303D_InitStruct->Temperature_Sensor | LSM303D_InitStruct->MagOutput_DataRate);
    crb_regm |= (uint8_t) (LSM303D_InitStruct->MagFull_Scale);  
    mr_regm |= (uint8_t) (LSM303D_InitStruct->Working_Mode);    
	}
	else
	{
	 	cra_regm |= (uint8_t) (LSM303D_InitStruct->Temperature_Sensor | LSM303D_InitStruct->MagOutput_DataRate);
    crb_regm |= (uint8_t) (LSM303D_InitStruct->MagFull_Scale);  
    mr_regm |= (uint8_t) (LSM303D_InitStruct->Working_Mode);  
	}
  
   //д�����õ���Ӧ�õ�ַ       
  LSM303D_Write_Reg(LSM303D_CTRL5,cra_regm);
  LSM303D_Write_Reg(LSM303D_CTRL6, crb_regm);
  LSM303D_Write_Reg(LSM303D_CTRL7, mr_regm);


}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_LSM303D::LSM303D_Read_Addr_Data(uint8_t regAddr,uint8_t *pBuffer,uint8_t len)
**��    �� : ��ȡ����
**��    �� : 
**��    �� : 
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_Read_Addr_Data(uint8_t regAddr,uint8_t *pBuffer,uint8_t len)
{
  uint8_t status;
	uint8_t num;
	Sensor.Sensor_Cs_Enable(LSM303D,ENABLE);
  if(len==1)
	{
	  status=LSM303D_SPI_ReadWriteByte(regAddr|0x80);
		*pBuffer=LSM303D_SPI_ReadWriteByte(0xff);
	  Sensor.Sensor_Cs_Enable(LSM303D,DISABLE);
	}
	else
	{
	  status=LSM303D_SPI_ReadWriteByte(regAddr|0xc0);
	  for(num=0;num<len;num++)
		{
		 *pBuffer=LSM303D_SPI_ReadWriteByte(0xff);
			pBuffer++;
		}
	}
  Sensor.Sensor_Cs_Enable(LSM303D,DISABLE);
}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_LSM303D::LSM303D_ReadMag_Data(float *pfData) 
**��    �� : 
**��    �� : 
**��    �� : 
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_ReadMag_Data(float *pfData) 
{
	static xyz_f_t LSM303D_Mag_Adc_fill[10];
	static xyz_f_t LSM303D_Mag_Adc_fill_total;
	static char temp_i;
	float data_mag[3]={0};
  static uint8_t buffer[6] = {0};
  uint8_t CTRLB = 0;
  float Magn_Sensitivity_XY = 0, Magn_Sensitivity_Z = 0;
  uint8_t i =0;
  LSM303D_Read_Addr_Data(LSM303D_CTRL6, &CTRLB, 1);
  LSM303D_Read_Addr_Data( LSM303DLHC_OUT_X_L_M, buffer, 6);

  
  switch(CTRLB & 60)
  {
  case LSM303D_FS_2_GA:
   
    Magn_Sensitivity_XY = LSM303D_M_SENSITIVITY_XY_2_1GA;
    Magn_Sensitivity_Z = LSM303D_M_SENSITIVITY_Z_2_1GA;   
    break;
  case LSM303D_FS_4_GA:
    Magn_Sensitivity_XY = LSM303D_M_SENSITIVITY_XY_4_1GA;//??855
    Magn_Sensitivity_Z = LSM303D_M_SENSITIVITY_Z_4_1GA; //??760
    break;
  case LSM303D_FS_8_GA:
    Magn_Sensitivity_XY = LSM303D_M_SENSITIVITY_XY_8_1GA; //??670
    Magn_Sensitivity_Z = LSM303D_M_SENSITIVITY_Z_8_1GA; //??600
    break;
  case LSM303D_FS_12_GA:
    Magn_Sensitivity_XY = LSM303D_M_SENSITIVITY_XY_12_1GA; //??450
    Magn_Sensitivity_Z = LSM303D_M_SENSITIVITY_Z_12_1GA; //??400
    break;

  }
 
  for(i=0; i<2; i++)
  {
    pfData[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]))*Magn_Sensitivity_XY;
  }
  pfData[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]))*Magn_Sensitivity_Z;
  //�ش�У׼����

}

/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� :void DEV_LSM303D::LSM303D_ReadAcc_Data(float *pfData)
**��    �� :��ȡ���ٶ�����
**��    �� : 
**��    �� : 
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_ReadAcc_Data(float *pfData)
{
  int16_t pnRawData[3]={0};
  uint8_t ctrlx[2]={0};
  uint8_t buffer[6]={0}, cDivider=0;
  uint8_t i = 0;
  float LSM303D_Acc_Sensitivity = LSM303D_Acc_Sensitivity_2g;
  
  LSM303D_Read_Addr_Data(LSM303D_CTRL4, ctrlx,2);
  LSM303D_Read_Addr_Data(LSM303D_OUT_X_L_A, buffer, 6);  
  if(ctrlx[1]&0x40)
	{ 
	   cDivider=64;//���
	}
  else
	{
	 cDivider=16; //С��
	}
  if(!(ctrlx[0] & 0x40) || (ctrlx[1] & 0x40)) 
  {
    for(i=0; i<3; i++)
    {
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/cDivider;
    }
  }
  else 
  {
    for(i=0; i<3; i++)
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1])/cDivider;
  }
  
  LSM303D_Read_Addr_Data(LSM303D_CTRL4, ctrlx,2);
  if(ctrlx[1]&0x40)
  {
    
    LSM303D_Acc_Sensitivity = 0.25;
  }
  else
  {
    
    
    switch(ctrlx[0] & 0x30)
    {
    case LSM303D_FULLSCALE_2G:
      LSM303D_Acc_Sensitivity = LSM303D_Acc_Sensitivity_2g; //1.0f
      break;
    case LSM303D_FULLSCALE_4G:
      LSM303D_Acc_Sensitivity = LSM303D_Acc_Sensitivity_4g; //0.5f
      break;
    case LSM303D_FULLSCALE_8G:
      LSM303D_Acc_Sensitivity = LSM303D_Acc_Sensitivity_8g; //0.25f
      break;
    case LSM303D_FULLSCALE_16G:     
      LSM303D_Acc_Sensitivity = LSM303D_Acc_Sensitivity_16g; //0.0834f
      break;
    }
  }
  
  pfData[0]=-((float)pnRawData[1]/LSM303D_Acc_Sensitivity/100);  //Ϊ�˺�mpu6000��acc����һ��
  pfData[1]=((float)pnRawData[0]/LSM303D_Acc_Sensitivity/100);   //Ϊ�˺�mpu6000��acc����һ��
	pfData[2]=((float)pnRawData[2]/LSM303D_Acc_Sensitivity/100);   //Ϊ�˺�mpu6000��acc����һ��
}


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_SPI::SPI_Init(uint8_t SPIx)
**��    �� : SPI�����ʼ������
**��    �� : SPIxȷ�������ĸ�SPI
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/	
void DEV_LSM303D::LSM303D_Caloffset_Mag(float *pfData)
{



}


/**************************************************************************************************************
*                                      file---end
***************************************************************************************************************/



