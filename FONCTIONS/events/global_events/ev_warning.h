#pragma once


#include "../../UI/txtstyle.h"
#include "../../time/movement_timer.h"

// ARRAYS	
const int MAX_WAR_DRAWERS = 20;

void Ev_Draw_Warnings();			// Message d'avertissement
void Ev_MultiColor_Warnings(); // voici un event custom



struct WarningDrawer
{
	SpeedTimer timer;
	int currStep = 0;
	bool dr_Er;	// draw ou erase?
	Colors clr;
};

class WarningDrawerList
{
	friend void Ev_Draw_Warnings();

	static int animationSteps;
	static WarningDrawer drawer[MAX_WAR_DRAWERS];
	static int total;

	static void Remove(int index);
public:
	static bool Add(bool dr_Er, Colors clr, int speed = 12000);	// Ajoute un item � draw

};
