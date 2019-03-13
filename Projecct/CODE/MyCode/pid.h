#ifndef _pid_h_
#define _pid_h_

	typedef struct
	{
	 float Kp;  											//比例系数Proportional
	 float Ki;  											//积分系数Integral
	 float Kd;  											//微分系数Derivative
	 
	 float Ek;  											//当前误差
	 float Ek1; 											//前一次误差 e(k-1)
	 float Ek2; 											//再前一次误差 e(k-2)
	}PID_IncTypeDef;


	typedef struct
	{
	 float Kp;												//比例系数Proportional
	 float Ki;												//积分系数Integral
	 float Kd;												//微分系数Derivative
	 
	 float Ek;												//当前误差
	 float Ek1;											//前一次误差 e(k-1)
	 float Ek2; 											//再前一次误差 e(k-2)
	 float LocSum; 									 //累计积分位置
	}PID_LocTypeDef;
extern PID_LocTypeDef ANGLE_PID;
extern PID_IncTypeDef MOTOR_PID_L;
extern PID_IncTypeDef MOTOR_PID_R;
	
	
float PID_Loc(float ErrorValue, PID_LocTypeDef *PID);
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID);
void PID_Change(void);
#endif
