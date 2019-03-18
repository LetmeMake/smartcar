#include "DataClass.h"
#include "Variable.h"
/*******************************************************************************
* 说    明 * :	测试所用
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT16U_ _16u[4] = {0};
_INT16S_ _16s[4] = {0};
_INT32U_ _32u[4] = {0};
_INT32S_ _32s[4] = {0};
_INT64U_ _64u[4] = {0};
_INT64S_ _64s[4] = {0};


/*******************************************************************************
* 说    明 * :	中断变量
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT16U_ PulseAddCount = 0;		// 累加脉冲数



/*******************************************************************************
* 说    明 * :	系统参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT16U_    StartTime = 0;		// 系统启动时间(上电开始),单位s
_INT16U_     MoveTime = 0;		// 小车行驶时间(发车开始),单位s
_INT32U_ AccuracyTime = 0;		// 行驶精确时间,单位5ms
_INT32S_      CarMove = 0;		// 小车行驶距离

_INT8U_    key[4] = {0};		// 独立按键
_INT8U_ button[4] = {0};		// 拨码开关

_INT8U_ model = 0;		// 模式控制

_INT8U_ TimeStopCar = 20;		// 定时停车时间(单位:s)

_INT8U_ TestElement = _Cross_;		// 测试赛道元素



/*******************************************************************************
* 说    明 * :	伺服电机参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT16S_ SteerAngle = 0;			// 舵机转向控制(相对中心值)

_INT16U_ 	Steer_AN_KP = 150;			// PD控制参数300
_INT8U_   Steer_AN_KD = 30;				//30



/*******************************************************************************
* 说    明 * :	DC电机参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_ MaxSpeed = 70;		// 最大速度
_INT8U_  MinSpeed = 0;		// 最小速度

_INT8U_ SuperSpeed = 0;		// 超级速度

_INT8U_ StopCarFlag = _Effective_;		// 停车标志

_INT16S_ ActualSpeed = 0;		// 实际速度
_INT8U_   IdealSpeed = 0;		// 理想速度

_INT16S_ Car_PWM = 0;		// 电机PWM值

_INT8U_ Motor_AN_KP = 32;		// 电机PID计算变量
_INT8U_ Motor_AN_KI = 12;
_INT8U_ Motor_AN_KD = 15;

_INT16S_ SpeedBias[3] = {0};		// 速度偏差



/*******************************************************************************
* 说    明 * :	搜线变量
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_                LeftConfine[_RowMax_] = {0};		// 左行边界
_INT8U_ RightConfine[_RowMax_] = {_ColumnMax_ - 1};		// 右行边界
_INT8U_               MidcourtLine[_RowMax_] = {0};		// 中线位置
_INT8U_                  TrackWide[_RowMax_] = {0};		// 赛道宽度

_INT8U_      LeftFirstConfine = _ColumnMax_ / 4;		// 左首行边界
_INT8U_ RightFirstConfine = _ColumnMax_ * 3 / 4;		// 右首行边界
_INT8U_                        LeftFirstRow = 0;		// 左首行位置
_INT8U_                       RightFirstRow = 0;		// 右首行位置
_INT8U_                          LeftEndRow = 0;		// 左结束行位置
_INT8U_                         RightEndRow = 0;		// 右结束行位置
_INT8U_                           StartLine = 0;		// 起始行

_INT8U_ sight = 0;		// 视野

_INT8U_  LeftLost = 0;		// 左丢线行数
_INT8U_ RightLost = 0;		// 右丢线行数

const _INT8U_ BlackLine[_RowMax_] =		// 黑线宽度
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
};

_INT8U_ SearchLineRange[_RowMax_] = {0};		// 搜索边界半径

//const _INT8U_ ConfineDistance[_RowMax_] =		// 边线间距
//{
//	 30, 31, 33, 34, 35, 37, 38, 39, 41, 42,
//	 44, 45, 46, 47, 48, 50, 51, 52, 54, 55,
//	 57, 58, 59, 61, 62, 63, 65, 66, 67, 68,
//	 69, 70, 71, 73, 74, 75, 76, 77, 78, 79,
//	 81, 82, 83, 84, 85, 86, 87, 88, 90, 91,
//	 92, 93, 94, 95, 96, 97, 98, 99,100,101,
//	102,103,104,105,106,107,108,109,110,111,
//	112,113,114,115,116,117,118,119,119,120,
//	121,122,123,124,125,126,127,128,129,130,
//	131,131,132,133,134,134,135,136,137,138,
//	139,140,140,141,142,143,144,144,145,146,
//	146,147,147,148,149,150,151,151,152,153
//};
const _INT8U_ ConfineDistance[_RowMax_] =		// 边线间距
{
	 30, 31, 33, 34, 35, 37, 38, 39, 41, 42,
	 44, 45, 46, 47, 48, 50, 51, 52, 54, 55,
	 57, 58, 59, 61, 62, 63, 65, 66, 67, 68,
	 69, 70, 71, 73, 74, 75, 76, 77, 78, 79,
	 81, 82, 83, 84, 85, 86, 87, 88, 90, 91,
	 92, 93, 94, 95, 96, 97, 98, 99,100,101,
	102,103,104,105,106,107,108,109,110,111,
	112,113,114,115,116,117,118,119,119,120,
	121,122,123,124,125,126,127,128,129,130,
	131,131,132,133,134,134,135,136,137,138,
	139,140,140,141,142,143,144,144,145,146,
	146,147,147,148,149,150,151,151,152,153
};


/*******************************************************************************
* 说    明 * :	计算有效行
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_   LeftEffective = 0;		// 左有效行
_INT8U_  RightEffective = 0;		// 右有效行
_INT8U_ AmountEffective = 0;		// 总有效行



/*******************************************************************************
* 说    明 * :	计算面积
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_  LeftTrapezoid[_RowMax_];		// 标准梯形左边
_INT8U_ RightTrapezoid[_RowMax_];		// 标准梯形右边

_INT8U_ AreaEndLine = 0;		// 面积计算终止行

_INT16U_  LeftArea = 0;		// 左边面积
_INT16U_ RightArea = 0;		// 右边面积

_INT16S_        offset = 0;		// 补偿项
_INT16S_     OldOffset = 0;		// 上一次的补偿值
_INT16S_ CorrectOffset = 0;		// 补偿项差值



/*******************************************************************************
* 说    明 * :	斜率计算
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT16S_  LeftFarSlope = 0;		// 左远端斜率
_INT16S_ RightFarSlope = 0;		// 右远端斜率

_INT16S_  LeftNearSlope = 0;		// 左近端斜率
_INT16S_ RightNearSlope = 0;		// 右近端斜率

_INT8U_  LeftInflexion = 0;		// 左拐点
_INT8U_ RightInflexion = 0;		// 右拐点



/*******************************************************************************
* 说    明 * :	赛道元素
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_  LeftCross = _Void_;		// 左十字
_INT8U_ RightCross = _Void_;		// 右十字
_INT16U_      CrossArea = 0;		// 十字面积

_INT8U_   HillFlag = _Void_;		// 坡道
_INT16U_     OnHillTime = 0;		// 上坡道时间
_INT16U_ OnHillDistance = 0;		// 坡道解锁距离

_INT8U_ StartLineFlag = _Void_;		// 起跑线标志
_INT32U_     StartLineTime = 0;		// 检测到起跑线时间

_INT8U_      BarrierFlag = _Void_;		// 障碍
_INT8U_           BarrierTime = 0;		// 检测到障碍时间
_INT16U_         BarrierShift = 0;		// 障碍解锁距离
_INT8U_     LeftBarrierBuffer = 0;		// 通过障碍缓冲级数
_INT8U_    RightBarrierBuffer = 0;
_INT8U_  LeftBarrierFlag = _Void_;		// 障碍标志
_INT8U_ RightBarrierFlag = _Void_;
_INT8U_            BarrierRow = 0;		// 障碍所在位置
_INT8U_            BarrierCol = 0;

_INT8U_ BigArcFlag = _Void_;		// 大圆弧标志



/*******************************************************************************
* 说    明 * :	远端距离
* 修改时间 * :	2016-5-16
*******************************************************************************/
_INT8U_ WhiteLengthNear[_ColumnMax_] = {0};		// 近端首个黑点
_INT16U_                   WhiteLength = 0;		// 前端累加
_INT16U_                OldWhiteLength = 0;		// 前一次前端累加
_INT16U_            CorrectWhiteLength = 0;		// WhiteLength - OldWhiteLength



/*******************************************************************************
* 说    明 * :	图像参数
* 修改时间 * :	2016-4-10
*******************************************************************************/
_INT8U_               CollectOverFlag = _Void_;		// 采图结束标志

_INT8U_  DataSave[_RowMax_][_ColumnMax_+2] = {0};		// 临时存图

_INT8U_ ImageData[_RowMax_][_ColumnMax_] = {0};		// 真实存图

_INT8U_              Threshold[_RowMax_] = {0};		// 图像临界值
