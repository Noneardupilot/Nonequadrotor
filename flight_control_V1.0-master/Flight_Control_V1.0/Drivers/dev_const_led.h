#ifndef __DEV_CONST_LED__H__
#define __DEV_CONST_LED__H__

#include "stm32f4xx.h"
#include "dev_led.h"


#define DRV_Pin_Led1		GPIO_Pin_12  


class CONST_LED: public DEV_LED
{

public:
		      void init(void);
          void update(void);
          void led_on(void);
          void led_off(void);


};


extern CONST_LED Const_led;







#endif