#pragma once


#include "../time/movement_timer.h"
#include "../UI/console_output/render_list.h"

extern const int WALL_DRAW_SPEED;


struct WallDrawer
{
	CoordIncrementor xy;
	char sym;
	Colors clr;
	SpeedTimer timer;

	WallDrawer* nxt = NULL;
};

class DrawWalls
{
	static WallDrawer* start, * end;

	static void Remove(WallDrawer* &prev, WallDrawer* &toRemove);
public:
	static void Draw_Them_Walls();
	static void Finish_Wall(WallDrawer& drawer); // Termine d'afficher un wall. Utilisé quand je veux afficher ou effacer 1 même mur durant 1 même frame
	static bool Find_And_Draw_Wall(WallDrawer& drawer);	// trouve un mur dans la liste et termine l'affichage
	static void Add(WallDrawer* data);
};

