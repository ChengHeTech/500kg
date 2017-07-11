#include "sys.h"

//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define Transducer_TASK_PRIO		4
//�����ջ��С	
#define Transducer_STK_SIZE 		512
//������ƿ�
OS_TCB TransducerTaskTCB;
//�����ջ	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//�������ȼ�
#define Auto_TASK_PRIO		5
//�����ջ��С	
#define Auto_STK_SIZE 		512
//������ƿ�
OS_TCB AutoTaskTCB;
//�����ջ	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//������
void Auto_task(void *p_arg);

//�������ȼ�
#define Manual_TASK_PRIO		6
//�����ջ��С	
#define Manual_STK_SIZE 		512
//������ƿ�
OS_TCB ManualTaskTCB;
//�����ջ	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//������
void Manual_task(void *p_arg);

//�������ȼ�
#define FLOAT_TASK_PRIO		7
//�����ջ��С
#define FLOAT_STK_SIZE		512
//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);

//�������ȼ�
#define Screen_TASK_PRIO		12
//�����ջ��С	
#define Screen_STK_SIZE 		512
//������ƿ�
OS_TCB ScreenTaskTCB;
//�����ջ	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//������
void Screen_task(void *p_arg);

//�������ȼ�
#define PID_TASK_PRIO		9
//�����ջ��С	
#define PID_STK_SIZE 		512
//������ƿ�
OS_TCB PIDTaskTCB;
//�����ջ	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//������
void PID_task(void *p_arg);


//�������ȼ�
#define Control_TASK_PRIO		10
//�����ջ��С	
#define Control_STK_SIZE 		512
//������ƿ�
OS_TCB ControlTaskTCB;
//�����ջ	
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//������
void Control_task(void *p_arg);


//�������ȼ�
#define WIFI_TASK_PRIO		11
//�����ջ��С	
#define WIFI_STK_SIZE 		512
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//������
void WIFI_task(void *p_arg);

//�������ȼ�
#define DEMO_TASK_PRIO		8
//�����ջ��С	
#define DEMO_STK_SIZE 		512
//������ƿ�
OS_TCB DEMOTaskTCB;
//�����ջ	
CPU_STK DEMO_TASK_STK[WIFI_STK_SIZE];
//������
void DEMO_task(void *p_arg);


//�������ȼ�
#define DEMO1_TASK_PRIO		13
//�����ջ��С	
#define DEMO1_STK_SIZE 		512
//������ƿ�
OS_TCB DEMO1TaskTCB;
//�����ջ	
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//������
void DEMO1_task(void *p_arg);

//�������ȼ�
#define DEMO2_TASK_PRIO		14
//�����ջ��С	
#define DEMO2_STK_SIZE 		512
//������ƿ�
OS_TCB DEMO2TaskTCB;
//�����ջ	
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//������
void DEMO2_task(void *p_arg);

//�������ȼ�
#define Task5_TASK_PRIO		15
//�����ջ��С	
#define Task5_STK_SIZE 		512
//������ƿ�
OS_TCB Task5_TaskTCB;
//�����ջ	
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//������
void Task5_task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	LED_Init();         //LED��ʼ��
	DMA_adc1_Init();
	DMA_Uart4_Init();
	DMA_Uart2_Init();
	DMA_Uart6_Init();
	DMA_Uart3_Init();
	ADC1_Configuration();
	USART1_Configuration(9600);
	USART4_Configuration(9600);
	USART6_Configuration(115200);
	USART2_Configuration(9600);
	USART3_Configuration(9600);
	TIM4_PWM_Init(1000-1,8-1);	//84M/8=10Mhz?????,????1000,??PWM??? 10M/50000=200hz. //500-10   20hz-1000hz
//	TLC5620_Init();	//DA��ʼ��
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN1��ʼ����ͨģʽ,������500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN2��ʼ����ͨģʽ,������500Kbps
	PID_Init();
	TIM2_Int_Init(5000-1,840-1);			//Tout=((arr+1)*(psc+1))/Ft us.  50ms	
	TIM3_CH1_Cap_Init1(5000,84-1); 			//��84/84=1Mhz��Ƶ�ʼ��� 5ms��������
 	TIM9_CH1_Cap_Init1(5000,84-1); 			//��84/84=1Mhz��Ƶ�ʼ��� 5ms��������
	IWDG_Init(4,500);
	can_Sebuf[2]=0x55;//���ͼ̵�����ͬ����Ϣ
	CanSend();	
	can_Sebuf[2]=0;
	MotoStop(5);

	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}
u8 State_Autotask=0,State_Controltask=0,State_PIDtask=0,State_Manualtask=1,State_DEMOtask=1,State_WIFItask=1;

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	//����Transducer����
	OSTaskCreate((OS_TCB 	* )&TransducerTaskTCB,		
				 (CPU_CHAR	* )"Transducer task", 		
                 (OS_TASK_PTR )Transducer_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Transducer_TASK_PRIO,     
                 (CPU_STK   * )&Transducer_TASK_STK[0],	
                 (CPU_STK_SIZE)Transducer_STK_SIZE/10,	
                 (CPU_STK_SIZE)Transducer_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);								 
	
	//�����Զ�����
//	OSTaskCreate((OS_TCB 	* )&AutoTaskTCB,		
//				 (CPU_CHAR	* )"Auto task", 		
//                 (OS_TASK_PTR )Auto_task, 			
//                 (void		* )0,					
//                 (OS_PRIO	  )Auto_TASK_PRIO,     	
//                 (CPU_STK   * )&Auto_TASK_STK[0],	
//                 (CPU_STK_SIZE)Auto_STK_SIZE/10,	
//                 (CPU_STK_SIZE)Auto_STK_SIZE,		
//                 (OS_MSG_QTY  )0,					
//                 (OS_TICK	  )0,					
//                 (void   	* )0,				
//                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//                 (OS_ERR 	* )&err);				 
				 
	//���������������
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//��������������
	OSTaskCreate((OS_TCB 	* )&ScreenTaskTCB,		
				 (CPU_CHAR	* )"Screen task", 		
                 (OS_TASK_PTR )Screen_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Screen_TASK_PRIO,     	
                 (CPU_STK   * )&Screen_TASK_STK[0],	
                 (CPU_STK_SIZE)Screen_STK_SIZE/10,	
                 (CPU_STK_SIZE)Screen_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//PID
//	OSTaskCreate((OS_TCB 	* )&PIDTaskTCB,		
//				 (CPU_CHAR	* )"PID task", 		
//                 (OS_TASK_PTR )PID_task, 			
//                 (void		* )0,					
//                 (OS_PRIO	  )PID_TASK_PRIO,     	
//                 (CPU_STK   * )&PID_TASK_STK[0],	
//                 (CPU_STK_SIZE)PID_STK_SIZE/10,	
//                 (CPU_STK_SIZE)PID_STK_SIZE,		
//                 (OS_MSG_QTY  )0,					
//                 (OS_TICK	  )0,					
//                 (void   	* )0,				
//                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//                 (OS_ERR 	* )&err);
	//Control
//	OSTaskCreate((OS_TCB 	* )&ControlTaskTCB,		
//				 (CPU_CHAR	* )"Control task", 		
//                 (OS_TASK_PTR )Control_task, 			
//                 (void		* )0,					
//                 (OS_PRIO	  )Control_TASK_PRIO,     	
//                 (CPU_STK   * )&Control_TASK_STK[0],	
//                 (CPU_STK_SIZE)Control_STK_SIZE/10,	
//                 (CPU_STK_SIZE)Control_STK_SIZE,		
//                 (OS_MSG_QTY  )0,					
//                 (OS_TICK	  )0,					
//                 (void   	* )0,				
//                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//                 (OS_ERR 	* )&err);
	//DEMO
	OSTaskCreate((OS_TCB 	* )&DEMOTaskTCB,		
				 (CPU_CHAR	* )"DEMO task", 		
                 (OS_TASK_PTR )DEMO_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
	//DEMO1
	OSTaskCreate((OS_TCB 	* )&DEMO1TaskTCB,		
				 (CPU_CHAR	* )"DEMO1 task", 		
                 (OS_TASK_PTR )DEMO1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO1_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO1_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO1_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
	//DEMO2
	OSTaskCreate((OS_TCB 	* )&DEMO2TaskTCB,		
				 (CPU_CHAR	* )"DEMO2 task", 		
                 (OS_TASK_PTR )DEMO2_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DEMO2_TASK_PRIO,     	
                 (CPU_STK   * )&DEMO2_TASK_STK[0],	
                 (CPU_STK_SIZE)DEMO2_STK_SIZE/10,	
                 (CPU_STK_SIZE)DEMO2_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//�����ֶ�����
	OSTaskCreate((OS_TCB 	* )&ManualTaskTCB,		
				 (CPU_CHAR	* )"Manual task", 		
				 (OS_TASK_PTR )Manual_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Manual_TASK_PRIO,     	
				 (CPU_STK   * )&Manual_TASK_STK[0],	
				 (CPU_STK_SIZE)Manual_STK_SIZE/10,	
				 (CPU_STK_SIZE)Manual_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	OSTaskCreate((OS_TCB 	* )&WIFITaskTCB,		
				 (CPU_CHAR	* )"WIFI task", 		
				 (OS_TASK_PTR )WIFI_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )WIFI_TASK_PRIO,     	
				 (CPU_STK   * )&WIFI_TASK_STK[0],	
				 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
				 (CPU_STK_SIZE)WIFI_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);	
							 
	OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,		
				 (CPU_CHAR	* )"Task5 task", 		
				 (OS_TASK_PTR )Task5_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task5_TASK_PRIO,     	
				 (CPU_STK   * )&Task5_TASK_STK[0],	
				 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task5_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�����ٽ���
}

//Transducer_task����
u8  flag_szd=1;
void Transducer_task(void *p_arg)//������ȣ��ֶ�ʱɾ�����Զ��йص������Զ�ʱɾ�����ֶ��йص�����
{
	OS_ERR err;
	p_arg = p_arg;
	HmiScreenControlMode = 1;
	while(1)
	{	
		if(((SouZiDongQieHuan==0)&&(flag_szd == 0))||(PLC_OutPut[18]==1))
		{
			speek("�ֶ�");
			flag_szd = 1;
			flag_qd = 0; 
			stopAsk= 1;
			HmiScreenControlMode = 1;
			if(State_Autotask == 1)   
			{
				OSTaskDel((OS_TCB*)&AutoTaskTCB,&err);
				State_Autotask = 0;
			}
			if(State_Controltask == 1)   
			{
				OSTaskDel((OS_TCB*)&ControlTaskTCB,&err);
				State_Controltask = 0;
			}	
			if(State_PIDtask == 1)   
			{
				OSTaskDel((OS_TCB*)&PIDTaskTCB,&err);
				State_PIDtask = 0;
			}				
			if(State_Manualtask==0)
			{
				//�����ֶ�����
				OSTaskCreate((OS_TCB 	* )&ManualTaskTCB,		
							 (CPU_CHAR	* )"Manual task", 		
							 (OS_TASK_PTR )Manual_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )Manual_TASK_PRIO,     	
							 (CPU_STK   * )&Manual_TASK_STK[0],	
							 (CPU_STK_SIZE)Manual_STK_SIZE/10,	
							 (CPU_STK_SIZE)Manual_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,				
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
							 (OS_ERR 	* )&err);
							 State_Manualtask=1;
			}
			if(State_WIFItask==0)
			{
				OSTaskCreate((OS_TCB 	* )&WIFITaskTCB,		
							 (CPU_CHAR	* )"WIFI task", 		
							 (OS_TASK_PTR )WIFI_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )WIFI_TASK_PRIO,     	
							 (CPU_STK   * )&WIFI_TASK_STK[0],	
							 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
							 (CPU_STK_SIZE)WIFI_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,				
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
							 (OS_ERR 	* )&err);	
							 State_WIFItask=1;
			}			
			while(SouZiDongQieHuan==0)
			{
				delay(0,0,0,10);
			}
			
		}
		else if(((SouZiDongQieHuan==0)&&(flag_szd == 1))||(PLC_OutPut[17]==1))
		{
			speek("�Զ�");	
			speed = ZiDongJiSu;	//�Զ�һ��ʼûɨ���ر�֮ǰ�����ٶ�		
			MotoStop(5);
			flag_szd = 0;
//			startAsk = 1;
//			car_statu = 1;
//			flag_qd = 1;
			HmiScreenControlMode = 0;
			if(State_Manualtask==1)
			{
				OSTaskDel((OS_TCB*)&ManualTaskTCB,&err);
				State_Manualtask=0;
			}
			if(State_WIFItask==1)
			{
				OSTaskDel((OS_TCB*)&WIFITaskTCB,&err);
				State_WIFItask=0;
			}			
			if(State_Autotask==0)
			{
				//�����Զ�����
				OSTaskCreate((OS_TCB 	* )&AutoTaskTCB,		
							 (CPU_CHAR	* )"Auto task", 		
							 (OS_TASK_PTR )Auto_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )Auto_TASK_PRIO,     	
							 (CPU_STK   * )&Auto_TASK_STK[0],	
							 (CPU_STK_SIZE)Auto_STK_SIZE/10,	
							 (CPU_STK_SIZE)Auto_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,				
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
							 (OS_ERR 	* )&err);
							 State_Autotask=1;
			}
			if(State_PIDtask==0)
			{
				OSTaskCreate((OS_TCB 	* )&PIDTaskTCB,		
							 (CPU_CHAR	* )"PID task", 		
							 (OS_TASK_PTR )PID_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )PID_TASK_PRIO,     	
							 (CPU_STK   * )&PID_TASK_STK[0],	
							 (CPU_STK_SIZE)PID_STK_SIZE/10,	
							 (CPU_STK_SIZE)PID_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,				
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
							 (OS_ERR 	* )&err);
							 State_PIDtask=1;
			}
			if(State_Controltask==0)
			{
				OSTaskCreate((OS_TCB 	* )&ControlTaskTCB,		
							 (CPU_CHAR	* )"Control task", 		
							 (OS_TASK_PTR )Control_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )Control_TASK_PRIO,     	
							 (CPU_STK   * )&Control_TASK_STK[0],	
							 (CPU_STK_SIZE)Control_STK_SIZE/10,	
							 (CPU_STK_SIZE)Control_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,				
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
							 (OS_ERR 	* )&err);
							 State_Controltask=1;
			}
			while(SouZiDongQieHuan==0)
			{
				delay(0,0,0,10);
			}
		}
		delay(0,0,0,10); //��ʱ10ms
	}
}
void Auto_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(flag_qd==0)//��ֹ�������
		{
			if((QD==0)||(HmiQiDong))
			{					
				startAsk = 1;		
			}
		}	
		if((TZ==0)||(HmiTinZhi))
		{
			flag_qd = 0;
			delay(0,0,0,10);
			stopAsk=1;		
		}		
		if(flag_qd==1)
		{
			if(dir==0)
			{
				if(QfangZ==0)
				{
					stopAsk=1;
					speek("��ͣ��������������");
				}
			}
			else if(dir==1)
			{
				if(HfangZ==0)
				{
					stopAsk=1;
					speek("��ͣ��������������");
				}			
			}			
		}
		delay(0,0,0,10); //��ʱ20ms
	}
}

void Manual_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{	
		if((QianJin==0))//ǰ��
		{
			Motor_Zzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);		
	
			if((ZuoXuan==0))//����
			{
				Motor_Zzhuan(2,SouDongSuDu*1.5);
				Motor_Zzhuan(4,SouDongSuDu*1.5);
			}
			else if((YouXuan==0))//����
				{
					Motor_Zzhuan(1,SouDongSuDu*1.5);
					Motor_Zzhuan(3,SouDongSuDu*1.5);
				}
		}
		else if((HouTui==0))//����
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Fzhuan(4,SouDongSuDu);
			
			if((ZuoXuan==0))//����
			{
				Motor_Zzhuan(2,SouDongSuDu*1.5);
				Motor_Zzhuan(4,SouDongSuDu*1.5);
			}
			else if((YouXuan==0))//����
				{
					Motor_Zzhuan(1,SouDongSuDu*1.5);
					Motor_Zzhuan(3,SouDongSuDu*1.5);
				}
		}
		else if((ZuoYi==0))//����
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			Motor_Fzhuan(4,SouDongSuDu);
		}
		else if((YouYI==0))//����
		{
			Motor_Zzhuan(1,SouDongSuDu);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((ZuoShang==0))//����
		{
			MotoStop(1);			
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			MotoStop(4);
		}
		else if((ZuoXia==0))//����
		{
			Motor_Fzhuan(1,SouDongSuDu);
			MotoStop(2);
			MotoStop(3);
			Motor_Fzhuan(4,SouDongSuDu);
		}
		else if((YouShang==0))//����
		{
			Motor_Zzhuan(1,SouDongSuDu);
			MotoStop(2);
			MotoStop(3);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((YouXia==0))//����
		{
			MotoStop(1);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			MotoStop(4);
		}
		else if((ZuoXuan==0))//����
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((YouXuan==0))//����
		{
			Motor_Zzhuan(1,SouDongSuDu);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			Motor_Fzhuan(4,SouDongSuDu);
		}
		if((QianJin==1)&&(HouTui==1)&&(ZuoYi==1)&&(YouYI==1)&&(ZuoShang==1)
			&&(ZuoXia==1)&&(YouShang==1)&&(YouXia==1)&&(ZuoXuan==1)&&(YouXuan==1))
		{
			MotoStop(5);			
		}
		delay(0,0,0,10); //��ʱ10ms
	}
}

u8 cy_time=5;
void PID_task(void *p_arg)
{
	while(1)
	{
		if((flag_qd==1)&&(car_statu == 1))
		{	
			PID_Adjust(speed,PID.Kp,PID.Ki,PID.Kd);
		}
		delay(0,0,0,cy_time);
	}
}
u8 speek_flag=0;
u16 motor1=0,motor2=0,motor3=0,motor4=0;
void float_task(void *p_arg)
{
	u8 num=0;
	u8 yuyin_flag=2;
	OS_ERR err;
	p_arg = p_arg;
	delay_ms(20);
	yuyin_flag=YinLiang;
	while(1)
	{
		cy_time = PIDZhouQi;
//		PID.Kp = SPID_P/10.0;
//		PID.Ki = SPID_I/10.0;
//		PID.Kd = SPID_D/10.0;
		PID.Kp = SPID_P/10.0;
		PID.Ki = SPID_I/1000.0;
		PID.Kd = SPID_D/10.0;	
		if(beep_flag)
		{
			BEEP=1;
			OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			BEEP=0;
			beep_flag = 0;
		}
		if(yuyin_flag!=YinLiang)
		{
			if(YinLiang==0)
			{
				yinling(2);
			}
			if(YinLiang==1)
			{
				yinling(5);
			}
			if(YinLiang==2)
			{
				yinling(9);
			}		
		}
		yuyin_flag = YinLiang;
		num++;
		if(num==50)
		{
			LED1 = ~LED1;//���е�
			TongXunDeng=~TongXunDeng;//������ͨѶָʾ��
			LiDian_send();//��ȡ�������
			num=0;
		}
		QianFangZhuang = QfangZ;//ǰ��ײ
		HouFangZhuang = HfangZ;//���ײ
		
		if(speek_flag==1)//������������
		{
			speek("ǰ�����ϰ�");
			OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);
		}
		
		if(JieMianHao==5)
		{
			//��̬ˢ���ֶ��Զ���ʱ�䰴ť����ʾ������
			//���򡢷��������������Ʒ��������������Ʒ���
			if(PLC_Data[4]==0||PLC_Data[4]==3||PLC_Data[4]==4||PLC_Data[4]==5||PLC_Data[4]==7||PLC_Data[4]==8)
			{
				PLC_OutPut[0]=1;//��ʾ�ֶ��Զ�
				if(PLC_Data[5]==0)//�Զ�
					PLC_OutPut[1]=1;//��ʾͣ��ʱ��
				else
					PLC_OutPut[1]=0;//����ͣ��ʱ��
			}
			else
			{
				PLC_OutPut[0]=0;//�����ֶ��Զ�
				PLC_OutPut[1]=0;//����ͣ��ʱ��
			}
		}
		//���ת�ټ��� ת/ÿ����
		motor1 = (tim31_count/0.05)*30;
		motor2 = (tim32_count/0.05)*30;
		motor3 = (tim91_count/0.05)*30;
		motor4 = (tim92_count/0.05)*30;
		delay(0,0,0,10); //��ʱ20ms
	}
}

//ִ��վ�㶯��
void StationAction(u16 num)
{
	////��յر�
	keynumber=0;
	HmiNextRfidNum = NowRouteInfor[num][5];
	while(keynumber==0||keynumber!=NowRouteInfor[num][5])	//ɨ���ر꣬��Ŀ��ֵ�Ļ�������while
	{		
		HmiRfidNum = keynumber;
		osdelay_ms(20);			
	}	
	//���Ͽ���		
	Jhwai_switch=NowRouteInfor[num][0];
	//���µ�����
	//�ٶ�
	if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
	if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
	if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];	
	
	//�˶�����
	//����
	if(NowRouteInfor[num][6]==0)
	{
		stopAsk=1 ;
		while(stopAsk) 
		{
			delay(0,0,0,10);
		} 
		dir = 0;						
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
		}			
	}
	//ͨ��
	else if(NowRouteInfor[num][6]==1)
	{
//                        startAsk=1 ;
	}
	//ͣ��
	else if(NowRouteInfor[num][6]==2)
	{
		stopAsk=1 ;
		while(stopAsk) 
		{
			delay(0,0,0,10);
		}                     
	}
	
	//����
	else if(NowRouteInfor[num][6]==3)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}                        
		dir = 1;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
		}
	}
	 
	//��������
	else if(NowRouteInfor[num][6]==4)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
			delay(0,0,NowRouteInfor[num][8],0);
			if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];			
			dir=0;
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}							
		}
	}
	
	//���Ʒ���
   else if(NowRouteInfor[num][6]==5)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];			
			dir=1;
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}							
		}						
	}
	
	//����ֹͣ
   else if(NowRouteInfor[num][6]==6)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=2;
		startAsk=1 ;
		while(startAsk)
		{
			delay(0,0,0,10);
		}
		stopAsk=1 ;
		while(stopAsk) 
		{
			delay(0,0,0,10);
		} 
		if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
		if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
		if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];		
		dir=0;
	}
	
	//��������
	else if(NowRouteInfor[num][6]==7)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];			
			dir=0;
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}							
		}						
	}
	
	//���Ʒ���
	else if(NowRouteInfor[num][6]==8)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		if(NowRouteInfor[num][7]==0)
		{
			delay(0,0,NowRouteInfor[num][8],0);
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}
			delay(0,0,NowRouteInfor[num][8],0);	
			if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
			if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
			if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];			
			dir=1;
			startAsk=1 ;
			while(startAsk)
			{
				delay(0,0,0,10);
			}							
		}
	}                    
	//����ֹͣ
	else if(NowRouteInfor[num][6]==9)
	{
		stopAsk=1 ;
		while(stopAsk)
		{
			delay(0,0,0,10);
		}
		dir=3;
		startAsk=1 ;
		while(startAsk)
		{
			delay(0,0,0,10);
		}
		stopAsk=1 ;
		while(stopAsk) 
		{
			delay(0,0,0,10);
		} 	
		if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
		if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
		if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];		
		dir=0;
	}                  
	//�ֲ��
	if(NowRouteInfor[num][1]==0)	fencha_dir = 0;
	if(NowRouteInfor[num][1]==1) 	fencha_dir = 1;
	if(NowRouteInfor[num][1]==2) 	fencha_dir = 2;
	
}
//u8 StationInfo[16];//ÿ��վ�����Ϣ
//Ҫд�뵽W25Q128���ַ������飬W25Q128��128M Bit��С��16M Bytes��С

u32 FLASH_SIZE=0; //FLASH ��СΪ16M�ֽ�16*8*1024*1024
u16 StationData[16]; 
u8 du_flag=0;
void Screen_task(void*p_arg)
{
    OS_ERR err ;
    u16 i=0,j=0 ;
    (void)p_arg ;    
    UserConfigInit();
    //�û�������ʼ��
//    JieMianHao=3 ;
    
    while(1)
    {
        switch(JieMianHao)
        {
            case 0 :
            break ;
			case 2 :
            break ;
            case ZiDongMoShiJieMian :
				while(JieMianHao==ZiDongMoShiJieMian)
				{
					if(flag_szd == 0)
					{
//								if(PLC_OutPut[11]==1)			//����
//								{
//									Qi_Dong();
//								}
//								if(PLC_OutPut[12]==1)		 	//ֹͣ
//								{
//									Ting_Zhi();
//								}
					}
					osdelay_ms(10);
				}				
            break ;
            case 4 :
            break ;
			//·���滮����
            case LuJingGuiHuaJieMian :
            {			
				while(JieMianHao==LuJingGuiHuaJieMian||JieMianHao==QueDingChaRuLuJingJieMian||JieMianHao==QueDingShanChuLuJingJieMian
					||JieMianHao==FuZhiLuJingTanChuJieMian)
				{  
					//����·��
					while(JieMianHao==FuZhiLuJingTanChuJieMian)//���ڸ���·������
					{
						//������·����Ϊ��ʱ��1
						if(HmiRouteCopiedNum==0)
							HmiRouteCopiedNum=1;	
						if(HmiRouteCopiedNum>RouteNum)	
						{
							HmiRouteCopiedNum =1;
						}
						
						//����ı�����·���ű仯ʱ����
						if(HmiRouteCopiedNumTemp!=HmiRouteCopiedNum)
							HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);
						
						
						//ȷ������
						if(HmiRoutemode==1)
						{
							//��ȡ��������Ϣ����ǰ
							GetRouteData(HmiRouteCopiedNum);
							
							//���沢���±�������Ϣ
							SetRouteData(HmiRouteNum);	
							
							UpdataStationToHmi();
							
							//���õ�ǰվ��Ϊ1
							if(HmiStationNum!=0)
								HmiStationSerialNum = 1;
							
							//�˳�����ģʽ
							HmiRoutemode=0;
						}
						osdelay_ms(10);
					}

					//���վ��
					if(HmiRoutemode==2)
					{ 
						//վ������һ
						HmiStationNum ++;
						//վ��ŵ���վ����
						HmiStationSerialNum = HmiStationNum;
						
						//�ر������
						keynumber = 0;		
						
						ClearStationToHmi();	
						
						while(HmiRoutemode==2)
						{
							//��������ر꣬���µ���ʾ��
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//ˢ�µر��
							}										
							//ȷ��
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//����վ�����ݵ���ǰ����
								UpdataStationToNow();

								//����վ����Ϣ
								SetStationData(HmiRouteNum,HmiStationSerialNum-1);
								//�˳����ģʽ
								HmiRoutemode = 0;
							}
							else
							//ȡ��
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//վ������һ
								HmiStationNum--;
								//վ��ŵ���վ����
								HmiStationSerialNum = HmiStationNum;
								//�˳����ģʽ
								HmiRoutemode = 0;
							}
							osdelay_ms(10);
						}
					}
					//����վ��
					if(HmiRoutemode==3)
					{
						//վ������һ
						HmiStationNum ++;
						//վ���Ϊ��ʱ��һ
						if(HmiStationNum==0)
							HmiStationSerialNum = 1;
						
						//�ر������
						keynumber = 0;		
						
						ClearStationToHmi();										

						while(HmiRoutemode==3)
						{
							//��������ر꣬���µ���ʾ��
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//ˢ�µر��
							}												
							
							//ȷ��
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								
								//վ����Ϣ����ƶ�һ��λ�ã������뵱ǰվ����Ϣ
								for(i=HmiStationNum;i>=HmiStationSerialNum;i--)
								{
									for(j=0;j<StaiionInfor;j++)
									{
										NowRouteInfor[i][j] = NowRouteInfor[i-1][j];
									}
								}
								
								//����վ����Ϣ����ǰ
								UpdataStationToNow();
								
								//����·����Ϣ
								SetRouteData(HmiRouteNum);

								//�˳����ģʽ
								HmiRoutemode=	0;
							}
							else
							//ȡ��
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//վ������һ
								HmiStationNum--;
								//վ���Ϊ1ʱ����
								if(HmiStationSerialNum==1)
									HmiStationSerialNum = 0;
								//�˳����ģʽ
								HmiRoutemode=	0;
							}

							osdelay_ms(10);
						}

					}
					//����վ��
					if(HmiRoutemode==4)
					{
						keynumber = 0;
						while(HmiRoutemode==4)
						{
							//��������ر꣬���µ���ʾ��
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//ˢ�µر��
							}			
							
							//ȷ��
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//����վ�����ݵ���ǰ����
								UpdataStationToNow();
								//���浱ǰվ������
								SetRouteData(HmiRouteNum);
								//�˳����ģʽ
								HmiRoutemode = 0;
							}
							else
							//ȡ��
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//���µ�����
								UpdataStationToHmi();
								//�˳����ģʽ
								HmiRoutemode=	0;
							}
							osdelay_ms(10);
						}
					}
				
					//ɾ��վ��
					if(HmiRoutemode==5)
					{
						if(HmiStationNum>0)
						{
							//��������������ǰ�ƶ�һλ
							if((HmiStationNum>0)&&((HmiStationNum)!=HmiStationSerialNum))
							{
								//վ����Ϣ��ǰ�ƶ�һ��λ��
								for(i=HmiStationSerialNum;i<HmiStationNum;i++)
								{
									for(j=0;j<StaiionInfor;j++)
									{
										NowRouteInfor[i-1][j] = NowRouteInfor[i][j];
									}
								}
							}

							HmiStationNum--;
							if(HmiStationNum==0)
								HmiStationSerialNum = 0;
							else if((HmiStationNum+1 )== HmiStationSerialNum)
								HmiStationSerialNum--;
							//����·����Ϣ
							SetRouteData(HmiRouteNum);
							
							//���½���
							UpdataStationToHmi();
						}	
						HmiRoutemode = 0;
					}
					
					//��ѯվ��
					if(HmiRoutemode==0)
					{
						//��·��վ��������0���������Ϊ0ʱ���������Ϊ1����������ʾ����
						if((HmiStationNum>0)&&(HmiStationSerialNum==0))
						{
							HmiStationSerialNum = 1;
							//���µ�����
							UpdataStationToHmi();
						}
						else
						if(HmiStationNum==0)
						{
							HmiStationSerialNum = 0;
						}
						
						//·���ű仯ʱ�����½���
						if(HmiRouteNumFlag != HmiRouteNum)
						{
							HmiRouteNumFlag = HmiRouteNum;
							//��ȡ·����Ϣ
							GetRouteData(HmiRouteNum);
							
							if(HmiStationNum>0)
								HmiStationSerialNum = 1;
							//���µ�����
							UpdataStationToHmi();
							
						}
						
						//��һ��
						if(HmiStationLast == 1)
						{
							HmiStationLast = 0;
							if(HmiStationSerialNum>1)
								HmiStationSerialNum--;
							else
								HmiStationSerialNum = HmiStationNum;
						}
						//��һ��
						if(HmiStationNext == 2)
						{
							HmiStationNext = 0;
							if(HmiStationSerialNum<HmiStationNum)
									HmiStationSerialNum++;
								else
									if(HmiStationSerialNum!=0)
										HmiStationSerialNum = 1;
						}
						
						if(HmiStationNum==0)		//û��վ��
						{
							//���վ����Ϣ
							ClearStationToHmi();
						}
						else
						{
							//����վ����Ϣ
							UpdataStationToHmi();
						}
					}
					osdelay_ms(10);
				}
			}
            break ;
			case 7 :
            case 6 :
			//���Խ�������
			case 8:
				while(JieMianHao==8)
				{		
					 SystemParameter[19] = PIDZhouQi;
					 SystemParameter[20] = SPID_P;
					 SystemParameter[21] = SPID_I ;
					 SystemParameter[22] = SPID_D;
					 SystemParameter[23] = QianHouJuLi;
					 SystemParameter[15] = ZiDongJiSu;
					 delay(0,0,0,10);					
				}			
				//�洢����ϵͳ����
				SetAllParameterToSystem();
			break;
			case 9 :
            //��������
            //
            while(JieMianHao==9)
            {				
				SystemParameter[6] = HmiRouteNum;   //·����                             
				SystemParameter[9] = PLC_Data[22];//����
				SystemParameter[10] = PLC_Data[23];//����
				SystemParameter[11] = PLC_Data[24];//����
				SystemParameter[14] = SouDongSuDu;
				SystemParameter[15] = ZiDongJiSu;
				SystemParameter[16] = SouDongBiZhang;
				SystemParameter[17] = YuYinKaiGuan;
				SystemParameter[18] = YinLiang;
				SystemParameter[98] = LiuChengZongShu;
				SystemParameter[99] = LuJingZongShu;
				SystemParameter[25]	= CheHao;	
                delay(0,0,0,10);
            }
            //ѭ���������������
			//Your Save Code��
			//�洢����ϵͳ����
			SetAllParameterToSystem();			
            break ;
			//��������
			case LiuChengGuiHuaJieMian:
				{
						while(JieMianHao==LiuChengGuiHuaJieMian||JieMianHao==FuZhiLiuChengTanChuJieMian||JieMianHao==QueDingChaRuLiuChengJieMian
							||JieMianHao==QueDingShanChuLiuChengJieMian)
						{ 
							//�鿴ģʽ
							if(HmiProcessMode==0)
							{
								//��ǰ���̲�������0�����ҽ������Ϊ0ʱ���������Ϊ1����������ʾ����
								if((HmiStepNum>0)&&(HmiProcessSerialNum==0))
								{
									HmiProcessSerialNum = 1;
									GetProcessData();
								}
								else
								if(HmiStepNum==0)
								{
									HmiProcessSerialNum = 0;
									HmiProcessStartNum = 1;
									HmiProcessStopNum = 0;
									HmiProcessAction = 0;
								}
								
								//���̺ű仯ʱ�����½���
								if(HmiProcessNumFlag != HmiProcessNum)
								{
									HmiProcessNumFlag = HmiProcessNum;
									GetProcessData();
								}
								
								if(HmiProcessLast==1)//��һ��
								{
									HmiProcessLast = 0;
									if(HmiProcessSerialNum>1)
										HmiProcessSerialNum--;
									else
										HmiProcessSerialNum = HmiStepNum;
								}
								else
									if(HmiProcessNext==2)//��һ��
									{
										HmiProcessNext = 0;
										if(HmiProcessSerialNum<HmiStepNum)
											HmiProcessSerialNum++;
										else
											if(HmiProcessSerialNum!=0)
												HmiProcessSerialNum = 1;
									}
								if(HmiStepNum==0)
								{
									ClearStepToHmi();
								}
								else
								{
									UpdataProcessToHmi();
								}								
							}									
							//��������
							if(JieMianHao==FuZhiLiuChengTanChuJieMian)
							{
								while(JieMianHao==FuZhiLiuChengTanChuJieMian)
								{
									//���������̺�Ϊ��ʱ��1
									if(HmiProcessCopiedNum==0)
										HmiProcessCopiedNum=1;	
									//����ı��������̺ű仯ʱ����
									if(HmiProcessCopiedNumTemp!=HmiProcessCopiedNum)
										HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);
									if(HmiProcessCopiedNum>ProcessNum)
									{
										HmiProcessCopiedNum = 1;
									}
									//ȷ������
									if(HmiProcessMode==1)
									{
										//��ȡ��������Ϣ����ǰ
										GetProcessDataFrom(HmiProcessCopiedNum);
										//���汻������Ϣ
										SetProcessData();	
										
										//���õ�ǰ���Ϊ1
										if(HmiStepNum!=0)
											HmiProcessSerialNum = 1;
									
										//�˳�����ģʽ
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							//�������
							if(HmiProcessMode==2)
							{
								//���̲�����һ
								HmiStepNum++;
								//��ŵ���������
								HmiProcessSerialNum = HmiStepNum;
								
								//��ʼ·����Ĭ��Ϊ0����1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==2)
								{
									switch(HmiProcessAction)
									{
										case 0://����ִ��
											break;
										case 1://˳��ִ�е�
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://����ִ��
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://ѭ��ִ��
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//ȷ��
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//���沢��������
										SetProcessData();
										
										//�˳����ģʽ
										HmiProcessMode = 0;
									}
									//ȡ��
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//���̲�����һ
										HmiStepNum--;
										//��ŵ���������
										HmiProcessSerialNum = HmiStepNum;
										
										//�˳����ģʽ
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							
							//��������
							if(HmiProcessMode==3)
							{
								//���̲�����һ
								HmiStepNum++;
								//���Ϊ��ʱ��һ
								if(HmiProcessSerialNum==0)
									HmiProcessSerialNum = 1;
								
								//��ʼ·����Ĭ��Ϊ0����1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==3)
								{
									switch(HmiProcessAction)
									{
										case 0://����ִ��
											break;
										case 1://˳��ִ�е�
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://����ִ��
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://ѭ��ִ��
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//ȷ��
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										
										//���沢��������
										InsertProcessData();
										
										//�˳�����ģʽ
										HmiProcessMode = 0;
									}
									//ȡ��
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//���̲�����һ
										HmiStepNum--;
										//���Ϊ1ʱ��һ
										if(HmiProcessSerialNum==1)
											HmiProcessSerialNum = 0;
										
										//�˳����ģʽ
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//��������
							if(HmiProcessMode==4)
							{
								while(HmiProcessMode==4)
								{
									switch(HmiProcessAction)
									{
										case 0://����ִ��
											break;
										case 1://˳��ִ�е�
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://����ִ��
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://ѭ��ִ��
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//ȷ��
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//���沢��������
										SetProcessData();
										
										//�˳�����ģʽ
										HmiProcessMode = 0;
									}
									//ȡ��
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;

										//�˳����ģʽ
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//ɾ������
							if(HmiProcessMode==5)
							{
								DeleteProcessData();
								//�˳�ɾ��ģʽ
								HmiProcessMode = 0;
							}
							osdelay_ms(10);
						}
				}
			break;
			//ȡ������
			case QuXiaoRenWuJieMian: 
			{		
				while(JieMianHao==QuXiaoRenWuJieMian)
				{
					if(QuXiaoRenWuQueDing==1)
					{
						QuXiaoRenWuQueDing = 0;
						
						HmiTask = 0;
						HmiTaskState = 0;
						//ͣ��
						stopAsk = 1;
						dir = 0;
						//ɾ������
						OSTaskDel((OS_TCB*)&Task5_TaskTCB,&err);
						//���´�������
						OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,		
						(CPU_CHAR	* )"Task5 task", 		
									 (OS_TASK_PTR )Task5_task, 			
									 (void		* )0,					
									 (OS_PRIO	  )Task5_TASK_PRIO,     	
									 (CPU_STK   * )&Task5_TASK_STK[0],	
									 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
									 (CPU_STK_SIZE)Task5_STK_SIZE,		
									 (OS_MSG_QTY  )0,					
									 (OS_TICK	  )0,					
									 (void   	* )0,				
									 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
									 (OS_ERR 	* )&err);
					}
					osdelay_ms(10);
				}							
			}
			break;
			case LiuChengSheZhiJieMian: 
				{		
					//���·����Ϊ�㣬����һ
					if(HmiProcessNum==0)
					{
						HmiProcessNum = 1;
					}
				}
			break;
			case LuJingSheZhiJieMian: 
				{		
					//���·����Ϊ�㣬����һ
					if(HmiRouteNum==0)
					{
						HmiRouteNum = 1;
					}
				}
			break;
			//ִ��·��
			case ZhiXingLuJingJieMian:
				{		
					while(JieMianHao==ZhiXingLuJingJieMian)
					{
						if(ZhiXingLuJingQueDing==1)
						{
							//����·����
							SetOneParameterToSystem(HmiRouteNum,6);
							HmiTask = 1;
							SystemParameter[8] = HmiTask;
							//���������
							SetOneParameterToSystem(HmiTask,8);
							ZhiXingLuJingQueDing = 0;
							
							//�Զ�������ʾ��Ϣ����
							HmiAutoReload();
						}
						osdelay_ms(10);
					}
				}
			break;
			//ִ������
			case ZhiXingLiuChengJieMian: 
			{		
				while(JieMianHao==ZhiXingLiuChengJieMian)
				{
					if(ZhiXingLiuChengQueDing==1)
					{
						//�������̺�
						SetOneParameterToSystem(HmiProcessNum,7);
						HmiTask = 2;
						SystemParameter[8] = HmiTask;
						//���������
						SetOneParameterToSystem(HmiTask,8);
						ZhiXingLiuChengQueDing = 0;
						
						//����״̬Ϊ��������
						HmiTaskState = 5;
						
						//�Զ�������ʾ��Ϣ����
						HmiAutoReload();
					}
					osdelay_ms(10);
				}							
			}
			break;				
            default :
            break ;
        }
        delay(0,0,0,10);
    }
}
//ִ������
void Task5_task(void *p_arg)
{	
	u16 i,j,k;
	p_arg = p_arg;

	while(1)
	{
		if(flag_szd == 0)
		{
			//ִ��·��
			if(HmiTask==1)
			{
				HmiStationSerialNum = 0;
				//������ѡ·����ִ����Ӧ����
				for(i=0;i<HmiStationNum;i++)
				{
					StationAction(i);
				}
			}
			else
				//ִ������
				if(HmiTask == 2)
				{
					HmiProcessSerialNum = 0;
					for(i=0;i<HmiStepNum;i++)
					{
						HmiProcessSerialNum++;
						switch(NowProcessInfor[i][1])
						{
							case 0://����ִ��
								//����·����
								HmiRouteNum = NowProcessInfor[i][0];
							  //��ȡ·������վ����
								GetRouteStationNum(HmiRouteNum);
								//��ȡ��ǰ·����Ϣ
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//������ѡ·����ִ����Ӧ����
								for(j=0;j<HmiStationNum;j++)
								{
									StationAction(j);
								}
								break;
							case 1://˳��ִ��
								for(k=NowProcessInfor[i][0];k<=NowProcessInfor[i][2];k++)
								{
									//����·����
									HmiRouteNum = k;
									//��ȡ·������վ����
									GetRouteStationNum(HmiRouteNum);
									//��ȡ��ǰ·����Ϣ
									GetRouteData(HmiRouteNum);
									
									HmiStationSerialNum = 0;
									//������ѡ·����ִ����Ӧ����
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 2://����ִ��
								for(k=NowProcessInfor[i][0];k>=NowProcessInfor[i][2];k--)
								{
									//����·����
									HmiRouteNum = k;
									//��ȡ·������վ����
									GetRouteStationNum(HmiRouteNum);
									//��ȡ��ǰ·����Ϣ
									GetRouteData(HmiRouteNum);
  
									HmiStationSerialNum = 0;
 									//������ѡ·����ִ����Ӧ����
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 3://ѭ��ִ��
								//����·����
								HmiRouteNum = NowProcessInfor[i][0];
							  //��ȡ·������վ����
								GetRouteStationNum(HmiRouteNum);
								//��ȡ��ǰ·����Ϣ
								GetRouteData(HmiRouteNum);
								for(k=0;k<NowProcessInfor[i][2];k++)
								{
									HmiStationSerialNum = 0;
									//������ѡ·����ִ����Ӧ����
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							default:break;
						}
					}
				}		
		}
		osdelay_ms(10);
	}
}
void Control_task(void *p_arg)
{
	u8 num=0;
	OS_ERR err;
	while(1)
	{
		num++;
		if(num==100)
		{
			LED3 = ~LED3;//���е�
			num=0;
		}
		ld_juli = QianHouJuLi;//ǰ�󵹳��״��������
		if(flag_szd==0)
		{
			if(Jhwai_switch&&(flag_qd==1))
			{				
				if(dir==0)//������
				{
					if(((QianZuoLeiDa<=ld_juli)||(QianYouLeiDa<=ld_juli))&&(Jhwai_flag == 0))
					{
						HmiTaskState = 2;
						Jhwai_flag = 1;
						MotoStop(5);
						speek("ǰ�����ϰ�");
					}
					if(((QianZuoLeiDa>ld_juli)&&(QianYouLeiDa>ld_juli))&&(Jhwai_flag == 1))
					{
						OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
						HmiTaskState = 5;
						Jhwai_flag = 0;
						startAsk = 1;		
					}
				}
				else if(dir == 1)
				{
					if(((HouZuoLeiDa<=ld_juli)||(HouYouLeiDa<=ld_juli))&&(Jhwai_flag == 0))
					{
						HmiTaskState = 2;
						Jhwai_flag = 1;
						MotoStop(5);
						speek("ǰ�����ϰ�");
					}
					if(((HouZuoLeiDa>ld_juli)&&(HouYouLeiDa>ld_juli))&&(Jhwai_flag == 1))
					{
						OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
						HmiTaskState = 5;
						Jhwai_flag = 0;
						startAsk = 1;					
					}
				}
				else if(dir == 2)
				{
					if(((ZuoQianLeiDa<=ld_juli)||(ZuoHouLeiDa<=ld_juli))&&(Jhwai_flag == 0))
					{
						HmiTaskState = 2;
						Jhwai_flag = 1;
						MotoStop(5);
						speek("ǰ�����ϰ�");
					}
					if(((ZuoQianLeiDa>ld_juli)&&(ZuoHouLeiDa>ld_juli))&&(Jhwai_flag == 1))
					{
						OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
						HmiTaskState = 5;
						Jhwai_flag = 0;
						startAsk = 1;				
					}
				}
				else if(dir == 3)
				{
					if(((YouQianLeiDa<=ld_juli)||(YouHouLeiDa<=ld_juli))&&(Jhwai_flag == 0))
					{
						HmiTaskState = 2;
						Jhwai_flag = 1;
						MotoStop(5);
						speek("ǰ�����ϰ�");
					}
					if(((YouQianLeiDa>ld_juli)&&(YouHouLeiDa>ld_juli))&&(Jhwai_flag == 1))
					{
						OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
						HmiTaskState = 5;
						Jhwai_flag = 0;
						startAsk = 1;					
					}
				}				
			}			
		}	
		delay(0,0,0,10);
	}
}
u8 Manual_juli=8;
void WIFI_task(void *p_arg)
{	
	while(1)
	{
		Manual_juli = QianHouJuLi;

		if((flag_szd==1)&&(SouDongBiZhang))
		{
			if(QianJin==0)//ǰ��
			{
				if(((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(QianFangZhuang==0)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);
				}
				else
				{
					speek_flag=0;
				}
			}			
			if(HouTui==0)//����
			{
				if(((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(HouFangZhuang==0)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}	
				else
				{
					speek_flag=0;
				}				
			}
			if(ZuoYi==0)//����
			{
				if(((ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);				
				}	
				else
				{
					speek_flag=0;
				}				
			}
			if(YouYI==0)//����
			{
				if(((YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}	
				else
				{
					speek_flag=0;
				}				
			}
			if(ZuoXuan==0)//����
			{
				if(((ZuoQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}
				else
				{
					speek_flag=0;
				}				
			}
			if(YouXuan==0)//����
			{
				if(((ZuoHouLeiDa<Manual_juli)||(YouQianLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}	
				else
				{
					speek_flag=0;
				}				
			}
			if(ZuoShang==0)//����
			{
				if(((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}
				else
				{
					speek_flag=0;
				}				
			}
			if(ZuoXia==0)//����
			{
				if(((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(ZuoQianLeiDa<Manual_juli)||(ZuoHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}	
				else
				{
					speek_flag=0;
				}				
			}
			if(YouShang==0)//����
			{
				if(((QianZuoLeiDa<Manual_juli)||(QianYouLeiDa<Manual_juli)||(YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}
				else
				{
					speek_flag=0;
				}				
			}
			if(YouXia==0)//����
			{
				if(((HouZuoLeiDa<Manual_juli)||(HouYouLeiDa<Manual_juli)||(YouQianLeiDa<Manual_juli)||(YouHouLeiDa<Manual_juli)))
				{
					speek_flag=1;
					speed_vul=0;
					MotoStop(5);					
				}
				else
				{
					speek_flag=0;
				}				
			}
			if((QianJin==1)&&(HouTui==1)&&(ZuoYi==1)&&(YouYI==1)&&(ZuoShang==1)
			&&(ZuoXia==1)&&(YouShang==1)&&(YouXia==1)&&(ZuoXuan==1)&&(YouXuan==1))
			{
				speek_flag=0;			
			}
		}
		else
		{
			speek_flag=0;
		}
		delay(0,0,0,10);
	}
	
}
u16 demo_speed=80;
void DEMO_task(void *p_arg)
{
	u16 num=0;
	while(1)
	{	
		num++;
		if(num==20)
		{
			num=0;
			IWDG_Feed();//ι��
		}		
		osdelay_ms(10);   
	}
}

//����
void DEMO1_task(void *p_arg)
{
	while(1)
	{
		if(startAsk)
		{
			if(HmiTask == 0)
			{
				JieMianHao = 21;
				speek("��ѡ����Ҫִ�е�����");
				startAsk = 0;					
			}
			else
			{
				start();
				HmiTaskState = 5;
				HmiShouZiDongYinCang = 0;//����������ʾֹͣ
				startAsk = 0;						
			}
					
		}	
		delay(0,0,0,10);      
	}
}
//ֹͣ
void DEMO2_task(void *p_arg)
{
	while(1)
	{
		if(receive_ok == 1)
		{
			data_Parameterreceive();
			DMA_Cmd(DMA2_Stream1, ENABLE);
		}
		if(stopAsk)
		{
			stop();
			HmiTaskState = 3;
			HmiShouZiDongYinCang = 1;//����ֹͣ��ʾ����
			stopAsk = 0;
		}
		delay(0,0,0,5);      
	}
}

