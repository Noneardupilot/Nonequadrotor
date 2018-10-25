#ifndef __DEV_RGBLED__H__
#define __DEV_RGBLED__H__


#include "stm32f4xx.h"
#include "dev_led.h"


extern uint8_t DEV_RGBLED_Color_Index[7][4];

 
#define  DEV_RGBLED_Driver_ADDR                  0x55        //��������rgbled�Ƶ�TCA62724fmgоƬ�ĵ�ַ��0x55
#define  DEV_RGBLED_Driver_Write_ADDR            0xAA        //��������rgbled�Ƶ�д��ַ��0xAA
#define  DEV_RGBLED_Driver_Read_ADDR             0xAB        //��������rgbled�ƵĶ���ַ��0xAB
#define  DEV_RGBLED_SUB_ADDR_START               0x01        //д���е�
#define  DEV_RGBLED_SUB_ADDR_PWM0                0x81        //��ɫ,���ò��Զ�����
#define  DEV_RGBLED_SUB_ADDR_PWM1                0x82        //��ɫ,���ò��Զ�����
#define  DEV_RGBLED_SUB_ADDR_PWM2                0x83        //��ɫ,���ò��Զ�����
#define  DEV_RGBLED_SUB_ADDR_ENABLE              0x84        //��ɫ,���ò��Զ�����
  
#define  DEV_RGBLEDSETTING_NOT_POWERSAVE         0x01        //SHDN,�������õ�Դģʽ������         
#define  DEV_RGBLEDSETTING_POWERSAVE             0x02        //���õ�Դʹ��
#define  DEV_RGBLEDSETTING_DATA_ENABLE        0x03        //����ʹ��������� 




class DEV_RGBLED: public DEV_LED
{

  public:
         void init(void);
	       void dev_rgbled_test(void);
	       void dev_rgbled_color_update(uint8_t led_status);
         void dev_rgbled_sensor_calibration(void);
	       void dev_rgbled_sensor_test(void);
	
	//ָʾ��
	typedef struct
	{
	  uint8_t setup_is_finish;               //��ʼ���Ƿ����
	  uint8_t setup_sensor_temp;             //������⴫������ʼ���Ƿ����
		uint8_t arm_is_lock;                   //ң���������Ƿ����
		uint8_t current_fly_mode;              //��ǰ���˻��ķ���ģʽ
	  uint8_t sensor_calibration;            //������У׼
	}SET_MODE_RGBLED_COLORS;
	


	//��ʼ��,����,����ģʽ,У׼
  enum
  {
	  JUDE_SETUP_FINISH=0,               //��ʼ��---0
		JUDE_ARM_IS_LOCK,                  //����---1
		JUDE_CURRENT_FLY_MODE,             //��ǰ�ķ���ģʽ--2
		JUDE_SENSOR_CALIBRATION            //У׼---3
		
	};
	
	//������������ʾö��
	 enum
  {
	  SET_MPU6000_ERR=2,               
		SET_MS5611_ERR=4, 
		SET_LSM303D_ERR=6, 
		SET_L3GD20_ERR=8, 
		
	};
	
	//ö�ټ��ٶ�У׼ָʾ��
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
	
	//ö�ٵش�У׼ָʾ��
	enum
  {
	  MAG_CALI_START=1,               
		MAG_CALI_GET_DATA, 
		MAG_CALI_FINISH, 
		MAG_CALI_FAIL, 
		
	};
	
};




extern DEV_RGBLED Rgb_led;

extern DEV_RGBLED::SET_MODE_RGBLED_COLORS Mode_Colour_Led;  //����ָʾ����ɫ�ṹ











#endif
