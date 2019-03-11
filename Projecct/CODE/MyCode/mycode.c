#include "headfile.h"



uint8 dis_image[60][128];

uint8 Speed_L_New,Speed_R_New;
void Motor_Read(void)
{
		
		if(gpio_get(A3)==1)
		Speed_L_New = ctimer_count_read(TIMER0_COUNT1_A2); 
		else 
		Speed_L_New =		0;
		if(gpio_get(A5)==0)
	  Speed_R_New = ctimer_count_read(TIMER3_COUNT0_A4);
		else
		Speed_R_New =		0;
		//lcd_showfloat(20,1,Speed_L_New,10,0);
		ctimer_count_clean(TIMER0_COUNT1_A2);
    ctimer_count_clean(TIMER3_COUNT0_A4);
		uart_putchar(USART_0,Speed_L_New);
		//uart_putchar(USART_0,'/n');
}

void Motor_Init(void)
{
		ctimer_pwm_init(TIMER1_PWMCH0_A18, 8000, 0);//左后
		ctimer_pwm_init(TIMER1_PWMCH1_A20, 8000, 0);
		ctimer_pwm_init(TIMER2_PWMCH1_B4, 8000, 0);
		ctimer_pwm_init(TIMER2_PWMCH0_B5, 8000, 0);
}
void Motor_PWM(uint32_t frontleft,uint32_t backleft,uint32_t frontright,uint32_t backright)
{
		ctimer_pwm_duty(TIMER1_PWMCH0_A18, backleft);//左后
		ctimer_pwm_duty(TIMER1_PWMCH1_A20, frontleft);
		ctimer_pwm_duty(TIMER2_PWMCH1_B4, backright);
		ctimer_pwm_duty(TIMER2_PWMCH0_B5, frontright);
}
int32_t Motor_limit(int32_t PWM_out)
{
	if(PWM_out > 8000)
			PWM_out = 8000;
	if(PWM_out < -3000)
			PWM_out = -3000;
	return PWM_out;
}
int32_t PWM_out_R,PWM_out_L;
int target_value=10;
void Motor_PID_Control()
{
		uint32_t backleft ,frontleft,backright,frontright;
    backleft = frontleft = backright = frontright =0;
		
		PWM_out_R =PWM_out_R+PID_Inc(target_value,Speed_R_New,&MOTOR_PID);       //增量型PID需要三个差速
    PWM_out_L =PWM_out_L+PID_Inc(target_value,Speed_L_New,&MOTOR_PID);       //增量型PID需要三个差速
	  
		PWM_out_L= Motor_limit(PWM_out_L);
		PWM_out_R= Motor_limit(PWM_out_R);

		if(PWM_out_L > 0)
			frontleft = PWM_out_L;
		else
			backleft  -= PWM_out_L;

		if(PWM_out_R > 0)
			frontright = PWM_out_R;
		else
			backright  -= PWM_out_R;
		
		Motor_PWM(frontleft,backleft,frontright,backright);
}
int count=0;
int inc_time,dec_time;
int flag_1=1,flag_2=1;
int max,min;
//void PID_Change()
//{
//	//if()
//	MOTOR_PID.Kp-=0.1;
//}
void PID_Check()
{
		count++;
	if(count==400)
	{
		target_value = 70;
		count = 0;
		mrt_start(MRT_CH0);
		flag_1=0;
	}
	if(Speed_R_New==70&&flag_1==0)
	{
		inc_time=mrt_get_ms(MRT_CH0);
		min=max=70;
		flag_1=1;
	}
	if(count==200)
	{
		target_value = 20;
		mrt_start(MRT_CH0);
		flag_2=0;
	}
	if(Speed_R_New==20&&flag_2==0)
	{
		inc_time=mrt_get_ms(MRT_CH0);
		min=max=20;
		flag_2=1;
	}
	if(flag_1==1&&flag_2==1)
	{
		if(Speed_R_New<min) min=Speed_R_New;
		if(Speed_R_New>max) max=Speed_R_New;
	}
	
}

static uint16_t head=0xBB,end=0xEE;
void uart_write(int16_t valuea,int16_t valueb ,int16_t valuec,int16_t valued)
{

  
 /*           start       */
  uart_putchar(USART_0, head);
  
/*           1            */
  uart_putchar(USART_0,(uint8_t)(valuea>>8));
	
  uart_putchar(USART_0,(uint8_t)(valuea&0xff));
	
  
/*           2            */
  uart_putchar(USART_0,(uint8_t)(valueb>>8));
	
  uart_putchar(USART_0,(uint8_t)(valueb&0xff));
	
  
/*           3            */ 
  uart_putchar(USART_0,(uint8_t)(valuec>>8));
	
  uart_putchar(USART_0,(uint8_t)(valuec&0xff));
	
	
  
/*           4            */ 
  uart_putchar(USART_0,(uint8_t)(valued>>8));
	
  uart_putchar(USART_0,(uint8_t)(valued&0xff));

  
  
 /*           end           */
  uart_putchar(USART_0, end);
	
}

