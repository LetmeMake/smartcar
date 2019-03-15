/*********************************************************************************************************************

 * Copyright (c) 2018,逐飞科技

 * @file       		bluetooth
 * @author     		jinkai
 * @version    		V1.0
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @date       		2019-03-14
 ********************************************************************************************************************/

#include "headfile.h"			//添加到主头文件中

char ParameterFlag_1,ParameterFlag_2,ParameterFlag_3,Parameter_num;

void ParameterFlag_init(void)
{
	ParameterFlag_1=_PID_void_;
	ParameterFlag_2=_PID_void_;
	ParameterFlag_3=_PID_void_;
}
void ParameterFlag_3_effective(void)
{
	if(ParameterFlag_2==_PID_up_)
	{
		if(ParameterFlag_1==_PID_P_)	
			Steer_AN_KP+=Parameter_num;
		else if(ParameterFlag_1==_PID_I_)
			target_value+=Parameter_num;
		else if(ParameterFlag_1==_PID_D_)
			Steer_AN_KD+=Parameter_num;
		}
	else if(ParameterFlag_2==_PID_down_)
	{
			if(ParameterFlag_1==_PID_P_)	
			Steer_AN_KP-=Parameter_num;
		else if(ParameterFlag_1==_PID_I_)
			target_value-=Parameter_num;
		else if(ParameterFlag_1==_PID_D_)
			Steer_AN_KD-=Parameter_num;
	}
	ParameterFlag_init();
	printf("debug OK P=%d,D=%d,target=%d\r\n",Steer_AN_KP,Steer_AN_KD,target_value);
}
void ParameterFlag_3_void(char receive)
{
	char i;
	char n;
	if(receive>='1'&&receive<='9')
	{
		ParameterFlag_3=_PID_effective_;
		for(i='1',n=1;i!=receive;i++)
		{
		n++;
			if(n>11) break;
		}
		Parameter_num=n;
	}
	else
		ParameterFlag_init();
	
}
void ParameterFlag_2_effective(char receive)
{
	if(ParameterFlag_3!=_PID_void_)
		ParameterFlag_3_effective();
	else
		ParameterFlag_3_void(receive);
}
void ParameterFlag_2_void(char receive)
{
	if(receive=='+')			ParameterFlag_2=_PID_up_;
	else if(receive=='-')	ParameterFlag_2=_PID_down_;
	else ParameterFlag_init();
}
void ParameterFlag_1_effective(char receive)
{
	if(ParameterFlag_2!=_PID_void_)
		ParameterFlag_2_effective(receive);
	else
		ParameterFlag_2_void(receive);
}

void ParameterFlag_1_void(char receive)
{
	if(receive=='p')			ParameterFlag_1=_PID_P_;
	else if(receive=='i')	ParameterFlag_1=_PID_I_;
	else if(receive=='d')	ParameterFlag_1=_PID_D_;
	else ParameterFlag_init();
}

void Parameter_Adjust(char receive)
{
	if(ParameterFlag_1!=_PID_void_)
	{
		ParameterFlag_1_effective(receive);
	}
	else
		ParameterFlag_1_void(receive);
}

