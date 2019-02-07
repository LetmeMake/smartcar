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

    simiic_init();
    icm20602_init();
    uart_init(USART_0,460800,UART0_TX_A25,UART0_RX_A24);
    EnableInterrupts;
    while(1)
    {
        get_icm20602_accdata();
        get_icm20602_gyro();
        data_conversion(icm_acc_x,icm_acc_y,icm_acc_z,icm_gyro_x,virtual_scope_data);
        uart_putbuff(USART_0,virtual_scope_data,sizeof(virtual_scope_data));
        systick_delay_ms(10);
    }
}
