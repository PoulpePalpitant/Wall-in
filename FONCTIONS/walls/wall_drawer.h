#pragma once


#include "../time/movement_timer.h"
#include "../UI/console_output/render_list.h"

extern const int WALL_DRAW_SPEED;


struct WallDrawer
{
	CoordIncrementor xy;
	char sym;
	Colors clr;
	MovementTimer timer;

	WallDrawer* nxt = NULL;
};

class DrawWalls
{
	static WallDrawer* start, * end;

	static void Remove(WallDrawer* &prev, WallDrawer* &toRemove);
public:
	static void Draw_Them_Walls();
	static void Add(WallDrawer* data);
};

