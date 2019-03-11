#include "headfile.h"
#include "pid.h"
//5.17/2.42
//6.5/3		赛场上调整
//5/4.12	转弯后会不到中线
//5.5/4.12		
PID_LocTypeDef ANGLE_PID = {7.5,0,0,0,0,0,0};

PID_IncTypeDef MOTOR_PID = {40,0,4,0,0,0} ;
/************************************************
函数名称 ： PI_Inc
功    能 ： PI增量(Increment)计算
参    数 ： SetValue ------ 设置值(期望值)
						ActualValue --- 实际值(反馈值)
					  PID ----------- PID数据结构
返 回 值 ： PIDInc -------- 本次PID增量(+/-)
作		者 ： strongerHuang
*************************************************/
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID)
{
 float PIDInc; //增量
 
 PID->Ek = SetValue - ActualValue;
PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1) + (PID->Kd * PID->Ek2);
 //PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1);			//仅保留PI计算

 PID->Ek2 = PID->Ek1;
 PID->Ek1 = PID->Ek; 
	return PIDInc;
}

/************************************************
函数名称 ： PD_Loc
功		能 ： PD位置(Location)计算
参	  数 ： SetValue ------ 设置值(期望值)
						ActualValue --- 实际值(反馈值)
						PID ----------- PID数据结构
返 回 值 ： PIDLoc -------- PID位置
作		者 ： strongerHuang
*************************************************/
float PID_Loc(float ErrorValue, PID_LocTypeDef *PID)
{
  float PIDLoc; 																	//位置
 
  PID->Ek = ErrorValue;
//  PID->LocSum += PID->Ek;													//累计误差
//  PIDLoc = PID->Kp * PID->Ek + (PID->Ki * PID->LocSum) + PID->Kd * (PID->Ek1 - PID->Ek);

	PIDLoc = PID->Kp * PID->Ek + PID->Kd * (PID->Ek1 - PID->Ek);		//只保留PD计算
	
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

