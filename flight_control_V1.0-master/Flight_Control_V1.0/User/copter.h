#ifndef __COPTER__H__
#define __COPTER__H__

/***************ϵͳͷ�ļ�*******************/
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"
#include <math.h>
/***************ϵͳͷ�ļ�*******************/




/***************Userͷ�ļ�*******************/
#include "arducopter.h"
#include "scheduler.h"
#include "system.h"
#include "board.h"
/***************Userͷ�ļ�*******************/


/***************����ͷ�ļ�*******************/
//led����
#include "dev_led.h"
#include "dev_rgbled.h"
#include "dev_ws2812.h"
#include "dev_const_led.h"

//��������
#include "dev_uart.h"

//iic����
#include "dev_soft_iic.h"
#include "dev_hard_iic.h"
//spi����
#include "dev_spi.h"
//����������
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
/***************����ͷ�ļ�*******************/

/***************ͨ��Э��ͷ�ļ�***************/
#include "protocol.h"
#include "dev_ppm.h"
/***************ͨ��Э��ͷ�ļ�***************/

/***************�����㷨ͷ�ļ�***************/
#include "pid.h"
#include "adrc.h"
#include "imu.h"
/***************�����㷨ͷ�ļ�***************/

#endif

