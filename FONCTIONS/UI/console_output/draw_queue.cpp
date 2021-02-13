
#include "draw_queue.h"

void DrawerQueue::Remove(int index)	// On delete rien au final
{
	// ITS GRID TIME MOTHERFUCKER

	for (int i = index; i < total; i++)		// Décale tout
		queue[i] = queue[i + 1];

	total--;
}


void DrawerQueue::Remove_All()
{
	for (int i = 0; i < this->MAX_QUEUE; i++)		// ALL SHALL BE DELETED
	{
		queue[i] = {};
		total--;
	}
}
void DrawerQueue::Cancel(Coord XY)	// Stop l'animation  sur cette position
{
	for (int index = 0; index < total; index++)		
	{
		if (Are_Equal(queue[index].XY, XY))
			queue[index].cancel = true;
	}
}
 void DrawerQueue::Step(int index, int speed, int MAX_STEPS, bool infinite)
 { 
	 queue[index].currStep++;
	 queue[index].timer.Start_Timer(speed, MAX_STEPS, infinite);
 }

bool DrawerQueue::Add(Coord XY)		// Ajoute l'item à draw dans la list
{
	static Drawer tempDrawer = {};

	if (total < MAX_QUEUE)
	{
		tempDrawer.XY = XY;
		tempDrawer.timer.Start_Timer(0);		// First step de l'animation
		tempDrawer.currStep = 1;
		
		queue[total] = tempDrawer;
		total++;	
		return true;
	}
	else
		return false;
}
