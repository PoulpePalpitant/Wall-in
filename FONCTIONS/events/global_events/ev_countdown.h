#pragma once 

#include "../../UI/coord.h"
#include "../../grid/AllGrids.h"



void Set_CountDown(int duration, Coord coord = { Find_Ctr_X(),linkGrid->link[0][(linkGrid->Get_Rows() / 2)].Get_XY().y + 1 }, bool disableBlast = true);// Translation: 1 case en dessous de l'élément au milieu du grid
void Ev_CountDown();							   		
bool Blast_Disabled_While_CD();							   		

bool CountDown_Finished(); // Permet de savoir quand le contdown est finit
bool CountDown_Cancel(); // Permet de savoir quand le contdown est finit

