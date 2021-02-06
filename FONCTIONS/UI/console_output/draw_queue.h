#pragma once

#include "../../grid/AllGrids.h"
#include "../txtstyle.h"

// Permet de faire une même animation avec la méthode des events plusieurs fois, et en même temps
struct Drawer
{
	Coord XY;					// Stock uniquement une coord, mais pourrait être personnalisé
	SpeedTimer timer;	
	int currStep = 0;
	bool cancel = false;		// Permet de canceler l'event
};


class DrawerQueue
{
	friend void Clear_All_States(bool eraseMap );	// Gros reset button
		
	int animationSteps;
	int MAX_QUEUE = 0;	// devrait être const sérieurx
	int total = 0;

	 void Remove_All();
public:
	Drawer * queue;			// public stuff
	int Get_Total() { return total; }
	void Step(int index, int speed = 0, int MAX_STEPS = 1, bool infinite = false);		// Avance l'event d'un step
	void Cancel(Coord XY);		// Stop l'animation sur cette position
	bool Add(Coord XY);		// Ajoute un élément à draw
	void Remove(int index);

	DrawerQueue(int MAX, int MAX_STEPS)
	{
		MAX_QUEUE = MAX;
		animationSteps = MAX_STEPS;
		queue = new Drawer[MAX];
	}

	~DrawerQueue()
	{
		delete [] queue;
	}
};
