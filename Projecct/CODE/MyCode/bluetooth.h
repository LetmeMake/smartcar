#ifndef __Bluetooth_H__
#define __Bluetooth_H__

#define _PID_void_     		0
#define _PID_effective_   1
#define _PID_up_      2
#define _PID_down_ 		3
#define _PID_P_       4
#define _PID_I_ 			5
#define _PID_D_       6

extern char ParameterFlag_1,ParameterFlag_2,ParameterFlag_3,Parameter_num;

void Parameter_Adjust(char receive);







#endif
