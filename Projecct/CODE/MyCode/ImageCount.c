#include "headfile.h"
_INT8U_ SearchRight(_INT8U_ location,_INT8U_ row,_INT8U_ range);	// �����ұ߽�
_INT8U_ SearchLeft(_INT8U_ location,_INT8U_ row,_INT8U_ range);		// ������߽�

_INT16S_ LeftSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke);				// ������б�ʣ��Ŵ�10��
_INT16S_ RightSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke);				// ������б�ʣ��Ŵ�10��

void FirstSearch(void);			// �������б߽�



/*******************************************************************************
* �� �� �� * :	download
* �������� * :	����ͼ��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-4-4
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
* �� �� �� * :	Standard
* �������� * :	�����׼����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-20
*******************************************************************************/
void Standard(void)
{
	_INT16S_ loop;
	
	for(loop = 0;loop < _RowMax_;loop++)
	{
		/* �������� */
		LeftTrapezoid[loop]   = _Center_ - (_AreaRangeMin_ + (_AreaRangeMax_-_AreaRangeMin_)*(loop+1)/_RowMax_);
		/* �������� */
		RightTrapezoid[loop]  = _Center_ + (_AreaRangeMin_ + (_AreaRangeMax_-_AreaRangeMin_)*(loop+1)/_RowMax_);
		/* ���߰뾶 */
		SearchLineRange[loop] = (_INT8U_)limit_B_C((_SearchRangeMax_ - (_RowMax_-1-loop)/5),_SearchRangeMin_,_SearchRangeMax_);
	}
}

/*******************************************************************************
* �� �� �� * :	CarProtect
* �������� * :	����С���������졢�ܷɣ���ʱͣ��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-4-4
*******************************************************************************/
void CarProtect(void)
{
	bool out = false;
	_INT8U_ *p0;
	_INT16S_ row,loop;
	
	if(1)//(MoveTime >= 1)			// ����1s����
	{
		for(row = (_RowMax_ - 1);row > (_RowMax_ - 3);row--)		// ��������
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
		//((gpio_get(_button3_) == 0) && (MoveTime >= 5))       ||		// 5s�Գ�
	 	//(MoveTime == TimeStopCar)                             ||		// ��ʱͣ��
		//(StartLineFlag && ((AccuracyTime-StartLineTime) > 10))||		// ������ͣ��
	 	out == true										        // ����
	  )
	{
		StopCarFlag = _Effective_;
	}
}

/*******************************************************************************
* �� �� �� * :	CountThreshold
* �������� * :	ͼ���ٽ�ֵ����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��ֵ = (���ֵ + ��Сֵ) / 2 + ����
* �޸�ʱ�� * :	2016-3-30
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
			if((*(*p0 + col) < _WhiteMax_) && (*(*p0 + col) > Max))			// ���ֵ����
				Max = *(*p0 + col);
			
			if((*(*p0 + col) > _WhiteMin_) && (*(*p0 + col) < Min))			// ��Сֵ����
				Min = *(*p0 + col);
		}
		*p1 = (Max + Min)/2 - 10;			// �����ٽ�ֵ
	}
}

/*******************************************************************************
* �� �� �� * :	GetMiddle
* �������� * :	��ֵ�˲�����
* ��    �� * :	_INT16U_ a,_INT16U_ b,_INT16U_ c
* ��    �� * :	�����м�ֵ
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
_INT16U_ GetMiddle(_INT16U_ a,_INT16U_ b,_INT16U_ c)
{
	return ((a>b) ? ((b>c) ? b : ((a>c) ? c : a)) : ((a>c) ? a : ((b>c) ? c : b)));		// ������ֵ
}

/*******************************************************************************
* �� �� �� * :	RowDealBit
* �������� * :	��ֵ���ɼ���ͼ��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void RowDealBit(void)
{
	_INT8U_ row,col;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData,*p1 = Threshold;
	
	CountThreshold();	// �����ٽ�ֵ
	
	for(row = 0;row < _RowMax_;row++,p0++,p1++)		//�����е��ֵ��
	{
		for(col = 0;col < _ColumnMax_;col++)
		{
			*(*p0 + col) = (*(*p0+col) < *(p1+col)) ? 0 : 255;
		}
	}
}

/*******************************************************************************
* �� �� �� * :	SearchRight
* �������� * :	�����������ұ߽�
* ��    �� * :	_INT8U_ location,_INT8U_ row,_INT8U_ range
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-4-3
*******************************************************************************/
_INT8U_ SearchRight(_INT8U_ location,_INT8U_ row,_INT8U_ range)
{
	_INT16S_ col,high,low;
	_INT8U_ *p0 = ImageData[row],BlackLineMax,loop;
	
	BlackLineMax = BlackLine[row] + 2;
	
	low  = location - range;		// ����������Χ
	if(low < 0)                           low = 0;
	high = location + range;
	if(high > (_ColumnMax_-BlackLineMax)) high = _ColumnMax_-BlackLineMax;
	
	for(col = low;col < high;col += BlackLine[row])
	{
		if(*(p0 + col) < _WhiteMin_) break;		// �����ڵ�ֱ���˳�
		
		else if(*(p0 + col) > _WhiteMax_) *(p0 + col)  = _WhiteMax_;	// ���Ʒ����
		
		if(
			(*(p0 + col) > _WhiteMin_)                             &&		// �׵�
			(*(p0 + col + BlackLineMax) < _WhiteMin_)              &&		// �ڵ�
			((*(p0 + col) - *(p0 + col + BlackLineMax)) > _Contrast_)		// ������ֵ
		  )
		{
			for(loop = 1;loop < BlackLineMax;loop++)
			{
				if(*(p0 + col + loop) < _WhiteMin_) return (col + loop);
			}
		}
	}
	return (_ColumnMax_ - 1);		// ����ʧ��
	
	
	
	
	/*
	int  i;                
	int r1,r2;
	uint8 *p0 = ImageData[row];
	
	r1 = location - (int)range; if(r1 < 0)                  r1 = 0;
	r2 = location + (int)range; if(r2 > _ColumnMax_ - 5)    r2 = _ColumnMax_ - 5;
	
	for(i=r1;i<r2;i++)    
	{
		if(*(p0+i) < _WhiteMin_)          break;                    //�����ڵ�ֱ���˳�   
		else if(*(p0+i) > _WhiteMax_)     *(p0+i) = _WhiteMax_;      //���Ʒ����
		
		if
		(
			*(p0+i) > _WhiteMin_              &&
			*(p0+i+5) < _WhiteMin_            &&
			((*(p0+i) - *(p0+i+5)) > _Contrast_)
		)			//ȷ���ǰ׵�ͺڵ�Ƚ�
		{
			return (uint8)i+4;
		}
	}
	return _ColumnMax_-1;     //û�ҵ�
	*/
}

/*******************************************************************************
* �� �� �� * :	SearchLeft
* �������� * :	������������߽�
* ��    �� * :	_INT8U_ location,_INT8U_ row,_INT8U_ range
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-4-11
*******************************************************************************/
_INT8U_ SearchLeft(_INT8U_ location,_INT8U_ row,_INT8U_ range)
{
	_INT16S_ col,high,low;
	_INT8U_ *p0 = ImageData[row],BlackLineMax,loop;
	
	BlackLineMax = BlackLine[row] + 2;
	
	low = location - range;		// ����������Χ
	if(low < BlackLineMax)       low = BlackLineMax;
	high = location + range;
	if(high > (_ColumnMax_ - 1)) high = _ColumnMax_ - 1;
	
	for(col = high;col > low;col -= BlackLine[row])
	{
		if(*(p0 + col) < _WhiteMin_) break;			// ���ⵥ�߶���
		
		if(*(p0 + col) > _WhiteMax_) *(p0 + col) = _WhiteMax_;			//���Ʒ����
		
		if(
			(*(p0 + col) > _WhiteMin_)                             &&		// �׵�
			(*(p0 + col - BlackLineMax) < _WhiteMin_)              &&		// �ڵ�
			((*(p0 + col) - *(p0 + col - BlackLineMax)) > _Contrast_)		// ���ڷ�ֵ
		  )
		{
			for(loop = 1;loop < BlackLineMax;loop++)					// �Һڵ�
			{
				if(*(p0 + col - loop) < _WhiteMin_) return (col - loop);
			}
		}
	}
	return 0;		// ����ʧ��
	
	
	
	
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
	return 0;     //û�ҵ�
	*/
}

/*******************************************************************************
* �� �� �� * :	FirstSearch
* �������� * :	�������б߽�
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-2
*******************************************************************************/
void FirstSearch(void)
{
	_INT8U_  srh_end,start_srhr;
	_INT16S_ loop;
	
	LeftFirstRow  = 0;		// ����������
	RightFirstRow = 0;		// ����������
	
	if(RightFirstConfine > _ColumnMax_/3)		// ��������
	{
		srh_end = RightCross ? (_SearchStop_+_CrossWide_) : _SearchStop_;		// ʮ����ǰ��������
		
		if(LeftBarrierFlag == _Effective_) start_srhr = _SearchRangeMin_;		// ��ֹ�ѵ��ϰ��߽�
		else                               start_srhr = 2*_SearchRangeMax_;
		
		for(loop = (_RowMax_-1);loop >= srh_end;loop--)		// ������ʼ��
		{
			LeftConfine[loop] = SearchLeft(LeftFirstConfine,loop,start_srhr);
			
			if(LeftConfine[loop] && (LeftConfine[loop] < _ColumnMax_*4/5))		// ��������
			{
				LeftFirstRow = loop;
				
				LeftFirstConfine = LeftConfine[loop];			// ��һ�����߲ο�
				
				if(LeftFirstConfine > _ColumnMax_*3/4)			// ���Ʋο�λ��
				{
					LeftFirstConfine = _ColumnMax_*3/4;
				} break;
			}
		}
	}
	
	if(LeftFirstConfine < _ColumnMax_*2/3)		// ��������
	{
		srh_end = LeftCross ? (_SearchStop_+_CrossWide_) : _SearchStop_;		// ʮ����ǰ��������
		
		if(RightBarrierFlag || StartLineFlag) start_srhr = _SearchRangeMin_;		// ��ֹ�ѵ��ϰ��߽�
		else                                  start_srhr = 2*_SearchRangeMax_;
		
		for(loop = _RowMax_-1;loop >= srh_end;loop--)		// ������ʼ��
		{
			RightConfine[loop] = SearchRight(RightFirstConfine,loop,start_srhr);
			
			if((RightConfine[loop] != (_ColumnMax_-1)) && (RightConfine[loop] > _ColumnMax_/5))
			{
				RightFirstRow = loop;
				
				RightFirstConfine = RightConfine[loop];          // ��һ�����߲ο�
				
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
* �� �� �� * :	SearchImage
* �������� * :	����ͼ��ı߽�ֵ
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	�ޣ����⣺���������ݲͬ����������
* �޸�ʱ�� * :	2016-4-3
*******************************************************************************/
void SearchImage(void)
{
	_INT16S_ loop = 0;
	_INT8U_ lost_num_l = 0,lost_num_r = 0,leftp,rightp;		// ��������ͳ�ƣ���һ������Ԥ��
	
	StartLine        = 0;		// ��ʼ��
	sight =   _RowMax_/4;		// ��Ұ
	
	FirstSearch();				// ��������
	
	leftp  = LeftFirstConfine;			// ȡ���߲ο�
	rightp = RightFirstConfine;
	
	if(StartLine > 0)			// ��ʼ����
	{
		LeftLost  = _LostMax_;		// �����������
		RightLost = _LostMax_;
		
		for(loop = StartLine;loop >= 0;loop--)
		{
			if(loop < RightFirstRow)			// �����п�ʼ����
			{
				if((lost_num_r < RightLost) && (LeftFirstConfine < (_ColumnMax_*2/3)))		// ��Χ����
				{
					RightConfine[loop] = SearchRight(rightp,loop,SearchLineRange[loop]);
					
					if(RightConfine[loop] != (_ColumnMax_ - 1))		// �ѵ��߽�
					{
						if(rightp > 10) rightp = RightConfine[loop];		// ������߽�
						
						lost_num_r = 0;
						
						RightLost = _LostMax_ - 5;
						
						if((RightConfine[loop] > (_ColumnMax_ - 6)) && (loop < sight))
						{
							lost_num_r = RightLost;
						}
					}
					else lost_num_r++;		// ���߼�1
				}
				else{lost_num_r++;RightConfine[loop] = _ColumnMax_-1;}
			}
			
			if(loop < LeftFirstRow)		// ������ʼ��������߽�
			{
				if((lost_num_l < LeftLost) && (RightFirstConfine > (_ColumnMax_/3)))		// ��Χ����
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
* �� �� �� * :	ActiveLine
* �������� * :	������Ч��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-8
*******************************************************************************/
void ActiveLine(void)
{
	_INT16S_ loop;
	
	if(LeftFirstRow)		// ��������Ч��
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
	
	if(RightFirstRow)		// ��������Ч��
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
* �� �� �� * :	LeftSlopeCou
* �������� * :	�������б�ʣ��Ŵ�100��
* ��    �� * :	_INT8U_ row_ks,_INT8U_ row_ke
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-24
*******************************************************************************/
_INT16S_ LeftSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke)
{
	/* һԪ���Իع���С���˷���б�� */
	_INT16S_ aver_x,aver_y;		// �С���ƽ��ֵ
	_FP32_ x_num = 0,y_num = 0;			// б���ܺ�ֵ
	_INT8U_ change,rowledge;
	
	rowledge = (_INT8U_)MyAbs(row_ks - row_ke);			// �о�
	
	if(rowledge >= 2)	// �о�ﵽ���м�����
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])	// ��߶����ж�
		{
			aver_x = (row_ks + row_ke) / 2;
			aver_y = (LeftConfine[row_ks] + LeftConfine[row_ke]) / 2;
			
			if(row_ks < row_ke) {change = row_ks;row_ks = row_ke;row_ke = change;}
			
			for(;row_ke <= row_ks;row_ke++)		// ������б��
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
	else if(rowledge)	// ��������
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])
		{
			return (_INT16S_)(100 * (LeftConfine[row_ke]-LeftConfine[row_ks]) / rowledge);	// ��߶����ж�
		}
		else return 0;
	}
	else return 0;
	
	
	
	/* ���㷨����б�� */
	/*
	int  kc,ks,ke;
	int  t,row_effect;  
	row_effect = row_ks-row_ke;
	
	if(row_effect >= 3)
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])					// ���б��
		{
			ks = LeftConfine[row_ks];
			ke = LeftConfine[row_ke];
			kc = LeftConfine[row_ke*2/3 + row_ks/3];
			if(kc == 0)       kc = (ks+ke)/2;
		}
		t = ( 0*ke + 5 * kc - 5 * ks) * 20 / row_effect;		// ����б��
	}
	else if(row_effect)
	{
		if(LeftConfine[row_ks] && LeftConfine[row_ke])			// ���б��
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
* �� �� �� * :	RightSlopeCou
* �������� * :	�����ұ�б�ʣ��Ŵ�100��
* ��    �� * :	_INT8U_ row_ks,_INT8U_ row_ke
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-24
*******************************************************************************/
_INT16S_ RightSlopeCou(_INT8U_ row_ks,_INT8U_ row_ke)
{
	/* һԪ���Իع���С���˷���б�� */
	_INT16S_ aver_x,aver_y;		// �С���ƽ��ֵ
	_FP32_ x_num = 0,y_num = 0;			// б���ܺ�ֵ
	_INT8U_ change,rowledge;
	
	rowledge = (_INT8U_)MyAbs((row_ks - row_ke));	// �о�
	
	if(rowledge >= 2)	// �о�ﵽ���м�����
	{
		if((RightConfine[row_ks] != (_ColumnMax_-1)) && (RightConfine[row_ke] != (_ColumnMax_-1)))	// �ұ߶����ж�
		{
			aver_x = (row_ks + row_ke) / 2;
			aver_y = (RightConfine[row_ks] + RightConfine[row_ke]) / 2;
			
			if(row_ks < row_ke) {change = row_ks;row_ks = row_ke;row_ke = change;}
			
			for(;row_ke <= row_ks;row_ke++)		// ������б��
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
	else if(rowledge)	// ��������
	{
		if((RightConfine[row_ks] != (_ColumnMax_-1)) && (RightConfine[row_ke] !=(_ColumnMax_-1)))	// �ұ߶����ж�
		{
			return (_INT16S_)(100 * (RightConfine[row_ke]-RightConfine[row_ks]) / rowledge);	// �ұ߶����ж�
		}
		else return 0;
	}
	else return 0;
	
	
	
	/* ���㷨����б�� */
	/*
	int  kc,ks,ke;
	int  t,row_effect;
	row_effect = row_ks-row_ke;
	
	if(row_effect >= 3)
	{
		if(RightConfine[row_ks] != _ColumnMax_-1 && RightConfine[row_ke] != _ColumnMax_-1 )   //�ұ�б��
		{
			ks = RightConfine[row_ks];
			ke = RightConfine[row_ke];
			kc = RightConfine[row_ke*2/3 + row_ks/3];   //�޸�-->���Ⱦ�ֲ���ѡȡ2/3��λ��
			if(kc == _ColumnMax_-1)   kc = (ks+ke)/2 ;
		}
		t = ( 0*ke + 5 * kc - 5 * ks) * 20 / row_effect;//����б��
	}
	else if(row_effect)
	{
		if(RightConfine[row_ks] != _ColumnMax_-1 && RightConfine[row_ke] != _ColumnMax_-1)
		{
			ks = RightConfine[row_ks];                                      //�ұ�б��
			ke = RightConfine[row_ke];
		}
		t = (ke - ks) * 100 / row_effect;
	}
	else    t = 0;
	return  t;
	*/
}
/*******************************************************************************
* �� �� �� * :	CalculateSlope
* �������� * :	����б��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void CalculateSlope(void)
{
	_INT16S_ loop,far,far1;
	
	if(LeftFirstRow)
	{
		LeftInflexion = LeftFirstRow;
		
		far = (LeftEndRow < _SlopeFarthest_) ? _SlopeFarthest_ : LeftEndRow;
		
		for(loop = (LeftFirstRow - 1);loop >= far;loop--)			// ������յ�
		{
			if(LeftConfine[loop] > LeftConfine[LeftInflexion])
			{
				LeftInflexion = loop;
			}
		}
		
		far1 = 2*LeftInflexion - LeftFirstRow;
		far1 = (far1<0) ? far : ((far1>far) ? far1 : far);
		
		if(LeftConfine[far1] == 0) LeftConfine[far1] = LeftConfine[LeftFirstRow];
		
		LeftFarSlope  = LeftSlopeCou(LeftInflexion,far1);			// Զ��б�� 
		LeftNearSlope = LeftSlopeCou(LeftFirstRow,LeftInflexion);	// ����б�� 
	}
	else {LeftFarSlope = 0;LeftNearSlope = 0;}
	
	if(RightFirstRow)
	{
		RightInflexion = RightFirstRow;
		far = (RightEndRow < _SlopeFarthest_) ? _SlopeFarthest_ : RightEndRow;
		 
		for(loop = (RightFirstRow - 1);loop >= far;loop--)			// �����ҹյ�
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
		
		RightFarSlope = RightSlopeCou(RightInflexion,far1);					//Զ��б�� 
		RightNearSlope = RightSlopeCou(RightFirstRow,RightInflexion);		//����б��
	}
	else {RightFarSlope = 0;RightNearSlope = 0;}
}

/*******************************************************************************
* �� �� �� * :	CrossFilter
* �������� * :	ʮ���˲�
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	�ޣ����⣺�����ǰ��⵽ʮ�֣����Ҳ���졣������
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void CrossFilter(void)
{
	_INT8U_ cou;
	_INT16S_ loop;
	
	if((HillFlag == _Void_) && ((LeftCross == _Void_) || (RightCross == _Void_)))
	{
		cou = 0;		// ����
		if(RightFarSlope && RightNearSlope && (RightInflexion > 30) && (RightInflexion < 70) && (RightCross == _Void_))		// ��ʮ���ж�
		{
			for(loop = (RightInflexion - 1);loop >= (RightInflexion - 6);loop--)		// ��ʮ����ʶ��
			{
				if(((RightConfine[loop] - RightConfine[loop + 1]) > 3) && (RightConfine[loop] != (_ColumnMax_ - 1)))		// ��ȡʮ������
				{
					cou++;
				}
				if(cou > 2) {RightCross = _Effective_;break;}
				_16u[1] = cou;
			}
			
			if(
				(RightConfine[RightInflexion + 5] != (_ColumnMax_ - 1))                 &&		// ��ʮ����ʶ��
				(RightConfine[RightInflexion - 5] != (_ColumnMax_ - 1))                 &&
				((RightConfine[RightInflexion - 5] - RightConfine[RightInflexion]) > 6) &&
				((RightConfine[RightInflexion + 5] - RightConfine[RightInflexion]) > 6)
			  ) RightCross = _Effective_;
		}
		
		cou = 0;		// ����
		if(LeftFarSlope && LeftNearSlope && (LeftInflexion > 30) && (RightInflexion < 70) && (LeftCross == _Void_))			// ��ʮ���ж�
		{
			for(loop = (LeftInflexion-1);loop >= (LeftInflexion-6);loop--)		// ��ʮ����ʶ��
			{
				if(((LeftConfine[loop] - LeftConfine[loop - 1]) > 3) && LeftConfine[loop])		// ��ȡʮ������
				{
					cou++;
				}
				if(cou > 2) {LeftCross = _Effective_;break;}
				_16u[0] = cou;
			}
			
			if(
				LeftConfine[LeftInflexion + 5]                                      &&		// ��ʮ����ʶ��
				LeftConfine[LeftInflexion - 5]                                      &&
				((LeftConfine[LeftInflexion] - LeftConfine[LeftInflexion + 5]) > 6) &&
				((LeftConfine[LeftInflexion] - LeftConfine[LeftInflexion - 5]) > 6)
			  ) LeftCross = _Effective_;
		}
	}
	
	if(LeftCross && (!LeftEffective  || ((RightFirstRow < 100) && (RightFirstRow > 70) && (RightEffective > 30))))		// ʮ�������
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
* �� �� �� * :	FillingLine
* �������� * :	����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void FillingLine(void)
{
	bool cps = false;
	_INT16S_ loop,far=0;
	_FP32_ slope,last_slope;	// б�ʼĴ�
	_INT8U_ buffer2 = 0;
	_FP32_ buffer1 = 0;		// ���ݼĴ�
	
	if(
		((LeftEffective > 10) && (LeftCross == _Void_))     ||		// ��ʮ�֣���Ч�� > 10��
		(LeftCross && ((_RowMax_ - 1 - LeftInflexion) > 10))		// ʮ����Զ��
	  )			// �������
	{
		buffer1 = LeftNearSlope/100.0f;
		buffer2 = LeftConfine[LeftFirstRow];
		
		for(loop = (LeftFirstRow - 1);loop > LeftEndRow;loop--)			// ������Ч�з�Χ�ں���
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
		
		if(LeftFarSlope && LeftNearSlope && (LeftCross == _Void_)) slope =  LeftFarSlope;		// ��ʮ�����
		else                                                       slope = LeftNearSlope;
		
		if(slope < 0) slope = 0;			// б������
		//last_slope = slope;
		
		if(LeftCross) far = LeftInflexion;
		else          far = LeftEndRow;
		
		buffer1 = slope/100.0f;
		
		for(loop = (far-1);loop >= 0;loop--)		// Զ�˲���(�������������)
		{
			LeftConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(LeftConfine[far]+buffer1),0,(_ColumnMax_ - 5));
			/*
			slope = LeftCross ? slope*102/100 : slope;		// ʮ��ÿ��б������5%
			
			if(slope > 2*last_slope) slope = 2*last_slope;			// �������б��
			*/
			buffer1 += slope/100.0f;
			
			if(LeftConfine[loop] > (_ColumnMax_ - 10))			// ������Ե
			{
				cps = true;
				break;
			}
		}
		
		if((cps == true) && (loop > 0))			// ����ͼ���Ե��ֱ�����
		{
			for(;loop >= 0;loop--)
			{
				LeftConfine[loop] = LeftConfine[loop+1];
			}
			cps = false;					// �����־
		}
	}
	
	if(
		((RightEffective > 10) && (RightCross == _Void_))     ||		// ��ʮ�֣���Ч�� > 10��
		(RightCross && ((_RowMax_ - 1 - RightInflexion) > 10))		// ʮ����Զ��
	  )			// ����
	{
		buffer1 = RightNearSlope/100.0f;
		buffer2 = RightConfine[RightFirstRow];
		
		for(loop = (RightFirstRow - 1);loop > RightEndRow;loop--)		// ������Ч�з�Χ����
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
		
		if(RightFarSlope && RightNearSlope && (RightCross == _Void_)) slope = RightFarSlope;		// ����ʮ��
		else                                                          slope = RightNearSlope;
		
		if(slope > 0) slope = 0;		// ������б��
		//last_slope = slope;
		
		if(RightCross) far = RightInflexion;
		else           far = RightEndRow;
		
		buffer1 = slope/100.0f;
		
		for(loop = (far-1);loop >= 0;loop--)
		{
			RightConfine[loop] = (_INT8U_)limit_B_C((_INT16S_)(RightConfine[far]+buffer1),5,(_ColumnMax_ - 1));
			/*
			slope = RightCross ? slope*102/100 : slope;		// ʮ��ÿ��б������5%
			
			if(slope < 2*last_slope) slope = 2*last_slope;			// �������б��
			*/
			buffer1 += slope/100.0f;
			
			if(RightConfine[loop] < 10)			// ������Ե
			{
				cps = true;
				break;
			}
		}
		if(cps && (loop > 0))			// ����ͼ���Ե��ֱ�����
		{
			for(;loop >= 0; loop--)
			{
				RightConfine[loop] = RightConfine[loop+1];
			}
			cps = false;			// �����־
		}
	}
}

/*******************************************************************************
* �� �� �� * :	CouBlackArea
* �������� * :	���������ڵ����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-3-30
*******************************************************************************/
void CouBlackArea(void)
{
	_INT8U_ loop,clp;
	_INT16S_ black;
	
	AreaEndLine = _RowMax_ - _LineArea_;		// ���������ֹ��
	
	if(LeftCross)  LeftArea  = limit1(LeftArea,600);		// ʮ�ִ���
	else           LeftArea  = 0;
	
	if(RightCross) RightArea  = limit1(RightArea,600);
	else           RightArea   = 0;
	
	if(
		((LeftEffective > 10) && (LeftCross == _Void_))    ||	// ��Ч�� > 10�У���ʮ��
		(
			LeftCross                        &&			// ʮ������Զ��
			(LeftFirstRow > 95)              &&
			(LeftFirstRow - LeftInflexion) > 10
		)
	  )		// �������
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
		((RightEffective > 10) && (RightCross == _Void_))    ||			// ��Ч�� > 10�У���ʮ��
		(
			RightCross                         &&			// ʮ������Զ��
			(RightFirstRow > 95)               &&
			(RightFirstRow - RightInflexion) > 10
		)
	  )			// ���������
	{
	    RightArea = 0;
	    for(loop = RightFirstRow;loop >= AreaEndLine;loop--)
	    {
	        black = RightTrapezoid[loop] - RightConfine[loop];
	        
	        black = (_INT8U_)limit_B_C(black,0,2*(RightTrapezoid[loop] - _Center_));
			
	        RightArea += black;
	    }
	}
	
	if(HillFlag)   // �µ�
	{
		LeftArea  = LeftArea/3;			// 2
		RightArea = RightArea/3;		// 2
	}
	
	if(BarrierRow < 100)  		// Խ�����ϰ�ԽС
	{
		if(LeftBarrierFlag)		// ���ϰ�
		{
			clp = _Center_ - BarrierCol;
			LeftArea += (800 - clp*5);
			RightArea = RightArea/2;
		}
		
		if(RightBarrierFlag)	// ���ϰ�
		{
			clp = BarrierCol - _Center_;
			RightArea += (800 - clp*5);
			LeftArea   = LeftArea/2;
		}
	}
	
	if(LeftBarrierBuffer)		// �ϰ�������ƽ��ת��
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
	
	if(LeftBarrierFlag || RightBarrierFlag) CorrectOffset = CorrectOffset/3;		// �����ϰ���ȡ��D��������
	
	OldOffset = offset;
	offset = limit1(offset,3000);
	CorrectOffset = limit1(CorrectOffset,300);
}

/*******************************************************************************
* �� �� �� * :	WhiteWide
* �������� * :	�����������
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-12
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
* �� �� �� * :	CheckHill
* �������� * :	�µ����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-12
*******************************************************************************/
void CheckHill(void)
{
	_INT16U_ loop,sum = 0;
	
	for(loop = 5;loop < 30;loop++)		// 1m ��ʼ���
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
			(sum > 1500)                   &&		// �������
			(sum < 2500)                   &&
			(LeftActive > 115)             &&		// ��Ч��
			(AmountActive < 230)           &&
			((MoveTime - OnHillTime) >= 2) &&		// ���ʱ��
			MyAbs(LeftNearSlope)  < 100    &&		// б��
			MyAbs(RightNearSlope) < 50     &&
			((MyAbs(LeftNearSlope) + MyAbs(RightNearSlope)) < 100) &&
			LeftFarSlope < 10              &&
			RightFarSlope < 10
	  )
	*/
	if(
	      !HillFlag                      &&
	      (sum > 1500)                   &&		// �������
	      (sum < 2500)                   &&
	      (LeftEffective  > 115)         &&		// ���µ�ǰ���𽥶�ͼ
	      (RightEffective > 115)         &&		// �����µ�����
	      ((MoveTime - OnHillTime) >= 2) &&		// �µ����������
		  (MyAbs(LeftNearSlope)  < 70)   &&		// б������
		  (MyAbs(RightNearSlope) < 70)   &&
		  (MyAbs(LeftFarSlope)   < 10)   &&
		  (MyAbs(RightFarSlope)  < 10)
	  )
	{
		HillFlag = 1;
		OnHillDistance = CarMove;
	}
	
	if(HillFlag && ((CarMove - OnHillDistance) > 20000))		// ����
	{
		HillFlag = 0;
		OnHillTime = MoveTime;
	}
}

/*******************************************************************************
* �� �� �� * :	CheckStartLine
* �������� * :	�����߼��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-13
*******************************************************************************/
void CheckStartLine(void)
{
	_INT8U_ loop;
	_INT8U_ x1 = 0,x2 = 0,x3 = 0,x4 = 0;	// �����߶˵�
	
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
			(MoveTime >=  2)   &&			// С����ʻ2s����
			(!StartLineFlag)   &&
			((x2 - x1) < 31)   &&         // 30
			((x2 - x1) >  8)   &&         //  5
			((x3 - x2) >  7)   &&         //  8
    		((x3 - x2) < 28)   &&         // 30
			((x4 - x3) < 31)   &&         // 30
			((x4 - x3) >  8)              //  5
	   )				// �������ж�
	{
		StartLineFlag = _Effective_;
		StartLineTime = AccuracyTime;
	}
	
	if(StartLineFlag && ((AccuracyTime-StartLineTime) > 200))		// ֹͣ��ʾ
	{
		StartLineFlag = _Void_;
	}
}

/*******************************************************************************
* �� �� �� * :	SearchLength
* �������� * :	������Զ�����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	���Զ��ֱ��33�� = RightConfine[0] - LeftConfine[0]
* �޸�ʱ�� * :	2016-6-22
*******************************************************************************/
void SearchLength(void)
{
	//bool flag;
	_INT16U_ buffer = 0;
	_INT8U_ row,col;
	_INT8U_ (*p0)[_ColumnMax_] = ImageData;
	
	/* ��ֱ��ʶ����� */
	/*
	for(row = 0;row < _RowMax_;row++,p0++)			// ɨ���м�n��ͼ��
	{
		for(col = (_Center_ - _LengthRange_);col <= (_Center_ + _LengthRange_);col++)
		{
			flag = (*(*p0 + col) > _WhiteMin_) ? true : false;
			
			if(flag == false) break;
		}
		if(flag == false) break;
	}
	
	if(
			(LeftArea  < 50) &&		// ����ϸ�����
			(RightArea < 50) &&
			(flag == true)			// �м����ȫ�׵�
	  )
	{
		WhiteLength = _Active_;
	}
	else
	{
		WhiteLength = _Void_;
	}
	*/
	
	for(col = 0;col <= (_ColumnMax_ - 1);col++)			// ��ȡÿ�н����׸��ڵ�λ��
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
		buffer += WhiteLengthNear[col];				// �ۼ��׸��ڵ�������
	}
	
	buffer /= (_LengthRange_ * 2 + 1);				// ��ڵ�λ��ƽ��ֵ
	
	WhiteLength = 0;
	for(row = (_RowMax_ - 1);row > buffer;row--)
	{
		WhiteLength += (_RowMax_-1) / (row+1);		// 0 ~ 470
	}
	
	CorrectWhiteLength = WhiteLength - OldWhiteLength;
	
	OldWhiteLength = WhiteLength;
}

/*******************************************************************************
* �� �� �� * :	CheckBarrier
* �������� * :	�ϰ����
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-16 
*******************************************************************************/
void CheckBarrier(void)
{
	_INT8U_ loop = 0;
	_INT8U_ y1 = 0,y2 = 0,y3 = 0,y4 = 0;		// ��������
	_INT8U_ x = 0,y = 0;						// ������
	
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
	
	BarrierRow = 0;		// �ƺ��˲����Ƕ����
	
	if(
			(HillFlag == _Void_)               &&		// ���µ�
			(y4 == 0)                          &&
			((y2 - y1) > 10)                   &&		// 14
			((y2 - y1) < 40)                   &&
			(ImageData[x - 3][y] < _WhiteMin_) &&
			(LeftBarrierFlag  == _Void_)       &&		// ���ϰ�
			(RightBarrierFlag == _Void_)
	   )
	{
		if(
				(
					(LeftConfine[x + 4] != 0)                           &&		// û����������
					(RightConfine[x + 4] != (_ColumnMax_ -1))           &&
					((y - LeftConfine[x + 4]) < (RightConfine[x + 4] - y))
				)                                                             ||
				(
					(LeftConfine[x + 4] == 0)              &&						// ĳ�߶�������
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
	
	if((CarMove - BarrierShift) > 3000)				// ����
	{
		if(RightBarrierFlag) {RightBarrierFlag = _Void_;RightBarrierBuffer = 20;}
		if (LeftBarrierFlag) {LeftBarrierFlag  = _Void_;LeftBarrierBuffer  = 20;}
	}
}

/*******************************************************************************
* �� �� �� * :	OverlapFilter
* �������� * :	�ص��˲�
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-5-22
*******************************************************************************/
void OverlapFilter(void)
{
	bool flag = false;
	_INT8S_ loop = 0;
	
	if(HillFlag) return;		// �µ�����
	
	for(loop = (_RowMax_-1);loop >= 30;loop--)					// ������
	{
		if((RightConfine[loop] != (_ColumnMax_ - 1)) && LeftConfine[loop])		// ���Ҳ�����
		{
			if( RightConfine[loop] - LeftConfine[loop] < 3)			// ���ұ��߼��
			{
				flag = true;
			}
			else if((RightConfine[loop] - LeftConfine[loop]) < (ConfineDistance[loop] - 20))		// ȥ����Ч���ٵ�һ��
			{
				if(LeftEffective < RightEffective) LeftConfine[loop]  = 0;
	    		else                               RightConfine[loop] = _ColumnMax_-1;
	    	}
		}
	}
	
	if(
			(LeftFirstRow < RightEndRow)                                &&		// ������ͼ
			((RightConfine[RightEndRow] - LeftConfine[LeftFirstRow]) < 30)
	  ) flag = true;
	
	if(
			(RightFirstRow < LeftEndRow)                                &&		// ���Ұ��ͼ
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
	
	if(!LeftFirstRow && RightFirstRow)			// ȡ��ʼ��
	{
		LeftFirstConfine  = (_INT8U_)limit_B_C(RightFirstConfine-_ColumnMax_*2/3,_ColumnMax_/15,_ColumnMax_/5);
	}
	else if(LeftFirstRow && !RightFirstRow)
	{
		RightFirstConfine = (_INT8U_)limit_B_C( LeftFirstConfine+_ColumnMax_*2/3,4*_ColumnMax_/5,14*_ColumnMax_/15);
	}
}

/*******************************************************************************
* �� �� �� * :	MCU_sqrt
* �������� * :	MCU���ٿ�ƽ��
* ��    �� * :	_INT32U_ M
* ��    �� * :	��ƽ��ֵ
* ˵    �� * :	ƽ�������ٶ�ΪC�⺯��sqrt()��2.5����ֵԽ������Խ����
				C�⺯��sqrt()����������ֵ��СӰ�죬ƽ����������7.5us
* �޸�ʱ�� * :	2016-6-3
*******************************************************************************/
_INT16U_ MCU_sqrt(_INT32U_ M)
{
	_INT8U_  Byte = 0,loop = 0;
	_INT16U_ value = 1,a = 0,b = 0;
	_INT32U_ cou = 0;
	
	if(M == 0) return 0;
	
	cou = M;
	
	while(cou != 0)			// ���� M λ��
	{
		cou >>= 1;
		Byte++;
	}
	
	Byte = (Byte % 2) ? ((Byte + 1) >> 1) : (Byte >> 1);		// �۰�
	
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
* �� �� �� * :	curvature
* �������� * :	�����������
* ��    �� * :	_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3
* ��    �� * :	���ʵĵ���
* ˵    �� * :	����˳ʱ�룬������ʱ��
* �޸�ʱ�� * :	2016-6-3
*******************************************************************************/
_INT16S_ curvature(_INT8U_ x1,_INT8U_ y1,_INT8U_ x2,_INT8U_ y2,_INT8U_ x3,_INT8U_ y3)
{
	_INT16S_ area,curl;
	_INT16U_ length1,length2,length3;
	
	area = (y2 - y1) * (x3 - x1) - (y3 - y1) * (x2 - x1);		// ����������ӱ�
	
	length1 = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	length2 = (x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1);
	length3 = (x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3);
	
	curl = (_INT16S_)sqrt(length1*length2*length3) / (area<<1);			// ȡ���ʵĵ���
	
	return curl;
}

/*******************************************************************************
* �� �� �� * :	CrossFillingLine
* �������� * :	ʮ�ֲ���
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-7
*******************************************************************************/
void CrossFillingLine(void)
{
	_INT8S_ i;
	_INT8U_ row,line,line_tp;
	_FP32_ slope,buffer;
	
	if(RightCross)			// ��ʮ��
	{
		row = 0;
		buffer = 0;
		line_tp = RightConfine[RightInflexion-15];
		
		for(i = (RightInflexion-15);i >= 0;i--)		// ��ʮ��Զ�˱���
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
		
		for(i = (RightInflexion-1);i > row;i--)		// ��ʮ��
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
		
		for(i = (LeftInflexion-15);i >= 0;i--)		// ��ʮ��Զ�˱���
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
		
		for(i = (LeftInflexion-1);i > row;i--)		// ��ʮ��
		{
			buffer += slope;
			
			LeftConfine[i] = (_INT8U_)(LeftConfine[LeftInflexion] + buffer);
		}
	}
}

/*******************************************************************************
* �� �� �� * :	BigArc
* �������� * :	��
* ��    �� * :	��
* ��    �� * :	��
* ˵    �� * :	��
* �޸�ʱ�� * :	2016-6-7
*******************************************************************************/
void BigArc(void)
{
	if(
			MyAbs(offset) > 1000         &&			// �����Χ
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
