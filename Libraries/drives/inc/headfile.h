/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		headfile
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/
#ifndef _headfile_h
#define _headfile_h

/*******************************************************************************
* 说    明 * :	编译选择
* 修改时间 * :	2016-6-19
*******************************************************************************/
#define _compile_ _RunCarSystem_		// 选择编译的程序

#define _ExecutiveForceTest_ 1414		// 测试代码执行力
#define _RunCarSystem_       1415		// 调车程序
#define _MotorOrSteerTest_   1416		// 电机、舵机测试
#define _RubTyreProgram_     1417		// 磨轮胎程序

#include <stdbool.h>
#include <math.h>



#include "common.h"

#include "SEEKFREE_FUN.h"

#include "LPC546XX_flexcomm.h" 
#include "LPC546XX_pll.h"
#include "LPC546XX_iocon.h"
#include "LPC546XX_gpio.h"
#include "LPC546XX_uart.h"
#include "LPC546XX_systick.h"
#include "LPC546XX_gint.h"
#include "LPC546XX_adc.h"
#include "LPC546XX_pit.h"
#include "LPC546XX_ctimer.h"
#include "LPC546XX_pint.h"
#include "LPC546XX_sct.h"
#include "LPC546XX_dma.h"
#include "LPC546XX_spi.h"
#include "LPC546XX_iic.h"
#include "LPC546XX_eeprom.h"
#include "LPC546XX_mrt.h"

#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_NRF24L01.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_MT9V032.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_ICM20602.h"

//mycode
#include "mycode.h"
#include "img_data_deal.h"
#include "angle_control.h"
#include "pid.h"
#include "ImageCount.h"
#include "DataClass.h"		// 数据类型定义
#include "Variable.h"		// 变量定义
#include "CommonFun.h"		// 常用功能
#include "control.h"
<<<<<<< HEAD
#include "inductance.h"
=======
#include "bluetooth.h"
>>>>>>> d505da9f6599f2df4878ab522962f87b6abe5125

#endif
