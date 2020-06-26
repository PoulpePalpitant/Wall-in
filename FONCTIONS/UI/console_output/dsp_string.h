#pragma once

#include <time.h>
#include "../txtstyle.h"
#include "../coord.h"
#include <string>

// AFFICHE UN CHAR
void UI_Dsp_String(Coord crd, std::string txt, Colors clr = WHITE, time_t time = 0);


int Find_Ctr_X(int size);		// Trouve la crd en x qui permettrait d'output un char au centre
