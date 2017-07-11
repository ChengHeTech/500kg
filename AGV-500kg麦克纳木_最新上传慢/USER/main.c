#include "sys.h"

//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define Transducer_TASK_PRIO		4
//任务堆栈大小	
#define Transducer_STK_SIZE 		512
//任务控制块
OS_TCB TransducerTaskTCB;
//任务堆栈	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);


//任务优先级
#define Auto_TASK_PRIO		5
//任务堆栈大小	
#define Auto_STK_SIZE 		512
//任务控制块
OS_TCB AutoTaskTCB;
//任务堆栈	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//任务函数
void Auto_task(void *p_arg);

//任务优先级
#define Manual_TASK_PRIO		6
//任务堆栈大小	
#define Manual_STK_SIZE 		512
//任务控制块
OS_TCB ManualTaskTCB;
//任务堆栈	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//任务函数
void Manual_task(void *p_arg);

//任务优先级
#define FLOAT_TASK_PRIO		7
//任务堆栈大小
#define FLOAT_STK_SIZE		512
//任务控制块
OS_TCB	FloatTaskTCB;
//任务堆栈
CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//任务函数
void float_task(void *p_arg);

//任务优先级
#define Screen_TASK_PRIO		12
//任务堆栈大小	
#define Screen_STK_SIZE 		512
//任务控制块
OS_TCB ScreenTaskTCB;
//任务堆栈	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//任务函数
void Screen_task(void *p_arg);

//任务优先级
#define PID_TASK_PRIO		9
//任务堆栈大小	
#define PID_STK_SIZE 		512
//任务控制块
OS_TCB PIDTaskTCB;
//任务堆栈	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//任务函数
void PID_task(void *p_arg);


//任务优先级
#define Control_TASK_PRIO		10
//任务堆栈大小	
#define Control_STK_SIZE 		512
//任务控制块
OS_TCB ControlTaskTCB;
//任务堆栈	
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//任务函数
void Control_task(void *p_arg);


//任务优先级
#define WIFI_TASK_PRIO		11
//任务堆栈大小	
#define WIFI_STK_SIZE 		512
//任务控制块
OS_TCB WIFITaskTCB;
//任务堆栈	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//任务函数
void WIFI_task(void *p_arg);

//任务优先级
#define DEMO_TASK_PRIO		8
//任务堆栈大小	
#define DEMO_STK_SIZE 		512
//任务控制块
OS_TCB DEMOTaskTCB;
//任务堆栈	
CPU_STK DEMO_TASK_STK[WIFI_STK_SIZE];
//任务函数
void DEMO_task(void *p_arg);


//任务优先级
#define DEMO1_TASK_PRIO		13
//任务堆栈大小	
#define DEMO1_STK_SIZE 		512
//任务控制块
OS_TCB DEMO1TaskTCB;
//任务堆栈	
CPU_STK DEMO1_TASK_STK[DEMO1_STK_SIZE];
//任务函数
void DEMO1_task(void *p_arg);

//任务优先级
#define DEMO2_TASK_PRIO		14
//任务堆栈大小	
#define DEMO2_STK_SIZE 		512
//任务控制块
OS_TCB DEMO2TaskTCB;
//任务堆栈	
CPU_STK DEMO2_TASK_STK[DEMO2_STK_SIZE];
//任务函数
void DEMO2_task(void *p_arg);

//任务优先级
#define Task5_TASK_PRIO		15
//任务堆栈大小	
#define Task5_STK_SIZE 		512
//任务控制块
OS_TCB Task5_TaskTCB;
//任务堆栈	
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//任务函数
void Task5_task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  	//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
	LED_Init();         //LED初始化
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
//	TLC5620_Init();	//DA初始化
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN1初始化普通模式,波特率500Kbps
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN2初始化普通模式,波特率500Kbps
	PID_Init();
	TIM2_Int_Init(5000-1,840-1);			//Tout=((arr+1)*(psc+1))/Ft us.  50ms	
	TIM3_CH1_Cap_Init1(5000,84-1); 			//以84/84=1Mhz的频率计数 5ms捕获脉冲
 	TIM9_CH1_Cap_Init1(5000,84-1); 			//以84/84=1Mhz的频率计数 5ms捕获脉冲
	IWDG_Init(4,500);
	can_Sebuf[2]=0x55;//发送继电器板同步信息
	CanSend();	
	can_Sebuf[2]=0;
	MotoStop(5);

	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}
u8 State_Autotask=0,State_Controltask=0,State_PIDtask=0,State_Manualtask=1,State_DEMOtask=1,State_WIFItask=1;

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
	//创建Transducer任务
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
	
	//创建自动任务
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
				 
	//创建浮点测试任务
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

	//创建触摸屏任务
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
				 
	//创建手动任务
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
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//进入临界区
}

//Transducer_task函数
u8  flag_szd=1;
void Transducer_task(void *p_arg)//任务调度，手动时删除与自动有关的任务，自动时删除与手动有关的任务
{
	OS_ERR err;
	p_arg = p_arg;
	HmiScreenControlMode = 1;
	while(1)
	{	
		if(((SouZiDongQieHuan==0)&&(flag_szd == 0))||(PLC_OutPut[18]==1))
		{
			speek("手动");
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
				//创建手动任务
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
			speek("自动");	
			speed = ZiDongJiSu;	//自动一开始没扫到地标之前给个速度		
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
				//创建自动任务
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
		delay(0,0,0,10); //延时10ms
	}
}
void Auto_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(flag_qd==0)//防止多次软起
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
					speek("急停，按启动键启动");
				}
			}
			else if(dir==1)
			{
				if(HfangZ==0)
				{
					stopAsk=1;
					speek("急停，按启动键启动");
				}			
			}			
		}
		delay(0,0,0,10); //延时20ms
	}
}

void Manual_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{	
		if((QianJin==0))//前进
		{
			Motor_Zzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);		
	
			if((ZuoXuan==0))//左旋
			{
				Motor_Zzhuan(2,SouDongSuDu*1.5);
				Motor_Zzhuan(4,SouDongSuDu*1.5);
			}
			else if((YouXuan==0))//右旋
				{
					Motor_Zzhuan(1,SouDongSuDu*1.5);
					Motor_Zzhuan(3,SouDongSuDu*1.5);
				}
		}
		else if((HouTui==0))//后退
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Fzhuan(4,SouDongSuDu);
			
			if((ZuoXuan==0))//左旋
			{
				Motor_Zzhuan(2,SouDongSuDu*1.5);
				Motor_Zzhuan(4,SouDongSuDu*1.5);
			}
			else if((YouXuan==0))//右旋
				{
					Motor_Zzhuan(1,SouDongSuDu*1.5);
					Motor_Zzhuan(3,SouDongSuDu*1.5);
				}
		}
		else if((ZuoYi==0))//左移
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			Motor_Fzhuan(4,SouDongSuDu);
		}
		else if((YouYI==0))//右移
		{
			Motor_Zzhuan(1,SouDongSuDu);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((ZuoShang==0))//左上
		{
			MotoStop(1);			
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Zzhuan(3,SouDongSuDu);
			MotoStop(4);
		}
		else if((ZuoXia==0))//左下
		{
			Motor_Fzhuan(1,SouDongSuDu);
			MotoStop(2);
			MotoStop(3);
			Motor_Fzhuan(4,SouDongSuDu);
		}
		else if((YouShang==0))//右上
		{
			Motor_Zzhuan(1,SouDongSuDu);
			MotoStop(2);
			MotoStop(3);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((YouXia==0))//右下
		{
			MotoStop(1);
			Motor_Fzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			MotoStop(4);
		}
		else if((ZuoXuan==0))//左旋
		{
			Motor_Fzhuan(1,SouDongSuDu);
			Motor_Zzhuan(2,SouDongSuDu);
			Motor_Fzhuan(3,SouDongSuDu);
			Motor_Zzhuan(4,SouDongSuDu);
		}
		else if((YouXuan==0))//右旋
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
		delay(0,0,0,10); //延时10ms
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
			LED1 = ~LED1;//运行灯
			TongXunDeng=~TongXunDeng;//触摸屏通讯指示灯
			LiDian_send();//获取电池数据
			num=0;
		}
		QianFangZhuang = QfangZ;//前防撞
		HouFangZhuang = HfangZ;//后防撞
		
		if(speek_flag==1)//语音播报处理
		{
			speek("前方有障碍");
			OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);
		}
		
		if(JieMianHao==5)
		{
			//动态刷新手动自动和时间按钮的显示或隐藏
			//正向、反向、左移正向、左移反向、右移正向、右移反向
			if(PLC_Data[4]==0||PLC_Data[4]==3||PLC_Data[4]==4||PLC_Data[4]==5||PLC_Data[4]==7||PLC_Data[4]==8)
			{
				PLC_OutPut[0]=1;//显示手动自动
				if(PLC_Data[5]==0)//自动
					PLC_OutPut[1]=1;//显示停留时间
				else
					PLC_OutPut[1]=0;//隐藏停留时间
			}
			else
			{
				PLC_OutPut[0]=0;//隐藏手动自动
				PLC_OutPut[1]=0;//隐藏停留时间
			}
		}
		//电机转速计算 转/每分钟
		motor1 = (tim31_count/0.05)*30;
		motor2 = (tim32_count/0.05)*30;
		motor3 = (tim91_count/0.05)*30;
		motor4 = (tim92_count/0.05)*30;
		delay(0,0,0,10); //延时20ms
	}
}

//执行站点动作
void StationAction(u16 num)
{
	////清空地标
	keynumber=0;
	HmiNextRfidNum = NowRouteInfor[num][5];
	while(keynumber==0||keynumber!=NowRouteInfor[num][5])	//扫到地标，是目标值的话则跳出while
	{		
		HmiRfidNum = keynumber;
		osdelay_ms(20);			
	}	
	//避障开关		
	Jhwai_switch=NowRouteInfor[num][0];
	//更新到车体
	//速度
	if(NowRouteInfor[num][4] == 0)	speed=PLC_Data[22];
	if(NowRouteInfor[num][4] == 1)	speed=PLC_Data[23];
	if(NowRouteInfor[num][4] == 2)	speed=PLC_Data[24];	
	
	//运动方向
	//正向
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
	//通过
	else if(NowRouteInfor[num][6]==1)
	{
//                        startAsk=1 ;
	}
	//停车
	else if(NowRouteInfor[num][6]==2)
	{
		stopAsk=1 ;
		while(stopAsk) 
		{
			delay(0,0,0,10);
		}                     
	}
	
	//反向
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
	 
	//左移正向
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
	
	//左移反向
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
	
	//左移停止
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
	
	//右移正向
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
	
	//右移反向
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
	//右移停止
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
	//分叉口
	if(NowRouteInfor[num][1]==0)	fencha_dir = 0;
	if(NowRouteInfor[num][1]==1) 	fencha_dir = 1;
	if(NowRouteInfor[num][1]==2) 	fencha_dir = 2;
	
}
//u8 StationInfo[16];//每个站点的信息
//要写入到W25Q128的字符串数组，W25Q128是128M Bit大小，16M Bytes大小

u32 FLASH_SIZE=0; //FLASH 大小为16M字节16*8*1024*1024
u16 StationData[16]; 
u8 du_flag=0;
void Screen_task(void*p_arg)
{
    OS_ERR err ;
    u16 i=0,j=0 ;
    (void)p_arg ;    
    UserConfigInit();
    //用户参数初始化
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
//								if(PLC_OutPut[11]==1)			//启动
//								{
//									Qi_Dong();
//								}
//								if(PLC_OutPut[12]==1)		 	//停止
//								{
//									Ting_Zhi();
//								}
					}
					osdelay_ms(10);
				}				
            break ;
            case 4 :
            break ;
			//路径规划界面
            case LuJingGuiHuaJieMian :
            {			
				while(JieMianHao==LuJingGuiHuaJieMian||JieMianHao==QueDingChaRuLuJingJieMian||JieMianHao==QueDingShanChuLuJingJieMian
					||JieMianHao==FuZhiLuJingTanChuJieMian)
				{  
					//复制路径
					while(JieMianHao==FuZhiLuJingTanChuJieMian)//处于复制路径界面
					{
						//被复制路径号为零时置1
						if(HmiRouteCopiedNum==0)
							HmiRouteCopiedNum=1;	
						if(HmiRouteCopiedNum>RouteNum)	
						{
							HmiRouteCopiedNum =1;
						}
						
						//输入的被复制路径号变化时更新
						if(HmiRouteCopiedNumTemp!=HmiRouteCopiedNum)
							HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);
						
						
						//确定复制
						if(HmiRoutemode==1)
						{
							//读取被复制信息到当前
							GetRouteData(HmiRouteCopiedNum);
							
							//保存并更新被复制信息
							SetRouteData(HmiRouteNum);	
							
							UpdataStationToHmi();
							
							//设置当前站点为1
							if(HmiStationNum!=0)
								HmiStationSerialNum = 1;
							
							//退出复制模式
							HmiRoutemode=0;
						}
						osdelay_ms(10);
					}

					//添加站点
					if(HmiRoutemode==2)
					{ 
						//站点数加一
						HmiStationNum ++;
						//站点号等于站点数
						HmiStationSerialNum = HmiStationNum;
						
						//地标号清零
						keynumber = 0;		
						
						ClearStationToHmi();	
						
						while(HmiRoutemode==2)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
							}										
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//更新站点数据到当前数据
								UpdataStationToNow();

								//保存站点信息
								SetStationData(HmiRouteNum,HmiStationSerialNum-1);
								//退出添加模式
								HmiRoutemode = 0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//站点数减一
								HmiStationNum--;
								//站点号等于站点数
								HmiStationSerialNum = HmiStationNum;
								//退出添加模式
								HmiRoutemode = 0;
							}
							osdelay_ms(10);
						}
					}
					//插入站点
					if(HmiRoutemode==3)
					{
						//站点数加一
						HmiStationNum ++;
						//站点号为零时加一
						if(HmiStationNum==0)
							HmiStationSerialNum = 1;
						
						//地标号清零
						keynumber = 0;		
						
						ClearStationToHmi();										

						while(HmiRoutemode==3)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
							}												
							
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								
								//站点信息向后移动一个位置，并插入当前站点信息
								for(i=HmiStationNum;i>=HmiStationSerialNum;i--)
								{
									for(j=0;j<StaiionInfor;j++)
									{
										NowRouteInfor[i][j] = NowRouteInfor[i-1][j];
									}
								}
								
								//更新站点信息到当前
								UpdataStationToNow();
								
								//保存路径信息
								SetRouteData(HmiRouteNum);

								//退出添加模式
								HmiRoutemode=	0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//站点数减一
								HmiStationNum--;
								//站点号为1时置零
								if(HmiStationSerialNum==1)
									HmiStationSerialNum = 0;
								//退出添加模式
								HmiRoutemode=	0;
							}

							osdelay_ms(10);
						}

					}
					//更改站点
					if(HmiRoutemode==4)
					{
						keynumber = 0;
						while(HmiRoutemode==4)
						{
							//如果读到地标，更新到显示器
							if(keynumber!=0)
							{
								HmiRfidNum = keynumber;//刷新地标号
							}			
							
							//确定
							if(HmiRouteEnter==1)
							{
								HmiRouteEnter = 0;
								//更新站点数据到当前数据
								UpdataStationToNow();
								//保存当前站点数据
								SetRouteData(HmiRouteNum);
								//退出添加模式
								HmiRoutemode = 0;
							}
							else
							//取消
							if(HmiRouteEnter==2)
							{
								HmiRouteEnter = 0;
								//更新到界面
								UpdataStationToHmi();
								//退出添加模式
								HmiRoutemode=	0;
							}
							osdelay_ms(10);
						}
					}
				
					//删除站点
					if(HmiRoutemode==5)
					{
						if(HmiStationNum>0)
						{
							//将后面所数据向前移动一位
							if((HmiStationNum>0)&&((HmiStationNum)!=HmiStationSerialNum))
							{
								//站点信息向前移动一个位置
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
							//保存路径信息
							SetRouteData(HmiRouteNum);
							
							//更新界面
							UpdataStationToHmi();
						}	
						HmiRoutemode = 0;
					}
					
					//查询站点
					if(HmiRoutemode==0)
					{
						//当路径站点数大于0，并且序号为0时，设置序号为1，并更新显示内容
						if((HmiStationNum>0)&&(HmiStationSerialNum==0))
						{
							HmiStationSerialNum = 1;
							//更新到界面
							UpdataStationToHmi();
						}
						else
						if(HmiStationNum==0)
						{
							HmiStationSerialNum = 0;
						}
						
						//路径号变化时，更新界面
						if(HmiRouteNumFlag != HmiRouteNum)
						{
							HmiRouteNumFlag = HmiRouteNum;
							//获取路径信息
							GetRouteData(HmiRouteNum);
							
							if(HmiStationNum>0)
								HmiStationSerialNum = 1;
							//更新到界面
							UpdataStationToHmi();
							
						}
						
						//上一个
						if(HmiStationLast == 1)
						{
							HmiStationLast = 0;
							if(HmiStationSerialNum>1)
								HmiStationSerialNum--;
							else
								HmiStationSerialNum = HmiStationNum;
						}
						//下一个
						if(HmiStationNext == 2)
						{
							HmiStationNext = 0;
							if(HmiStationSerialNum<HmiStationNum)
									HmiStationSerialNum++;
								else
									if(HmiStationSerialNum!=0)
										HmiStationSerialNum = 1;
						}
						
						if(HmiStationNum==0)		//没有站点
						{
							//清除站点信息
							ClearStationToHmi();
						}
						else
						{
							//更新站点信息
							UpdataStationToHmi();
						}
					}
					osdelay_ms(10);
				}
			}
            break ;
			case 7 :
            case 6 :
			//调试界面设置
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
				//存储所有系统参数
				SetAllParameterToSystem();
			break;
			case 9 :
            //参数设置
            //
            while(JieMianHao==9)
            {				
				SystemParameter[6] = HmiRouteNum;   //路径号                             
				SystemParameter[9] = PLC_Data[22];//慢速
				SystemParameter[10] = PLC_Data[23];//中速
				SystemParameter[11] = PLC_Data[24];//快速
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
            //循环结束，保存参数
			//Your Save Code！
			//存储所有系统参数
			SetAllParameterToSystem();			
            break ;
			//流程设置
			case LiuChengGuiHuaJieMian:
				{
						while(JieMianHao==LiuChengGuiHuaJieMian||JieMianHao==FuZhiLiuChengTanChuJieMian||JieMianHao==QueDingChaRuLiuChengJieMian
							||JieMianHao==QueDingShanChuLiuChengJieMian)
						{ 
							//查看模式
							if(HmiProcessMode==0)
							{
								//当前流程步数大于0，并且界面序号为0时，设置序号为1，并更新显示内容
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
								
								//流程号变化时，更新界面
								if(HmiProcessNumFlag != HmiProcessNum)
								{
									HmiProcessNumFlag = HmiProcessNum;
									GetProcessData();
								}
								
								if(HmiProcessLast==1)//上一个
								{
									HmiProcessLast = 0;
									if(HmiProcessSerialNum>1)
										HmiProcessSerialNum--;
									else
										HmiProcessSerialNum = HmiStepNum;
								}
								else
									if(HmiProcessNext==2)//下一个
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
							//复制流程
							if(JieMianHao==FuZhiLiuChengTanChuJieMian)
							{
								while(JieMianHao==FuZhiLiuChengTanChuJieMian)
								{
									//被复制流程号为零时置1
									if(HmiProcessCopiedNum==0)
										HmiProcessCopiedNum=1;	
									//输入的被复制流程号变化时更新
									if(HmiProcessCopiedNumTemp!=HmiProcessCopiedNum)
										HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);
									if(HmiProcessCopiedNum>ProcessNum)
									{
										HmiProcessCopiedNum = 1;
									}
									//确定复制
									if(HmiProcessMode==1)
									{
										//读取被复制信息到当前
										GetProcessDataFrom(HmiProcessCopiedNum);
										//保存被复制信息
										SetProcessData();	
										
										//设置当前序号为1
										if(HmiStepNum!=0)
											HmiProcessSerialNum = 1;
									
										//退出复制模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							//添加流程
							if(HmiProcessMode==2)
							{
								//流程步数加一
								HmiStepNum++;
								//序号等于流程数
								HmiProcessSerialNum = HmiStepNum;
								
								//起始路径号默认为0则置1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==2)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//保存并更新数据
										SetProcessData();
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//流程步数减一
										HmiStepNum--;
										//序号等于流程数
										HmiProcessSerialNum = HmiStepNum;
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}
							
							//插入流程
							if(HmiProcessMode==3)
							{
								//流程步数加一
								HmiStepNum++;
								//序号为零时加一
								if(HmiProcessSerialNum==0)
									HmiProcessSerialNum = 1;
								
								//起始路径号默认为0则置1
								if(HmiProcessStartNum==0)
									HmiProcessStartNum = 1;
								
								ClearStepToHmi();
								
								while(HmiProcessMode==3)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										
										//保存并更新数据
										InsertProcessData();
										
										//退出插入模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;
										
										//流程步数减一
										HmiStepNum--;
										//序号为1时减一
										if(HmiProcessSerialNum==1)
											HmiProcessSerialNum = 0;
										
										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//更改流程
							if(HmiProcessMode==4)
							{
								while(HmiProcessMode==4)
								{
									switch(HmiProcessAction)
									{
										case 0://单次执行
											break;
										case 1://顺序执行到
											if(HmiProcessStopNum<=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==ProcessNum)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum+1;
											}
											break;
										case 2://倒序执行
											if(HmiProcessStopNum>=HmiProcessStartNum)
											{
												if(HmiProcessStartNum==1)
													HmiProcessStopNum=HmiProcessStartNum;
												else
													HmiProcessStopNum=HmiProcessStartNum-1;
											}
											break;
										case 3://循环执行
											if(HmiProcessStopNum==0)
											{
													HmiProcessStopNum=1;
											}
											break;
										default:break;
									}
									
									//确定
									if(HmiProcessEnter==1)
									{
										HmiProcessEnter = 0;
										//保存并更新数据
										SetProcessData();
										
										//退出更改模式
										HmiProcessMode = 0;
									}
									//取消
									else if(HmiProcessEnter==2) 
									{
										HmiProcessEnter = 0;

										//退出添加模式
										HmiProcessMode = 0;
									}
									osdelay_ms(10);
								}
							}									
							//删除流程
							if(HmiProcessMode==5)
							{
								DeleteProcessData();
								//退出删除模式
								HmiProcessMode = 0;
							}
							osdelay_ms(10);
						}
				}
			break;
			//取消任务
			case QuXiaoRenWuJieMian: 
			{		
				while(JieMianHao==QuXiaoRenWuJieMian)
				{
					if(QuXiaoRenWuQueDing==1)
					{
						QuXiaoRenWuQueDing = 0;
						
						HmiTask = 0;
						HmiTaskState = 0;
						//停车
						stopAsk = 1;
						dir = 0;
						//删除任务
						OSTaskDel((OS_TCB*)&Task5_TaskTCB,&err);
						//重新创建任务
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
					//如果路径号为零，则置一
					if(HmiProcessNum==0)
					{
						HmiProcessNum = 1;
					}
				}
			break;
			case LuJingSheZhiJieMian: 
				{		
					//如果路径号为零，则置一
					if(HmiRouteNum==0)
					{
						HmiRouteNum = 1;
					}
				}
			break;
			//执行路径
			case ZhiXingLuJingJieMian:
				{		
					while(JieMianHao==ZhiXingLuJingJieMian)
					{
						if(ZhiXingLuJingQueDing==1)
						{
							//保存路径号
							SetOneParameterToSystem(HmiRouteNum,6);
							HmiTask = 1;
							SystemParameter[8] = HmiTask;
							//保存任务号
							SetOneParameterToSystem(HmiTask,8);
							ZhiXingLuJingQueDing = 0;
							
							//自动界面显示信息重载
							HmiAutoReload();
						}
						osdelay_ms(10);
					}
				}
			break;
			//执行流程
			case ZhiXingLiuChengJieMian: 
			{		
				while(JieMianHao==ZhiXingLiuChengJieMian)
				{
					if(ZhiXingLiuChengQueDing==1)
					{
						//保存流程号
						SetOneParameterToSystem(HmiProcessNum,7);
						HmiTask = 2;
						SystemParameter[8] = HmiTask;
						//保存任务号
						SetOneParameterToSystem(HmiTask,8);
						ZhiXingLiuChengQueDing = 0;
						
						//任务状态为正在运行
						HmiTaskState = 5;
						
						//自动界面显示信息重载
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
//执行任务
void Task5_task(void *p_arg)
{	
	u16 i,j,k;
	p_arg = p_arg;

	while(1)
	{
		if(flag_szd == 0)
		{
			//执行路径
			if(HmiTask==1)
			{
				HmiStationSerialNum = 0;
				//根据所选路径，执行相应动作
				for(i=0;i<HmiStationNum;i++)
				{
					StationAction(i);
				}
			}
			else
				//执行流程
				if(HmiTask == 2)
				{
					HmiProcessSerialNum = 0;
					for(i=0;i<HmiStepNum;i++)
					{
						HmiProcessSerialNum++;
						switch(NowProcessInfor[i][1])
						{
							case 0://单次执行
								//更新路径号
								HmiRouteNum = NowProcessInfor[i][0];
							  //获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//根据所选路径，执行相应动作
								for(j=0;j<HmiStationNum;j++)
								{
									StationAction(j);
								}
								break;
							case 1://顺序执行
								for(k=NowProcessInfor[i][0];k<=NowProcessInfor[i][2];k++)
								{
									//更新路径号
									HmiRouteNum = k;
									//获取路径包含站点数
									GetRouteStationNum(HmiRouteNum);
									//获取当前路径信息
									GetRouteData(HmiRouteNum);
									
									HmiStationSerialNum = 0;
									//根据所选路径，执行相应动作
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 2://倒序执行
								for(k=NowProcessInfor[i][0];k>=NowProcessInfor[i][2];k--)
								{
									//更新路径号
									HmiRouteNum = k;
									//获取路径包含站点数
									GetRouteStationNum(HmiRouteNum);
									//获取当前路径信息
									GetRouteData(HmiRouteNum);
  
									HmiStationSerialNum = 0;
 									//根据所选路径，执行相应动作
									for(j=0;j<HmiStationNum;j++)
									{
										StationAction(j);
									}
								}
								break;
							case 3://循环执行
								//更新路径号
								HmiRouteNum = NowProcessInfor[i][0];
							  //获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);
								for(k=0;k<NowProcessInfor[i][2];k++)
								{
									HmiStationSerialNum = 0;
									//根据所选路径，执行相应动作
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
			LED3 = ~LED3;//运行灯
			num=0;
		}
		ld_juli = QianHouJuLi;//前后倒车雷达距离设置
		if(flag_szd==0)
		{
			if(Jhwai_switch&&(flag_qd==1))
			{				
				if(dir==0)//正方向
				{
					if(((QianZuoLeiDa<=ld_juli)||(QianYouLeiDa<=ld_juli))&&(Jhwai_flag == 0))
					{
						HmiTaskState = 2;
						Jhwai_flag = 1;
						MotoStop(5);
						speek("前方有障碍");
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
						speek("前方有障碍");
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
						speek("前方有障碍");
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
						speek("前方有障碍");
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
			if(QianJin==0)//前进
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
			if(HouTui==0)//后退
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
			if(ZuoYi==0)//左移
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
			if(YouYI==0)//右移
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
			if(ZuoXuan==0)//左旋
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
			if(YouXuan==0)//右旋
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
			if(ZuoShang==0)//左上
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
			if(ZuoXia==0)//左下
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
			if(YouShang==0)//右上
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
			if(YouXia==0)//右下
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
			IWDG_Feed();//喂狗
		}		
		osdelay_ms(10);   
	}
}

//启动
void DEMO1_task(void *p_arg)
{
	while(1)
	{
		if(startAsk)
		{
			if(HmiTask == 0)
			{
				JieMianHao = 21;
				speek("请选择需要执行的任务！");
				startAsk = 0;					
			}
			else
			{
				start();
				HmiTaskState = 5;
				HmiShouZiDongYinCang = 0;//隐藏启动显示停止
				startAsk = 0;						
			}
					
		}	
		delay(0,0,0,10);      
	}
}
//停止
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
			HmiShouZiDongYinCang = 1;//隐藏停止显示启动
			stopAsk = 0;
		}
		delay(0,0,0,5);      
	}
}

