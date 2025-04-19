
#include <STC8G.H>
#include "intrins.h"
#include "tool.h"

unsigned int DJ1_ds = 0;
unsigned int DJ2_ds = 0;
unsigned int DJ3_ds = 0;
unsigned int DJ4_ds = 0;

void pin()
{
    P1M0 = 0x00; P1M1 = 0x00;
    P3M0 = 0x00; P3M1 = 0x00;
    P5M0 = 0x00; P5M1 = 0x00;
}

void Delay1ms(int ms)	//@11.0592MHz
{
    while(ms--)
    {           
        unsigned char data i, j;

        i = 15;
        j = 90;
        do
        {
            while (--j);
        } while (--i);
    }
}

void Timer0_Init(void)		//100微秒@33.1776MHz
{
	EA = 1;					//开启总中断
    ET0 = 1;				//开启定时器0中断
    AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x0A;				//设置定时初始值
	TH0 = 0xF3;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void sec(int s)
{
	Delay1ms(s*1000);
}

unsigned char  degreecount(int ds)
{
    unsigned char ds_temp = 0;
    ds_temp = ds/9 + 5;

    return ds_temp;
}

void pmw_degree(int No,int degree)
{
    switch (No)
    {
        case 1:
            DJ1_ds = degreecount(degree);
            break;
        case 2:
            DJ2_ds = degreecount(degree);
            break;
        case 3:
            DJ3_ds = degreecount(degree);
            break;
        case 4:
            DJ4_ds = degreecount(degree);
            break;
    }
}

void pd(int temp) 
{
    if (DJ1_ds > temp){DJ1 = 1;}else{DJ1 = 0;}
    if (DJ2_ds > temp){DJ2 = 1;}else{DJ2 = 0;}
    if (DJ3_ds > temp){DJ3 = 1;}else{DJ3 = 0;}
    if (DJ4_ds > temp){DJ4 = 1;}else{DJ4 = 0;}
}

void speed(int degree1,int degree2,int degree3,int degree4,int level,int mode,bit re)
{
    int i;

    int S1 = degree1/10;
    int S2 = degree2/10;
    int S3 = degree3/10;   
    int S4 = degree4/10;

    switch(mode)
    {   
        case 1:
            for (i = 0; i < 10; i++)
            {
                pmw_degree(1,S1*i);
                pmw_degree(2,S2*i);
                pmw_degree(3,S3*i);
                pmw_degree(4,S4*i);
                Delay1ms(5*level);
            }
            
			sec(1);
						
            if(re)
            {
								
							
				pmw_degree(1,0);
                pmw_degree(2,0);
                pmw_degree(3,0);
                pmw_degree(4,0);
                
                 
            }
            sec(1);
            break;

        case 2:
            pmw_degree(1,degree1);
            pmw_degree(2,degree2);
            pmw_degree(3,degree3);
            pmw_degree(4,degree4);
            sec(1);		
         
            
            if(re)
            {
							
								
				pmw_degree(1,0);
                pmw_degree(2,0);
                pmw_degree(3,0);
                pmw_degree(4,0);
                sec(1);		
								
            }
            break;

    }
}

