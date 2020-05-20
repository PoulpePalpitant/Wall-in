#pragma once

#include <time.h>
#include "../txtstyle.h"
#include "../coord.h"


// AFFICHE UN CHAR
void UI_Dsp_Char(Coord crd, char sym, Colors clr = WHITE, time_t time = 0);
