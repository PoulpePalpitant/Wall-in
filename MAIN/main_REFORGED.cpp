//
#include <iostream>   // pour le cout
#include <conio.h>   // pour le _getch()
#include <thread>	// Pour multiplier les processus en simultan�!
//#include <string>	// pour le string
//#include <iomanip> // pour les manipulateurs
//#include <windows.h> //pour le time, et toute sorte de shits.
//#include < ctime >	// pour utiliser la fonction clock()
//#include "WinUser.h"


#include "../FONCTIONS/time/clock.h"
#include "../FONCTIONS/grid/managegrids.h"
#include "../FONCTIONS/grid/wallgrid.h"
#include "../FONCTIONS/link/link.h"
#include "../FONCTIONS/bots/botlist.h"
#include "../FONCTIONS/bots/bot.h"
#include "../FONCTIONS/bots/botinitialize/bot_intializer.h"


#include "../FONCTIONS/UI/console_output/dsp_char.h"
#include "../FONCTIONS/UI/console_output/dsp_int.h"

using namespace std;


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le d�but!
{
	// START STUFF LOOP
	// ***************

	//int** intp = NULL;
	//Grid intGrid;
	//intGrid.Create(10, 5, intp);
	//cout << intp[9][4] << '\n'; _getch();
	//intGrid.Resize(20, 20, intp);
	//cout << intp[10][5] << '\n'; _getch();


	
	Resize_Grids_To_Level(linkGrid, wallGrids, spawnGrid, 1);	// Woorks ^^

	

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	char UI; Coord crd;	int maxC, maxR;
	
	maxC = linkGrid.Get_Cols();
	maxR = linkGrid.Get_Rows();

	UI = LinkSym::PARENT;

	for (int i = 0; i < maxC; i++)	// Affiche Le Link grid
	{
		for (int j = 0; j < maxR; j++)
		{
			crd = linkGrid.link[i][j].Get_XY(); gotoxy(crd.x, crd.y); cout << UI;
		}
	}

	maxC = wallGrids.hor->Get_Cols();
	maxR = wallGrids.hor->Get_Rows();

	for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	{
		for (int j = 0; j < maxR; j++)
		{
			UI = wallGrids.hor->wall[i][j].Get_Sym();crd=wallGrids.hor->wall[i][j].Get_XY();
			
			UI_Dsp_Char(crd, UI,(Colors)j);
			
			
		}
	}


	maxC = wallGrids.ver->Get_Cols();
	maxR = wallGrids.ver->Get_Rows();

	for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	{
		for (int j = 0; j < maxR; j++)
		{
			UI = wallGrids.ver->wall[i][j].Get_Sym();crd = wallGrids.ver->wall[i][j].Get_XY();	UI_Dsp_Char(crd, UI,(Colors)i);

		}
	}

	for (int i = 0; i < 4; i++)	// Affiche Le spawn Grid
	{
		for (int j = 0; j < spawnGrid.border[i].Get_Num_Spawns(); j++)
		{
			//spawnGrid->border[i].spawn[j]->GetSpawnXY(crd); 
			crd = spawnGrid.border[i].spawn[j].Get_XY();
			UI_Dsp_Int(crd, j, (Colors)j);	// Ceci pourrait �tre une fonction d'affichage

				// Cette fonction est incapable d'afficher un int...
		}
	}

	
	
	Bot *bot;

	
	

	CustomBot specialBot;
	specialBot.NoWarning = true;

	gGrd = { 2,3 };

	bot = Create_New_Bot(BotType::REGULAR, gGrd, true);
	
	gGrd = { 0, 10 };
	bot = Create_New_Bot(BotType::SUPERSONIC, gGrd, true);
	bot = Create_New_Bot(BotType::SUPERSONIC, gGrd, true);
	

	
	

	
	Coord dep, arr;

	dep.x = 3, dep.y = 5;
	arr.x = 0, arr.y = 1;

	if (Is_Equal(dep, arr))
		true;
	cout << TXT_CONST.MINUS;

	// THREADING TESTING

	std::thread swag[10];

	for (size_t i = 0; i < 100; i++)
	{
		thread th1(Get_GrdX, 2);
		
		if(th1.joinable())
			th1.join();

	}

	// CLOCK TESTING

	GameClock LvlClock;
	LvlClock.clockName = "Swag Clock";
	LvlClock.updateDelay = 0;
	crd = { 0,0 };
	LvlClock.Dsp_Name(crd);
	
	thread thbla ;
	thbla(LvlClock.Activate_Clock());

	crd = { 13,0 };

	while (true)
	{
		LvlClock.Dsp_Time(crd);
	}




	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------o---------

	do
	{
		// MENU LOOP
		// *********
		
		do	// Affiche MENU
		{	
			// Check input
			// if (input) -> Stuff
		} while (true); // Game pas start�

	
		// GAME LOOP
		// *********

		while (true)	// Le joueur joue, ou n'est pas mort 
		{
			// Check lvl stuff
			// Check input stuff
			// if(input) -> stuff
		}

	} while (true);	// Le joueur ne quitte pas
}