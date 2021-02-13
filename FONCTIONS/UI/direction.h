#pragma once

#include "polarisation.h"
#include "axis.h"

enum Direction { UP, LEFT , DOWN, RIGHT, NONE = -1 };

Direction Find_Opposite_Dir(Direction direction);	
Direction Create_Direction(Axis ax, Polarization plr); 
bool Is_Same_Direction(Direction dir, Axis ax, Polarization plr);

/* Outisder, pour r�gler la circularit�*/
Axis Find_Opp_Axis(Direction dir);	// Trouve l'axe "oppos�" � une direction