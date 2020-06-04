#pragma once

#include "direction.h"
#include "axis.h"


Axis Find_Opp_Axis(Axis ax)	// L'axe "oppos�", soit l'autre
{
	if (ax == HOR)
		return VER;
	else
		return HOR;

}

Axis Find_Opp_Axis(Direction dir)	// Trouve l'axe "oppos�" � une direction
{
	if (dir == UP || dir == DOWN)	// L'axe est vertical si UP/DOWN
		return HOR;	// oppos�
	else
		return VER;
}