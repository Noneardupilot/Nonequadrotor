/******************************************************************************************************************
**ͷ�ļ�˵�� �� �������ļ�����
**ʱ      �� �� 2018-4-30
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע ��
******************************************************************************************************************/


/*=============================================================================================================
                                   
																	 ͷ�ļ�START
==============================================================================================================*/
#include "dev_sensor.h"
#include "copter.h"


DEV_SENSOR  Sensor;   //��������������

Sensor_Set_Up_Flag Sensor_finish_flag; //��������ʼ����ɱ�־
Sensor_Initial_Data  Get_Sensor_Data;  //��ȡ��������ʼ��ֵ
Amend_Sensor_Initial_Data  Amend_Get_Sensor_Data;
/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/
void DEV_SENSOR::Sensor_Cs_Enable(IC_NAME name,FunctionalState NewState)
{
  if(NewState==ENABLE)
	{
	  switch(name)
		{
		  case MPU6000: L3GD20_CS=1;MPU6000_CS=0;MS5611_CS=0;LSM303D_CS=0;
		  case L3GD20: L3GD20_CS=1;MPU6000_CS=0;MS5611_CS=0;LSM303D_CS=0;
			case MS5611: L3GD20_CS=1;MPU6000_CS=0;MS5611_CS=0;LSM303D_CS=0;
			case LSM303D: L3GD20_CS=1;MPU6000_CS=0;MS5611_CS=0;LSM303D_CS=0;
			default: break;
		}
	
	}
	else
	{
	  L3GD20_CS=1;
	  MPU6000_CS=1;
	  MS5611_CS=1;
	  LSM303D_CS=1;
	}

}




void DEV_SENSOR::Align_Sensor(int16_t *src,int16_t *dest,uint8_t rotation)
{

 switch(rotation)
 {
 
	 case CW0_DEG:
							 dest[X_Vector]=src[X_Vector];
							 dest[Y_Vector]=src[Y_Vector];
							 dest[Z_Vector]=src[Z_Vector];
	             break;
	 case CW90_DEG:
							 dest[X_Vector]=src[Y_Vector];
							 dest[Y_Vector]=-src[X_Vector];
							 dest[Z_Vector]=src[Z_Vector];
	             break;
 
	 	case CW180_DEG:
							 dest[X_Vector]=-src[X_Vector];
							 dest[Y_Vector]=-src[Y_Vector];
							 dest[Z_Vector]=src[Z_Vector];
	             break;
 
		case CW270_DEG:
							 dest[X_Vector]=-src[Y_Vector];
							 dest[Y_Vector]=src[X_Vector];
							 dest[Z_Vector]=src[Z_Vector];
	             break;
 
		case CW0_DEG_FLIP:
							 dest[X_Vector]=-src[X_Vector];
							 dest[Y_Vector]=src[Y_Vector];
							 dest[Z_Vector]=-src[Z_Vector];
	             break;
 
	  case CW90_DEG_FLIP:
							 dest[X_Vector]=src[Y_Vector];
							 dest[Y_Vector]=src[X_Vector];
							 dest[Z_Vector]=-src[Z_Vector];
	             break;
 	  case CW180_DEG_FLIP:
							 dest[X_Vector]=src[X_Vector];
							 dest[Y_Vector]=-src[Y_Vector];
							 dest[Z_Vector]=-src[Z_Vector];
	             break;
 	  case CW270_DEG_FLIP:
							 dest[X_Vector]=-src[Y_Vector];
							 dest[Y_Vector]=-src[X_Vector];
							 dest[Z_Vector]=-src[Z_Vector];
	             break;
 

 }













}










void DEV_SENSOR::IMU_Sensor_Init_Test(void)
{
  IMU_MPU6000_Test();
  IMU_MS5611_Test();
  IMU_LSM303D_Test();
	IMU_L3GD20_Test();
}

void DEV_SENSOR::IMU_MPU6000_Test(void)
{




}
void DEV_SENSOR::IMU_MS5611_Test(void)
{




}


void DEV_SENSOR::IMU_LSM303D_Test(void)
{




}

void DEV_SENSOR::IMU_L3GD20_Test(void)
{




}

/**************************************************************************************************************************
*                                      file---end
**************************************************************************************************************************/