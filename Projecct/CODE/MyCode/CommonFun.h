#ifndef __CommonFun_h__
#define __CommonFun_h__
#include "Variable.h"	// ��������
/*******************************************************************************
* ˵    �� * :	�����ӿڶ���
* �޸�ʱ�� * :	2016-3-30
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
* ˵    �� * :	��������
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void Delay_1ms(_INT32U_ cou);		// ��ʱ����
void GetSpeed(void);				// ��õ�ǰ�ٶ�
_INT16U_ MyAbs(_INT16S_ x);			// �����ֵ����
_INT16S_ limit1(_INT16S_ a,_INT16S_ b);					// ��a�޷���-b��+b֮��
_INT16S_ limit_B_C(_INT16S_ a,_INT16S_ b,_INT16S_ c);	// ��a�޷���b��c֮��(b<c)
void keyscan(void);					// ����ɨ��
void DispalyData(void);					// ��ʾ��Ϣ
void TestTip(void);					// �������Ԫ��

#endif
