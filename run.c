#include <STC8G.H>
#include "intrins.H"
#include "tool.h"

void feet_on(int side ,int degree ,int mode,int sd)
{
		if(side==1)
		{speed(degree,0,degree,0,sd,mode,1);}
		if(side==2)
		{speed(0,degree,0,degree,sd,mode,1);}
}

void leftwalk(void)
{
    feet_on(1, 50, 2, 0);

}

void rightwalk(void)
{
	feet_on(2, 50,2,0);
}

