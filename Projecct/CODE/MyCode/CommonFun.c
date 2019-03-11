#include "headfile.h"
/*******************************************************************************
* �� �� �� * :	Delay_1ms
* �������� * :	��ʱ����
* ��    �� * :	_INT32U_ cou
* ��    �� * :	��
* ˵    �� * :	����ֵ���4.29e9
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void Delay_1ms(_INT32U_ cou)
{
	while(cou--);
}

/*******************************************************************************
* �� �� �� * :	MyAbs
* �������� * :	�����ֵ����
* ��    �� * :	_INT16S_ value
* ��    �� * :	��
* ˵    �� * :	����һ������
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
_INT16U_ MyAbs(_INT16S_ value)
{
    return((value > 0) ? value : (-value));
}

/*******************************************************************************
* �� �� �� * :	limit
* �������� * :	��a�޷���-b��+b֮��
* ��    �� * :	_INT16S_ a,_INT16S_ b
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
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
* �� �� �� * :	limit_B_C
* �������� * :	��a�޷���b��c֮��
* ��    �� * :	_INT16S_ a,_INT16S_ b,_INT16S_ c
* ��    �� * :	��
* ˵    �� * :	b<c
* �޸�ʱ�� * :	2016-3-30
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
//* �� �� �� * :	GetSpeed
//* �������� * :	��õ�ǰС���ٶ�
//* ��    �� * :	��
//* ��    �� * :	��
//* ˵    �� * :	��
//* �޸�ʱ�� * :	2016-4-4
//*******************************************************************************/
//void GetSpeed(void)
//{
//	PulseAddCount = lptmr_pulse_get();		// ����ٶ�
//	
//	ActualSpeed = (!gpio_get(PTA17)) ? PulseAddCount : (-PulseAddCount);		// ȡ����
//	
//	lptmr_pulse_clean();					// �ۼ�������
//}

///*******************************************************************************
//* �� �� �� * :	TestTip
//* �������� * :	������ʾ
//* ��    �� * :	��
//* ��    �� * :	��
//* ˵    �� * :	��
//* �޸�ʱ�� * :	2016-5-5
//*******************************************************************************/
//void TestTip(void)
//{
//	switch (TestElement)
//	{
//		case _Cross_ :			// ��⵽ʮ����
//		{
//			if(LeftCross || RightCross)
//			{
//				gpio_set(PTE26, LOW);					// ����������
//				if(LeftCross)  gpio_set(PTD7, LOW);		// ���ָʾ����
//				else           gpio_set(PTD7,HIGH);		// ���ָʾ����
//				if(RightCross) gpio_set(PTD6, LOW);		// �Ҳ�ָʾ����
//				else           gpio_set(PTD6,HIGH);		// �Ҳ�ָʾ����
//			}
//			else
//			{
//				gpio_set(PTE26,HIGH);		// ֹͣ����
//				gpio_set( PTD7,HIGH);		// �Ҳ�ָʾ����
//				gpio_set( PTD6,HIGH);		// �Ҳ�ָʾ����
//			}
//		} break;
//			
//		case _Barrier_ :		// ��⵽�ϰ�
//		{
//			if(LeftBarrierFlag || RightBarrierFlag)
//			{
//				gpio_set(PTE26, LOW);							// ����������
//				if(LeftBarrierFlag)  gpio_set(PTD7, LOW);		// ���ָʾ����
//				else                 gpio_set(PTD7,HIGH);		// ���ָʾ����
//				if(RightBarrierFlag) gpio_set(PTD6, LOW);		// �Ҳ�ָʾ����
//				else                 gpio_set(PTD6,HIGH);		// �Ҳ�ָʾ����
//			}
//			else
//			{
//				gpio_set(PTE26,HIGH);		// ֹͣ����
//				gpio_set( PTD7,HIGH);		// �Ҳ�ָʾ����
//				gpio_set( PTD6,HIGH);		// �Ҳ�ָʾ����
//			}
//		} break;
//			
//		case _Hill_ :			// ��⵽�µ�
//		{
//			if(HillFlag) gpio_set(PTE26, LOW);				// ����������
//			else         gpio_set(PTE26,HIGH);				// ֹͣ����
//		} break;
//			
//		case _StartLine_ :		// ��⵽������
//		{
//			if(StartLineFlag) gpio_set(PTE26, LOW);			// ����������
//			else              gpio_set(PTE26,HIGH);			// ֹͣ����
//		} break;
//		default : break;
//	}
//}

///*******************************************************************************
//* �� �� �� * :	keyscan
//* �������� * :	����ɨ��
//* ��    �� * :	��
//* ��    �� * :	��
//* ˵    �� * :	������������������������ʱ����
//* �޸�ʱ�� * :	2016-3-12
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
//	if((key[1] == _Effective_) || (key[2] == _Effective_) || (key[3] == _Effective_))			// ������������
//	{
//		if((MyAbs(BasicTime - LockTime) >= 50) && (MyAbs(BasicTime - LockTime) < 150))		// �����ͷ�
//		{
//			key[1] = _Void_;
//			key[2] = _Void_;
//			key[3] = _Void_;
//		}
//	}
//	
//	
//	
//	if((key[0] == _Void_) && (gpio_get(_StartKey_) == 0))		// һ������,����
//	{
//		if(StartKey == 0)
//			StartKey = BasicTime;
//		
//		if(
//				(MyAbs(BasicTime - StartKey)    >=   2) &&		// ɨ��ʱ�����
//				(MyAbs(StartKey  - BasicTime)   <= 198) &&
//				(gpio_get(_StartKey_) == 0)
//		  )
//		{
//			disable_irq(PIT0_IRQn);				// ��ֹ����ȶ���,��ֹ5ms�ж�
//			key[0]      = _Effective_;					// ������״̬����
//			StartKey    = 0;
//			StopCarFlag = 0;
//		}
//	}
//	
//	
//	
//	if(gpio_get(_ModelKey_) == 0)		// ģʽ�ж�
//	{
//		if(ModelKey == 0)
//			ModelKey = BasicTime;
//		
//		if(
//				(key[1] == _Void_)                && 
//				(
//					((MyAbs(BasicTime-ModelKey)>=2) && (MyAbs(ModelKey-BasicTime)<=198)) ||		// ɨ��ʱ�����
//					(gpio_get(_button1_) && key[0])			// ģʽ����
//				)                            &&
//				(gpio_get(_ModelKey_) == 0)
//		  )
//		{
//			model++;
//			ModelKey = 0;
//			if(model > 4) model = 0;
//			key[1]   = _Effective_;			// ��������
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	if((key[0] == 0) && (gpio_get(_AddKey_) == 0))			// �ۼӼ�
//	{
//		if(AddKey == 0)
//			AddKey = BasicTime;
//		
//		if(
//				(key[2] == _Void_)           &&
//				(
//					((MyAbs(BasicTime-AddKey)>=2) && (MyAbs(AddKey-BasicTime)<=198)) ||		// ɨ��ʱ�����
//					(gpio_get(_button1_) && key[0])			// ģʽ����
//				)                       &&
//				(gpio_get(_AddKey_) == 0)
//		  )
//		{
//			AddKey = 0;
//			switch(model)		// ��ǰ����ģʽ�ж�
//			{
//				case 0:TestElement += 1;
//				if(TestElement > _StartLine_) TestElement = _StartLine_;break;		// ���Ԫ��
//				
//				case 1:MaxSpeed    += 3;
//				if(MaxSpeed > 200) MaxSpeed=200;break;					// ����ٶȿ���
//				
//				case 2:TimeStopCar += 1;
//				if(TimeStopCar > 60) TimeStopCar = 60;break;		// ����ʱ������
//				
//				case 3:Steer_AN_KP += 3;
//				if(Steer_AN_KP > 800) Steer_AN_KP = 800;break;		// �������
//				case 4:Steer_AN_KD += 1;
//				if(Steer_AN_KD > 80) Steer_AN_KD = 80;break;
//				
//				/*
//				case 4:Motor_AN_KP += 1;
//				if(Motor_AN_KP > 70) Motor_AN_KP = 70;break;			// ���PID���Ʋ���
//				case 5:Motor_AN_KI += 1;
//				if(Motor_AN_KI > 50) Motor_AN_KI = 50;break;
//				case 6:Motor_AN_KD += 1;
//				if(Motor_AN_KD > 50) Motor_AN_KD = 50;break;
//				*/
//				default: break;
//			}
//			key[2]   = _Effective_;			// ��������
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	if((key[0] == 0) && (gpio_get(_SubbKey_) == 0))			// �ݼ���
//	{
//		if(SubbKey == 0)
//			SubbKey = BasicTime;
//		
//		if(
//				(key[3] == _Void_)            &&
//				(
//					((MyAbs(BasicTime-SubbKey)>=2) && (MyAbs(SubbKey-BasicTime)<=198)) ||		// ɨ��ʱ�����
//					(gpio_get(_button1_) && key[0])			// ģʽ����
//				)                        &&
//				(gpio_get(_SubbKey_) == 0)
//		  )
//		{
//			SubbKey = 0;
//			switch(model)			// ��ǰ����ģʽ�ж�
//			{
//				case 0:TestElement -= 1;
//				if(TestElement < _Cross_) TestElement = _Cross_;break;		// ���Ԫ��
//				
//				case 1:MaxSpeed    -= 2;
//				if(MaxSpeed < 50) MaxSpeed = 50;break;					// ����ٶȿ���
//				
//				case 2:TimeStopCar -= 1;
//				if(TimeStopCar < 1) TimeStopCar = 1;break;			// ����ʱ������
//				
//				case 3:Steer_AN_KP -= 2;
//				if(Steer_AN_KP < 50) Steer_AN_KP = 50;break;		// �������
//				case 4:Steer_AN_KD -= 1;
//				if(Steer_AN_KD < 1) Steer_AN_KD = 1;break;
//				
//				/*
//				case 4:Motor_AN_KP -= 1;
//				if(Motor_AN_KP < 1) Motor_AN_KP = 1;break;			// ���PID���Ʋ���
//				case 5:Motor_AN_KI -= 1;
//				if(Motor_AN_KI < 1) Motor_AN_KI = 1;break;
//				case 6:Motor_AN_KD -= 1;
//				if(Motor_AN_KD < 1) Motor_AN_KD = 1;break;
//				*/
//				default: break;
//			}
//			key[3]   = _Effective_;			// ��������
//			LockTime = BasicTime;
//		}
//	}
//	
//	
//	
//	/*
//	for(;;)				// �������ּ��
//	{
//		if(
//				//!StopCarFlag             ||		// �������������ּ��
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
//* �� �� �� * :	DispalyData
//* �������� * :	��ʾ��Ϣ
//* ��    �� * :	��
//* ��    �� * :	��
//* ˵    �� * :	��
//* �޸�ʱ�� * :	2016-3-12
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
