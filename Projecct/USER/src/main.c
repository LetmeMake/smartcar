/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本


//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

#include "headfile.h"


//int target_value=30;
int main(void)
{   
    get_clk();


		//电机
		Motor_Init();
		//舵机
		ctimer_pwm_init(TIMER4_PWMCH0_A6, 50, 780);
		//光电编码器计数
		ctimer_count_init(TIMER0_COUNT1_A2);
		gpio_init(A3,GPI, 1, PULLUP);
		ctimer_count_init(TIMER3_COUNT0_A4);	
		gpio_init(A5,GPI, 1, PULLUP);
		
	  lcd_init();
	  camera_init();
    uart_init(USART_0,115200,UART0_TX_A25,UART0_RX_A24);
	  	//按键
		gpio_init(B1,GPI, 1, PULLUP);
		gpio_init(B2,GPI, 1, PULLUP);
		gpio_init(B3,GPI, 1, PULLUP);
		gpio_init(B23,GPI, 1, PULLUP);
		gpio_init(B17,GPI, 1, PULLUP);
		gpio_init(B22,GPI, 1, PULLUP);
		pit_init_ms(5);
    EnableInterrupts;
    while(1)
    {
				if(mt9v032_finish_flag)
				{			
				//lcd_displayimage032(*image,MT9V032_W,MT9V032_H,Middle_line,Left_Blackline,Right_Blackline);		
				pint_enable_irq(MT9V032_VSYNC_PINT);
				//lcd_showfloat(1,1,pit_get_ms(),10,0);
				Find_Blackline();
				//if(gpio_get(B2)==0)
				lcd_displayimage032(*image3,MT9V032_W,MT9V032_H,Middle_line,Left_Blackline,Right_Blackline);				
				mt9v032_finish_flag = 0;
				lcd_drawpoint(3,3,GREEN);
				//pit_start();
				}
				Get_Weighted_Average();
				Direct_control();
				uart_write(Speed_L_New,Speed_R_New,count,0);
        systick_delay_ms(10);
    }
}
