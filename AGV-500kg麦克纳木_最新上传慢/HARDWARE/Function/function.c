#include "sys.h"

u8 beep_flag=0;
OS_Q BEEP_MES;
u8  USART6_TX_BUF[100];
void u6_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART6_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART6_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
	  while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);  //�ȴ��ϴδ������ 
		USART_SendData(USART6,(uint8_t)USART6_TX_BUF[j]); 	 //�������ݵ�����6 
	}	
}

u8 dir=1;//0Ϊ����1Ϊ����
//�˶������߳�
//����������ԭ��״̬
//dirΪ0������Ϊ��������������
void start(void)
{
	car_statu = 1;
	flag_qd = 1;
	if(dir == 0)
	{		
		QJ();
	}
	else if(dir == 1)
	{
		HT();				
	}
	else if(dir == 2)
	{
		ZY();
	}
	else if(dir == 3)
	{
		YY();
	}
	else if(dir == 4)
	{
		ZX();
	}
	else if(dir == 5)
	{
		YX();
	}
}
void stop(void)
{
	MotoStop(5);
	flag_qd = 0;car_statu = 0;	
}
u8  startAsk=0,stopAsk=0,zyAsk=0,yyAsk=0,flag_qd=0;
u8 	car_statu=0;
u16 DstSpeed = 80;//���ֵ��DA��ֵ�����Ϊ255����Ӧ5V
u8 CAN1_Sebuf[5]={1,0,1,0,0x55};
u16 xunzhuan_speed = 150;
u8 jiting_flag = 0,zuoyi_flag = 0,youyi_flag = 0,zuoxuan_flag = 0,youxuan_flag = 0;

void QJ(void)
{	
	CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 0;
	CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 0;
	CAN1_Send_Msg(CAN1_Sebuf,4);
}
void HT(void)
{
	CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 1;
	CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 1;
	CAN1_Send_Msg(CAN1_Sebuf,4);	
}
void ZY(void)
{	
	CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
	CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
	CAN1_Send_Msg(CAN1_Sebuf,4);
	Motor_Fzhuan(1,xunzhuan_speed);
	Motor_Zzhuan(2,xunzhuan_speed);
	Motor_Fzhuan(3,xunzhuan_speed);
	Motor_Zzhuan(4,xunzhuan_speed);	
	speed = 100;
	while((cdh_16!=0xffff))
	{	
		zuoyi_flag = 0;
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	while(!((cdh_16<0xffff)&&(abs(front_cdh16.Distance)<2)))
	{
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);			
		}
		delay(0,0,0,10);
	}
	zuoyi_flag = 1;
	MotoStop(5);
}
void YY(void)
{		
	CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
	CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
	CAN1_Send_Msg(CAN1_Sebuf,4);
	Motor_Fzhuan(1,xunzhuan_speed);
	Motor_Zzhuan(2,xunzhuan_speed);
	Motor_Fzhuan(3,xunzhuan_speed);
	Motor_Zzhuan(4,xunzhuan_speed);	
	speed = 100;
	while((cdh_16!=0xffff))//�ȳ���
	{
		youyi_flag = 0;
//�����ϱ���סʱ��speed�Լ����ʹ�ܱ��أ����ϰ���Ų��ʱ��ͨ�����Jhwai_flag��ֵ���ָ�YY״̬	
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	while(!((cdh_16<0xffff)&&(abs(front_cdh16.Distance)<2)))//���Ϲ�
	{			
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	youyi_flag = 1;
	MotoStop(5);
}

void YX(void)//����
{	
	CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
	CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
	CAN1_Send_Msg(CAN1_Sebuf,4);
	Motor_Fzhuan(1,xunzhuan_speed);
	Motor_Zzhuan(2,xunzhuan_speed);
	Motor_Fzhuan(3,xunzhuan_speed);
	Motor_Zzhuan(4,xunzhuan_speed);
	while((cdh_16!=0xffff))
	{
		youxuan_flag = 0;
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
			CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
			CAN1_Send_Msg(CAN1_Sebuf,4);			
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	while(!((cdh_16<0xffff)&&(abs(front_cdh16.Distance)<4)))
	{
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			CAN1_Sebuf[0] = 0;CAN1_Sebuf[1] = 0;
			CAN1_Sebuf[2] = 0;CAN1_Sebuf[3] = 0;
			CAN1_Send_Msg(CAN1_Sebuf,4);
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	youxuan_flag = 1;
	MotoStop(5);
}
void ZX(void)//����
{	
	CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
	CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
	CAN1_Send_Msg(CAN1_Sebuf,4);
	Motor_Fzhuan(1,xunzhuan_speed);
	Motor_Zzhuan(2,xunzhuan_speed);
	Motor_Fzhuan(3,xunzhuan_speed);
	Motor_Zzhuan(4,xunzhuan_speed);
	while((cdh_16!=0xffff))
	{	
		zuoxuan_flag = 0;
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
			CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
			CAN1_Send_Msg(CAN1_Sebuf,4);
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	while(!((cdh_16<0xffff)&&(abs(front_cdh16.Distance)<4)))
	{
		if((Jhwai_flag==0)&&(jiting_flag == 0))
		{
			CAN1_Sebuf[0] = 1;CAN1_Sebuf[1] = 1;
			CAN1_Sebuf[2] = 1;CAN1_Sebuf[3] = 1;
			CAN1_Send_Msg(CAN1_Sebuf,4);
			Motor_Fzhuan(1,xunzhuan_speed);
			Motor_Zzhuan(2,xunzhuan_speed);
			Motor_Fzhuan(3,xunzhuan_speed);
			Motor_Zzhuan(4,xunzhuan_speed);
		}
		delay(0,0,0,10);
	}
	zuoxuan_flag = 1;
	MotoStop(5);
}

void delay(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_STRICT,&err);
}
u16 keynumber=0;
void UserConfigInit(void)
{
	LED4=0;
	W25QXX_Init();			//W25QXX��ʼ��
	LED4=1;
	while(W25QXX_ReadID()!=W25Q128)//��ⲻ��W25Q128��LED��˸
	{
		LED4=~LED4;//DS0��˸
		delay(0, 0,0 , 100);
	}
	LED4=0;
	
	//��ȡ����ϵͳ����
	GetAllParameterFromSystem();

	if(SystemParameter[0]!=5)
	{
		//�жϱ�־λ
		SystemParameter[0]=5;
		
		//����
		SystemParameter[1]=0;
		SystemParameter[2]=0;
		SystemParameter[3]=0;
		SystemParameter[4]=0;
		SystemParameter[5]=0;	
		
		SystemParameter[6] = 1;	//·����		
		SystemParameter[7] = 1;	//���̺�
		SystemParameter[8] = 0;	//�����	
		//��λ�ٶ�
		SystemParameter[9]=50;
		SystemParameter[10]=150;		
		SystemParameter[11]=250;
		SystemParameter[12]=0;		
		SystemParameter[13]=0;
		//�ֶ��ٶ�
		SystemParameter[14] = 200;
		//�Զ��ٶ�
		SystemParameter[15] = 200;
		
		//�ֶ����Ͽ���		
		SystemParameter[16] = 1;
		//��������		
		SystemParameter[17] = 1;
		
		//��������		
		SystemParameter[18] = 2;
		
		//PID��������		
		SystemParameter[19] = 5;			
		//P		
		SystemParameter[20] = 50;			
		//I		
		SystemParameter[21] = 3;		
		//D		
		SystemParameter[22] = 2;
		//ǰ����Ͼ���		
		SystemParameter[23] = 3;
		
		//·������
		SystemParameter[24] = RouteNum;
		
		//����
		SystemParameter[25] = 1;	
			
		SystemParameter[26] = 0;
		SystemParameter[27] = 0;
		SystemParameter[28] = 0;		
		SystemParameter[29] = 0;
		SystemParameter[30] = 0;
		SystemParameter[31] = 0;		
		SystemParameter[32] = 0;
		SystemParameter[33] = 0;
		SystemParameter[34] = 0;		
		SystemParameter[35] = 0;
		SystemParameter[36] = 0;
		SystemParameter[37] = 0;		
		SystemParameter[38] = 0;
		SystemParameter[39] = 0;
		SystemParameter[40] = 0;
		SystemParameter[41] = 0;		
		SystemParameter[42] = 0;
		SystemParameter[43] = 0;
		SystemParameter[44] = 0;		
		SystemParameter[45] = 0;
		SystemParameter[46] = 0;
		SystemParameter[47] = 0;
		SystemParameter[48] = 0;		
		SystemParameter[49] = 0;
		SystemParameter[50] = 0;
		SystemParameter[51] = 0;
		SystemParameter[52] = 0;
		SystemParameter[53] = 0;
		SystemParameter[54] = 0;		
		SystemParameter[55] = 0;
		SystemParameter[56] = 0;
		SystemParameter[57] = 0;
		SystemParameter[58] = 0;
		SystemParameter[59] = 0;
		SystemParameter[60] = 0;		
		SystemParameter[61] = 0;
		SystemParameter[62] = 0;
		SystemParameter[63] = 0;
		SystemParameter[64] = 0;
		SystemParameter[65] = 0;		
		SystemParameter[66] = 0;
		SystemParameter[67] = 0;
		SystemParameter[68] = 0;
		SystemParameter[69] = 0;
		SystemParameter[70] = 0;
		SystemParameter[71] = 0;		
		SystemParameter[72] = 0;
		SystemParameter[73] = 0;
		SystemParameter[74] = 0;
		SystemParameter[75] = 0;
		SystemParameter[76] = 0;		
		SystemParameter[77] = 0;
		SystemParameter[78] = 0;
		SystemParameter[79] = 0;
		SystemParameter[80] = 0;
		SystemParameter[81] = 0;
		SystemParameter[82] = 0;
		SystemParameter[83] = 0;
		SystemParameter[84] = 0;
		SystemParameter[85] = 0;
		SystemParameter[86] = 0;
		SystemParameter[87] = 0;
		SystemParameter[88] = 0;
		SystemParameter[89] = 0;
		SystemParameter[90] = 0;
		SystemParameter[91] = 0;
		SystemParameter[92] = 0;
		SystemParameter[93] = 0;
		SystemParameter[94] = 0;
		SystemParameter[95] = 0;
		SystemParameter[96] = StaiionInfor;
		SystemParameter[97] = StepInfor;		
		SystemParameter[98] = 500;
		SystemParameter[99] = 500;
		SystemParameter[100] = 0;		
		//�洢����ϵͳ����
		SetAllParameterToSystem();
		
		//���·������վ����
		memset(RouteStationNum,0,RouteNum);
		//��������·��������վ����
		SetAllStationNum();
		
		//������̰�������
		memset(ProcessStepNum,0,ProcessNum);
		//�����������̰����Ĳ���
		SetAllStepNum();
	}
	
	//��ʼ������
	HmiRouteNum = SystemParameter[6];   //·����
	HmiProcessNum = SystemParameter[7]; //���̺�
	HmiTask = SystemParameter[8]; //�����
	
	HmiAutoReload();
	
	//ˢ���ٶ�
	PLC_Data[22] =  SystemParameter[9];//����
	PLC_Data[23] =  SystemParameter[10];//����
	PLC_Data[24] =  SystemParameter[11];//����

	PLC_Data[1] = 0;	//��ǰ�ر��
	PLC_OutPut[0] = 0;//Ĭ�ϲ���ʾ�Զ�/�ֶ�
	PLC_OutPut[1] = 0;//Ĭ�ϲ���ʾͣ��ʱ��
	PLC_OutPut[2] = 0;//Ĭ�ϲ����������룬����վ��ʱ��������
	
	SouDongSuDu = SystemParameter[14];
	ZiDongJiSu = SystemParameter[15];
	SouDongBiZhang = SystemParameter[16];
	YuYinKaiGuan = SystemParameter[17];
	YinLiang = SystemParameter[18];
	
	PIDZhouQi = SystemParameter[19];
	SPID_P = SystemParameter[20];
	SPID_I = SystemParameter[21];
	SPID_D = SystemParameter[22];
	QianHouJuLi = SystemParameter[23];
	LiuChengZongShu = SystemParameter[98];
	LuJingZongShu = SystemParameter[99];
	CheHao	= SystemParameter[25];
		//��ȡ·������վ����
	GetRouteStationNum(HmiRouteNum);

	//��ȡ��ǰ·����Ϣ
	GetRouteData(HmiRouteNum);
		
	//��ȡ��������������
	GetProcessData();
}
void Motor_Zzhuan(u8 Motor,u32 PWM)
{
	car_statu = 1;
	
	switch(Motor)
	{
		case 1:	
			PDout(4)=1;//Ϊ0ʱֹͣ��Ϊ1ʱ����					
			TIM_SetCompare1(TIM4,1000-PWM);		
		break;
		case 2:
			PDout(3)=1;
			TIM_SetCompare2(TIM4,1000-PWM);
		break;
		case 3:
			PDout(1)=1;
			TIM_SetCompare3(TIM4,1000-PWM);
		break;
		case 4:
			PDout(0)=1;
			TIM_SetCompare4(TIM4,1000-PWM);
		break;
		default:
		break;
	}
}

void Motor_Fzhuan(u8 Motor,u32 PWM)
{
	car_statu = 1;
	switch(Motor)
	{
		case 1:	
			PDout(4)=1;			
			TIM_SetCompare1(TIM4,1000-PWM);
		break;
		case 2:
			PDout(3)=1;
			TIM_SetCompare2(TIM4,1000-PWM);
		break;
		case 3:
			PDout(1)=1;
			TIM_SetCompare3(TIM4,1000-PWM);
		break;
		case 4:
			PDout(0)=1;
			TIM_SetCompare4(TIM4,1000-PWM);
		break;
		default:
		break;
	}
}
double ADC_POWER,ADC_DWQ1,ADC_DWQ2;

void MotoStop(u8 num)
{
	if(num==1)
	{
		PDout(4)=0;//ʹ��
		TIM_SetCompare1(TIM4,0);
	}
	else if(num==2)
	{
		PDout(3)=0;//ʹ��
		TIM_SetCompare2(TIM4,0);		
	}
	else if(num==3)
	{
		PDout(1)=0;//ʹ��	
		TIM_SetCompare3(TIM4,0);		
	}
	else if(num==4)
	{

		PDout(0)=0;//ʹ��
		TIM_SetCompare4(TIM4,0);
	}
	else
	{
		car_statu = 0;
		PDout(4)=0;//ʹ��
		PDout(3)=0;//ʹ��		
		PDout(1)=0;//ʹ��		
		PDout(0)=0;//ʹ��
		TIM_SetCompare1(TIM4,0);
		TIM_SetCompare2(TIM4,0);
		TIM_SetCompare3(TIM4,0);
		TIM_SetCompare4(TIM4,0);
	}
}

u16 speed=0;
u8 ld_juli=10,Jhwai_flag=0,Yhwai_flag=0,Jhwai_switch=1,Yhwai_switch=0;//�״���Ͼ���

float speed1=0,speed2=0,speed3=0,speed4=0;
float Cdh1_Inc=0;
u8 fencha_dir=0,tubian_num = 0;
void PID_Adjust(u16 j_speed,float kp,float ki,float kd)
{
	PID.Kp = kp;
	PID.Ki = ki;
	PID.Kd = kd; 
	if(dir == 0)
	{			
		if(front_cdh16.Num==0)
		{
			MotoStop(5);
			HmiTaskState = 4;
		}
		else
		{
			HmiTaskState = 5;
			Cdh1_Inc = PosPIDCalc(front_cdh16.Distance);
		
			speed1 = j_speed-Cdh1_Inc;
			speed2 = j_speed+Cdh1_Inc;

			if(abs(front_cdh16.Distance)>4)
			{
				if(Cdh1_Inc<0)
				{
					speed3 = j_speed;
					speed4 = j_speed+Cdh1_Inc;						
				}
				else
				{
					speed3 = j_speed-Cdh1_Inc;
					speed4 = j_speed;						
				}
			}
			else
			{
				speed3 = j_speed;
				speed4 = j_speed;					
			}
			if(speed1>1000)	speed1 = 1000;
			if(speed2>1000)	speed2 = 1000;
			if(speed3>1000)	speed3 = 1000;
			if(speed4>1000)	speed4 = 1000;
			if(speed1<0)	speed1 = 0;
			if(speed2<0)	speed2 = 0;
			if(speed3<0)	speed3 = 0;
			if(speed4<0)	speed4 = 0;

			Motor_Zzhuan(1,speed1);
			Motor_Zzhuan(3,speed3);
			Motor_Zzhuan(2,speed2);
			Motor_Zzhuan(4,speed4);								
		}
	}
	else if(dir == 1)
	{
		if(front_cdh16.Num==0)
		{
			MotoStop(5);
			HmiTaskState = 4;
		}
		else
		{
			HmiTaskState = 5;
			Cdh1_Inc = PosPIDCalc(front_cdh16.Distance);
		
			speed3 = j_speed-Cdh1_Inc;
			speed4 = j_speed+Cdh1_Inc;
			if(abs(front_cdh16.Distance)>4)
			{
				if(Cdh1_Inc<0)
				{
					speed1 = j_speed;
					speed2 = j_speed+Cdh1_Inc;						
				}
				else
				{
					speed1 = j_speed-Cdh1_Inc;
					speed2 = j_speed;						
				}
			}
			else
			{
				speed1 = j_speed;
				speed2 = j_speed;					
			}
			if(speed1>1000)	speed1 = 1000;
			if(speed2>1000)	speed2 = 1000;
			if(speed3>1000)	speed3 = 1000;
			if(speed4>1000)	speed4 = 1000;
			if(speed1<0)	speed1 = 0;
			if(speed2<0)	speed2 = 0;
			if(speed3<0)	speed3 = 0;
			if(speed4<0)	speed4 = 0;
		
			Motor_Fzhuan(1,speed1);
			Motor_Fzhuan(2,speed2);
			Motor_Fzhuan(3,speed3);
			Motor_Fzhuan(4,speed4);				
		}

	}
}
void Clear_ReceBuf(u8 num)
{
	if(num==2)
	{

		memset(rece2_buf,0,rece2_index);
	}
	else if(num==6)
	{
		memset(rece6_buf,0,rece6_index);
	}
}
u16 voltage=0,MAh=0,Current=0;
void LiDian_send(void)
{
//	7E 32 35 30 30 34 36 34 32 45 30 30 32 30 31 46 44 33 31 0D  ��ȡģ����  ��PACK = 0x01��
	send3_buf[0] = 0x7e;
	send3_buf[1] = 0x32;
	send3_buf[2] = 0x35;
	send3_buf[3] = 0x30;
	send3_buf[4] = 0x30;
	send3_buf[5] = 0x34;
	send3_buf[6] = 0x36;
	send3_buf[7] = 0x34;
	send3_buf[8] = 0x32;
	send3_buf[9] = 0x45;
	send3_buf[10] = 0x30;
	send3_buf[11] = 0x30;
	send3_buf[12] = 0x32;
	send3_buf[13] = 0x30;
	send3_buf[14] = 0x31;
	send3_buf[15] = 0x46;
	send3_buf[16] = 0x44;
	send3_buf[17] = 0x33;
	send3_buf[18] = 0x31;
	send3_buf[19] = 0x0D;
	Uart3_Start_DMA_Tx(20);
}
u8 HexToChar(u8 bChar)
{
	if((bChar>=0x30)&&(bChar<=0x39))
	{
		bChar -= 0x30;
	}
	else if((bChar>=0x41)&&(bChar<=0x46)) // Capital
	{
		bChar -= 0x37;
	}
	else if((bChar>=0x61)&&(bChar<=0x66)) //littlecase
	{
		bChar -= 0x57;
	}
	else 
	{
		bChar = 0xff;
	}
	return bChar;
}
long FloatTohex(float HEX)
{
	return *( long *)&HEX;//ע��˴���long��ָ��ǿ��ָ�򸡵���HEX�ĵ�ַ
}
float HexTofloat(long HEX)
{
	return *( float *)&HEX;
}
