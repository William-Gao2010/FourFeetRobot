#include <STC8G.H>
#include "intrins.H"
#include "tool.h"

void feet_on(int side ,int degree ,int mode,int sd)
{
		if(side==1)
		{speed(degree,degree,0,0,sd,mode,1);}
		if(side==2)
		{speed(0,0,degree,degree,sd,mode,1);}
}



	
