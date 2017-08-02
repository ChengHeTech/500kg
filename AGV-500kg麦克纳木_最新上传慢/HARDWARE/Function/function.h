#ifndef __FUNCTION_H
#define __FUNCTION_H	
#include "sys.h"

void Manual_speed(void);
void start(void);
void QJ(void);
void HT(void);
void ZY(void);
void YY(void);
void ZX(u8 num);
void YX(u8 num);
void stop(void);
void delay(u32 h,u32 m,u32 s,u32 ms);
void UserConfigInit(void);

void Motor_Zzhuan(u8 Motor,u32 PWM);
void Motor_Fzhuan(u8 Motor,u32 PWM);


void PID_Adjust(u16 j_speed,float kp,float ki,float kd);
void Clear_ReceBuf(u8 num);
void MotoStop(u8 num);
long FloatTohex(float HEX);
float HexTofloat(long HEX);
void u6_printf(char* fmt,...);
void LiDian_send(void);
u8 HexToChar(u8 bChar);
extern double ADC_POWER,ADC_DWQ1,ADC_DWQ2;
extern u16 speed;
extern OS_Q BEEP_MES;

extern double speed_vul,speed_dis;
extern u8 dir,startAsk,stopAsk,zyAsk,yyAsk,flag_qd,fencha_dir;
extern u8 beep_flag,Parameter[100],StationTemp[1000][16],IspTemp[1000];
extern u8 Jhwai_flag,Yhwai_flag,Jhwai_switch,Yhwai_switch,ld_juli,car_statu;
extern u16 DstSpeed,StationNum[500],keynumber,voltage,MAh,Current;
extern u8 CAN1_Sebuf[5],jiting_flag,zuoyi_flag,youyi_flag,zuoxuan_flag,youxuan_flag,tubian_num;
extern u8 XuanZhuanNUM;
#endif
