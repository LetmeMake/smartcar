/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		headfile
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴LPC546XX_config.h�ļ��ڰ汾�궨��
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 ********************************************************************************************************************/
#ifndef _headfile_h
#define _headfile_h

/*******************************************************************************
* ˵    �� * :	����ѡ��
* �޸�ʱ�� * :	2016-6-19
*******************************************************************************/
#define _compile_ _RunCarSystem_		// ѡ�����ĳ���

#define _ExecutiveForceTest_ 1414		// ���Դ���ִ����
#define _RunCarSystem_       1415		// ��������
#define _MotorOrSteerTest_   1416		// ������������
#define _RubTyreProgram_     1417		// ĥ��̥����

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
#include "DataClass.h"		// �������Ͷ���
#include "Variable.h"		// ��������
#include "CommonFun.h"		// ���ù���
#include "control.h"
<<<<<<< HEAD
#include "inductance.h"
=======
#include "bluetooth.h"
>>>>>>> d505da9f6599f2df4878ab522962f87b6abe5125

#endif
