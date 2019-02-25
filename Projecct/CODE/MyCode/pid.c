#include "headfile.h"
#include "pid.h"

PID_LocTypeDef ANGLE_PID = {5.17,0,2.42,0,0,0,0};
PID_IncTypeDef MOTOR_PID = {15,12,0,0,0,0} ;
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
//PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1) + (PID->Kd * PID->Ek2);
 PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1);			//������PI����

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

