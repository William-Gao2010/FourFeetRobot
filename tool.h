#ifndef __tool_H__
#define __tool_H__



sbit DJ1 = P1^0;
sbit DJ2 = P1^1;
sbit DJ3 = P1^6;
sbit DJ4 = P1^7;

void pin(void);
void Timer0_Init(void);

void pd(int temp);
void speed(int degree1,int degree2,int degree3,int degree4,int level,int mode,bit re);
void feet_on(int side , int degree , int mode,int speed);
void sec(int s);

#endif