#pragma once

#include "direction.h"
#include "axis.h"


Axis Find_Opp_Axis(Axis ax)	
{
	if (ax == HOR)
		return VER;
	else
		return HOR;

}

Axis Find_Opp_Axis(Direction dir)	
{
	if (dir == UP || dir == DOWN)
		return HOR;	
	else
		return VER;
}