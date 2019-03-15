#ifndef _inductance_h
#define _inductance_h

#include "headfile.h"




#if !defined(MIN)              //取最小
    #define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)             //取最大
    #define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif

extern int16_t left_min_A,right_min_A,left_max_A,right_max_A,left_min_B,right_min_B,left_max_B,right_max_B,angle_z,middle_max,middle_min,Aim_speed,FMQ;
extern int16_t	Left_a,Left_b,Right_a,Right_b,middle;

extern void  Inductance_Read(int16_t* left_data,int16_t* right_data);
extern void  Inductance_Self_test();
extern void Inductance_Init(void);


#endif
