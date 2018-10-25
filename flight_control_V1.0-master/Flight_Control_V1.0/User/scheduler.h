#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "stm32f4xx.h"

class SCHEDULER
{

	public:
		
								//系统运行时间定义
					typedef struct
					{
								uint8_t check_flag;
								uint8_t err_flag;
								int16_t cnt_1ms;
								int16_t cnt_2ms;
								int16_t cnt_4ms;
								int16_t cnt_5ms;
								int16_t cnt_10ms;
								int16_t cnt_20ms;
								int16_t cnt_25ms;
								int16_t cnt_50ms;
								int16_t cnt_80ms;
								int16_t cnt_90ms;
								int16_t cnt_100ms;
								uint16_t time;
					}System_loop_time;
	
	       int time_1h,time_1m,time_1s,time_1ms;//实现1h,1minute,1s,1ms,计时开始
	       int16_t loop_cnt;               //循环计数
		      void  Loop_Schedule(void);
					void  Loop_Task_1ms(void);
					void  Loop_Task_2ms(void);
					void  Loop_Task_4ms(void);
					void  Loop_Task_5ms(void);
					void  Loop_Task_10ms(void);
					void  Loop_Task_20ms(void);
					void  Loop_Task_25ms(void);
					void  Loop_Task_50ms(void);
					void  Loop_Task_80ms(void);
					void  Loop_Task_90ms(void);
					void  Loop_Task_100ms(void);
					void  Loop_Task_Trigger_Start(void);
					void  Loop_check(void);
				
};


extern SCHEDULER Scheduler;


#endif