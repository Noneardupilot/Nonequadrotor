/******************************************************************************************************************
**头文件说明 ： 主函数文件配置
**时      间 ： 2018-4-30
**作      者 ： 历小伟
**联系 方式  ： 15982962929
**备      注 ：
******************************************************************************************************************/


/*=============================================================================================================
                                   
																	 头文件START
==============================================================================================================*/
#include "dev_sensor.h"
#include "copter.h"


DEV_SENSOR  Sensor;   //创建传感器对象

Sensor_Set_Up_Flag Sensor_finish_flag; //传感器初始化完成标志
Sensor_Initial_Data  Get_Sensor_Data;  //获取传感器初始化值
Amend_Sensor_Initial_Data  Amend_Get_Sensor_Data;
/*=============================================================================================================
                                         头文件START
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