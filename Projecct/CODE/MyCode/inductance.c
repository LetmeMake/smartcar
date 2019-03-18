#include "inductance.h"

int16_t left_min_A,right_min_A,left_max_A,right_max_A,left_min_B,right_min_B,left_max_B,right_max_B,middle_max,middle_min,Aim_speed;
int16_t	Left_a,Left_b,Right_a,Right_b,middle;

#define down 0
#define up 1

double inductance_right,inductance_left;
                               //a10 a31
/**
 * @brief  Inductance_Init
 * @retval void
 *note       电感初始化，开启A10和A31的AD转化
 *@param[in]	
*/
void Inductance_Init(void)
{
   adc_init(ADC_CH0_A10);
	 adc_init(ADC_CH5_A31);
}

/**
 * @brief  Inductance_Self_test
 * @retval void
 *note       得到左右电感AD幅值变化范围并算出归一值
 *@param[in]	
*/

void  Inductance_Read(int16_t* left_data,int16_t* right_data)
{ 
   *left_data  =   adc_convert(ADC_CH0_A10,ADC_12BIT);   	
   *right_data  =  adc_convert(ADC_CH5_A31,ADC_12BIT);																																
}

/**
 * @brief  Inductance_Self_test
 * @retval void
 *note       得到左右电感AD幅值变化范围并算出归一值
 *@param[in]	
*/
void  Inductance_Self_test()
{
	bool pass=1;
		
	while(pass)
	{
		Inductance_Read(&Left_a,&Right_a);
		left_max_A=MAX(Left_a,left_max_A)	;		
		left_min_A=MIN(Left_a,left_min_A)	;		
		right_max_A=MAX(Right_a,right_max_A)	;		
		right_min_A=MIN(Right_a,right_min_A)	;		
		
			Left_b=1000*(Left_b-left_min_B)/(left_max_B-left_min_B);															//归一化
			Right_b=1000*(Right_b-right_min_B)/(right_max_B-right_min_B);
			Left_a=1000*(Left_a-left_min_A)/(left_max_A-left_min_A);	
			Right_a=1000*(Right_a-right_min_A)/(right_max_A-right_min_A);
		
		if(gpio_get(B1)==down)																														//发车启动
		{	
			pass=0;
			systick_delay_ms(20);
			
		}		
	}
}





