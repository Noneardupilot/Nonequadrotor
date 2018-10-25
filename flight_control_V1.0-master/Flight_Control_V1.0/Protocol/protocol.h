#ifndef  __PROTOCOL__H___
#define  __PROTOCOL__H___

#include "stm32f4xx.h"

//数据宏定义拆分，主要针对数据大于一个字节的,如float,int16,需要拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )



class PROTOCOL 
{
  public:
		  void Communicate_DT_Send_Data(u8 *dataToSend , u8 length);
	    void Communicate_DT_Send_Check(u8 head, u8 check_sum);
	    void Communicate_DT_Send_Msg(u8 id, u8 data);
			void Communicate_DT_Data_Exchange(void);
			void Communicate_DT_Data_Receive_Prepare(uint8_t data);
			void Communicate_DT_Data_Receive_Anl(uint8_t *data_buf,uint8_t num);
			void Communicate_DT_Send_Version(uint8_t hardware_type, uint16_t hardware_ver,uint16_t software_ver,uint16_t protocol_ver,uint16_t bootloader_ver);
			void Communicate_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, int32_t alt, uint8_t fly_model, uint8_t armed);
			void Communicate_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z);
			void Communicate_DT_Send_Senser2(int32_t bar_alt,uint16_t csb_alt);
			void Communicate_DT_Send_RCData(uint16_t thr,uint16_t yaw,uint16_t rol,uint16_t pit,uint16_t aux1,uint16_t aux2,uint16_t aux3,uint16_t aux4,uint16_t aux5,uint16_t aux6);
			void Communicate_DT_Send_Power(uint16_t votage, uint16_t current);
			void Communicate_DT_Send_MotoPWM(uint16_t m_1,uint16_t m_2,uint16_t m_3,uint16_t m_4,uint16_t m_5,uint16_t m_6,uint16_t m_7,uint16_t m_8);
			void Communicate_DT_Send_PID(uint8_t group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);
			void Communicate_DT_Send_User(void);
			void Communicate_DT_Send_Speed(float,float,float);
			void Communicate_DT_Send_Location(uint8_t state,uint8_t sat_num,int32_t lon,int32_t lat,float back_home_angle);
	
	private:
					uint8_t msg_id;
					uint8_t msg_data;
					uint8_t send_check;
					uint8_t send_version;
					uint8_t send_status;
					uint8_t send_senser;
					uint8_t send_senser2;
					uint8_t send_pid1;
					uint8_t send_pid2;
					uint8_t send_pid3;
					uint8_t send_pid4;
					uint8_t send_pid5;
					uint8_t send_pid6;
					uint8_t send_rcdata;
					uint8_t send_offset;
					uint8_t send_motopwm;
					uint8_t send_power;
					uint8_t send_user;
					uint8_t send_speed;
					uint8_t send_location;

};

extern PROTOCOL Protocol;     //创建通信对象


#endif