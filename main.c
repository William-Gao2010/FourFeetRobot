#include <STC8G.H>
#include "intrins.H"
#include "tool.h"
#include "run.h"



int count = 0; 

void main()
{
    Timer0_Init();
    pin();
    while(1)
    {
        feet_on(2,50,2,0);
    }
}

void Timer0() interrupt 1
{
    TL0 = 0x0A;				//设置定时初始值
	TH0 = 0xF3;				//设置定时初始值
    
    pd(count);     
    count++;
    count %= 200;
}