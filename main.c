#include <STC8G.H>
#include "intrins.H"

sbit DJ1 = P1^0;
sbit DJ2 = P1^1;
sbit DJ3 = P1^6;
sbit DJ4 = P1^7;

int count = 0; 
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

void Timer0_Init(void)		//100΢��@33.1776MHz
{
	EA = 1;					//�������ж�
    ET0 = 1;				//������ʱ��0�ж�
    AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x0A;				//���ö�ʱ��ʼֵ
	TH0 = 0xF3;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
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
        
        case 2:
            DJ2_ds = degreecount(degree);
            break;
        case 4:
            DJ4_ds = degreecount(degree);
            break;
        case 1:
            DJ1_ds = degreecount(degree);
            break;
        
        case 3:
            DJ3_ds = degreecount(degree);
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

//void speed(int degree1,int degree2,int degree3,int degree4,int level,int mode,bit re)
//{
//    int i;

//    int S1 = degree1/10;
//    int S2 = degree2/10;
//    int S3 = degree3/10;   
//    int S4 = degree4/10;

//    switch(mode)
//    {   
//        case 1:
//            for (i = 0; i < 10; i++)
//            {
//                pmw_degree(1,S1*i);
//                pmw_degree(2,S2*i);
//                pmw_degree(3,S3*i);
//                pmw_degree(4,S4*i);
//                Delay1ms(5*level);
//            }
//            
//			sec(1);
//						
//            if(re)
//            {
//								
//							
//				pmw_degree(1,0);
//                pmw_degree(2,0);
//                pmw_degree(3,0);
//                pmw_degree(4,0);
//                
//                 
//            }
//            sec(1);
//            break;

//        case 2:
//            pmw_degree(1,degree1);
//            pmw_degree(2,degree2);
//            pmw_degree(3,degree3);
//            pmw_degree(4,degree4);
//            sec(1);		
//         
//            
//            if(re)
//            {
//							
//								
//				pmw_degree(1,0);
//                pmw_degree(2,0);
//                pmw_degree(3,0);
//                pmw_degree(4,0);
//                sec(1);		
//								
//            }
//            break;

//    }
//}

//void speedfan(int degree1,int degree2,int degree3,int degree4)
//{


//    int S1 = degree1/10;
//    int S2 = degree2/10;
//    int S3 = degree3/10;   
//    int S4 = degree4/10;

//   

//        pmw_degree(1,0);
//        pmw_degree(2,0);
//        pmw_degree(3,0);
//        pmw_degree(4,0);	
//		sec(1);			
//		pmw_degree(1,degree1);
//        pmw_degree(2,degree2);
//        pmw_degree(3,degree3);
//        pmw_degree(4,degree4);		
//        sec(1);	       
//                 


//}

void first(int degree)
{
    pmw_degree(2,degree);
    pmw_degree(4,0);
    
    sec(1);
    
    pmw_degree(4,degree);
    pmw_degree(2,0);
    
    sec(1);  
}

void second(int degree)
{
    pmw_degree(1,degree);
    pmw_degree(3,0);
    
    sec(1);
    
    pmw_degree(3,degree);
    pmw_degree(1,0);
    
    sec(1);  
}

void main()
{
    Timer0_Init();
    pin();
    while(1)
    {
        first(60);
        sec(1);
        second(60);

    }
}

void Timer0() interrupt 1
{
    TL0 = 0x0A;				//���ö�ʱ��ʼֵ
	TH0 = 0xF3;				//���ö�ʱ��ʼֵ
    
    pd(count);     
    count++;
    count %= 200;
}


