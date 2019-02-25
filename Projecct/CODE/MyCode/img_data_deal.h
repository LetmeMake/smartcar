#ifndef _img_data_deal_h_
#define _img_data_deal_h_

#define img_H 120 
#define img_W 188 

extern float middle_value;               //����ֵ
extern uint8   image3[MT9V032_H][MT9V032_W];      //ͼ������
extern uint8_t Middle_line[MT9V032_H];        //����
extern uint8 Right_Blackline[MT9V032_H];//�ұ�Ե��������
extern uint8 Left_Blackline[MT9V032_H]; //���Ե��������
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);
void img_change(uint8_t * dst);
void img_change_char(uint8_t * dst);
void Find_Blackline(void);
void Get_Weighted_Average(void);
#endif
