#include "headfile.h"
#include "math.h"

uint8   image3[MT9V032_H][MT9V032_W];      //图像数组
uint8 Right_Blackline[MT9V032_H];//右边缘黑线数组
uint8 Left_Blackline[MT9V032_H]; //左边缘黑线数组
uint8 Right_Blackline_Save[MT9V032_H];
uint8 Left_Blackline_Save[MT9V032_H];
uint8_t Middle_line[MT9V032_H];        //中线
uint8 image_threshold = 100;
float middle_value=0;               //中线值
uint8 row_error[20];
/**********************************************************************************/
/*!
 *  @brief      otsuThreshold函数
 *  @since      2018.12.27
 *  @note      	摄像头程序大律法函数
 */
 /**********************************************************************************/
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
    #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //统计灰度级中每个像素在整幅图像中的个数  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
        }
    }

    //计算每个像素在整幅图像中的比例  
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //遍历灰度级[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i作为阈值
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //背景部分  
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //前景部分  
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }

    return threshold;
}
/**********************************************************************************/
/*!
 *  @brief      img_change函数
 *  @since      5.22
 *  @note       将图像数据放到数组img中，从而进行分析 （一个像素点一位）                
 */
 /**********************************************************************************/
void img_change(uint8_t * dst)                                                                        
{

	uint16_t i;					        // 0（0） 表示 白色，1（255）表示 黑色
	uint8 *tmpsrc;
	
//	if(mt9v032_finish_flag1 == 1)
//	{
//	tmpsrc = *image1;
//	image_threshold = otsuThreshold(*image1, MT9V032_W, MT9V032_H);
//	}
//	else if(mt9v032_finish_flag1 == 0)
//	{
//	tmpsrc = *image2;
//	image_threshold = otsuThreshold(*image2, MT9V032_W, MT9V032_H);
//	}
                                                               //dst+4700为数组最后一元素，一个个减上去，得到矫正的图像
	for(i=0;i<MT9V032_H*MT9V032_W/8;i++)
	{
		*dst = 0x00;
		*dst  += *tmpsrc++>=image_threshold?0x80:0;
		*dst  += *tmpsrc++>=image_threshold?0x40:0;
		*dst  += *tmpsrc++>=image_threshold?0x20:0;
		*dst  += *tmpsrc++>=image_threshold?0x10:0;
		*dst  += *tmpsrc++>=image_threshold?0x08:0;
		*dst  += *tmpsrc++>=image_threshold?0x04:0;
		*dst  += *tmpsrc++>=image_threshold?0x02:0;
		*dst  += *tmpsrc++>=image_threshold?0x01:0;
		dst++;
	}
	
}
/**********************************************************************************/
/*!
 *  @brief      img_change函数
 *  @since      5.22
 *  @note       将图像数据从imgbuff放到二维数组img中，从而进行分析                 //此图像搬运为上下颠倒，左右相反，因为摄像头是倒的，进行矫正
 */
 /**********************************************************************************/
void img_change_char(uint8_t * dst)                                                                        
{

	uint16_t i;					        // 0（0） 表示 白色，1（255）表示 黑色
	uint8 *tmpsrc;
	
//	if(mt9v032_finish_flag1 == 1)
//	{
//	tmpsrc = *image1;
//	image_threshold = otsuThreshold(*image1, MT9V032_W, MT9V032_H);
//	}
//	else if(mt9v032_finish_flag1 == 0)
//	{
//	tmpsrc = *image2;
//	image_threshold = otsuThreshold(*image2, MT9V032_W, MT9V032_H);
//	}
		tmpsrc = *image;
		image_threshold = otsuThreshold(*image, MT9V032_W, MT9V032_H);
                                                               //dst+4700为数组最后一元素，一个个减上去，得到矫正的图像
	for(i=0;i<MT9V032_H*MT9V032_W;i++)
	{
		//*dst = 0x00;
		*dst = (*tmpsrc++>=image_threshold)?0xff:0;
		dst++;
	}
	
}

uint8 One_flag=1;
void Find_Blackline(void)
{
		int i=0;
    int16_t Black_Point;
//    int flag;

	/*图像数据搬移*/
	if(mt9v032_finish_flag)
	img_change_char((uint8 *)image3);
//	if(img[2][2] == 255)			//摄像头正装，图像正，左上角开始，255为黑
//		printf("1111");

	/*第一次提取中线(由中间向两边扫描)*/
	/*
	0			/	|	\
	|		 /	|	 \
  60	/		|		\
		 0<-  40 ->80
	*/
	if(One_flag==1)
	{
		for(i=0;i<MT9V032_H;i++)
        {
            for(Black_Point=MT9V032_W/2;Black_Point>=0;Black_Point--)      //提取右黑线
            {
                Right_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
                {
                    Right_Blackline[i]=Black_Point;
                    break;
                }
            }
            for(Black_Point=MT9V032_W/2;Black_Point<MT9V032_W;Black_Point++)     //提取左黑线
            {
                Left_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
                {
                    Left_Blackline[i]=Black_Point;
                    break;
                }
            }
						
            Middle_line[i]=(Left_Blackline[i]+Right_Blackline[i])/2; 
            
//            Handle_M_line[i].y=i;				K60LCD显示
//            Handle_M_line[i].x=Middle_line[i]; 
					

           if(i == MT9V032_H-1)
           {
                One_flag=0;
           }  
       }
   }
				
    /*除第一次之外提取中线(由之前中线向两边扫描)*/		
			/*
	0			/	|	\
	|		 /	|	 \
  55	/		|		\
		 0<- 中线 ->80
	*/
    if(One_flag == 0)
    {
       for(i=MT9V032_H-5;i>=10;i--)      //现在使用了0~55行的数据
       {  
            for(Black_Point=Middle_line[i];Black_Point>=0;Black_Point--)      //提取右黑线
            {
                Right_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
								//	if(img[i][Black_Point+1]==0xff)
                {
                    Right_Blackline[i]=Black_Point;
                    Right_Blackline_Save[i] = Right_Blackline[i];
                    break;
                }
            }
            for(Black_Point=Middle_line[i];Black_Point<MT9V032_W;Black_Point++) //提取左黑线
            {
                Left_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
								//	if(img[i][Black_Point-1]==0xff)
                {
                    Left_Blackline[i]=Black_Point;
                    Left_Blackline_Save[i] = Left_Blackline[i];
                    break;
                }
            }
						//去除错误点
						if(Right_Blackline[i+1]-Right_Blackline[i+2]>8&&Right_Blackline[i]-Right_Blackline[i+1]>8)
						Right_Blackline[i+1]=(Right_Blackline[i+2]+Right_Blackline[i])/2;
						if(Left_Blackline[i+2]-Left_Blackline[i+1]>8&&Left_Blackline[i+1]-Left_Blackline[i]>8) 
						Left_Blackline[i+1]=(Left_Blackline[i+2]+Left_Blackline[i])/2;
						
            //中线坐标 = 两边黑线坐标取平均
            if(Right_Blackline[i]>0 && Left_Blackline[i]<MT9V032_W-1) 
                Middle_line[i]=(Left_Blackline[i]+ Right_Blackline[i])/2;   //取出中点
						
            /*中线坐标提取保存*/	
//            Handle_M_line[i].y=i-30;			LCD显示
//            Handle_M_line[i].x=Middle_line[i];
      
//            if(Left_Blackline[i]!=79 || Right_Blackline[i]!=0)
//                circle_flag=0; 			//入环标志位
		 
//            Judge_Row(i);				//判断错误行，过滤
//            if(error_row[i] == 0)
//							LCD_rectangle(Handle_M_line[i], line_size, RED);   //LCD中线输出     

            /******************** 单边补线 ***********************/
						
          if(Right_Blackline[i]==0 && Left_Blackline[i] < MT9V032_W-1 && Left_Blackline[i] > Right_Blackline[i])      //右线丢失   
            {
							if(i==MT9V032_H-5)
								 Middle_line[i] = Left_Blackline[i]/2 ;
							else
                 Middle_line[i] = Middle_line[i+1] + (Left_Blackline[i] - Left_Blackline[i+1]);               
							if(Middle_line[i] < 1)
									Middle_line[i] = 1;
            }
            if(Left_Blackline[i]==MT9V032_W-1 && Right_Blackline[i] > 0 && Left_Blackline[i] > Right_Blackline[i])      //左线丢失
            {
							if(i==MT9V032_H-5)
								 Middle_line[i] = Right_Blackline[i] + (MT9V032_W-Right_Blackline[i])/2;
							else
                 Middle_line[i] = Middle_line[i+1] + (Right_Blackline[i] - Right_Blackline[i+1]);                 //60度    -(0.5471 * i - 44.5186)
							if(Middle_line[i] > MT9V032_W-1)
									Middle_line[i] = MT9V032_W-1;
            } 
						
          
//            /******************** 十字处理 ***********************/
//           if(Right_Blackline[i] == 0 && Left_Blackline[i]==187) 
//            {
//                add_cross_line(i);
//                //printf("2\n");
//                               
//                /******************** 单边补线 ***********************/
//              if(Right_Blackline[i]==0 && Left_Blackline[i] < 187 && Left_Blackline[i] > Right_Blackline[i])      //右线丢失    //(0.5271 * i + 0.8946 - 40)
//                {
//                        Middle_line[i] = Left_Blackline[i] + (0.5215 * i - 0.0442 - 35);               //60度    (0.5271 * i + 0.8946 - 40)
//                        if(Middle_line[i] < 1)
//                                Middle_line[i] = 1;
//                }
//                if(Left_Blackline[i]==187 && Right_Blackline[i] > 0 && Left_Blackline[i] > Right_Blackline[i])      //左线丢失
//                {
//                        Middle_line[i] = Right_Blackline[i] -(0.6122 * i -78.52 + 40);                 //60度    -(0.5471 * i - 44.5186)
//                        if(Middle_line[i] > 79)
//                                Middle_line[i] = 79;
//                } 
//                                        
//                Middle_line[i]=(Left_Blackline[i]+ Right_Blackline[i])/2; 
//            } 		
//                       
            /******************** 圆环处理 ***********************/
//            if(error_row[i] == 2)
//                pass_round(i);
//    
//            if(circle_flag==1)
//            {
//                Middle_line[i] = 77;
//            }   

//            /*两侧坐标提取保存*/							
//						Handle_L_line[i].y=i;                                               
//            Handle_L_line[i].x=Left_Blackline[i];
//            
//						Handle_R_line[i].y=i;
//            Handle_R_line[i].x=Right_Blackline[i];
//            
//            LCD_rectangle(Handle_L_line[i], line_size, GREEN);
//            LCD_rectangle(Handle_R_line[i], line_size, BLUE);

//            if(error_row[i] == 1||error_row[i] == 2)
//                LCD_rectangle(Handle_M_line[i], line_size, RED);
            
 //           error_row[i] = 0;  
         	 
        }
//        circle_flag=0; 
//        cross_flag=0;
				row_error[0]=0;
				row_error[1]=0;
				row_error[2]=0;
				row_error[3]=0;
				for(i=110;i>15;i--)//下
				{

					if(Right_Blackline[i]-Right_Blackline[i-1]>10&&Right_Blackline[i]-Right_Blackline[i-2]>10&&row_error[1]==0)
						row_error[1]=i;

					if(Left_Blackline[i-1]-Left_Blackline[i]>10&&Left_Blackline[i-2]-Left_Blackline[i]>10&&row_error[3]==0)
						row_error[3]=i;
					
					if(row_error[1]!=0 && row_error[3]!=0)
						break;
				}
				for(i=110;i>30;i--)//上
				{
					if(Right_Blackline[i]-Right_Blackline[i+1]>10&&Right_Blackline[i]-Right_Blackline[i+2]>10&&row_error[0]==0)
						row_error[0]=i;

					if(Left_Blackline[i+1]-Left_Blackline[i]>10&&Left_Blackline[i+2]-Left_Blackline[i]>10&&row_error[2]==0)
						row_error[2]=i;
					
					if(row_error[0]!=0 && row_error[2]!=0)
						break;
				}
//				if(row_error[0]>0&&row_error[1]>0&&row_error[2]>0&&row_error[3]>0)
//				{
//				row_error[4]=fmin(row_error[0],row_error[2])-3;
//				row_error[5]=fmax(row_error[1],row_error[3])+3;
//				for(i=row_error[4];i<=row_error[5];i++)
//					{
//				Right_Blackline[i]=Right_Blackline[row_error[5]]+(i-row_error[4])/(row_error[5]-row_error[4])*(Right_Blackline[row_error[4]]-Right_Blackline[row_error[5]]);
//				Left_Blackline[i]=Left_Blackline[row_error[5]]-(i-row_error[4])*(Left_Blackline[row_error[5]]-Left_Blackline[row_error[4]])/(row_error[5]-row_error[4]);
//				Middle_line[i]=(Middle_line[row_error[4]]-Middle_line[row_error[5]])/(row_error[5]-row_error[4])*(i-row_error[4])+Middle_line[row_error[5]];	
//					}
//			}
				if(row_error[1]>0&&row_error[0]>0)
					for(i=row_error[1];i<row_error[0];i--)
				{
					Right_Blackline[i]=Right_Blackline[row_error[1]];
					//if(Left_Blackline[i]==0)
						
				}
			  if(row_error[3]>0&&row_error[2]>0)
					for(i=row_error[3];i<row_error[2];i--)
				{
					Right_Blackline[i]=Right_Blackline[row_error[3]];
					//if(Left_Blackline[i]==0)
						
				}
				//Right_Blackline[row_error[0]]+(i-row_error[0])/(row_error[0]-row_error[1])*(Right_Blackline[row_error[1]]-Right_Blackline[row_error[0]]);
		
 				    
}
}

//void add_cross_line(int i)
//{
//    float a_left,b_left;
//    int a_right,b_right;
//    float sum_a_left = 0,sum_b_left = 0;
//    float sum_a_right,sum_b_right;
//    Site_Lcd_t line_use;
//    int n,m;
//	
//    for(n=0;n<1;n++)
//    {
//        for(m=0;m<10;m++)
//        {
//            if(error_row[55+n+m] != 2)
//            {
//                line_use.x = 40;
//                line_use.y = 55+n+m;
//                LCD_cross(line_use,80,GREEN);
////                m = 0;
//                break;
//            }
//        }

//        a_left=((n+10)-(55+n+m))/(Handle_L_line[n+10].x-Handle_L_line[55+n+m].x);
//        a_right=((n+10)-(55+n+m))/(Handle_R_line[n+10].x-Handle_R_line[55+n+m].x);
//    
//        b_left=-((55+n+m)-a_left*Left_Blackline[55+n+m]);
//        b_right=(55+n+m)-a_right*Right_Blackline[55+n+m];
//        m = 0;
//        sum_a_left = a_left + sum_a_left;
//        sum_b_left = b_left + sum_b_left;
//        sum_a_right = a_right + sum_a_right;
//        sum_b_right = b_right + sum_a_right;

//    }
//    sum_a_left = sum_a_left/n;
//    sum_b_left = sum_b_left/n;

//    sum_a_right = sum_a_right/n;
//    sum_b_right = sum_b_right/n;
//		
//    if((Right_Blackline[10] == 0 && Right_Blackline[11] == 0 && Right_Blackline[12] == 0) || (Left_Blackline[10] == 79 && Left_Blackline[11] == 79 && Left_Blackline[12] == 79))
//    {
//        if(sum_a_left != 0)
//        {
//            Left_Blackline[i] = (i+sum_b_left)/sum_a_left;
//        } 
//        if(Left_Blackline[i] > 79)
//            Left_Blackline[i] = 79;
//        Handle_L_line[i].x = Left_Blackline[i];
//        
//        if(sum_a_right != 0)
//        {
//            Right_Blackline[i] = (i-sum_b_right)/sum_a_right;
//        }
//         
//        if(Right_Blackline[i] <0)
//            Right_Blackline[i] = 0;

//        if(Left_Blackline[i] > 79)
//            Left_Blackline[i] = 79;
//        
//        Handle_R_line[i].x = Right_Blackline[i];
//        Handle_L_line[i].x = Left_Blackline[i];   
//    }
//}



/*!
 *  @brief      Get_weighted_average函数
 *  @since      v5.0
 *  @note       求中线加权平均
 */

void Get_Weighted_Average(void)
{
	int i,effective_line;
	
	middle_value=0;
	effective_line=0;
	
	for(i=30;i<110;i++)
   {
        if(effective_line<20)
        {
           middle_value += (MT9V032_W/2-Middle_line[i])*0.5;  
                     
        }	
        if(effective_line>20 && effective_line<40)
        { 
           middle_value += (MT9V032_W/2-Middle_line[i])*0.55; 
        }  
        effective_line++; 
    }		 
    middle_value = middle_value/(effective_line+1);
    if(middle_value>=MT9V032_W/2) middle_value=MT9V032_W/2;
    if(middle_value<=-MT9V032_W/2) middle_value=-MT9V032_W/2;
//	 printf("get middle_value:%f\n",middle_value);
}

