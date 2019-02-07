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
