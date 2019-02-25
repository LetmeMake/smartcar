#ifndef _mycode_h_
#define _mycode_h_

extern uint8 Speed_L_New,Speed_R_New;
extern int count;
extern int target_value;
void Motor_Read(void);
void Motor_Init(void);
void Motor_PWM(uint32_t frontleft,uint32_t backleft,uint32_t frontright,uint32_t backright);
void Motor_PID_Control(void);
void PID_Check(void);
void uart_write(int16_t valuea,int16_t valueb ,int16_t valuec,int16_t valued);

#endif
