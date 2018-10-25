#ifndef __DEV_SENSOR_H__
#define __DEV_SENSOR_H__

#include "stm32f4xx.h"


#define L3GD20_CS  PCout(13)
#define MPU6000_CS PCout(2)
#define MS5611_CS  PDout(7)
#define LSM303D_CS PCout(15)

//芯片类型枚举
typedef enum
{
	 MPU6000=0,
	 L3GD20=1,
	 MS5611=2,
	 LSM303D=3,			 
}IC_NAME;

//传感器初始化标志
typedef struct
{
  uint8_t set_up_is_finish_mpu6000;
  uint8_t set_up_is_finish_ms5611;
	uint8_t set_up_is_finish_lsm303d;
  uint8_t set_up_is_finish_l3gd20;
}Sensor_Set_Up_Flag;
extern Sensor_Set_Up_Flag Sensor_finish_flag;

//传感器初始数据
typedef struct
{
  int16_t  mpu6000_acc[3];
	int16_t  mpu6000_gyro[3];
}Sensor_Initial_Data;
extern Sensor_Initial_Data  Get_Sensor_Data;

//传感器导航数据
typedef struct
{
  int16_t  amend_mpu6000_acc[3];
	int16_t  amend_mpu6000_gyro[3];
}Amend_Sensor_Initial_Data;
extern Amend_Sensor_Initial_Data  Amend_Get_Sensor_Data;





 enum
{
	ALIGN_DEFAULT=0,
	CW0_DEG=1,
	CW90_DEG=2,
	CW180_DEG=3,
	CW270_DEG=4,
	CW0_DEG_FLIP=5,
	CW90_DEG_FLIP=6,
	CW180_DEG_FLIP=7,
	CW270_DEG_FLIP=8
};
enum
{
	X_Vector=0,
  Y_Vector,
	Z_Vector
};


class DEV_SENSOR
{
  public:
		     void Sensor_Cs_Enable(IC_NAME name,FunctionalState NewState);
	       void Align_Sensor(int16_t *src,int16_t *dest,uint8_t rotation);
         void IMU_Sensor_Init_Test(void);
	       void IMU_MPU6000_Test(void);
	       void IMU_MS5611_Test(void);
	       void IMU_LSM303D_Test(void);
	       void IMU_L3GD20_Test(void);
	

	
	
	
	private:



};

extern DEV_SENSOR  Sensor;   //创建传感器对象


#endif