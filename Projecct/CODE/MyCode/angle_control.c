#include "headfile.h"

double mid_value=0;
double last_mid_value=0;
double Dir_out;
void Steering_Engine_Init(void)
{
    ctimer_pwm_init(TIMER4_PWMCH0_A6, 50, 780);
}

void Direct_control()
{			

//	Dir_out =Dir_middle-0.0558*Dir_gap-0.002*(Dir_gap-Dir_oldGap);    //pd
	
//	mid_value = -middle_value;
	
	/*方向PD控制*/
	Dir_out = (int)PID_Loc(-middle_value, &ANGLE_PID) + 780;
//	printf("mid_value ： %f  direction_value ： %d\n",mid_value,direction_value);
//	last_mid_value = middle_value;	 
	

	//设定阀值
	if(Dir_out>=Dir_max)				Dir_out=Dir_max;							
	if(Dir_out<=Dir_min)				Dir_out=Dir_min;	
	ctimer_pwm_duty(TIMER4_PWMCH0_A6, Dir_out); /* 0-10000 对应 0-100% */
//	Dir_oldOut=Dir_out;//保留上次占空比
}
