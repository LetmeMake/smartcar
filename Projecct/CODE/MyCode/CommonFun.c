#include "headfile.h"
/*******************************************************************************
* 函 数 名 * :	Delay_1ms
* 函数功能 * :	延时函数
* 输    入 * :	_INT32U_ cou
* 输    出 * :	无
* 说    明 * :	输入值最大4.29e9
* 修改时间 * :	2016-3-30
*******************************************************************************/
void Delay_1ms(_INT32U_ cou)
{
	while(cou--);
}

/*******************************************************************************
* 函 数 名 * :	MyAbs
* 函数功能 * :	求绝对值函数
* 输    入 * :	_INT16S_ value
* 输    出 * :	无
* 说    明 * :	返回一个正数
* 修改时间 * :	2016-3-30
*******************************************************************************/
_INT16U_ MyAbs(_INT16S_ value)
{
    return((value > 0) ? value : (-value));
}

/*******************************************************************************
* 函 数 名 * :	limit
* 函数功能 * :	将a限幅到-b到+b之间
* 输    入 * :	_INT16S_ a,_INT16S_ b
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
_INT16S_ limit1(_INT16S_ a,_INT16S_ b)
{
    if(a > b)
		return b;
    else if(a < (-b))
		return (-b);
	else
		return a;
}

/*******************************************************************************
* 函 数 名 * :	limit_B_C
* 函数功能 * :	将a限幅到b到c之间
* 输    入 * :	_INT16S_ a,_INT16S_ b,_INT16S_ c
* 输    出 * :	无
* 说    明 * :	b<c
* 修改时间 * :	2016-3-30
*******************************************************************************/
_INT16S_ limit_B_C(_INT16S_ a,_INT16S_ b,_INT16S_ c)
{
	if(a < b)
		return b;
	else if(a > c)
		return c;
	else
		return a;
}

///*******************************************************************************
//* 函 数 名 * :	GetSpeed
//* 函数功能 * :	获得当前小车速度
//* 输    入 * :	无
//* 输    出 * :	无
//* 说    明 * :	无
//* 修改时间 * :	2016-4-4
//*******************************************************************************/
//void GetSpeed(void)
//{
//	PulseAddCount = lptmr_pulse_get();		// 获得速度
//	
//	ActualSpeed = (!gpio_get(PTA17)) ? PulseAddCount : (-PulseAddCount);		// 取方向
//	
//	lptmr_pulse_clean();					// 累加器清零
//}

///*******************************************************************************
//* 函 数 名 * :	TestTip
//* 函数功能 * :	测试提示
//* 输    入 * :	无
//* 输    出 * :	无
//* 说    明 * :	无
//* 修改时间 * :	2016-5-5
//*******************************************************************************/
//void TestTip(void)
//{
//	switch (TestElement)
//	{
//		case _Cross_ :			// 检测到十字弯
//		{
//			if(LeftCross || RightCross)
//			{
//				gpio_set(PTE26, LOW);					// 蜂鸣器发声
//				if(LeftCross)  gpio_set(PTD7, LOW);		// 左侧指示灯亮
//				else           gpio_set(PTD7,HIGH);		// 左侧指示灯灭
//				if(RightCross) gpio_set(PTD6, LOW);		// 右侧指示灯亮
//				else           gpio_set(PTD6,HIGH);		// 右侧指示灯灭
//			}
//			else
//			{
//				gpio_set(PTE26,HIGH);		// 停止发声
//				gpio_set( PTD7,HIGH);		// 右侧指示灯灭
//				gpio_set( PTD6,HIGH);		// 右侧指示灯灭
//			}
//		} break;
//			
//		case _Barrier_ :		// 检测到障碍
//		{
//			if(LeftBarrierFlag || RightBarrierFlag)
//			{
//				gpio_set(PTE26, LOW);							// 蜂鸣器发声
//				if(LeftBarrierFlag)  gpio_set(PTD7, LOW);		// 左侧指示灯亮
//				else                 gpio_set(PTD7,HIGH);		// 左侧指示灯灭
//				if(RightBarrierFlag) gpio_set(PTD6, LOW);		// 右侧指示灯亮
//				else                 gpio_set(PTD6,HIGH);		// 右侧指示灯灭
//			}
//			else
//			{
//				gpio_set(PTE26,HIGH);		// 停止发声
//				gpio_set( PTD7,HIGH);		// 右侧指示灯灭
//				gpio_set( PTD6,HIGH);		// 右侧指示灯灭
//			}
//		} break;
//			
//		case _Hill_ :			// 检测到坡道
//		{
//			if(HillFlag) gpio_set(PTE26, LOW);				// 蜂鸣器发声
//			else         gpio_set(PTE26,HIGH);				// 停止发声
//		} break;
//			
//		case _StartLine_ :		// 检测到起跑线
//		{
//			if(StartLineFlag) gpio_set(PTE26, LOW);			// 蜂鸣器发声
//			else              gpio_set(PTE26,HIGH);			// 停止发声
//		} break;
//		default : break;
//	}
//}

///*******************************************************************************
//* 函 数 名 * :	keyscan
//* 函数功能 * :	键盘扫描
//* 输    入 * :	无
//* 输    出 * :	无
//* 说    明 * :	利用主函数中其它函数做延时消抖
//* 修改时间 * :	2016-3-12
//*******************************************************************************/
//void keyscan(void)
//{
//	/*
//	test_16s[0] = gpio_get(_StartKey_);
//	test_16s[1] = gpio_get(_AddKey_);
//	test_16s[2] = gpio_get(_SubbKey_);
//	test_16s[3] = gpio_get(_ModelKey_);
//	*/
//	static _INT8U_ StartKey = 0,ModelKey = 0,AddKey = 0,SubbKey = 0,LockTime = 0;
//	
//	if((key[1] == _Effective_) || (key[2] == _Effective_) || (key[3] == _Effective_))			// 按键解锁控制
//	{
//		if((MyAbs(BasicTime - LockTime) >= 50) && (MyAbs(BasicTime - LockTime) < 150))		// 按键释放
//		{
//			key[1] = _Void_;
//			key[2] = _Void_;
//			key[3] = _Void_;
//		}
//	}
//	
//	
//	
//	if((key[0] == _Void_) && (gpio_get(_StartKey_) == 0))		// 一键发车,加锁
//	{
//		if(StartKey == 0)
//			StartKey = BasicTime;
//		
//		if(
//				(MyAbs(BasicTime - StartKey)    >=   2) &&		// 扫描时间管理
//				(MyAbs(StartKey  - BasicTime)   <= 198) &&
//				(gpio_get(_StartKey_) == 0)
//		  )
//		{
//			disable_irq(PIT0_IRQn);				// 防止电机先动作,禁止5ms中断
//			key[0]      = _Effective_;					// 发车键状态保持
//			StartKey    = 0;
//			StopCarFlag = 0;
//		}
//	}
//	
//	
//	
//	if(gpio_get(_ModelKey_) == 0)		// 模式判断
//	{
//		if(ModelKey == 0)
//			ModelKey = BasicTime;
//		
//		if(
//				(key[1] == _Void_)                && 
//				(
//					((MyAbs(BasicTime-ModelKey)>=2) && (MyAbs(ModelKey-BasicTime)<=198)) ||		// 扫描时间管理
//					(gpio_get(_button1_) && key[0])			// 模式管理
//				)                            &&
//				(gpio_get(_ModelKey_) == 0)
//		  )
//		{
//			model++;
//			ModelKey = 0;
//			if(model > 4) model = 0;
//			key[1]   = _Effective_;			// 按键上锁
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	if((key[0] == 0) && (gpio_get(_AddKey_) == 0))			// 累加键
//	{
//		if(AddKey == 0)
//			AddKey = BasicTime;
//		
//		if(
//				(key[2] == _Void_)           &&
//				(
//					((MyAbs(BasicTime-AddKey)>=2) && (MyAbs(AddKey-BasicTime)<=198)) ||		// 扫描时间管理
//					(gpio_get(_button1_) && key[0])			// 模式管理
//				)                       &&
//				(gpio_get(_AddKey_) == 0)
//		  )
//		{
//			AddKey = 0;
//			switch(model)		// 当前运行模式判断
//			{
//				case 0:TestElement += 1;
//				if(TestElement > _StartLine_) TestElement = _StartLine_;break;		// 检测元素
//				
//				case 1:MaxSpeed    += 3;
//				if(MaxSpeed > 200) MaxSpeed=200;break;					// 最大速度控制
//				
//				case 2:TimeStopCar += 1;
//				if(TimeStopCar > 60) TimeStopCar = 60;break;		// 启动时间限制
//				
//				case 3:Steer_AN_KP += 3;
//				if(Steer_AN_KP > 800) Steer_AN_KP = 800;break;		// 舵机参数
//				case 4:Steer_AN_KD += 1;
//				if(Steer_AN_KD > 80) Steer_AN_KD = 80;break;
//				
//				/*
//				case 4:Motor_AN_KP += 1;
//				if(Motor_AN_KP > 70) Motor_AN_KP = 70;break;			// 电机PID控制参数
//				case 5:Motor_AN_KI += 1;
//				if(Motor_AN_KI > 50) Motor_AN_KI = 50;break;
//				case 6:Motor_AN_KD += 1;
//				if(Motor_AN_KD > 50) Motor_AN_KD = 50;break;
//				*/
//				default: break;
//			}
//			key[2]   = _Effective_;			// 按键上锁
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	if((key[0] == 0) && (gpio_get(_SubbKey_) == 0))			// 递减键
//	{
//		if(SubbKey == 0)
//			SubbKey = BasicTime;
//		
//		if(
//				(key[3] == _Void_)            &&
//				(
//					((MyAbs(BasicTime-SubbKey)>=2) && (MyAbs(SubbKey-BasicTime)<=198)) ||		// 扫描时间管理
//					(gpio_get(_button1_) && key[0])			// 模式管理
//				)                        &&
//				(gpio_get(_SubbKey_) == 0)
//		  )
//		{
//			SubbKey = 0;
//			switch(model)			// 当前运行模式判断
//			{
//				case 0:TestElement -= 1;
//				if(TestElement < _Cross_) TestElement = _Cross_;break;		// 检测元素
//				
//				case 1:MaxSpeed    -= 2;
//				if(MaxSpeed < 50) MaxSpeed = 50;break;					// 最大速度控制
//				
//				case 2:TimeStopCar -= 1;
//				if(TimeStopCar < 1) TimeStopCar = 1;break;			// 启动时间限制
//				
//				case 3:Steer_AN_KP -= 2;
//				if(Steer_AN_KP < 50) Steer_AN_KP = 50;break;		// 舵机参数
//				case 4:Steer_AN_KD -= 1;
//				if(Steer_AN_KD < 1) Steer_AN_KD = 1;break;
//				
//				/*
//				case 4:Motor_AN_KP -= 1;
//				if(Motor_AN_KP < 1) Motor_AN_KP = 1;break;			// 电机PID控制参数
//				case 5:Motor_AN_KI -= 1;
//				if(Motor_AN_KI < 1) Motor_AN_KI = 1;break;
//				case 6:Motor_AN_KD -= 1;
//				if(Motor_AN_KD < 1) Motor_AN_KD = 1;break;
//				*/
//				default: break;
//			}
//			key[3]   = _Effective_;			// 按键上锁
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	/*
//	for(;;)				// 按键松手检测
//	{
//		if(
//				//!StopCarFlag             ||		// 发车后不在做松手检测
//				(
//					gpio_get(_StartKey_) &&
//					gpio_get(_AddKey_)   &&
//					gpio_get(_SubbKey_)  &&
//					gpio_get(_ModelKey_)
//				)
//		  ) break;
//	}
//	*/
//}

///*******************************************************************************
//* 函 数 名 * :	DispalyData
//* 函数功能 * :	显示信息
//* 输    入 * :	无
//* 输    出 * :	无
//* 说    明 * :	无
//* 修改时间 * :	2016-3-12
//*******************************************************************************/
//void DispalyData(void)
//{
//	switch(model)
//	{
//		case 0:
//			OLED_WrStr(1,2,"->  Speed Control  <-");
//			OLED_WrStr(0,3,"Max:");
//			OLED_Out_SP(24,3,3);
//			OLED_PutNum(24,3,MaxSpeed);
//			
//			OLED_Out_SP(24,4,3);
//			OLED_PutNum(24,4,MaxSpeed);
//			break;
//		case 1:
//			OLED_WrStr(1,2,"->  Auto Stop Car  <-");
//			OLED_WrStr(0,3,"Time:");
//			OLED_Out_SP(30,3,3);
//			OLED_PutNum(30,3,TimeStopCar);
//			
//			OLED_Out_SP(94,4,3);
//			OLED_PutNum(94,4,TimeStopCar);
//			break;
//		case 2:
//			OLED_WrStr(1,2,"->  Steer Control  <-");
//			OLED_WrStr(0,3,"AN_KP:");
//			OLED_Out_SP(36,3,4);
//			OLED_PutNum(36,3,Steer_AN_KP);
//			
//			OLED_Out_SP(72,5,4);
//			OLED_PutNum(72,5,Steer_AN_KP);
//			break;
//		case 3:
//			OLED_WrStr(1,2,"->  Steer Control  <-");
//			OLED_WrStr(0,3,"AN_KD:");
//			OLED_Out_SP(36,3,3);
//			OLED_PutNum(36,3,Steer_AN_KD);
//			
//			OLED_Out_SP(72,6,3);
//			OLED_PutNum(72,6,Steer_AN_KD);
//			break;
//			
//		case 4:
//			OLED_WrStr(1,2,"->  Motor Control  <-");
//			OLED_WrStr(0,3,"AN_KP:");
//			OLED_Out_SP(36,3,3);
//			OLED_PutNum(36,3,Motor_AN_KP);
//			
//			OLED_Out_SP(48,7,3);
//			OLED_PutNum(48,7,Motor_AN_KP);
//			break;
//		case 5:
//			OLED_WrStr(1,2,"->  Motor Control  <-");
//			OLED_WrStr(0,3,"AN_KI:");
//			OLED_Out_SP(36,3,3);
//			OLED_PutNum(36,3,Motor_AN_KI);
//			
//			OLED_Out_SP(66,7,3);
//			OLED_PutNum(66,7,Motor_AN_KI);
//			break;
//		case 6:
//			OLED_WrStr(1,2,"->  Motor Control  <-");
//			OLED_WrStr(0,3,"AN_KD:");
//			OLED_Out_SP(36,3,3);
//			OLED_PutNum(36,3,Motor_AN_KD);
//			
//			OLED_Out_SP(84,7,3);
//			OLED_PutNum(84,7,Motor_AN_KD);
//			break;
//			
//		default:break;
//	}
//}
