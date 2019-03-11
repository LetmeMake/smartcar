#include "headfile.h"
_INT8U_ SearchRight(_INT8U_ location,_INT8U_ row,_INT8U_ range);	// 搜索右边界
_INT8U_ SearchLeft(_INT8U_ location,_INT8U_ row,_INT8U_ range);		// 搜索左边界

_INT16S_ LeftSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke);				// 计算左斜率，放大10倍
_INT16S_ RightSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke);				// 计算右斜率，放大10倍

void FirstSearch(void);			// 搜锁首行边界



/*******************************************************************************
* 函 数 名 * :	download
* 函数功能 * :	下载图像
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-4-4
*******************************************************************************/
void download(void)
{
	_INT16S_ row,col;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData,(*p1)[_ColumnMax_+2] = DataSave;
	
	for(row = 0;row < _RowMax_;row++,p0++,p1++)
	{
		for(col = 0;col < _ColumnMax_;col++)
		{
			*(*p0 + col) = *(*p1 + col+1);
		}
	}
}

/*******************************************************************************
* 函 数 名 * :	Standard
* 函数功能 * :	计算标准参数
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-20
*******************************************************************************/
void Standard(void)
{
	_INT16S_ loop;
	
	for(loop = 0;loop < _RowMax_;loop++)
	{
		/* 梯形左腰 */
		LeftTrapezoid[loop]   = _Center_ - (_AreaRangeMin_ + (_AreaRangeMax_-_AreaRangeMin_)*(loop+1)/_RowMax_);
		/* 梯形右腰 */
		RightTrapezoid[loop]  = _Center_ + (_AreaRangeMin_ + (_AreaRangeMax_-_AreaRangeMin_)*(loop+1)/_RowMax_);
		/* 搜线半径 */
		SearchLineRange[loop] = (_INT8U_)limit_B_C((_SearchRangeMax_ - (_RowMax_-1-loop)/5),_SearchRangeMin_,_SearchRangeMax_);
	}
}

/*******************************************************************************
* 函 数 名 * :	CarProtect
* 函数功能 * :	保护小车，防出轨、跑飞，定时停车
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-4-4
*******************************************************************************/
void CarProtect(void)
{
	bool out = false;
	_INT8U_ *p0;
	_INT16S_ row,loop;
	
	if(1)//(MoveTime >= 1)			// 起跑1s跳过
	{
		for(row = (_RowMax_ - 1);row > (_RowMax_ - 3);row--)		// 近端两行
		{
			p0 = ImageData[row];
			
			for(loop = 0;loop < _ColumnMax_;loop++)
			{
				out = (*(p0 + loop) < _WhiteMin_) ? true : false;
				
				if(out == false) break;
			}
		}
	}
	
	if(
		//((gpio_get(_button3_) == 0) && (MoveTime >= 5))       ||		// 5s试车
	 	//(MoveTime == TimeStopCar)                             ||		// 定时停车
		//(StartLineFlag && ((AccuracyTime-StartLineTime) > 10))||		// 起跑线停车
	 	out == true										        // 出轨
	  )
	{
		StopCarFlag = _Effective_;
	}
}

/*******************************************************************************
* 函 数 名 * :	CountThreshold
* 函数功能 * :	图像临界值计算
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	阈值 = (最大值 + 最小值) / 2 + 常数
* 修改时间 * :	2016-3-30
*******************************************************************************/
void CountThreshold(void)
{
	_INT8U_ row,col;
	_INT8U_ Max,Min;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData,*p1 = Threshold;
	
	for(row = 0;row < _RowMax_;row++,p0++,p1++)
	{
		Max = Min = **p0;
		for(col = 1;col < _ColumnMax_;col++)
		{
			if((*(*p0 + col) < _WhiteMax_) && (*(*p0 + col) > Max))			// 最大值计算
				Max = *(*p0 + col);
			
			if((*(*p0 + col) > _WhiteMin_) && (*(*p0 + col) < Min))			// 最小值计算
				Min = *(*p0 + col);
		}
		*p1 = (Max + Min)/2 - 10;			// 计算临界值
	}
}

/*******************************************************************************
* 函 数 名 * :	GetMiddle
* 函数功能 * :	中值滤波程序
* 输    入 * :	_INT16U_ a,_INT16U_ b,_INT16U_ c
* 输    出 * :	返回中间值
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
_INT16U_ GetMiddle(_INT16U_ a,_INT16U_ b,_INT16U_ c)
{
	return ((a>b) ? ((b>c) ? b : ((a>c) ? c : a)) : ((a>c) ? a : ((b>c) ? c : b)));		// 计算中值
}

/*******************************************************************************
* 函 数 名 * :	RowDealBit
* 函数功能 * :	二值化采集的图像
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
void RowDealBit(void)
{
	_INT8U_ row,col;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData,*p1 = Threshold;
	
	CountThreshold();	// 计算临界值
	
	for(row = 0;row < _RowMax_;row++,p0++,p1++)		//把所有点二值化
	{
		for(col = 0;col < _ColumnMax_;col++)
		{
			*(*p0 + col) = (*(*p0+col) < *(p1+col)) ? 0 : 255;
		}
	}
}

/*******************************************************************************
* 函 数 名 * :	SearchRight
* 函数功能 * :	搜索对象行右边界
* 输    入 * :	_INT8U_ location,_INT8U_ row,_INT8U_ range
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-4-3
*******************************************************************************/
_INT8U_ SearchRight(_INT8U_ location,_INT8U_ row,_INT8U_ range)
{
	_INT16S_ col,high,low;
	_INT8U_ *p0 = ImageData[row],BlackLineMax,loop;
	
	BlackLineMax = BlackLine[row] + 2;
	
	low  = location - range;		// 计算搜索范围
	if(low < 0)                           low = 0;
	high = location + range;
	if(high > (_ColumnMax_-BlackLineMax)) high = _ColumnMax_-BlackLineMax;
	
	for(col = low;col < high;col += BlackLine[row])
	{
		if(*(p0 + col) < _WhiteMin_) break;		// 遇到黑点直接退出
		
		else if(*(p0 + col) > _WhiteMax_) *(p0 + col)  = _WhiteMax_;	// 限制反光点
		
		if(
			(*(p0 + col) > _WhiteMin_)                             &&		// 白点
			(*(p0 + col + BlackLineMax) < _WhiteMin_)              &&		// 黑点
			((*(p0 + col) - *(p0 + col + BlackLineMax)) > _Contrast_)		// 超过阀值
		  )
		{
			for(loop = 1;loop < BlackLineMax;loop++)
			{
				if(*(p0 + col + loop) < _WhiteMin_) return (col + loop);
			}
		}
	}
	return (_ColumnMax_ - 1);		// 搜线失败
	
	
	
	
	/*
	int  i;                
	int r1,r2;
	uint8 *p0 = ImageData[row];
	
	r1 = location - (int)range; if(r1 < 0)                  r1 = 0;
	r2 = location + (int)range; if(r2 > _ColumnMax_ - 5)    r2 = _ColumnMax_ - 5;
	
	for(i=r1;i<r2;i++)    
	{
		if(*(p0+i) < _WhiteMin_)          break;                    //遇到黑点直接退出   
		else if(*(p0+i) > _WhiteMax_)     *(p0+i) = _WhiteMax_;      //限制反光点
		
		if
		(
			*(p0+i) > _WhiteMin_              &&
			*(p0+i+5) < _WhiteMin_            &&
			((*(p0+i) - *(p0+i+5)) > _Contrast_)
		)			//确保是白点和黑点比较
		{
			return (uint8)i+4;
		}
	}
	return _ColumnMax_-1;     //没找到
	*/
}

/*******************************************************************************
* 函 数 名 * :	SearchLeft
* 函数功能 * :	搜索对象行左边界
* 输    入 * :	_INT8U_ location,_INT8U_ row,_INT8U_ range
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-4-11
*******************************************************************************/
_INT8U_ SearchLeft(_INT8U_ location,_INT8U_ row,_INT8U_ range)
{
	_INT16S_ col,high,low;
	_INT8U_ *p0 = ImageData[row],BlackLineMax,loop;
	
	BlackLineMax = BlackLine[row] + 2;
	
	low = location - range;		// 计算搜索范围
	if(low < BlackLineMax)       low = BlackLineMax;
	high = location + range;
	if(high > (_ColumnMax_ - 1)) high = _ColumnMax_ - 1;
	
	for(col = high;col > low;col -= BlackLine[row])
	{
		if(*(p0 + col) < _WhiteMin_) break;			// 避免单边丢线
		
		if(*(p0 + col) > _WhiteMax_) *(p0 + col) = _WhiteMax_;			//限制反光点
		
		if(
			(*(p0 + col) > _WhiteMin_)                             &&		// 白点
			(*(p0 + col - BlackLineMax) < _WhiteMin_)              &&		// 黑点
			((*(p0 + col) - *(p0 + col - BlackLineMax)) > _Contrast_)		// 大于阀值
		  )
		{
			for(loop = 1;loop < BlackLineMax;loop++)					// 找黑点
			{
				if(*(p0 + col - loop) < _WhiteMin_) return (col - loop);
			}
		}
	}
	return 0;		// 搜线失败
	
	
	
	
	/*
	int  i;
	int r1,r2;
	uint8 *p0 = ImageData[row];
	
	r1 = location - (int)range; if(r1 < 5)               r1 = 5;
	r2 = location + (int)range; if(r2 > (_ColumnMax_-1)) r2 = _ColumnMax_-1;
	
	for(i = r2;i >= r1;i--)
	{
		if(*(p0+i) < _WhiteMin_)        break;       
		else if(*(p0+i) > _WhiteMax_)   *(p0+i) = _WhiteMax_; 
		
		if
		(
			*(p0+i) > _WhiteMin_              &&
			*(p0+i-5) < _WhiteMin_            &&
			((*(p0+i) - *(p0+i-5)) > _Contrast_)
		)
		{
			return (uint8)i-4;
		}
	}
	return 0;     //没找到
	*/
}

/*******************************************************************************
* 函 数 名 * :	FirstSearch
* 函数功能 * :	搜索首行边界
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-2
*******************************************************************************/
void FirstSearch(void)
{
	_INT8U_  srh_end,start_srhr;
	_INT16S_ loop;
	
	LeftFirstRow  = 0;		// 近端左首行
	RightFirstRow = 0;		// 近端右首行
	
	if(RightFirstConfine > _ColumnMax_/3)		// 基础条件
	{
		srh_end = RightCross ? (_SearchStop_+_CrossWide_) : _SearchStop_;		// 十字提前结束搜线
		
		if(LeftBarrierFlag == _Effective_) start_srhr = _SearchRangeMin_;		// 防止搜到障碍边界
		else                               start_srhr = 2*_SearchRangeMax_;
		
		for(loop = (_RowMax_-1);loop >= srh_end;loop--)		// 搜左起始行
		{
			LeftConfine[loop] = SearchLeft(LeftFirstConfine,loop,start_srhr);
			
			if(LeftConfine[loop] && (LeftConfine[loop] < _ColumnMax_*4/5))		// 首行条件
			{
				LeftFirstRow = loop;
				
				LeftFirstConfine = LeftConfine[loop];			// 下一幅搜线参考
				
				if(LeftFirstConfine > _ColumnMax_*3/4)			// 限制参考位置
				{
					LeftFirstConfine = _ColumnMax_*3/4;
				} break;
			}
		}
	}
	
	if(LeftFirstConfine < _ColumnMax_*2/3)		// 基础条件
	{
		srh_end = LeftCross ? (_SearchStop_+_CrossWide_) : _SearchStop_;		// 十字提前结束搜线
		
		if(RightBarrierFlag || StartLineFlag) start_srhr = _SearchRangeMin_;		// 防止搜到障碍边界
		else                                  start_srhr = 2*_SearchRangeMax_;
		
		for(loop = _RowMax_-1;loop >= srh_end;loop--)		// 搜右起始行
		{
			RightConfine[loop] = SearchRight(RightFirstConfine,loop,start_srhr);
			
			if((RightConfine[loop] != (_ColumnMax_-1)) && (RightConfine[loop] > _ColumnMax_/5))
			{
				RightFirstRow = loop;
				
				RightFirstConfine = RightConfine[loop];          // 下一幅搜线参考
				
				if(RightFirstConfine < (_ColumnMax_ / 4))
				{
					RightFirstConfine = _ColumnMax_ / 4;
				} break;
			}
		}
	}
	
	if(RightFirstRow || LeftFirstRow)
	{
		if(RightFirstRow > LeftFirstRow)
		{
			LeftFirstConfine = (LeftFirstConfine < (RightFirstConfine-(_ColumnMax_*2/3))) ? LeftFirstConfine : (RightFirstConfine - _ColumnMax_*2/3);
			
			StartLine = RightFirstRow;
			
			LeftFirstConfine = (_INT8U_)limit_B_C(LeftFirstConfine,_ColumnMax_/15,_ColumnMax_/5);
		}
		else
		{
			RightFirstConfine = (RightFirstConfine > (LeftFirstConfine + (_ColumnMax_*2/3))) ? RightFirstConfine : (LeftFirstConfine + (_ColumnMax_*2/3));
			
			StartLine = LeftFirstRow;
			
			RightFirstConfine = (_INT8U_)limit_B_C(RightFirstConfine,4*_ColumnMax_/5,14*_ColumnMax_/15);
		}
	}
}

/*******************************************************************************
* 函 数 名 * :	SearchImage
* 函数功能 * :	搜索图像的边界值
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无（问题：左右搜线容差不同！！！！）
* 修改时间 * :	2016-4-3
*******************************************************************************/
void SearchImage(void)
{
	_INT16S_ loop = 0;
	_INT8U_ lost_num_l = 0,lost_num_r = 0,leftp,rightp;		// 丢线行数统计，下一行搜线预判
	
	StartLine        = 0;		// 起始行
	sight =   _RowMax_/4;		// 视野
	
	FirstSearch();				// 搜索首行
	
	leftp  = LeftFirstConfine;			// 取搜线参考
	rightp = RightFirstConfine;
	
	if(StartLine > 0)			// 开始搜线
	{
		LeftLost  = _LostMax_;		// 最大允许丢线行
		RightLost = _LostMax_;
		
		for(loop = StartLine;loop >= 0;loop--)
		{
			if(loop < RightFirstRow)			// 从首行开始搜线
			{
				if((lost_num_r < RightLost) && (LeftFirstConfine < (_ColumnMax_*2/3)))		// 范围限制
				{
					RightConfine[loop] = SearchRight(rightp,loop,SearchLineRange[loop]);
					
					if(RightConfine[loop] != (_ColumnMax_ - 1))		// 搜到边界
					{
						if(rightp > 10) rightp = RightConfine[loop];		// 避免左边界
						
						lost_num_r = 0;
						
						RightLost = _LostMax_ - 5;
						
						if((RightConfine[loop] > (_ColumnMax_ - 6)) && (loop < sight))
						{
							lost_num_r = RightLost;
						}
					}
					else lost_num_r++;		// 丢线加1
				}
				else{lost_num_r++;RightConfine[loop] = _ColumnMax_-1;}
			}
			
			if(loop < LeftFirstRow)		// 从左起始行搜索左边界
			{
				if((lost_num_l < LeftLost) && (RightFirstConfine > (_ColumnMax_/3)))		// 范围限制
				{
					LeftConfine[loop] = SearchLeft(leftp,loop,SearchLineRange[loop]);
					
					if(LeftConfine[loop])
					{
						if(leftp < (_ColumnMax_ - 10)) leftp = LeftConfine[loop];
						
						lost_num_l = 0;
						
						LeftLost = _LostMax_ - 5;
						
						if((LeftConfine[loop] < 6) && (loop < sight))
						{
							lost_num_l = LeftLost;
						}
					}
					else lost_num_l++;
				}
				else{lost_num_l++;LeftConfine[loop] = 0;}
			}
			
			//MidcourtLine[loop] = (LeftConfine[loop]+RightConfine[loop]) / 2;
		}
	}
	else for(loop = 0;loop < _RowMax_;loop++)
	{
		LeftConfine[loop]  = 0;
		//MidcourtLine[loop] = _Center_;
		RightConfine[loop] = _ColumnMax_-1;
	}
}

/*******************************************************************************
* 函 数 名 * :	ActiveLine
* 函数功能 * :	计算有效行
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-8
*******************************************************************************/
void ActiveLine(void)
{
	_INT16S_ loop;
	
	if(LeftFirstRow)		// 计算左有效行
	{
		for(loop=0;loop < _RowMax_;loop++)
		{
			if(LeftConfine[loop] != 0)
			{
				LeftEndRow = loop;
				break;
			}
		}
		LeftEffective = LeftFirstRow - LeftEndRow + 1;
	}
	else {LeftEffective = 0;LeftEndRow = 0;}
	
	if(RightFirstRow)		// 计算右有效行
	{
		for(loop=0;loop < _RowMax_;loop++)
		{
			if(RightConfine[loop] != (_ColumnMax_ - 1))
			{
				RightEndRow = loop;
				break;
			}
		}
		RightEffective = RightFirstRow - RightEndRow + 1;
	}
	else {RightEffective = 0;RightEndRow = 0;}
	
	AmountEffective = RightEffective + LeftEffective;
}

/*******************************************************************************
* 函 数 名 * :	LeftSlopeCou
* 函数功能 * :	计算左边斜率，放大100倍
* 输    入 * :	_INT8U_ row_ks,_INT8U_ row_ke
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-24
*******************************************************************************/
_INT16S_ LeftSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke)
{
	/* 一元线性回归最小二乘法求斜率 */
	_INT16S_ aver_x,aver_y;		// 行、列平均值
	_FP32_ x_num = 0,y_num = 0;			// 斜率总和值
	_INT8U_ change,rowledge;
	
	rowledge = (_INT8U_)MyAbs(row_ks - row_ke);			// 行距
	
	if(rowledge >= 2)	// 行距达到两行及以上
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])	// 左边丢线判断
		{
			aver_x = (row_ks + row_ke) / 2;
			aver_y = (LeftConfine[row_ks] + LeftConfine[row_ke]) / 2;
			
			if(row_ks < row_ke) {change = row_ks;row_ks = row_ke;row_ke = change;}
			
			for(;row_ke <= row_ks;row_ke++)		// 计算左斜率
			{
				if(LeftConfine[row_ke])
				{
					y_num += (row_ke-aver_x) * (LeftConfine[row_ke]-aver_y);
					x_num += (row_ke-aver_x) * (row_ke-aver_x);
				}
			}
			return (_INT16S_)(-100 * y_num / x_num);
		}
		else return 0;
	}
	else if(rowledge)	// 相邻两行
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])
		{
			return (_INT16S_)(100 * (LeftConfine[row_ke]-LeftConfine[row_ks]) / rowledge);	// 左边丢线判断
		}
		else return 0;
	}
	else return 0;
	
	
	
	/* 三点法计算斜率 */
	/*
	int  kc,ks,ke;
	int  t,row_effect;  
	row_effect = row_ks-row_ke;
	
	if(row_effect >= 3)
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])					// 左边斜率
		{
			ks = LeftConfine[row_ks];
			ke = LeftConfine[row_ke];
			kc = LeftConfine[row_ke*2/3 + row_ks/3];
			if(kc == 0)       kc = (ks+ke)/2;
		}
		t = ( 0*ke + 5 * kc - 5 * ks) * 20 / row_effect;		// 计算斜率
	}
	else if(row_effect)
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])			// 左边斜率
		{
			ks = LeftConfine[row_ks];
			ke = LeftConfine[row_ke];
		}
		t = (ke - ks) * 100 / row_effect;
	}
	else    t = 0;
	return  t;
	*/
}

/*******************************************************************************
* 函 数 名 * :	RightSlopeCou
* 函数功能 * :	计算右边斜率，放大100倍
* 输    入 * :	_INT8U_ row_ks,_INT8U_ row_ke
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-24
*******************************************************************************/
_INT16S_ RightSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke)
{
	/* 一元线性回归最小二乘法求斜率 */
	_INT16S_ aver_x,aver_y;		// 行、列平均值
	_FP32_ x_num = 0,y_num = 0;			// 斜率总和值
	_INT8U_ change,rowledge;
	
	rowledge = (_INT8U_)MyAbs((row_ks - row_ke));	// 行距
	
	if(rowledge >= 2)	// 行距达到两行及以上
	{
		if((RightConfine[row_ks] != (_ColumnMax_-1)) && (RightConfine[row_ke] != (_ColumnMax_-1)))	// 右边丢线判断
		{
			aver_x = (row_ks + row_ke) / 2;
			aver_y = (RightConfine[row_ks] + RightConfine[row_ke]) / 2;
			
			if(row_ks < row_ke) {change = row_ks;row_ks = row_ke;row_ke = change;}
			
			for(;row_ke <= row_ks;row_ke++)		// 计算右斜率
			{
				if(RightConfine[row_ke] != (_ColumnMax_-1))
				{
					y_num += (row_ke-aver_x) * (RightConfine[row_ke]-aver_y);
					x_num += (row_ke-aver_x) * (row_ke-aver_x);
				}
			}
			return (_INT16S_)(-100 * y_num / x_num);
		}
		else return 0;
	}
	else if(rowledge)	// 相邻两行
	{
		if((RightConfine[row_ks] != (_ColumnMax_-1)) && (RightConfine[row_ke] !=(_ColumnMax_-1)))	// 右边丢线判断
		{
			return (_INT16S_)(100 * (RightConfine[row_ke]-RightConfine[row_ks]) / rowledge);	// 右边丢线判断
		}
		else return 0;
	}
	else return 0;
	
	
	
	/* 三点法计算斜率 */
	/*
	int  kc,ks,ke;
	int  t,row_effect;
	row_effect = row_ks-row_ke;
	
	if(row_effect >= 3)
	{
		if(RightConfine[row_ks] != _ColumnMax_-1 && RightConfine[row_ke] != _ColumnMax_-1 )   //右边斜率
		{
			ks = RightConfine[row_ks];
			ke = RightConfine[row_ke];
			kc = RightConfine[row_ke*2/3 + row_ks/3];   //修改-->不等距分布，选取2/3的位置
			if(kc == _ColumnMax_-1)   kc = (ks+ke)/2 ;
		}
		t = ( 0*ke + 5 * kc - 5 * ks) * 20 / row_effect;//计算斜率
	}
	else if(row_effect)
	{
		if(RightConfine[row_ks] != _ColumnMax_-1 && RightConfine[row_ke] != _ColumnMax_-1)
		{
			ks = RightConfine[row_ks];                                      //右边斜率
			ke = RightConfine[row_ke];
		}
		t = (ke - ks) * 100 / row_effect;
	}
	else    t = 0;
	return  t;
	*/
}
/*******************************************************************************
* 函 数 名 * :	CalculateSlope
* 函数功能 * :	计算斜率
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
void CalculateSlope(void)
{
	_INT16S_ loop,far,far1;
	
	if(LeftFirstRow)
	{
		LeftInflexion = LeftFirstRow;
		
		far = (LeftEndRow < _SlopeFarthest_) ? _SlopeFarthest_ : LeftEndRow;
		
		for(loop = (LeftFirstRow - 1);loop >= far;loop--)			// 搜索左拐点
		{
			if(LeftConfine[loop] > LeftConfine[LeftInflexion])
			{
				LeftInflexion = loop;
			}
		}
		
		far1 = 2*LeftInflexion - LeftFirstRow;
		far1 = (far1<0) ? far : ((far1>far) ? far1 : far);
		
		if(LeftConfine[far1] == 0) LeftConfine[far1] = LeftConfine[LeftFirstRow];
		
		LeftFarSlope  = LeftSlopeCou(LeftInflexion,far1);			// 远端斜率 
		LeftNearSlope = LeftSlopeCou(LeftFirstRow,LeftInflexion);	// 近端斜率 
	}
	else {LeftFarSlope = 0;LeftNearSlope = 0;}
	
	if(RightFirstRow)
	{
		RightInflexion = RightFirstRow;
		far = (RightEndRow < _SlopeFarthest_) ? _SlopeFarthest_ : RightEndRow;
		 
		for(loop = (RightFirstRow - 1);loop >= far;loop--)			// 搜索右拐点
		{
			if(RightConfine[loop] < RightConfine[RightInflexion])
			{
				RightInflexion = loop;
			}
		}
		
		far1 = 2*RightInflexion - RightFirstRow;
		far1 = (far1<0) ? far : ((far1>far) ? far1 : far);
		
		if(RightConfine[far1] == (_ColumnMax_ - 1))
		{
			RightConfine[far1] = RightConfine[RightFirstRow];
		}
		
		RightFarSlope = RightSlopeCou(RightInflexion,far1);					//远端斜率 
		RightNearSlope = RightSlopeCou(RightFirstRow,RightInflexion);		//近端斜率
	}
	else {RightFarSlope = 0;RightNearSlope = 0;}
}

/*******************************************************************************
* 函 数 名 * :	CrossFilter
* 函数功能 * :	十字滤波
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无（问题：如何提前检测到十字，并且不误检。。。）
* 修改时间 * :	2016-3-30
*******************************************************************************/
void CrossFilter(void)
{
	_INT8U_ cou;
	_INT16S_ loop;
	
	if((HillFlag == _Void_) && ((LeftCross == _Void_) || (RightCross == _Void_)))
	{
		cou = 0;		// 清零
		if(RightFarSlope && RightNearSlope && (RightInflexion > 30) && (RightInflexion < 70) && (RightCross == _Void_))		// 右十字判定
		{
			for(loop = (RightInflexion - 1);loop >= (RightInflexion - 6);loop--)		// 入十字弯识别
			{
				if(((RightConfine[loop] - RightConfine[loop + 1]) > 3) && (RightConfine[loop] != (_ColumnMax_ - 1)))		// 提取十字特征
				{
					cou++;
				}
				if(cou > 2) {RightCross = _Effective_;break;}
				_16u[1] = cou;
			}
			
			if(
				(RightConfine[RightInflexion + 5] != (_ColumnMax_ - 1))                 &&		// 出十字弯识别
				(RightConfine[RightInflexion - 5] != (_ColumnMax_ - 1))                 &&
				((RightConfine[RightInflexion - 5] - RightConfine[RightInflexion]) > 6) &&
				((RightConfine[RightInflexion + 5] - RightConfine[RightInflexion]) > 6)
			  ) RightCross = _Effective_;
		}
		
		cou = 0;		// 清零
		if(LeftFarSlope && LeftNearSlope && (LeftInflexion > 30) && (RightInflexion < 70) && (LeftCross == _Void_))			// 左十字判定
		{
			for(loop = (LeftInflexion-1);loop >= (LeftInflexion-6);loop--)		// 入十字弯识别
			{
				if(((LeftConfine[loop] - LeftConfine[loop - 1]) > 3) && LeftConfine[loop])		// 提取十字特征
				{
					cou++;
				}
				if(cou > 2) {LeftCross = _Effective_;break;}
				_16u[0] = cou;
			}
			
			if(
				LeftConfine[LeftInflexion + 5]                                      &&		// 出十字弯识别
				LeftConfine[LeftInflexion - 5]                                      &&
				((LeftConfine[LeftInflexion] - LeftConfine[LeftInflexion + 5]) > 6) &&
				((LeftConfine[LeftInflexion] - LeftConfine[LeftInflexion - 5]) > 6)
			  ) LeftCross = _Effective_;
		}
	}
	
	if(LeftCross && (!LeftEffective  || ((RightFirstRow < 100) && (RightFirstRow > 70) && (RightEffective > 30))))		// 十字弯解锁
	{
		LeftCross = _Void_;
		
		//CrossArea = LeftArea;
	}
	if(RightCross && (!RightEffective || ((LeftFirstRow < 100) && (LeftFirstRow > 70) && (LeftEffective > 30))))  
	{
		RightCross = _Void_;
		
		//CrossArea = RightArea;
	}
}

/*******************************************************************************
* 函 数 名 * :	FillingLine
* 函数功能 * :	补线
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
void FillingLine(void)
{
	bool cps = false;
	_INT16S_ loop,far=0;
	_FP32_ slope,last_slope;	// 斜率寄存
	_INT8U_ buffer2 = 0;
	_FP32_ buffer1 = 0;		// 数据寄存
	
	if(
		((LeftEffective > 10) && (LeftCross == _Void_))     ||		// 非十字，有效行 > 10行
		(LeftCross && ((_RowMax_ - 1 - LeftInflexion) > 10))		// 十字在远处
	  )			// 补左黑线
	{
		buffer1 = LeftNearSlope/100.0f;
		buffer2 = LeftConfine[LeftFirstRow];
		
		for(loop = (LeftFirstRow - 1);loop > LeftEndRow;loop--)			// 补左有效行范围内黑线
		{
			if(LeftConfine[loop] == 0)
			{
				LeftConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(buffer2+buffer1),0,(_ColumnMax_ - 5));
			}
			else
			{
				buffer2 = LeftConfine[loop];buffer1 = 0;
			}
			
			buffer1 += LeftNearSlope/100.0f;
		}
		
		if(LeftFarSlope && LeftNearSlope && (LeftCross == _Void_)) slope =  LeftFarSlope;		// 非十字弯道
		else                                                       slope = LeftNearSlope;
		
		if(slope < 0) slope = 0;			// 斜率限制
		//last_slope = slope;
		
		if(LeftCross) far = LeftInflexion;
		else          far = LeftEndRow;
		
		buffer1 = slope/100.0f;
		
		for(loop = (far-1);loop >= 0;loop--)		// 远端补线(结束行以外黑线)
		{
			LeftConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(LeftConfine[far]+buffer1),0,(_ColumnMax_ - 5));
			/*
			slope = LeftCross ? slope*102/100 : slope;		// 十字每行斜率提升5%
			
			if(slope > 2*last_slope) slope = 2*last_slope;			// 限制最大斜率
			*/
			buffer1 += slope/100.0f;
			
			if(LeftConfine[loop] > (_ColumnMax_ - 10))			// 靠近边缘
			{
				cps = true;
				break;
			}
		}
		
		if((cps == true) && (loop > 0))			// 靠近图像边缘，直接填充
		{
			for(;loop >= 0;loop--)
			{
				LeftConfine[loop] = LeftConfine[loop+1];
			}
			cps = false;					// 清除标志
		}
	}
	
	if(
		((RightEffective > 10) && (RightCross == _Void_))     ||		// 非十字，有效行 > 10行
		(RightCross && ((_RowMax_ - 1 - RightInflexion) > 10))		// 十字在远处
	  )			// 补右
	{
		buffer1 = RightNearSlope/100.0f;
		buffer2 = RightConfine[RightFirstRow];
		
		for(loop = (RightFirstRow - 1);loop > RightEndRow;loop--)		// 补右有效行范围黑线
		{
			if(RightConfine[loop] == (_ColumnMax_-1))
			{
				RightConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(buffer2+buffer1),5,(_ColumnMax_ - 1));
			}
			else
			{
				buffer2 = RightConfine[loop];buffer1 = 0;
			}
			
			buffer1 += RightNearSlope/100.0f;
		}
		
		if(RightFarSlope && RightNearSlope && (RightCross == _Void_)) slope = RightFarSlope;		// 非右十字
		else                                                          slope = RightNearSlope;
		
		if(slope > 0) slope = 0;		// 限制右斜率
		//last_slope = slope;
		
		if(RightCross) far = RightInflexion;
		else           far = RightEndRow;
		
		buffer1 = slope/100.0f;
		
		for(loop = (far-1);loop >= 0;loop--)
		{
			RightConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(RightConfine[far]+buffer1),5,(_ColumnMax_ - 1));
			/*
			slope = RightCross ? slope*102/100 : slope;		// 十字每行斜率提升5%
			
			if(slope < 2*last_slope) slope = 2*last_slope;			// 限制最大斜率
			*/
			buffer1 += slope/100.0f;
			
			if(RightConfine[loop] < 10)			// 靠近边缘
			{
				cps = true;
				break;
			}
		}
		if(cps && (loop > 0))			// 靠近图像边缘，直接填充
		{
			for(;loop >= 0; loop--)
			{
				RightConfine[loop] = RightConfine[loop+1];
			}
			cps = false;			// 清除标志
		}
	}
}

/*******************************************************************************
* 函 数 名 * :	CouBlackArea
* 函数功能 * :	计算赛道黑点面积
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-3-30
*******************************************************************************/
void CouBlackArea(void)
{
	_INT8U_ loop,clp;
	_INT16S_ black;
	
	AreaEndLine = _RowMax_ - _LineArea_;		// 计算面积终止行
	
	if(LeftCross)  LeftArea  = limit1(LeftArea,600);		// 十字处理
	else           LeftArea  = 0;
	
	if(RightCross) RightArea  = limit1(RightArea,600);
	else           RightArea   = 0;
	
	if(
		((LeftEffective > 10) && (LeftCross == _Void_))    ||	// 有效行 > 10行，非十字
		(
			LeftCross                        &&			// 十字弯在远端
			(LeftFirstRow > 95)              &&
			(LeftFirstRow - LeftInflexion) > 10
		)
	  )		// 算左面积
	{
		LeftArea = 0;
		for(loop = LeftFirstRow;loop >= AreaEndLine;loop--)
		{
			black = LeftConfine[loop] - LeftTrapezoid[loop];
			
			black = (_INT8U_)limit_B_C(black,0,2*(_Center_ - LeftTrapezoid[loop]));
			
			LeftArea += black;
		}
	}
	
	if(
		((RightEffective > 10) && (RightCross == _Void_))    ||			// 有效行 > 10行，非十字
		(
			RightCross                         &&			// 十字弯在远端
			(RightFirstRow > 95)               &&
			(RightFirstRow - RightInflexion) > 10
		)
	  )			// 计算右面积
	{
	    RightArea = 0;
	    for(loop = RightFirstRow;loop >= AreaEndLine;loop--)
	    {
	        black = RightTrapezoid[loop] - RightConfine[loop];
	        
	        black = (_INT8U_)limit_B_C(black,0,2*(RightTrapezoid[loop] - _Center_));
			
	        RightArea += black;
	    }
	}
	
	if(HillFlag)   // 坡道
	{
		LeftArea  = LeftArea/3;			// 2
		RightArea = RightArea/3;		// 2
	}
	
	if(BarrierRow < 100)  		// 越靠近障碍越小
	{
		if(LeftBarrierFlag)		// 左障碍
		{
			clp = _Center_ - BarrierCol;
			LeftArea += (800 - clp*5);
			RightArea = RightArea/2;
		}
		
		if(RightBarrierFlag)	// 右障碍
		{
			clp = BarrierCol - _Center_;
			RightArea += (800 - clp*5);
			LeftArea   = LeftArea/2;
		}
	}
	
	if(LeftBarrierBuffer)		// 障碍解锁，平缓转角
	{
		LeftArea  += LeftBarrierBuffer*35;
		RightArea  = RightArea*(40 - LeftBarrierBuffer)/40;
		LeftBarrierBuffer--;
	}
	if(RightBarrierBuffer)
	{
		RightArea += RightBarrierBuffer*35;
		LeftArea   = LeftArea*(40 - RightBarrierBuffer)/40;
		RightBarrierBuffer--;
	}
	
	offset = LeftArea - RightArea;
	CorrectOffset = offset - OldOffset;
	
	if(LeftBarrierFlag || RightBarrierFlag) CorrectOffset = CorrectOffset/3;		// 遇到障碍，取消D量，消抖
	
	OldOffset = offset;
	offset = limit1(offset,3000);
	CorrectOffset = limit1(CorrectOffset,300);
}

/*******************************************************************************
* 函 数 名 * :	WhiteWide
* 函数功能 * :	计算赛道宽度
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-12
*******************************************************************************/
void WhiteWide(void)
{
	_INT8S_ loop;
	
	for(loop = 0;loop < _RowMax_;loop++)
	{
		if(LeftConfine[loop] && (RightConfine[loop] != (_ColumnMax_ - 1)))
			TrackWide[loop] = RightConfine[loop] - LeftConfine[loop];
		else
			TrackWide[loop] = 250;
	}
}

/*******************************************************************************
* 函 数 名 * :	CheckHill
* 函数功能 * :	坡道检测
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-12
*******************************************************************************/
void CheckHill(void)
{
	_INT16U_ loop,sum = 0;
	
	for(loop = 5;loop < 30;loop++)		// 1m 开始检测
	{
		if(TrackWide[loop] != 250)
		{
			sum += TrackWide[loop];
		}
	}
	_16u[0] = sum;
    /*
	if(
			!HillFlag                      &&
			(sum > 1500)                   &&		// 赛道宽度
			(sum < 2500)                   &&
			(LeftActive > 115)             &&		// 有效行
			(AmountActive < 230)           &&
			((MoveTime - OnHillTime) >= 2) &&		// 检测时间
			MyAbs(LeftNearSlope)  < 100    &&		// 斜率
			MyAbs(RightNearSlope) < 50     &&
			((MyAbs(LeftNearSlope) + MyAbs(RightNearSlope)) < 100) &&
			LeftFarSlope < 10              &&
			RightFarSlope < 10
	  )
	*/
	if(
	      !HillFlag                      &&
	      (sum > 1500)                   &&		// 赛道宽度
	      (sum < 2500)                   &&
	      (LeftEffective  > 115)         &&		// 上坡道前端逐渐丢图
	      (RightEffective > 115)         &&		// 减少坡道误检测
	      ((MoveTime - OnHillTime) >= 2) &&		// 坡道不连续检测
		  (MyAbs(LeftNearSlope)  < 70)   &&		// 斜率限制
		  (MyAbs(RightNearSlope) < 70)   &&
		  (MyAbs(LeftFarSlope)   < 10)   &&
		  (MyAbs(RightFarSlope)  < 10)
	  )
	{
		HillFlag = 1;
		OnHillDistance = CarMove;
	}
	
	if(HillFlag && ((CarMove - OnHillDistance) > 20000))		// 解锁
	{
		HillFlag = 0;
		OnHillTime = MoveTime;
	}
}

/*******************************************************************************
* 函 数 名 * :	CheckStartLine
* 函数功能 * :	起跑线检测
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-13
*******************************************************************************/
void CheckStartLine(void)
{
	_INT8U_ loop;
	_INT8U_ x1 = 0,x2 = 0,x3 = 0,x4 = 0;	// 起跑线端点
	
	for(loop = 1;loop < (_ColumnMax_ - 1);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop - 1] > 7)  
		{x1 = loop;break;}
	}
	
	for(loop = x1;loop < (_ColumnMax_ - 1);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop + 1] > 7)
		{x2 = loop;break;}
	}
	
	for(loop = x2 + 1;loop < (_ColumnMax_ - 1);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop - 1] > 20)  
		{x3 = loop;break;}
	}
	
	for(loop = x3;loop < (_ColumnMax_ - 1);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop + 1] > 7)
		{x4 = loop;break;}
	}
	
	if(
			(MoveTime >=  2)   &&			// 小车行驶2s后检测
			(!StartLineFlag)   &&
			((x2 - x1) < 31)   &&         // 30
			((x2 - x1) >  8)   &&         //  5
			((x3 - x2) >  7)   &&         //  8
    		((x3 - x2) < 28)   &&         // 30
			((x4 - x3) < 31)   &&         // 30
			((x4 - x3) >  8)              //  5
	   )				// 起跑线判断
	{
		StartLineFlag = _Effective_;
		StartLineTime = AccuracyTime;
	}
	
	if(StartLineFlag && ((AccuracyTime-StartLineTime) > 200))		// 停止提示
	{
		StartLineFlag = _Void_;
	}
}

/*******************************************************************************
* 函 数 名 * :	SearchLength
* 函数功能 * :	计算最远点距离
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	测得远端直道33列 = RightConfine[0] - LeftConfine[0]
* 修改时间 * :	2016-6-22
*******************************************************************************/
void SearchLength(void)
{
	//bool flag;
	_INT16U_ buffer = 0;
	_INT8U_ row,col;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData;
	
	/* 长直道识别程序 */
	/*
	for(row = 0;row < _RowMax_;row++,p0++)			// 扫描中间n列图像
	{
		for(col = (_Center_ - _LengthRange_);col <= (_Center_ + _LengthRange_);col++)
		{
			flag = (*(*p0 + col) > _WhiteMin_) ? true : false;
			
			if(flag == false) break;
		}
		if(flag == false) break;
	}
	
	if(
			(LeftArea  < 50) &&		// 面积严格限制
			(RightArea < 50) &&
			(flag == true)			// 中间矩形全白点
	  )
	{
		WhiteLength = _Active_;
	}
	else
	{
		WhiteLength = _Void_;
	}
	*/
	
	for(col = 0;col <= (_ColumnMax_ - 1);col++)			// 获取每列近端首个黑点位置
	{
		p0 = ImageData + _RowMax_ - 1;
		for(row = (_RowMax_ - 1);row > 2;row--,p0--)
		{
			if(*(*p0 + col) < _WhiteMin_)
			{
				WhiteLengthNear[col] = row;
				break;
			}
		}
		if(row == 2) WhiteLengthNear[col] = 0;
	}
	
	for(col = (_Center_ - _LengthRange_);col <= (_Center_ + _LengthRange_);col++)
	{
		buffer += WhiteLengthNear[col];				// 累加首个黑点所在行
	}
	
	buffer /= (_LengthRange_ * 2 + 1);				// 算黑点位置平均值
	
	WhiteLength = 0;
	for(row = (_RowMax_ - 1);row > buffer;row--)
	{
		WhiteLength += (_RowMax_-1) / (row+1);		// 0 ~ 470
	}
	
	CorrectWhiteLength = WhiteLength - OldWhiteLength;
	
	OldWhiteLength = WhiteLength;
}

/*******************************************************************************
* 函 数 名 * :	CheckBarrier
* 函数功能 * :	障碍检测
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-16 
*******************************************************************************/
void CheckBarrier(void)
{
	_INT8U_ loop = 0;
	_INT8U_ y1 = 0,y2 = 0,y3 = 0,y4 = 0;		// 具体坐标
	_INT8U_ x = 0,y = 0;						// 点坐标
	
	for(loop = 0;loop < (_ColumnMax_ - 3);loop++)
	{
		if(WhiteLengthNear[loop + 1] - WhiteLengthNear[loop] > 6)
		{
			y1 = loop + 1;break;
		}
	}
	if(y1) for(loop = y1;loop < (_ColumnMax_ - 3);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop + 1] > 6)
		{
			y2 = loop;break;
		}
	}
	if(y2) for(loop = y2;loop < (_ColumnMax_ - 3);loop++)
	{
		if(WhiteLengthNear[loop + 1] - WhiteLengthNear[loop] > 6)
		{
			y3 = loop + 1;break;
		}
	}
	if(y3) for(loop = y3;loop < (_ColumnMax_ - 3);loop++)
	{
		if(WhiteLengthNear[loop] - WhiteLengthNear[loop + 1] > 6)
		{
			y4 = loop;break;
		}
	}
	
	y = (y1 + y2) / 2;
	x = WhiteLengthNear[y];
	
	BarrierRow = 0;		// 似乎此操作是多余的
	
	if(
			(HillFlag == _Void_)               &&		// 非坡道
			(y4 == 0)                          &&
			((y2 - y1) > 10)                   &&		// 14
			((y2 - y1) < 40)                   &&
			(ImageData[x - 3][y] < _WhiteMin_) &&
			(LeftBarrierFlag  == _Void_)       &&		// 非障碍
			(RightBarrierFlag == _Void_)
	   )
	{
		if(
				(
					(LeftConfine[x + 4] != 0)                           &&		// 没丢边线条件
					(RightConfine[x + 4] != (_ColumnMax_ -1))           &&
					((y - LeftConfine[x + 4]) < (RightConfine[x + 4] - y))
				)                                                             ||
				(
					(LeftConfine[x + 4] == 0)              &&						// 某边丢线条件
					(RightConfine[x + 4] != (_ColumnMax_ -1))
				)
		  )
		{
			LeftBarrierFlag  = _Effective_;
		}
		else
		{
			RightBarrierFlag = _Effective_;
		}
	}
	
    if(LeftBarrierFlag || RightBarrierFlag)
	{
		BarrierRow = WhiteLengthNear[y2];
		/*
		
		if(LeftBarrierFlag) BarrierCol = y2;
		else                BarrierCol = y1;
		
		*/
		BarrierCol = y;
		LeftBarrierBuffer = 0;
		RightBarrierBuffer = 0;
		if(BarrierRow > 100) BarrierRow = 100;
		else BarrierShift = CarMove;
	}
	
	if((CarMove - BarrierShift) > 3000)				// 解锁
	{
		if(RightBarrierFlag) {RightBarrierFlag = _Void_;RightBarrierBuffer = 20;}
		if (LeftBarrierFlag) {LeftBarrierFlag  = _Void_;LeftBarrierBuffer  = 20;}
	}
}

/*******************************************************************************
* 函 数 名 * :	OverlapFilter
* 函数功能 * :	重叠滤波
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-5-22
*******************************************************************************/
void OverlapFilter(void)
{
	bool flag = false;
	_INT8S_ loop = 0;
	
	if(HillFlag) return;		// 坡道避免
	
	for(loop = (_RowMax_-1);loop >= 30;loop--)					// 行搜索
	{
		if((RightConfine[loop] != (_ColumnMax_ - 1)) && LeftConfine[loop])		// 左右不丢线
		{
			if( RightConfine[loop] - LeftConfine[loop] < 3)			// 左右边线间距
			{
				flag = true;
			}
			else if((RightConfine[loop] - LeftConfine[loop]) < (ConfineDistance[loop] - 20))		// 去除有效行少的一边
			{
				if(LeftEffective < RightEffective) LeftConfine[loop]  = 0;
	    		else                               RightConfine[loop] = _ColumnMax_-1;
	    	}
		}
	}
	
	if(
			(LeftFirstRow < RightEndRow)                                &&		// 丢左半边图
			((RightConfine[RightEndRow] - LeftConfine[LeftFirstRow]) < 30)
	  ) flag = true;
	
	if(
			(RightFirstRow < LeftEndRow)                                &&		// 丢右半边图
			((RightConfine[RightFirstRow] - LeftConfine[LeftEndRow]) < 30)
	  ) flag = true;
	
	if(flag == true)
	{
		if(LeftFirstRow < RightFirstRow)
		{
			for(loop = (_RowMax_ - 1);loop >= 0;loop--)
			{
				LeftConfine[loop] = 0;
			}
			LeftEffective = 0;
			LeftFirstRow = 0;
			LeftEndRow = 0;
		}
		else
		{
			for(loop = (_RowMax_ - 1);loop >= 0;loop--)
			{
				RightConfine[loop] = _ColumnMax_-1;
			}
			RightEffective = 0;
			RightFirstRow = 0;
			RightEndRow = 0;
		}
	}
	
	if(!LeftFirstRow && RightFirstRow)			// 取起始行
	{
		LeftFirstConfine  = (_INT8U_)limit_B_C(RightFirstConfine-_ColumnMax_*2/3,_ColumnMax_/15,_ColumnMax_/5);
	}
	else if(LeftFirstRow && !RightFirstRow)
	{
		RightFirstConfine = (_INT8U_)limit_B_C( LeftFirstConfine+_ColumnMax_*2/3,4*_ColumnMax_/5,14*_ColumnMax_/15);
	}
}

/*******************************************************************************
* 函 数 名 * :	MCU_sqrt
* 函数功能 * :	MCU快速开平方
* 输    入 * :	_INT32U_ M
* 输    出 * :	开平方值
* 说    明 * :	平均运行速度为C库函数sqrt()的2.5倍，值越大运行越慢；
				C库函数sqrt()几乎不受数值大小影响，平均运行周期7.5us
* 修改时间 * :	2016-6-3
*******************************************************************************/
_INT16U_ MCU_sqrt(_INT32U_ M)
{
	_INT8U_  Byte = 0,loop = 0;
	_INT16U_ value = 1,a = 0,b = 0;
	_INT32U_ cou = 0;
	
	if(M == 0) return 0;
	
	cou = M;
	
	while(cou != 0)			// 计算 M 位数
	{
		cou >>= 1;
		Byte++;
	}
	
	Byte = (Byte % 2) ? ((Byte + 1) >> 1) : (Byte >> 1);		// 折半
	
	b = M - (1 << ((Byte - 1) << 1));
	
	for(loop = (Byte - 1);loop > 0;loop--)
	{
		value <<= 1;
		a = ((value << 1) + 1) * (1 << ((loop - 1) << 1));
		if(b >= a)
		{
			value += 1;
			b -= a;
		}
	}
	return value;
}

/*******************************************************************************
* 函 数 名 * :	curvature
* 函数功能 * :	三点计算曲率
* 输    入 * :	_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3
* 输    出 * :	曲率的倒数
* 说    明 * :	负：顺时针，正：逆时针
* 修改时间 * :	2016-6-3
*******************************************************************************/
_INT16S_ curvature(_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3)
{
	_INT16S_ area,curl;
	_INT16U_ length1,length2,length3;
	
	area = (y2 - y1) * (x3 - x1) - (y3 - y1) * (x2 - x1);		// 三角形面积加倍
	
	length1 = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	length2 = (x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1);
	length3 = (x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3);
	
	curl = (_INT16S_)sqrt(length1*length2*length3) / (area<<1);			// 取曲率的倒数
	
	return curl;
}

/*******************************************************************************
* 函 数 名 * :	CrossFillingLine
* 函数功能 * :	十字补线
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-7
*******************************************************************************/
void CrossFillingLine(void)
{
	_INT8S_ i;
	_INT8U_ row,line,line_tp;
	_FP32_ slope,buffer;
	
	if(RightCross)			// 右十字
	{
		row = 0;
		buffer = 0;
		line_tp = RightConfine[RightInflexion-15];
		
		for(i = (RightInflexion-15);i >= 0;i--)		// 搜十字远端边线
		{
			line = SearchRight(line_tp,i,SearchLineRange[i]);
			if(line != (_ColumnMax_ - 1))
			{
				RightConfine[i] = line;
				
				if(row == 0) row = i;
				
				line_tp = line;
			}
			else line_tp = RightConfine[i];
		}
		
		slope = ((_FP32_)RightConfine[row]-RightConfine[RightInflexion]) / (RightInflexion-row);
		
		for(i = (RightInflexion-1);i > row;i--)		// 补十字
		{
			buffer += slope;
			
			RightConfine[i] = (_INT8U_)(RightConfine[RightInflexion] + buffer);
		}
	}
	
	if(LeftCross)
	{
		row = 0;
		buffer = 0;
		line_tp = LeftConfine[LeftInflexion-15];
		
		for(i = (LeftInflexion-15);i >= 0;i--)		// 搜十字远端边线
		{
			line = SearchLeft(line_tp,i,SearchLineRange[i]);
			if(line)
			{
				LeftConfine[i] = line;
				
				if(row == 0) row = i;
				
				line_tp = line;
			}
			else line_tp = LeftConfine[i];
		}
		
		slope = ((_FP32_)LeftConfine[row]-LeftConfine[LeftInflexion]) / (LeftInflexion-row);
		
		for(i = (LeftInflexion-1);i > row;i--)		// 补十字
		{
			buffer += slope;
			
			LeftConfine[i] = (_INT8U_)(LeftConfine[LeftInflexion] + buffer);
		}
	}
}

/*******************************************************************************
* 函 数 名 * :	BigArc
* 函数功能 * :	大弧
* 输    入 * :	无
* 输    出 * :	无
* 说    明 * :	无
* 修改时间 * :	2016-6-7
*******************************************************************************/
void BigArc(void)
{
	if(
			MyAbs(offset) > 1000         &&			// 面积范围
			MyAbs(offset) < 2100         &&
			!RightFarSlope               &&
			!LeftFarSlope                &&
			!(LeftNearSlope*RightNearSlope)
	   )
	{
		if(
			(
				(RightEffective > RightArea / 25 + 52) &&
				(RightEffective < RightArea / 25 + 88) &&
				(LeftEffective  < RightEffective + 25)
			)                                           ||
			(
				(LeftEffective  > LeftArea / 25 + 52)   &&
				(LeftEffective  < LeftArea / 25 + 88)   &&
				(RightEffective < LeftEffective + 25)
			)
	      )
		{
			BigArcFlag = _Effective_;
		}
	    else
		{
			BigArcFlag = _Void_;
		}
	}
}
