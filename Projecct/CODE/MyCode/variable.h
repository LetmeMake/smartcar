#ifndef __Variable_H__
#define __Variable_H__
#include "DataClass.h"
/*******************************************************************************
* ˵    �� * :	ͼ�������������
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
#define _ColumnMax_      186		// ȡͼ����
#define _RowMax_         120		// ȡͼ����
#define _Center_          93		// ����λ��

#define _SearchRangeMax_  30		// �������뾶
#define _SearchRangeMin_  10		// ������С�뾶

#define _SearchStop_      10		// ������ʼ����ֹ

#define _LostMax_         50		// ���������

#define _LineArea_       112		// �������������
#define _AreaRangeMax_    70		// ���γ�����뾶
#define _AreaRangeMin_    15		// ���ζ̵���뾶

#define _WhiteMax_       115		// �׵����ֵ
#define _WhiteMin_        50		// �׵���Сֵ
#define _Contrast_        15		// �Աȶȷ�ֵ

#define _LengthRange_     15		// ������Զ��뾶

#define _CrossWide_       30		// ʮ�ֿ��

#define _SlopeFarthest_   20		// ����б����Զ��

#define _Effective_        1		// ��Ч��־
#define _Void_             0		// ��Ч��־



/*******************************************************************************
* ˵    �� * :	�����������������
* �޸�ʱ�� * :	2016-3-16
*******************************************************************************/
#define _SpeedParameter_   100		// ��������ٶȲ���

#define _SteerDutyMax_     950		// �������ת�ǿ���
#define _SteerCenter_     4350		// �������ֵ

#define _MotorDutyMax_    1000		// �����תռ�ձ�����
#define _MotorDutyMin_    -500		// �����תռ�ձ�����

#define _SuperCarMove_    2000		// С���ƶ���Զ����



/*******************************************************************************
* ˵    �� * :	����Ԫ��
* �޸�ʱ�� * :	2016-6-14
*******************************************************************************/
//enum test{cross,barrier,hill,start_line};
#define _Cross_     1
#define _Barrier_   2
#define _Hill_      3
#define _StartLine_ 4



/*******************************************************************************
* ˵    �� * :	��������
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT16U_ _16u[4];
extern _INT16S_ _16s[4];
extern _INT32U_ _32u[4];
extern _INT32S_ _32s[4];
extern _INT64U_ _64u[4];
extern _INT64S_ _64s[4];



/*******************************************************************************
* ˵    �� * :	�жϱ���
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT16U_ PulseAddCount;		// �ۼ�������



/*******************************************************************************
* ˵    �� * :	ϵͳ����
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT16U_    StartTime;		// ϵͳ����ʱ��(�ϵ翪ʼ),��λs
extern _INT16U_     MoveTime;		// С����ʻʱ��(������ʼ),��λs
extern _INT32U_ AccuracyTime;		// ��ʻ��ȷʱ��,��λ5ms

extern _INT32S_ CarMove;		// С����ʻ����

extern _INT8U_    key[4];		// ��������
extern _INT8U_ button[4];		// ���뿪��

extern _INT8U_ model;		// ģʽ����

extern _INT8U_ TimeStopCar;		// ��ʱͣ��ʱ��(��λ:s)

extern _INT8U_ TestElement;		// ��������Ԫ��



/*******************************************************************************
* ˵    �� * :	�ŷ��������
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT16S_ SteerAngle;		// ���ת�����

extern _INT16U_ Steer_AN_KP;		// PD���Ʋ���
extern _INT8U_  Steer_AN_KD;



/*******************************************************************************
* ˵    �� * :	DC�������
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_ MaxSpeed;		// ����ٶ�
extern _INT8U_ MinSpeed;		// ��С�ٶ�

extern _INT8U_ SuperSpeed;		// �����ٶ�

extern _INT8U_ StopCarFlag;		// ͣ����־

extern _INT16S_ ActualSpeed;	// ʵ���ٶ�
extern _INT8U_  IdealSpeed;		// �����ٶ�

extern _INT16S_ Car_PWM;		// ���PWMֵ

extern _INT8U_ Motor_AN_KP;		// ���PID�������
extern _INT8U_ Motor_AN_KI;
extern _INT8U_ Motor_AN_KD;

extern _INT16S_ SpeedBias[3];	// �ٶ�ƫ��



/*******************************************************************************
* ˵    �� * :	���߱���
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftConfine[_RowMax_];		// ���б߽�
extern _INT8U_ RightConfine[_RowMax_];		// ���б߽�
extern _INT8U_ MidcourtLine[_RowMax_];		// ����λ��
extern _INT8U_    TrackWide[_RowMax_];		// �������

extern _INT8U_  LeftFirstConfine;		// �����б߽�
extern _INT8U_ RightFirstConfine;		// �����б߽�
extern _INT8U_      LeftFirstRow;		// ������λ��
extern _INT8U_     RightFirstRow;		// ������λ��
extern _INT8U_         StartLine;		// ��ʼ��
extern _INT8U_        LeftEndRow;		// �������λ��
extern _INT8U_       RightEndRow;		// �ҽ�����λ��

extern _INT8U_ sight;		// ��Ұ

extern _INT8U_  LeftLost;		// ��������
extern _INT8U_ RightLost;		// �Ҷ�������

extern const _INT8U_ BlackLine[_RowMax_];		// ���߿��

extern _INT8U_ SearchLineRange[_RowMax_];		// �����߽�뾶

extern const _INT8U_ ConfineDistance[_RowMax_];		// ���߼��



/*******************************************************************************
* ˵    �� * :	������Ч��
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_   LeftEffective;		// ����Ч��
extern _INT8U_  RightEffective;		// ����Ч��
extern _INT8U_ AmountEffective;		// ����Ч��



/*******************************************************************************
* ˵    �� * :	�������
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftTrapezoid[_RowMax_];		// ��׼�������
extern _INT8U_ RightTrapezoid[_RowMax_];		// ��׼�����ұ�

extern _INT8U_ AreaEndLine;		// ���������ֹ��

extern _INT16U_  LeftArea;		// ������
extern _INT16U_ RightArea;		// �ұ����

extern _INT16S_        offset;		// ������
extern _INT16S_     OldOffset;		// ��һ�εĲ���ֵ
extern _INT16S_ CorrectOffset;		// �������ֵ



/*******************************************************************************
* ˵    �� * :	б�ʼ���
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT16S_  LeftFarSlope;		// ��Զ��б��
extern _INT16S_ RightFarSlope;		// ��Զ��б��

extern _INT16S_  LeftNearSlope;		// �����б��
extern _INT16S_ RightNearSlope;		// �ҽ���б��

extern _INT8U_  LeftInflexion;		// ��յ�
extern _INT8U_ RightInflexion;		// �ҹյ�



/*******************************************************************************
* ˵    �� * :	����Ԫ��
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftCross;		// ��ʮ��
extern _INT8U_ RightCross;		// ��ʮ��
extern _INT16U_ CrossArea;		// ʮ�����

extern _INT8U_        HillFlag;		// �µ�
extern _INT16U_     OnHillTime;		// ���µ�ʱ��
extern _INT16U_ OnHillDistance;		// �µ���������

extern _INT8U_  StartLineFlag;		// �����߱�־
extern _INT32U_ StartLineTime;		// ��⵽������ʱ��

extern _INT8U_        BarrierFlag;		// �ϰ�
extern _INT8U_        BarrierTime;		// ��⵽�ϰ�ʱ��
extern _INT16U_      BarrierShift;		// �ϰ���������
extern _INT8U_  LeftBarrierBuffer;		// ͨ���ϰ����弶��
extern _INT8U_ RightBarrierBuffer;
extern _INT8U_    LeftBarrierFlag;		// �ϰ���־
extern _INT8U_   RightBarrierFlag;
extern _INT8U_         BarrierRow;		// �ϰ�����λ��
extern _INT8U_         BarrierCol;

extern _INT8U_ BigArcFlag;		// ��Բ����־



/*******************************************************************************
* ˵    �� * :	Զ�˾���
* �޸�ʱ�� * :	2016-5-16
*******************************************************************************/
extern _INT8U_ WhiteLengthNear[_ColumnMax_];		// �����׸��ڵ�
extern _INT16U_                 WhiteLength;		// ǰ���ۼ�
extern _INT16U_              OldWhiteLength;		// ǰһ��ǰ���ۼ�
extern _INT16U_          CorrectWhiteLength;		// WhiteLength - OldWhiteLength



/*******************************************************************************
* ˵    �� * :	ͼ�����
* �޸�ʱ�� * :	2016-4-10
*******************************************************************************/
extern _INT8U_                  CollectOverFlag;		// ��ͼ������־

extern _INT8U_  DataSave[_RowMax_][_ColumnMax_+2];		// ��ʱ��ͼ

extern _INT8U_ ImageData[_RowMax_][_ColumnMax_];		// ��ʵ��ͼ

extern _INT8U_              Threshold[_RowMax_];		// ͼ���ٽ�ֵ



#endif
