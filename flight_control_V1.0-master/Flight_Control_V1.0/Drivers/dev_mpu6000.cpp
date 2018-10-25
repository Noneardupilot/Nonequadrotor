/******************************************************************************************************************
**ͷ�ļ�˵�� �� mpu6000��������
**ʱ      �� �� 2018-5-10
**��      �� �� ��Сΰ
**��ϵ ��ʽ  �� 15982962929
**��      ע ��
******************************************************************************************************************/


/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/

#include "dev_mpu6000.h"
#include "copter.h"

/*=============================================================================================================
                                         ͷ�ļ�START
==============================================================================================================*/


/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_MPU6000::Mpu6000_Init(void)
**��    �� : mpu6000��ʼ��
**��    �� : None
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/
void DEV_MPU6000::Mpu6000_Init(void)
{
	  char id=0;  //�����ȡ��������ַ�ı���
  	SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0X80);   		//��Դ����,��λMPU6000
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0X00);   		//����MPU6000
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_GYRO_CONFIG,0x03<<3);   		//����������������+-2000 deg/s
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_ACCEL_CONFIG,0x10);   		//����ACCEL���� -8g +8g 4096LSB/g
		System_set.delay_ms(2);

    SPI_MPU6000_WriteReg(MPU6000_SMPLRT_DIV,0x13);   		//���ֵ�ͨ�˲���50HZ
		System_set.delay_ms(2);
	  SPI_MPU6000_WriteReg(MPU6000_CONFIG,0x19); 
	  System_set.delay_ms(2);
	  SPI_MPU6000_WriteReg(MPU6000_INT_ENABLE,0x00);   	   //�ر������ж�
		System_set.delay_ms(2);
	
	  SPI_MPU6000_WriteReg(MPU6000_USER_CTRL_REG,0x00);   //i2c��ģʽ�ر�		
		System_set.delay_ms(2);

    SPI_MPU6000_WriteReg(MPU6000_FIFO_EN,0x00);        //�ر�FIFO	
		System_set.delay_ms(2);
		
		SPI_MPU6000_WriteReg(MPU6000_INT_PIN_CFG,0x80);   //INT���ŵ͵�ƽ��Ч
		System_set.delay_ms(2);
		
		SPI_MPU6000_WriteReg(MPU6000_USER_CTRL_REG,0x00);   //i2c��ģʽ�ر�		
		System_set.delay_ms(2);
    id=SPI_MPU6000_ReadReg(MPU6000_DEVICE_ID_REG);
		System_set.delay_ms(2);
		if(id==0x68) //����ID��ȷ
		{
		
			SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT1_REG,0x01);   //����CLKSEL,PLL x��Ϊ�ο�
			System_set.delay_ms(2);
			
			SPI_MPU6000_WriteReg(MPU6000_PWR_MGMT2_REG,0x00);   //���ٶ��������Ƕ�����
			System_set.delay_ms(2);

			SPI_MPU6000_WriteReg(MPU6000_SMPLRT_DIV,0x13);   //�������ֵ�ͨ�˲���
			System_set.delay_ms(2);
			
			SPI_MPU6000_WriteReg(MPU6000_CONFIG,0x19);   
			System_set.delay_ms(2);
		  Sensor_finish_flag.set_up_is_finish_mpu6000=1; //��ʼ����ɱ�־
		}
		else
		{
		
		 Sensor_finish_flag.set_up_is_finish_mpu6000=0; //��ʼ��ʧ�ܱ�־
			Mode_Colour_Led.setup_sensor_temp=2;
		}

}




/*==================================================================================================================*/
/*==================================================================================================================*
**����ԭ�� : void DEV_MPU6000::Mpu6000_Get_Initial_Data(void)
**��    �� : mpu6000��ʼ��
**��    �� : None
**��    �� : None
**��    ע : 
**================================================================================================================*/
/*================================================================================================================*/
void DEV_MPU6000::Mpu6000_Get_Initial_Data(void)
{
		uint8_t i;

		int16_t mpu6000_acc_temp[3];
		int16_t mpu6000_gyro_temp[3];
	  //ʹ�����߶�ȡ����
    Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
	  //���Ͷ�ȡ��������
	  Spi1.SPI1_ReadWriteByte(MPU6000_ACCEL_XOUT_H| 0x80); 
	  //��ȡԭʼ����---acc--gyro--temp
	  for(i=0;i<14;i++)
	 {
	   mpu6000_buf[i]=Spi1.SPI1_ReadWriteByte(0xff);
	 }
	 //��ȡԭʼ���ٶ�����
	 Get_Sensor_Data.mpu6000_acc[0]=BYTE16(int16_t,mpu6000_buf[0],mpu6000_buf[1]);
   Get_Sensor_Data.mpu6000_acc[1]=BYTE16(int16_t,mpu6000_buf[2],mpu6000_buf[3]);
	 Get_Sensor_Data.mpu6000_acc[2]=BYTE16(int16_t,mpu6000_buf[4],mpu6000_buf[5]);
	 //��ȡԭʼ����������
	 Get_Sensor_Data.mpu6000_gyro[0]=BYTE16(int16_t,mpu6000_buf[8],mpu6000_buf[9]);
   Get_Sensor_Data.mpu6000_gyro[1]=BYTE16(int16_t,mpu6000_buf[10],mpu6000_buf[11]);
	 Get_Sensor_Data.mpu6000_gyro[2]=BYTE16(int16_t,mpu6000_buf[12],mpu6000_buf[13]);
	 //ת������ϵ��������
	 Sensor.Align_Sensor(Get_Sensor_Data.mpu6000_acc,mpu6000_acc_temp,6);
	 Sensor.Align_Sensor(Get_Sensor_Data.mpu6000_gyro,mpu6000_gyro_temp,6);
	 //��ȡ��������
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[0]=mpu6000_acc_temp[0];
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[1]=mpu6000_acc_temp[1];
	 Amend_Get_Sensor_Data.amend_mpu6000_acc[2]=mpu6000_acc_temp[2];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[0]=mpu6000_gyro_temp[0];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[1]=mpu6000_gyro_temp[1];
	 Amend_Get_Sensor_Data.amend_mpu6000_gyro[2]=mpu6000_gyro_temp[2];
	 
	 //��ʹ������
	 Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);
}














/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : uint8_t SPI_MPU_WriteReg(uint8_t reg,uint8_t dat)
**��    �� : SPI1д������оƬ
**��    �� : reg:MPU������+�Ĵ�����ַ��dat:��Ҫ��Ĵ���д�������
**��    �� : MPU��status�Ĵ�����״̬
**��    ע : 
**====================================================================================================*/
/*====================================================================================================*/
uint8_t DEV_MPU6000::SPI_MPU6000_WriteReg(uint8_t reg,uint8_t dat)
{
 	  uint8_t status;
	/*�õ�CSN��ʹ��SPI����*/
    Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
				
	/*��������Ĵ����� */
	  status = Spi1.SPI1_ReadWriteByte(reg); 
		 
	 /*��Ĵ���д������*/
    Spi1.SPI1_ReadWriteByte(dat); 
	          
	/*CSN���ߣ����*/	   
  	Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);	
		
	/*����״̬�Ĵ�����ֵ*/
   	return(status);
	
}

/*====================================================================================================*/
/*====================================================================================================*
**����ԭ�� : uint8_t SPI_MPU_ReadReg(uint8_t reg)
**��    �� : ���ڴ�MPU�ض��ļĴ�����������
**��    �� : reg:MPU������+�Ĵ�����ַ��
**��    �� : �Ĵ����е�����
**��    ע : 
**====================================================================================================*/
/*====================================================================================================*/

uint8_t DEV_MPU6000::SPI_MPU6000_ReadReg(uint8_t reg)
{
 	uint8_t reg_val;


	/*�õ�CSN��ʹ��SPI����*/
  Sensor.Sensor_Cs_Enable(MPU6000,ENABLE);
				
  	 /*���ͼĴ�����*/
	Spi1.SPI1_ReadWriteByte(reg| 0x80); 

	 /*��ȡ�Ĵ�����ֵ */
	reg_val = Spi1.SPI1_ReadWriteByte(0xff);
	            
   	/*CSN���ߣ����*/
	Sensor.Sensor_Cs_Enable(MPU6000,DISABLE);		
   	
	return reg_val;
}	



/**********************************************************************************************************
*                                      file---end
**********************************************************************************************************/