#ifndef _pid_h_
#define _pid_h_

	typedef struct
	{
	 float Kp;  											//����ϵ��Proportional
	 float Ki;  											//����ϵ��Integral
	 float Kd;  											//΢��ϵ��Derivative
	 
	 float Ek;  											//��ǰ���
	 float Ek1; 											//ǰһ����� e(k-1)
	 float Ek2; 											//��ǰһ����� e(k-2)
	}PID_IncTypeDef;


	typedef struct
	{
	 float Kp;												//����ϵ��Proportional
	 float Ki;												//����ϵ��Integral
	 float Kd;												//΢��ϵ��Derivative
	 
	 float Ek;												//��ǰ���
	 float Ek1;											//ǰһ����� e(k-1)
	 float Ek2; 											//��ǰһ����� e(k-2)
	 float LocSum; 									 //�ۼƻ���λ��
	}PID_LocTypeDef;
extern PID_LocTypeDef ANGLE_PID;
extern PID_IncTypeDef MOTOR_PID_L;
extern PID_IncTypeDef MOTOR_PID_R;
	
	
float PID_Loc(float ErrorValue, PID_LocTypeDef *PID);
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID);
void PID_Change(void);
#endif
