#ifndef __SYSTEM__H__
#define __SYSTEM__H__


#include "stm32f4xx.h"


#define  GET_TIME_NUM   15    //获取的时间组数
#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

class SYSTEM 
{
	public:
					void SysTick_Init(void);
					uint32_t GetSysTime_us(void);
					void delay_us(uint32_t us);
					void delay_ms(uint32_t ms);

					float Get_Cycle_T(u8 item);	
					void Cycle_Time_Init(void);
	        void Systick_Handler(void);
	
	
	
	private:
		     volatile uint32_t sysTickUptime ;
         volatile float Cycle_T[GET_TIME_NUM][3];
	       enum
         {
					 NOW=0,
					 OLD,
					 NEW,
				 };

};
extern SYSTEM System_set;



#endif



