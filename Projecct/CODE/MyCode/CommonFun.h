#ifndef __CommonFun_h__
#define __CommonFun_h__
#include "Variable.h"	// 变量定义
/*******************************************************************************
* 说    明 * :	按键接口定义
* 修改时间 * :	2016-3-30
*******************************************************************************/
#define _StartKey_ PTB23
#define _AddKey_   PTB22
#define _SubbKey_  PTB21
#define _ModelKey_ PTB20
#define _button1_   PTB9
#define _button2_  PTB10
#define _button3_  B17
#define _button4_  PTB16


/*******************************************************************************
* 说    明 * :	函数申明
* 修改时间 * :	2016-3-30
*******************************************************************************/
void Delay_1ms(_INT32U_ cou);		// 延时函数
void GetSpeed(void);				// 获得当前速度
_INT16U_ MyAbs(_INT16S_ x);			// 求绝对值函数
_INT16S_ limit1(_INT16S_ a,_INT16S_ b);					// 将a限幅到-b到+b之间
_INT16S_ limit_B_C(_INT16S_ a,_INT16S_ b,_INT16S_ c);	// 将a限幅到b到c之间(b<c)
void keyscan(void);					// 按键扫描
void DispalyData(void);					// 显示信息
void TestTip(void);					// 检测特殊元素

#endif
