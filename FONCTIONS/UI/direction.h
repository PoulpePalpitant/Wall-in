#pragma once

#include "polarisation.h"
#include "axis.h"

enum Direction { UP, LEFT , DOWN, RIGHT, RESTE_ICITTE = -1 };

Direction Find_Opposite_Dir(Direction direction);	// Trouve la direction oppos�e
Direction Create_Direction(Axis ax, Polarization plr); // transforme un Axe et une polarisation en une direction
bool Is_Same_Direction(Direction dir, Axis ax, Polarization plr);	// Compare une direction avec un Axe et une Polarization

/* Outisder, pour r�gler la circularit�*/
Axis Find_Opp_Axis(Direction dir);	// Trouve l'axe "oppos�" � une direction