#ifndef __Variable_H__
#define __Variable_H__
#include "DataClass.h"
/*******************************************************************************
* 说    明 * :	图像处理命令或限制
* 修改时间 * :	2016-4-10
*******************************************************************************/
#define _ColumnMax_      186		// 取图列数
#define _RowMax_         120		// 取图行数
#define _Center_          93		// 中心位置

#define _SearchRangeMax_  30		// 搜索最大半径
#define _SearchRangeMin_  10		// 搜索最小半径

#define _SearchStop_      10		// 搜索起始行终止

#define _LostMax_         50		// 丢线最大数

#define _LineArea_       112		// 计算面积的行数
#define _AreaRangeMax_    70		// 梯形长底面半径
#define _AreaRangeMin_    15		// 梯形短底面半径

#define _WhiteMax_       115		// 白点最大值
#define _WhiteMin_        50		// 白点最小值
#define _Contrast_        15		// 对比度阀值

#define _LengthRange_     15		// 计算最远点半径

#define _CrossWide_       30		// 十字宽度

#define _SlopeFarthest_   20		// 计算斜率最远端

#define _Effective_        1		// 有效标志
#define _Void_             0		// 无效标志



/*******************************************************************************
* 说    明 * :	舵机、电机命令或限制
* 修改时间 * :	2016-3-16
*******************************************************************************/
#define _SpeedParameter_   100		// 电机理想速度参数

#define _SteerDutyMax_     950		// 舵机左右转角控制
#define _SteerCenter_     4350		// 舵机中心值

#define _MotorDutyMax_    1000		// 电机正转占空比限制
#define _MotorDutyMin_    -500		// 电机反转占空比限制

#define _SuperCarMove_    2000		// 小车移动最远距离



/*******************************************************************************
* 说    明 * :	测试元素
* 修改时间 * :	2016-6-14
*******************************************************************************/
//enum test{cross,barrier,hill,start_line};
#define _Cross_     1
#define _Barrier_   2
#define _Hill_      3
#define _StartLine_ 4



/*******************************************************************************
* 说    明 * :	测试所用
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT16U_ _16u[4];
extern _INT16S_ _16s[4];
extern _INT32U_ _32u[4];
extern _INT32S_ _32s[4];
extern _INT64U_ _64u[4];
extern _INT64S_ _64s[4];



/*******************************************************************************
* 说    明 * :	中断变量
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT16U_ PulseAddCount;		// 累加脉冲数



/*******************************************************************************
* 说    明 * :	系统参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT16U_    StartTime;		// 系统启动时间(上电开始),单位s
extern _INT16U_     MoveTime;		// 小车行驶时间(发车开始),单位s
extern _INT32U_ AccuracyTime;		// 行驶精确时间,单位5ms

extern _INT32S_ CarMove;		// 小车行驶距离

extern _INT8U_    key[4];		// 独立按键
extern _INT8U_ button[4];		// 拨码开关

extern _INT8U_ model;		// 模式控制

extern _INT8U_ TimeStopCar;		// 定时停车时间(单位:s)

extern _INT8U_ TestElement;		// 测试赛道元素



/*******************************************************************************
* 说    明 * :	伺服电机参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT16S_ SteerAngle;		// 舵机转向控制

extern _INT16U_ Steer_AN_KP;		// PD控制参数
extern _INT8U_  Steer_AN_KD;



/*******************************************************************************
* 说    明 * :	DC电机参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_ MaxSpeed;		// 最大速度
extern _INT8U_ MinSpeed;		// 最小速度

extern _INT8U_ SuperSpeed;		// 超级速度

extern _INT8U_ StopCarFlag;		// 停车标志

extern _INT16S_ ActualSpeed;	// 实际速度
extern _INT8U_  IdealSpeed;		// 理想速度

extern _INT16S_ Car_PWM;		// 电机PWM值

extern _INT8U_ Motor_AN_KP;		// 电机PID计算变量
extern _INT8U_ Motor_AN_KI;
extern _INT8U_ Motor_AN_KD;

extern _INT16S_ SpeedBias[3];	// 速度偏差



/*******************************************************************************
* 说    明 * :	搜线变量
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftConfine[_RowMax_];		// 左行边界
extern _INT8U_ RightConfine[_RowMax_];		// 右行边界
extern _INT8U_ MidcourtLine[_RowMax_];		// 中线位置
extern _INT8U_    TrackWide[_RowMax_];		// 赛道宽度

extern _INT8U_  LeftFirstConfine;		// 左首行边界
extern _INT8U_ RightFirstConfine;		// 右首行边界
extern _INT8U_      LeftFirstRow;		// 左首行位置
extern _INT8U_     RightFirstRow;		// 右首行位置
extern _INT8U_         StartLine;		// 起始行
extern _INT8U_        LeftEndRow;		// 左结束行位置
extern _INT8U_       RightEndRow;		// 右结束行位置

extern _INT8U_ sight;		// 视野

extern _INT8U_  LeftLost;		// 左丢线行数
extern _INT8U_ RightLost;		// 右丢线行数

extern const _INT8U_ BlackLine[_RowMax_];		// 黑线宽度

extern _INT8U_ SearchLineRange[_RowMax_];		// 搜索边界半径

extern const _INT8U_ ConfineDistance[_RowMax_];		// 边线间距



/*******************************************************************************
* 说    明 * :	计算有效行
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_   LeftEffective;		// 左有效行
extern _INT8U_  RightEffective;		// 右有效行
extern _INT8U_ AmountEffective;		// 总有效行



/*******************************************************************************
* 说    明 * :	计算面积
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftTrapezoid[_RowMax_];		// 标准梯形左边
extern _INT8U_ RightTrapezoid[_RowMax_];		// 标准梯形右边

extern _INT8U_ AreaEndLine;		// 面积计算终止行

extern _INT16U_  LeftArea;		// 左边面积
extern _INT16U_ RightArea;		// 右边面积

extern _INT16S_        offset;		// 补偿项
extern _INT16S_     OldOffset;		// 上一次的补偿值
extern _INT16S_ CorrectOffset;		// 补偿项差值



/*******************************************************************************
* 说    明 * :	斜率计算
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT16S_  LeftFarSlope;		// 左远端斜率
extern _INT16S_ RightFarSlope;		// 右远端斜率

extern _INT16S_  LeftNearSlope;		// 左近端斜率
extern _INT16S_ RightNearSlope;		// 右近端斜率

extern _INT8U_  LeftInflexion;		// 左拐点
extern _INT8U_ RightInflexion;		// 右拐点



/*******************************************************************************
* 说    明 * :	赛道元素
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_  LeftCross;		// 左十字
extern _INT8U_ RightCross;		// 右十字
extern _INT16U_ CrossArea;		// 十字面积

extern _INT8U_        HillFlag;		// 坡道
extern _INT16U_     OnHillTime;		// 上坡道时间
extern _INT16U_ OnHillDistance;		// 坡道解锁距离

extern _INT8U_  StartLineFlag;		// 起跑线标志
extern _INT32U_ StartLineTime;		// 检测到起跑线时间

extern _INT8U_        BarrierFlag;		// 障碍
extern _INT8U_        BarrierTime;		// 检测到障碍时间
extern _INT16U_      BarrierShift;		// 障碍解锁距离
extern _INT8U_  LeftBarrierBuffer;		// 通过障碍缓冲级数
extern _INT8U_ RightBarrierBuffer;
extern _INT8U_    LeftBarrierFlag;		// 障碍标志
extern _INT8U_   RightBarrierFlag;
extern _INT8U_         BarrierRow;		// 障碍所在位置
extern _INT8U_         BarrierCol;

extern _INT8U_ BigArcFlag;		// 大圆弧标志



/*******************************************************************************
* 说    明 * :	远端距离
* 修改时间 * :	2016-5-16
*******************************************************************************/
extern _INT8U_ WhiteLengthNear[_ColumnMax_];		// 近端首个黑点
extern _INT16U_                 WhiteLength;		// 前端累加
extern _INT16U_              OldWhiteLength;		// 前一次前端累加
extern _INT16U_          CorrectWhiteLength;		// WhiteLength - OldWhiteLength



/*******************************************************************************
* 说    明 * :	图像参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
extern _INT8U_                  CollectOverFlag;		// 采图结束标志

extern _INT8U_  DataSave[_RowMax_][_ColumnMax_+2];		// 临时存图

extern _INT8U_ ImageData[_RowMax_][_ColumnMax_];		// 真实存图

extern _INT8U_              Threshold[_RowMax_];		// 图像临界值



#endif
