#include "headfile.h"
#include "math.h"

uint8   image3[MT9V032_H][MT9V032_W];      //ͼ������
uint8 Right_Blackline[MT9V032_H];//�ұ�Ե��������
uint8 Left_Blackline[MT9V032_H]; //���Ե��������
uint8 Right_Blackline_Save[MT9V032_H];
uint8 Left_Blackline_Save[MT9V032_H];
uint8_t Middle_line[MT9V032_H];        //����
uint8 image_threshold = 100;
float middle_value=0;               //����ֵ
uint8 row_error[20];
/**********************************************************************************/
/*!
 *  @brief      otsuThreshold����
 *  @since      2018.12.27
 *  @note      	����ͷ������ɷ�����
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
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���  
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������  
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������  
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
 *  @brief      img_change����
 *  @since      5.22
 *  @note       ��ͼ�����ݷŵ�����img�У��Ӷ����з��� ��һ�����ص�һλ��                
 */
 /**********************************************************************************/
void img_change(uint8_t * dst)                                                                        
{

	uint16_t i;					        // 0��0�� ��ʾ ��ɫ��1��255����ʾ ��ɫ
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
                                                               //dst+4700Ϊ�������һԪ�أ�һ��������ȥ���õ�������ͼ��
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
 *  @brief      img_change����
 *  @since      5.22
 *  @note       ��ͼ�����ݴ�imgbuff�ŵ���ά����img�У��Ӷ����з���                 //��ͼ�����Ϊ���µߵ��������෴����Ϊ����ͷ�ǵ��ģ����н���
 */
 /**********************************************************************************/
void img_change_char(uint8_t * dst)                                                                        
{

	uint16_t i;					        // 0��0�� ��ʾ ��ɫ��1��255����ʾ ��ɫ
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
                                                               //dst+4700Ϊ�������һԪ�أ�һ��������ȥ���õ�������ͼ��
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

	/*ͼ�����ݰ���*/
	if(mt9v032_finish_flag)
	img_change_char((uint8 *)image3);
//	if(img[2][2] == 255)			//����ͷ��װ��ͼ���������Ͻǿ�ʼ��255Ϊ��
//		printf("1111");

	/*��һ����ȡ����(���м�������ɨ��)*/
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
            for(Black_Point=MT9V032_W/2;Black_Point>=0;Black_Point--)      //��ȡ�Һ���
            {
                Right_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
                {
                    Right_Blackline[i]=Black_Point;
                    break;
                }
            }
            for(Black_Point=MT9V032_W/2;Black_Point<MT9V032_W;Black_Point++)     //��ȡ�����
            {
                Left_Blackline[i]=Black_Point;
                if(image3[i][Black_Point]==0)
                {
                    Left_Blackline[i]=Black_Point;
                    break;
                }
            }
						
            Middle_line[i]=(Left_Blackline[i]+Right_Blackline[i])/2; 
            
//            Handle_M_line[i].y=i;				K60LCD��ʾ
//            Handle_M_line[i].x=Middle_line[i]; 
					

           if(i == MT9V032_H-1)
           {
                One_flag=0;
           }  
       }
   }
				
    /*����һ��֮����ȡ����(��֮ǰ����������ɨ��)*/		
			/*
	0			/	|	\
	|		 /	|	 \
  55	/		|		\
		 0<- ���� ->80
	*/
    if(One_flag == 0)
    {
       for(i=MT9V032_H-5;i>=10;i--)      //����ʹ����0~55�е�����
       {  
            for(Black_Point=Middle_line[i];Black_Point>=0;Black_Point--)      //��ȡ�Һ���
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
            for(Black_Point=Middle_line[i];Black_Point<MT9V032_W;Black_Point++) //��ȡ�����
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
						//ȥ�������
						if(Right_Blackline[i+1]-Right_Blackline[i+2]>8&&Right_Blackline[i]-Right_Blackline[i+1]>8)
						Right_Blackline[i+1]=(Right_Blackline[i+2]+Right_Blackline[i])/2;
						if(Left_Blackline[i+2]-Left_Blackline[i+1]>8&&Left_Blackline[i+1]-Left_Blackline[i]>8) 
						Left_Blackline[i+1]=(Left_Blackline[i+2]+Left_Blackline[i])/2;
						
            //�������� = ���ߺ�������ȡƽ��
            if(Right_Blackline[i]>0 && Left_Blackline[i]<MT9V032_W-1) 
                Middle_line[i]=(Left_Blackline[i]+ Right_Blackline[i])/2;   //ȡ���е�
						
            /*����������ȡ����*/	
//            Handle_M_line[i].y=i-30;			LCD��ʾ
//            Handle_M_line[i].x=Middle_line[i];
      
//            if(Left_Blackline[i]!=79 || Right_Blackline[i]!=0)
//                circle_flag=0; 			//�뻷��־λ
		 
//            Judge_Row(i);				//�жϴ����У�����
//            if(error_row[i] == 0)
//							LCD_rectangle(Handle_M_line[i], line_size, RED);   //LCD�������     

            /******************** ���߲��� ***********************/
						
          if(Right_Blackline[i]==0 && Left_Blackline[i] < MT9V032_W-1 && Left_Blackline[i] > Right_Blackline[i])      //���߶�ʧ   
            {
							if(i==MT9V032_H-5)
								 Middle_line[i] = Left_Blackline[i] + ( MT9V032_W-1 - Left_Blackline[i])/2;
							else
                 Middle_line[i] = Middle_line[i+1] + (Left_Blackline[i] - Left_Blackline[i+1]);               
							if(Middle_line[i] < 1)
									Middle_line[i] = 1;
            }
            if(Left_Blackline[i]==MT9V032_W-1 && Right_Blackline[i] > 0 && Left_Blackline[i] > Right_Blackline[i])      //���߶�ʧ
            {
							if(i==MT9V032_H-1)
								 Middle_line[i] = Right_Blackline[i] /2;
							else
                 Middle_line[i] = Middle_line[i+1] + (Right_Blackline[i] - Right_Blackline[i+1]);                 //60��    -(0.5471 * i - 44.5186)
							if(Middle_line[i] > MT9V032_W-1)
									Middle_line[i] = MT9V032_W-1;
            } 
          
            /******************** ʮ�ִ��� ***********************/
        /*    if(Right_Blackline[i] == 0 && Left_Blackline[i]==79) 
            {
                add_cross_line(i);
                //printf("2\n");
         */                       
                /******************** ���߲��� ***********************/
               /*if(Right_Blackline[i]==0 && Left_Blackline[i] < 79 && Left_Blackline[i] > Right_Blackline[i])      //���߶�ʧ    //(0.5271 * i + 0.8946 - 40)
                {
                        Middle_line[i] = Left_Blackline[i] + (0.5215 * i - 0.0442 - 35);               //60��    (0.5271 * i + 0.8946 - 40)
                        if(Middle_line[i] < 1)
                                Middle_line[i] = 1;
                }
                if(Left_Blackline[i]==79 && Right_Blackline[i] > 0 && Left_Blackline[i] > Right_Blackline[i])      //���߶�ʧ
                {
                        Middle_line[i] = Right_Blackline[i] -(0.6122 * i -78.52 + 40);                 //60��    -(0.5471 * i - 44.5186)
                        if(Middle_line[i] > 79)
                                Middle_line[i] = 79;
                } 
                                        
                Middle_line[i]=(Handle_R_line[i].x + Handle_L_line[i].x)/2;
            } 		
              */          
            /******************** Բ������ ***********************/
//            if(error_row[i] == 2)
//                pass_round(i);
//    
//            if(circle_flag==1)
//            {
//                Middle_line[i] = 77;
//            }   

//            /*����������ȡ����*/							
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
				for(i=55;i>10;i--)
				{
					
					if(Right_Blackline[i-1]-Right_Blackline[i]>20&&Right_Blackline[i-2]-Right_Blackline[i]>20)
						row_error[0]=i;
					if(Right_Blackline[i+1]-Right_Blackline[i]>20&&Right_Blackline[i+2]-Right_Blackline[i]>20)
						row_error[1]=i;
					if(Left_Blackline[i]-Left_Blackline[i-1]>20&&Left_Blackline[i]-Left_Blackline[i-2]>20)
						row_error[2]=i;
					if(Left_Blackline[i]-Left_Blackline[i+1]>20&&Left_Blackline[i]-Left_Blackline[i+2]>20)
						row_error[3]=i;
				}
				row_error[4]=fmin(row_error[0],row_error[2]);
				row_error[5]=fmin(row_error[1],row_error[3]);
				for(i=row_error[4]+3;i<row_error[5]-3;i++)
				Middle_line[i]=(Middle_line[row_error[4]+4]+Middle_line[row_error[5]-4])/2;//Right_Blackline[row_error[0]]+(i-row_error[0])/(row_error[0]-row_error[1])*(Right_Blackline[row_error[1]]-Right_Blackline[row_error[0]]);
		
    }				    
}





/*!
 *  @brief      Get_weighted_average����
 *  @since      v5.0
 *  @note       �����߼�Ȩƽ��
 */

void Get_Weighted_Average(void)
{
	int i,effective_line;
	
	middle_value=0;
	effective_line=0;
	
	for(i=5;i<26;i++)
   {
        if(effective_line<26)
        {
           middle_value += (MT9V032_W/2-Middle_line[i])*0.08;  
                     
        }	
        if(effective_line>5 && effective_line<15)
        { 
           middle_value += (MT9V032_W/2-Middle_line[i])*0.4; 
        }  
        effective_line++; 
    }		 
    middle_value = middle_value/(effective_line+1);
    if(middle_value>=MT9V032_W/2) middle_value=MT9V032_W/2;
    if(middle_value<=-MT9V032_W/2) middle_value=-MT9V032_W/2;
//	 printf("get middle_value:%f\n",middle_value);
}

