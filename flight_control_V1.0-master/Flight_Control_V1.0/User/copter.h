#ifndef __COPTER__H__
#define __COPTER__H__

/***************系统头文件*******************/
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"
#include <math.h>
/***************系统头文件*******************/




/***************User头文件*******************/
#include "arducopter.h"
#include "scheduler.h"
#include "system.h"
#include "board.h"
/***************User头文件*******************/


/***************驱动头文件*******************/
//led驱动
#include "dev_led.h"
#include "dev_rgbled.h"
#include "dev_ws2812.h"
#include "dev_const_led.h"

//串口驱动
#include "dev_uart.h"

//iic驱动
#include "dev_soft_iic.h"
#include "dev_hard_iic.h"
//spi驱动
#include "dev_spi.h"
//传感器驱动
#include "dev_mpu6000.h"
#include "dev_mpu6050.h"
#include "dev_mpu6500.h"
#include "dev_mpu9250.h"
#include "dev_mpu9150.h"
#include "dev_icm_20602.h"
#include "dev_sensor.h"

#include "dev_hmc5883l.h"
#include "dev_ist8310.h"

#include "dev_ms5611.h"

#include "dev_lsm303d.h"

#include "dev_l3gd20.h"

#include "dev_can.h"
#include "dev_sdcard.h"
#include "dev_pwm.h"
#include "dev_gps.h"
#include "dev_fm25v01.h"
#include "dev_sbus.h"
/***************驱动头文件*******************/

/***************通信协议头文件***************/
#include "protocol.h"
#include "dev_ppm.h"
/***************通信协议头文件***************/

/***************控制算法头文件***************/
#include "pid.h"
#include "adrc.h"
#include "imu.h"
/***************控制算法头文件***************/

#endif

