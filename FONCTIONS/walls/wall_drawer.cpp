
#include "wall_drawer.h"

extern const int WALL_DRAW_SPEED = 40000;

WallDrawer* DrawWalls::start = NULL; 
WallDrawer*DrawWalls::end = NULL;


void DrawWalls::Reset_Drawer(WallDrawer* &drawer)
{
	drawer->timer.Stop();
	drawer->nxt = NULL;
	drawer = NULL;	
}

void DrawWalls::Remove(WallDrawer* &prev, WallDrawer* &toRemove)
{
	toRemove->timer.Stop();

	if (toRemove == start && toRemove == end)
		start = end = toRemove = NULL;
	else
		if (toRemove == start)
		{
			// Je me suis fais chi� ici, car le .nxt n'�tait pas reset � chaque fois. Et comme on d�truit pas, �a peut cr�er une loop infinie!
			start = start->nxt;
			toRemove->nxt = NULL;		
			toRemove = start;
		}
		else
			if (toRemove == end)
			{
				end = prev;
 				toRemove->nxt = NULL;
				toRemove = prev->nxt = NULL;
			}
			else
			{
				toRemove = toRemove->nxt;
				prev->nxt->nxt = NULL;
				prev->nxt = toRemove;
			}
}
void DrawWalls::Remove_All()
{
	WallDrawer* toRemove, *nxt;

	toRemove = start;

	while (toRemove)
	{
		nxt = toRemove->nxt;
		Reset_Drawer(toRemove);
	}

	start = end = NULL;
}

void DrawWalls::Add(WallDrawer* data)	// Ajoute le wall � draw
{
	if (start == NULL)
		start = end = data;
	else
		end = end->nxt = data;
	
}
 bool DrawWalls::Find_And_Draw_Wall(WallDrawer& drawer)
{
	 if (start == NULL) return false;

	 static WallDrawer* it;
	 static WallDrawer* prev;
	 static int bugChecker; bugChecker = 0;
	 it = start;
	 prev = NULL;

	 while (it)
	 {
		 bugChecker++;

		 if (it == &drawer)
		 {
			 for (int i = it->timer.Get_Moves_Left(); i > 0; i--)
			 {
				 ConsoleRender::Add_Char(it->xy.coord, it->sym, it->clr);
				 it->xy.Increment_Coord();
			 }

			 Remove(prev, it);
			 return true;
		 }
		 else
		 {
			 prev = it;
			 it = it->nxt;
		 }

		 if (bugChecker == 10000)
			 throw "Building and breaking doens't quite work";
	 }

	 return false;
}

 void DrawWalls::Finish_Wall(WallDrawer& drawer) 
 {
	 if (start == NULL) return;	

	 static WallDrawer* it;
	 static WallDrawer* prev;

	 it = start;
	 prev = NULL;

	 int charsLeft = drawer.timer.Get_Moves_Left();

	 while (it)
	 {
		 if (it == &drawer)
		 {
			 for (int i = 0; i < charsLeft; i++)
			 {
				 ConsoleRender::Add_Char(it->xy.coord, it->sym, it->clr);
				 it->xy.Increment_Coord();
				 Remove(prev, it);
				 return;
			 }
		 }
		 else
		 {
			 prev = it;
			 it = it->nxt;
		 }
	 }
 }
 
 bool DrawWalls::Is_Empty()
 {
	 if (start)
		 return false;
	 else
		 return true;

 }

 void DrawWalls::Finish_All() // Termine d'afficher tout les walls! Alternative � remove all qui crash tout le temps
 {

	 if (start == NULL) return;	

	 static WallDrawer* it;
	 static WallDrawer* prev;

	 it = start;
	 prev = NULL;

	 int charsLeft = it->timer.Get_Moves_Left();

	 while (it)
	 {
		 for (int i = 0; i < charsLeft; i++)
		 {
			 ConsoleRender::Add_Char(it->xy.coord, it->sym, it->clr);
			 it->xy.Increment_Coord();
		 }

		 Remove(prev, it);
		 
	 }

	 start = end = NULL;
 }


void DrawWalls::Draw_Them_Walls()		
{
	if (start == NULL) return;	

	static WallDrawer* it;
	static WallDrawer* prev;
	
	it = DrawWalls::start;
	prev = NULL;

	while(it)
	{
		while (it->timer.Tick())
		{
			ConsoleRender::Add_Char(it->xy.coord, it->sym, it->clr);
			it->xy.Increment_Coord();
		}

		if (!it->timer.Is_On())	// we done here
		{
			Remove(prev, it);
			continue;
		}
	
		prev = it;
		it = it->nxt;
	}
}

