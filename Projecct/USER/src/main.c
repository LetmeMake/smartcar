/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴LPC546XX_config.h�ļ��ڰ汾�궨��
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�


//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������

#include "headfile.h"


//int target_value=30;
int main(void)
{   
    get_clk();


		//���
		Motor_Init();
		//���
		ctimer_pwm_init(TIMER4_PWMCH0_A6, 50, 780);
		//������������
		ctimer_count_init(TIMER0_COUNT1_A2);
		gpio_init(A3,GPI, 1, PULLUP);
		ctimer_count_init(TIMER3_COUNT0_A4);	
		gpio_init(A5,GPI, 1, PULLUP);
		
	  lcd_init();
	  camera_init();
    uart_init(USART_0,115200,UART0_TX_A25,UART0_RX_A24);
	  	//����
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
