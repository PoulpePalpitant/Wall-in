//
#include <iostream>   // pour le cout
#include <conio.h>   // pour le _getch()
#include <thread>	// Pour multiplier les processus en simultané!
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
#include "../FONCTIONS/UI/console_output/dsp_string.h"


#include "../FONCTIONS/inputs/detect_input.h"
using namespace std;


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le début!
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
	// AFFICHE TOUS LES GRIDS 

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
			UI_Dsp_String(crd, std::to_string(i), (Colors)j);	// Ceci pourrait être une fonction d'affichage

				// Cette fonction est incapable d'afficher un int...
		}
	}

	/*
	 Création de bots liés dans une liste
	Bot *bot;
	CustomBot specialBot;
	specialBot.NoWarning = true;

	gGrd = { 2,3 };

	bot = Create_New_Bot(BotType::REGULAR, gGrd, true);
	
	gGrd = { 0, 10 };
	bot = Create_New_Bot(BotType::SUPERSONIC, gGrd, true);
	bot = Create_New_Bot(BotType::SUPERSONIC, gGrd, true);
	*/

	

	
	Coord dep, arr;
	dep.x = 3, dep.y = 5;
	arr.x = 0, arr.y = 1;

	if (Is_Equal(dep, arr))
		true;
	cout << TXT_CONST.MINUS;


	// CLOCK TESTING
	Coord crd2 = { 35,1 };
	Coord crd3 = { 35,2 };

	GameClock LvlClock;
	LvlClock.clockName = "Swag Clock";
	crd = { 0,1 };
	LvlClock.Dsp_Name(crd);
	crd = { 13,1 };
	LvlClock.Start_Clock();

	thread Clockydy(&GameClock::Infinite_Dsp, &LvlClock, crd, WHITE);			/// FOUND THE SOLUTION : Si ta un default argument, tu dois quand même mettre quekchose en paramètre! Sinon ça ne marche pas!!!

	//for (size_t i = 0; i < 1000000; i++)
	//{
	//	for (size_t j = 0; j < 100; j++)
	//	{
	//		UI_Dsp_Int(crd2, i);
	//		UI_Dsp_Int(crd3, j);

	//	}
	//}
	//Sleep(10000);

	//LvlClock.Pause_Clock();



	std::thread blastThread;	// test les input qui font des blast
	int input = 0;
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------o---------

	do
	{
		// MENU LOOP
		// *********
		
		do	// Affiche MENU
		{	
			//blastThread = thread(Check_Input);
			//blastThread.join();
			
			
			while (_kbhit())
				_getch();
			input = 0;

			do
			{
				if ((_kbhit()))
					input++;

			} while (input < 1);
			
			Check_Input();
			
			// Check input
			// if (input) -> Stuff
		} while (true); // Game pas starté

	
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