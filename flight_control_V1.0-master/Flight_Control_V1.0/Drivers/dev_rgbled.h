#ifndef __DEV_RGBLED__H__
#define __DEV_RGBLED__H__


#include "stm32f4xx.h"
#include "dev_led.h"


extern uint8_t DEV_RGBLED_Color_Index[7][4];

 
#define  DEV_RGBLED_Driver_ADDR                  0x55        //定义驱动rgbled灯的TCA62724fmg芯片的地址是0x55
#define  DEV_RGBLED_Driver_Write_ADDR            0xAA        //定义驱动rgbled灯的写地址是0xAA
#define  DEV_RGBLED_Driver_Read_ADDR             0xAB        //定义驱动rgbled灯的读地址是0xAB
#define  DEV_RGBLED_SUB_ADDR_START               0x01        //写所有的
#define  DEV_RGBLED_SUB_ADDR_PWM0                0x81        //蓝色,设置不自动增加
#define  DEV_RGBLED_SUB_ADDR_PWM1                0x82        //绿色,设置不自动增加
#define  DEV_RGBLED_SUB_ADDR_PWM2                0x83        //红色,设置不自动增加
#define  DEV_RGBLED_SUB_ADDR_ENABLE              0x84        //红色,设置不自动增加
  
#define  DEV_RGBLEDSETTING_NOT_POWERSAVE         0x01        //SHDN,这里设置电源模式不保留         
#define  DEV_RGBLEDSETTING_POWERSAVE             0x02        //设置电源使能
#define  DEV_RGBLEDSETTING_DATA_ENABLE        0x03        //设置使能数据输出 




class DEV_RGBLED: public DEV_LED
{

  public:
         void init(void);
	       void dev_rgbled_test(void);
	       void dev_rgbled_color_update(uint8_t led_status);
         void dev_rgbled_sensor_calibration(void);
	       void dev_rgbled_sensor_test(void);
	
	//指示灯
	typedef struct
	{
	  uint8_t setup_is_finish;               //初始化是否完成
	  uint8_t setup_sensor_temp;             //用来检测传感器初始化是否完成
		uint8_t arm_is_lock;                   //遥控器解锁是否完成
		uint8_t current_fly_mode;              //当前无人机的飞行模式
	  uint8_t sensor_calibration;            //传感器校准
	}SET_MODE_RGBLED_COLORS;
	


	//初始化,解锁,飞行模式,校准
  enum
  {
	  JUDE_SETUP_FINISH=0,               //初始化---0
		JUDE_ARM_IS_LOCK,                  //解锁---1
		JUDE_CURRENT_FLY_MODE,             //当前的飞行模式--2
		JUDE_SENSOR_CALIBRATION            //校准---3
		
	};
	
	//传感器报错提示枚举
	 enum
  {
	  SET_MPU6000_ERR=2,               
		SET_MS5611_ERR=4, 
		SET_LSM303D_ERR=6, 
		SET_L3GD20_ERR=8, 
		
	};
	
	//枚举加速度校准指示灯
	enum
	{
	  ACCEL_CALI_START=1,  //1
	  ACCEL_CALI_X1,       //2
		ACCEL_CALI_X2,       //3
	  ACCEL_CALI_Y1,       //4
		ACCEL_CALI_Y2,	     //5
	  ACCEL_CALI_Z1,       //6
		ACCEL_CALI_Z2,		   //7
	  ACCEL_CALI_FINISH    //8
	
	};
	
	//枚举地磁校准指示灯
	enum
  {
	  MAG_CALI_START=1,               
		MAG_CALI_GET_DATA, 
		MAG_CALI_FINISH, 
		MAG_CALI_FAIL, 
		
	};
	
};




extern DEV_RGBLED Rgb_led;

extern DEV_RGBLED::SET_MODE_RGBLED_COLORS Mode_Colour_Led;  //创建指示灯颜色结构











#endif
