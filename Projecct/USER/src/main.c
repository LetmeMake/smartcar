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



int main(void)
{   
    get_clk();


	  lcd_init();
	  camera_init();
    uart_init(USART_0,460800,UART0_TX_A25,UART0_RX_A24);
	  gpio_init(B2,GPI, 1, PULLUP);
    EnableInterrupts;
    while(1)
    {
				if(mt9v032_finish_flag)
				{			
				lcd_displayimage032(*image,MT9V032_W,MT9V032_H);
				pint_enable_irq(MT9V032_VSYNC_PINT);
				lcd_showfloat(1,1,pit_get_ms(),10,0);
				if(gpio_get(B2)==0)
				mt9v032_finish_flag = 0;
				pit_start();
				}

        systick_delay_ms(10);
    }
}
