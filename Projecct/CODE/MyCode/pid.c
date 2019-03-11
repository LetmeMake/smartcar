#include "headfile.h"
#include "pid.h"
//5.17/2.42
//6.5/3		�����ϵ���
//5/4.12	ת���᲻������
//5.5/4.12		
PID_LocTypeDef ANGLE_PID = {7.5,0,0,0,0,0,0};

PID_IncTypeDef MOTOR_PID = {40,0,4,0,0,0} ;
/************************************************
�������� �� PI_Inc
��    �� �� PI����(Increment)����
��    �� �� SetValue ------ ����ֵ(����ֵ)
						ActualValue --- ʵ��ֵ(����ֵ)
					  PID ----------- PID���ݽṹ
�� �� ֵ �� PIDInc -------- ����PID����(+/-)
��		�� �� strongerHuang
*************************************************/
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID)
{
 float PIDInc; //����
 
 PID->Ek = SetValue - ActualValue;
PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1) + (PID->Kd * PID->Ek2);
 //PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1);			//������PI����

 PID->Ek2 = PID->Ek1;
 PID->Ek1 = PID->Ek; 
	return PIDInc;
}

/************************************************
�������� �� PD_Loc
��		�� �� PDλ��(Location)����
��	  �� �� SetValue ------ ����ֵ(����ֵ)
						ActualValue --- ʵ��ֵ(����ֵ)
						PID ----------- PID���ݽṹ
�� �� ֵ �� PIDLoc -------- PIDλ��
��		�� �� strongerHuang
*************************************************/
float PID_Loc(float ErrorValue, PID_LocTypeDef *PID)
{
  float PIDLoc; 																	//λ��
 
  PID->Ek = ErrorValue;
//  PID->LocSum += PID->Ek;													//�ۼ����
//  PIDLoc = PID->Kp * PID->Ek + (PID->Ki * PID->LocSum) + PID->Kd * (PID->Ek1 - PID->Ek);

	PIDLoc = PID->Kp * PID->Ek + PID->Kd * (PID->Ek1 - PID->Ek);		//ֻ����PD����
	
  PID->Ek1 = PID->Ek; 
	return PIDLoc;
}
void PID_Change(void)
{
		if(gpio_get(B2)==0)
			ANGLE_PID.Kp+=0.001f;
		if(gpio_get(B3)==0)
			ANGLE_PID.Kp-=0.001f;
		if(gpio_get(B23)==0)
			ANGLE_PID.Kd+=0.001f;
		if(gpio_get(B1)==0)
			ANGLE_PID.Kd-=0.001f;
		//lcd_showfloat(10,10,ANGLE_PID.Kp,2,3);
		//lcd_showfloat(40,10,ANGLE_PID.Kd,2,3);
}

