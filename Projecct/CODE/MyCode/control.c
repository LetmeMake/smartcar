#include "fly_K60.h"
/*******************************************************************************
* �� �� �� * :	SteerControl
* �������� * :	ת�����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	������΢��
* �޸�ʱ�� * :	2016-3-28
*******************************************************************************/
void SteerControl(void)
{
	_INT16S_ angle = 0,kd = 0;
	_INT8U_ t = 0;
	
	/*
	ks = limit_B_C(ActualSpeed-60,0,60);	//�ٶ�Ӱ��60-120
    ks = limit_B_C(ks/4,0,15);
	
    p1 = (MyAbs(offset)-0)/200;				//���Ӱ��
    p1 = limit_B_C(p1,0,18);
    
    a1 = offset*AN_K1/500;
    a2 = MyAbs(offset/10)*(offset/10)*AN_K2/50000;
    a3 = (offset/10)*(offset/10)*(offset/10)/10000*AN_K3/1000;
    
    if(offset*CorrectOffset > 0) kd = CorrectOffset*(12+ks)/20;			//  ����
    else                         kd = CorrectOffset*(16+p1)/20;			//  ����
    
    angle = a1 + a2 + a3 + kd;
	*/
	
	kd = (offset * CorrectOffset > 0) ?
		CorrectOffset*(8  + MyAbs(offset)/300) / 20:		// ����
		CorrectOffset*(12 + MyAbs(offset)/300) / 20;		// ����
	
	t = BigArcFlag ? 4 : 0;		// ��Բ��
	
	angle = MyAbs(offset/10)*(offset/10)/(Steer_AN_KP-10*t) + offset*(Steer_AN_KD+t)/300 + kd;
	
	SteerAngle = limit(angle,_SteerDutyMax_);    // ����޷�
	
	ftm_pwm_duty(FTM2,FTM_CH1,_SteerCenter_ + SteerAngle);
}

/*******************************************************************************
* �� �� �� * :	SpeedControl
* �������� * :	�ٶȿ���
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	���������֡�΢��
* �޸�ʱ�� * :	2016-4-8
*******************************************************************************/
void SpeedControl(void)
{
	_INT8U_ s_kp = 0,s_ki = 0,s_kd = 0;			// P��I��D����
	_INT16S_ sk0 = 0,sk1 = 0,sk2 = 0,sk3 = 0;	// �����ٶȲ���
	_INT8U_ speed_position = 0;
	
	MinSpeed = MaxSpeed*65/100;								// ��С�ٶ�
	
	/*
	sk1 = limit_B_C(MyAbs(CorrectWhiteLength)*3/2,0,50);
	
    sk2 = limit_B_C(400 - sx,0,350);
    sk2 = (sk1/5)*(sk1/5)/60 + sk1/12;
    
    sk0 = limit_B_C(new_speed-90,0,50);		//�ٶ�Ӱ��
    sk0 = sk0*sk0/180;
    sk2 = sk2*(sk0+100)/100;
    
    sk0 = (LeftArea/LeftActive) > (RightArea/RightActive) ? (LeftArea/LeftActive) : (RightArea/RightActive);
    sk0 = limit_B_C(sk0-10,0,40);
    sk3 = sk0*sk0/15;
	*/
	
	sk0 = (_INT8U_)limit_B_C((ActualSpeed-MinSpeed),0,50);			// �ٶȲ���
	
	sk1 = MyAbs(SteerAngle) / (_SteerDutyMax_/70);			// ת�ǲ���
	sk2 = (_INT8U_)limit_B_C(350-WhiteLength,0,250)/5;						// ǰ�˲���
	sk3 = (_INT8U_)limit(MyAbs(CorrectOffset/10)*(20+sk0)/20,50);	// ������ٶ�
	
	speed_position = (_INT8U_)limit(sk1+sk2+sk3,_SpeedParameter_);		// ϵ���ϳ�,��ǰ����Ч��
	
	IdealSpeed = MaxSpeed - (MaxSpeed - MinSpeed) * speed_position / _SpeedParameter_;
	
	IdealSpeed = (_INT8U_)limit_B_C(IdealSpeed,MinSpeed,MaxSpeed);
	/*
	if(LeftCross || RightCross)              IdealSpeed =  IdealSpeed * 70  / 100;	// ʮ�ּ���
	//if((WhiteLength > 400) && !HillFlag)     IdealSpeed =  MaxSpeed * 120 / 100;	// ֱ������
	if(HillFlag)                             IdealSpeed =  IdealSpeed * 80  / 100;	// �µ�����
	if(LeftBarrierFlag||RightBarrierFlag)    IdealSpeed =  MaxSpeed * 80  / 100;	// �ϰ�����
	if(StartLineFlag)                        IdealSpeed =  MaxSpeed * 150 / 100;	// ����
	if(BigArcFlag)                           IdealSpeed =  MaxSpeed * 110 / 100;	// �󻡼���
	if(MoveTime % 4 == 0)                    IdealSpeed -= 1;						// ÿ4�����
	*/
	if(StopCarFlag) IdealSpeed = 0;		// ׼��ͣ��
	
	SpeedBias[0] = IdealSpeed - ActualSpeed;		// �ٶȵ�ǰƫ��
	
	if(StopCarFlag)			// ͣ��PID
	{
		s_kp =  Motor_AN_KP + MyAbs(ActualSpeed/3);
		s_ki =  Motor_AN_KI + MyAbs(ActualSpeed/4);
		s_kd =  Motor_AN_KD + MyAbs(ActualSpeed/5);
	}
	else if(SpeedBias[0] > 0)		// ����PID
	{
		s_kp = Motor_AN_KP;
		s_ki = Motor_AN_KI;
		s_kd = Motor_AN_KD;
	}
	else					//����PID
	{
		s_kp = 60;
		s_ki = 30;
		s_kd = 20;
	}
	
	Car_PWM += (
					s_kp * (SpeedBias[0] - SpeedBias[1])                +		// P ����
					s_ki *  SpeedBias[0]                                +		// I ����
					s_kd * (SpeedBias[0] - 2*SpeedBias[1] + SpeedBias[2])		// D ΢��
			   )/5;
	
	SpeedBias[2] = SpeedBias[1];		// �ٶ����ϴ�ƫ��
	SpeedBias[1] = SpeedBias[0];		// �ٶ��ϴ�ƫ��
	
	Car_PWM = limit_B_C(Car_PWM,_MotorDutyMin_,_MotorDutyMax_);		// ռ�ձ��޷�
	
	if(Car_PWM > 0)		// ��ת
	{
		ftm_pwm_duty(FTM1,FTM_CH0,0);
		ftm_pwm_duty(FTM1,FTM_CH1,Car_PWM);
	}
	else				// ��ת
	{
		ftm_pwm_duty(FTM1,FTM_CH0,-Car_PWM);
		ftm_pwm_duty(FTM1,FTM_CH1,0);
	}
}