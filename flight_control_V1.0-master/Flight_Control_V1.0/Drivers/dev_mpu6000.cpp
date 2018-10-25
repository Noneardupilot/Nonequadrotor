/******************************************************************************************************************
**头文件说明 ： mpu6000驱动配置
**时      间 ： 2018-5-10
**作      者 ： 历小伟
**联系 方式  ： 15982962929
**备      注 ：
******************************************************************************************************************/


/*=============================================================================================================
                                         头文件START
==============================================================================================================*/

#include "dev_mpu6000.h"
#include "copter.h"

/*=============================================================================================================
                                         头文件START
==============================================================================================================*/


/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_MPU6000::Mpu6000_Init(void)
**功    能 : mpu6000初始化
**输    入 : None
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/
void DEV_MPU6000::Mpu6000_Init(void)
{
	  char id=0;  //定义读取的器件地址的变量
  	SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0X80);   		//电源管理,复位MPU6000
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0X00);   		//唤醒MPU6000
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_GYRO_CONFIG,0x03<<3);   		//设置陀螺仪满量程+-2000 deg/s
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_ACCEL_CONFIG,0x10);   		//设置ACCEL量程 -8g +8g 4096LSB/g
		System_set.delay_ms(2);

    SPI_MPU6000_WriteReg(MPU6000_SMPLRT_DIV,0x13);   		//数字低通滤波器50HZ
		System_set.delay_ms(2);
	  SPI_MPU6000_WriteReg(MPU6000_CONFIG,0x19); 
	  System_set.delay_ms(2);
	  SPI_MPU6000_WriteReg(MPU6000_INT_ENABLE,0x00);   	   //关闭所有中断
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_USER_CTRL_REG,0x00);   //i2c主模式关闭		
		System_set.delay_ms(2);

    SPI_MPU6000_WriteReg(MPU6000_FIFO_EN,0x00);        //关闭FIFO	
		System_set.delay_ms(2);
		
		SPI_MPU6000_WriteReg(MPU6000_INT_PIN_CFG,0x80);   //INT引脚低电平有效
		System_set.delay_ms(2);
		
		SPI_MPU6000_WriteReg(MPU6000_USER_CTRL_REG,0x00);   //i2c主模式关闭		
		System_set.delay_ms(2);
    id=SPI_MPU6000_ReadReg(MPU6000_DEVICE_ID_REG);
		System_set.delay_ms(2);
		if(id==0x68) //器件ID正确
		{
		
			SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0x01);   //设置CLKSEL,PLL x轴为参考
			System_set.delay_ms(2);
			
			SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT2_REG,0x00);   //加速度与陀螺仪都工作
			System_set.delay_ms(2);

			SPI_MPU6000_WriteReg(MPU6000_SMPLRT_DIV,0x13);   //设置数字低通滤波器
			System_set.delay_ms(2);
			
			SPI_MPU6000_WriteReg(MPU6000_CONFIG,0x19);   
			System_set.delay_ms(2);
		  Sensor_finish_flag.set_up_is_finish_mpu6000=1; //初始化完成标志
		}
		else
		{
		
		 Sensor_finish_flag.set_up_is_finish_mpu6000=0; //初始化失败标志
			Mode_Colour_Led.setup_sensor_temp=2;
		}

}




/*==================================================================================================================*/
/*==================================================================================================================*
**函数原型 : void DEV_MPU6000::Mpu6000_Get_Initial_Data(void)
**功    能 : mpu6000初始化
**输    入 : None
**输    出 : None
**备    注 : 
**================================================================================================================*/
/*================================================================================================================*/
void DEV_MPU6000::Mpu6000_Get_Initial_Data(void)
{
		uint8_t i;

		int16_t mpu6000_acc_temp[3];
		int16_t mpu6000_gyro_temp[3];
	  //使能总线读取数据
    Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
	  //发送读取数据命令
	  Spi1.SPI1_ReadWriteByte(MPU6000_ACCEL_XOUT_H| 0x80); 
	  //获取原始数据---acc--gyro--temp
	  for(i=0;i<14;i++)
	 {
	   mpu6000_buf[i]=Spi1.SPI1_ReadWriteByte(0xff);
	 }
	 //获取原始加速度数据
	 Get_Sensor_Data.mpu6000_acc[0]=BYTE16(int16_t,mpu6000_buf[0],mpu6000_buf[1]);
   Get_Sensor_Data.mpu6000_acc[1]=BYTE16(int16_t,mpu6000_buf[2],mpu6000_buf[3]);
	 Get_Sensor_Data.mpu6000_acc[2]=BYTE16(int16_t,mpu6000_buf[4],mpu6000_buf[5]);
	 //获取原始陀螺仪数据
	 Get_Sensor_Data.mpu6000_gyro[0]=BYTE16(int16_t,mpu6000_buf[8],mpu6000_buf[9]);
   Get_Sensor_Data.mpu6000_gyro[1]=BYTE16(int16_t,mpu6000_buf[10],mpu6000_buf[11]);
	 Get_Sensor_Data.mpu6000_gyro[2]=BYTE16(int16_t,mpu6000_buf[12],mpu6000_buf[13]);
	 //转换坐标系到北东天
	 Sensor.Align_Sensor(Get_Sensor_Data.mpu6000_acc,mpu6000_acc_temp,6);
	 Sensor.Align_Sensor(Get_Sensor_Data.mpu6000_gyro,mpu6000_gyro_temp,6);
	 //获取修正数据
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[0]=mpu6000_acc_temp[0];
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[1]=mpu6000_acc_temp[1];
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[2]=mpu6000_acc_temp[2];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[0]=mpu6000_gyro_temp[0];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[1]=mpu6000_gyro_temp[1];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[2]=mpu6000_gyro_temp[2];
	 
	 //不使能数据
	 Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);
}














/*====================================================================================================*/
/*====================================================================================================*
**函数原型 : uint8_t SPI_MPU_WriteReg(uint8_t reg,uint8_t dat)
**功    能 : SPI1写函数到芯片
**输    入 : reg:MPU的命令+寄存器地址，dat:将要向寄存器写入的数据
**输    出 : MPU的status寄存器的状态
**备    注 : 
**====================================================================================================*/
/*====================================================================================================*/
uint8_t DEV_MPU6000::SPI_MPU6000_WriteReg(uint8_t reg,uint8_t dat)
{
 	  uint8_t status;
	/*置低CSN，使能SPI传输*/
    Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
				
	/*发送命令及寄存器号 */
	  status = Spi1.SPI1_ReadWriteByte(reg); 
		 
	 /*向寄存器写入数据*/
    Spi1.SPI1_ReadWriteByte(dat); 
	          
	/*CSN拉高，完成*/	   
  	Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);	
		
	/*返回状态寄存器的值*/
   	return(status);
	
}

/*====================================================================================================*/
/*====================================================================================================*
**函数原型 : uint8_t SPI_MPU_ReadReg(uint8_t reg)
**功    能 : 用于从MPU特定的寄存器读出数据
**输    入 : reg:MPU的命令+寄存器地址。
**输    出 : 寄存器中的数据
**备    注 : 
**====================================================================================================*/
/*====================================================================================================*/

uint8_t DEV_MPU6000::SPI_MPU6000_ReadReg(uint8_t reg)
{
 	uint8_t reg_val;


	/*置低CSN，使能SPI传输*/
  Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
				
  	 /*发送寄存器号*/
	Spi1.SPI1_ReadWriteByte(reg| 0x80); 

	 /*读取寄存器的值 */
	reg_val = Spi1.SPI1_ReadWriteByte(0xff);
	            
   	/*CSN拉高，完成*/
	Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);		
   	
	return reg_val;
}	



/**********************************************************************************************************
*                                      file---end
**********************************************************************************************************/