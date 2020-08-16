
#include "wall_drawer.h"

extern const int WALL_DRAW_SPEED = 40000;


WallDrawer* DrawWalls::start; 
WallDrawer*DrawWalls::end;

void DrawWalls::Remove(WallDrawer* &prev, WallDrawer* &toRemove)	// On delete rien au final
{
	if (toRemove == start && toRemove == end)
		start = end = toRemove = NULL;
	else
		if (toRemove == start)
		{
			start = start->nxt;
			toRemove->nxt = NULL;		// Je me suis fais chié ici, car le .nxt n'était pas reset à chaque fois. Et comme on détruit pas, ça peut créer une loop infinie!
			toRemove = start;
		}
		else
			if (toRemove == end)
			{
				end = prev;
				toRemove = prev->nxt = NULL;
			}
			else
			{
				toRemove = toRemove->nxt;
				prev->nxt->nxt = NULL;
				prev->nxt = toRemove;
			}
}

void DrawWalls::Add(WallDrawer* data)	// Ajoute le wall à draw
{
	if (start == NULL)
		start = end = data;
	else
		end = end->nxt = data;
	
}
 bool DrawWalls::Find_And_Draw_Wall(WallDrawer& drawer)
{
	 if (start == NULL) return false;	// Liste vide

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

		 if (bugChecker == 10000)
			 throw "Building and breaking doens't quite work";
	 }

	 return false;
}

void DrawWalls::Draw_Them_Walls()		
{
	if (start == NULL) return;	// Liste vide

	static WallDrawer* it;
	static WallDrawer* prev;
	
	it = start;
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

