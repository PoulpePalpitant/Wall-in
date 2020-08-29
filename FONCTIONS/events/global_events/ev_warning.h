#pragma once


#include "../../UI/txtstyle.h"
#include "../../time/movement_timer.h"
#include "clear_all_states.h"

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
	friend void Clear_All_States(bool eraseMap );	// Gros reset button


	static int animationSteps;
	static WarningDrawer drawer[MAX_WAR_DRAWERS];
	static int total;

	static void Remove(int index);
	static void Remove_All();

public:
	static bool Add(bool dr_Er, Colors clr, int speed = 12000);	// Ajoute un item à draw

};
