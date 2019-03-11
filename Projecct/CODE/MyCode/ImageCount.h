#ifndef __ImageCount_H__
#define __ImageCount_H__
#include "DataClass.h"
/*******************************************************************************
* 说    明 * :	函数申明
* 修改时间 * :	2016-5-16
*******************************************************************************/
/* 灰度图像处理 */
void download(void);				// 下载图像
void CountThreshold(void);			// 计算临界值
void RowDealBit(void);				// 二值化采集的图像
_INT16U_ GetMiddle(_INT16U_ a,_INT16U_ b,_INT16U_ c);		// 中值滤波程序

void Standard(void);				// 计算标准参数

/* 赛道边线处理 */
void SearchImage(void);				// 搜图
void OverlapFilter(void);			// 重叠滤波
void CalculateSlope(void);			// 计算斜率
void FillingLine(void);				// 补线
void CrossFillingLine(void);		// 十字补线

/* 赛道元素处理 */
void SearchLength(void);			// 计算最远点距离
void WhiteWide(void);				// 计算赛道宽度
void ActiveLine(void);				// 计算有效行
void CrossFilter(void);				// 十字检测
void CheckHill(void);				// 坡道检测
void CheckStartLine(void);			// 起跑线检测
void CheckBarrier(void);			// 障碍检测
void BigArc(void);					// 大圆弧检测
void CarProtect(void);				// 保护小车，防出轨、跑飞，定时停车

/* 拟合赛道参数 */
void CouBlackArea(void);			// 计算赛道黑点面积
_INT16U_ MCU_sqrt(_INT32U_ M);		// MCU快速开平方
_INT16S_ curvature(_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3);		// 三点计算曲率



#endif
