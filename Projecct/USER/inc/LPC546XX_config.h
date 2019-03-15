/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		LPC546XX库配置文件
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/

#ifndef _LPC546XX_config_h
#define _LPC546XX_config_h

//-------------------------------------------------------------------------------------------------------------------
//  当前版本号
//  如果此处版本号与version.txt文件版本不一致，以version.txt文件为准
//-------------------------------------------------------------------------------------------------------------------
#define SEEKFREE_LPC546XX_VERSION   0X116


//-------------------------------------------------------------------------------------------------------------------
//  LPC546XX_CLOSE_ISP 为 0   不关闭ISP
//  LPC546XX_CLOSE_ISP 为 1   永久关闭ISP,只要运行一次程序则永久关闭，如果想要使用ISP就只能更换芯片
//-------------------------------------------------------------------------------------------------------------------
#define LPC546XX_CLOSE_ISP          0



//-------------------------------------------------------------------------------------------------------------------
//  LPC546XX_PLL_CLOCK_SOURCE 为 0   使用内部12M晶振
//  LPC546XX_PLL_CLOCK_SOURCE 为 1   使用外部12M晶振
//-------------------------------------------------------------------------------------------------------------------
#define LPC546XX_PLL_CLOCK_SOURCE   1
    
//-------------------------------------------------------------------------------------------------------------------
//  LPC546XX_MAIN_CLOCK 为 0         内核频率 180M  标准频率
//  LPC546XX_MAIN_CLOCK 为 1         内核频率 200M  超频有风险，需自行承担一切后果
//  LPC546XX_MAIN_CLOCK 为 2         内核频率 210M  超频有风险，需自行承担一切后果
//-------------------------------------------------------------------------------------------------------------------
#define LPC546XX_MAIN_CLOCK         0

//-------------------------------------------------------------------------------------------------------------------
//  CLK_OUT 为 0                     不通过P026输出main_clk/200时钟
//  CLK_OUT 为 1                     通过P026输出main_clk/200时钟，P026输出的频率乘200等于main_clk频率
//-------------------------------------------------------------------------------------------------------------------
#define CLK_OUT                     0


//-------------------------------------------------------------------------------------------------------------------
//  PRINTF 为 0                      不使用printf串口打印函数及不输出调试信息，则不会初始化相应串口
//  PRINTF 为 1                      使用printf串口打印函数及输出调试信息，则会初始化相应串口
//-------------------------------------------------------------------------------------------------------------------
#define PRINTF                      1


#if(1 == PRINTF)

//-------------------------------------------------------------------------------------------------------------------
//printf串口打印函数所使用的串口、串口波特率、串口引脚宏定义
//-------------------------------------------------------------------------------------------------------------------
#define DEBUG_UART                  USART_0
#define DEBUG_UART_BAUD             115200
#define DEBUG_UART_TX_PIN           UART0_TX_A25
#define DEBUG_UART_RX_PIN           UART0_RX_A24

//-------------------------------------------------------------------------------------------------------------------
//  DEBUG_INFO 为 0                  不输出断言信息
//  DEBUG_INFO 为 1                  输出断言信息，断言信息包含错误所在文件及所在行  需要PRINTF宏定义为1才能有效输出
//-------------------------------------------------------------------------------------------------------------------
#define DEBUG_ASSERT                1

#endif





#endif
