#ifndef __ImageCount_H__
#define __ImageCount_H__
#include "DataClass.h"
/*******************************************************************************
* ˵    �� * :	��������
* �޸�ʱ�� * :	2016-5-16
*******************************************************************************/
/* �Ҷ�ͼ���� */
void download(void);				// ����ͼ��
void CountThreshold(void);			// �����ٽ�ֵ
void RowDealBit(void);				// ��ֵ���ɼ���ͼ��
_INT16U_ GetMiddle(_INT16U_ a,_INT16U_ b,_INT16U_ c);		// ��ֵ�˲�����

void Standard(void);				// �����׼����

/* �������ߴ��� */
void SearchImage(void);				// ��ͼ
void OverlapFilter(void);			// �ص��˲�
void CalculateSlope(void);			// ����б��
void FillingLine(void);				// ����
void CrossFillingLine(void);		// ʮ�ֲ���

/* ����Ԫ�ش��� */
void SearchLength(void);			// ������Զ�����
void WhiteWide(void);				// �����������
void ActiveLine(void);				// ������Ч��
void CrossFilter(void);				// ʮ�ּ��
void CheckHill(void);				// �µ����
void CheckStartLine(void);			// �����߼��
void CheckBarrier(void);			// �ϰ����
void BigArc(void);					// ��Բ�����
void CarProtect(void);				// ����С���������졢�ܷɣ���ʱͣ��

/* ����������� */
void CouBlackArea(void);			// ���������ڵ����
_INT16U_ MCU_sqrt(_INT32U_ M);		// MCU���ٿ�ƽ��
_INT16S_ curvature(_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3);		// �����������



#endif
