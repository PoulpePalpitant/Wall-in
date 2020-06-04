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
#include "../FONCTIONS/grid/AllGrids.h"
#include "../FONCTIONS/link/link.h"
#include "../FONCTIONS/bots/botlist.h"
#include "../FONCTIONS/bots/bot.h"
#include "../FONCTIONS/bots/botinitialize/bot_intializer.h"


#include "../FONCTIONS/UI/console_output/dsp_char.h"
#include "../FONCTIONS/UI/console_output/dsp_string.h"


#include "../FONCTIONS/inputs/detect_input.h"
using namespace std;

void Test_Animation(Colors one, Colors two);	// So pretty...


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le début!
{
	// START STUFF LOOP
	// ***************

	char UI; Coord crd;	int maxC, maxR;

	Resize_Grids_To_Level(gGrids, 1);	// Woorks ^^

	
										
										// test the all grids
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// AFFICHE TOUS LES GRIDS 
	maxC = gGrids.linkGrd.Get_Cols();
	maxR = gGrids.linkGrd.Get_Rows();
	UI = LinkSym::PARENT;

	for (int i = 0; i < maxC; i++)	// Affiche Le Link grid
	{
		for (int j = 0; j < maxR; j++)
		{
			crd = gGrids.linkGrd.link[i][j].Get_XY(); gotoxy(crd.x, crd.y); cout << UI;
		}
	}

	maxC = gGrids.wallGrdHor.Get_Cols();
	maxR = gGrids.wallGrdVer.Get_Cols();

	for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	{
		for (int j = 0; j < maxR; j++)
		{
			UI = gGrids.wallGrdHor.wall[i][j].Get_Sym();crd = gGrids.wallGrdHor.wall[i][j].Get_XY();

			UI_Dsp_Char(crd, UI, (Colors)j);


		}
	}


	maxC = gGrids.wallGrdVer.Get_Cols();
	maxR = gGrids.wallGrdVer.Get_Rows();

	for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	{
		for (int j = 0; j < maxR; j++)
		{
			UI = gGrids.wallGrdVer.wall[i][j].Get_Sym();crd = gGrids.wallGrdVer.wall[i][j].Get_XY();	UI_Dsp_Char(crd, UI, (Colors)i);

		}
	}

	for (int i = 0; i < 4; i++)	// Affiche Le spawn Grid
	{
		for (int j = 0; j < gGrids.spawnGrd.border[i].Get_Num_Spawns(); j++)
		{
			//spawnGrid->border[i].spawn[j]->GetSpawnXY(crd); 
			crd = gGrids.spawnGrd.border[i].spawn[j].Get_XY();
			UI_Dsp_String(crd, std::to_string(j), (Colors)j);	// Ceci pourrait être une fonction d'affichage

				
		}
	}

	GrdCoord Jerry = { 5,10 };
	gGrids.Activate_Chain_Of_Walls(Jerry, UP, 3);
	Jerry = { 5,20 };
	gGrids.Activate_Chain_Of_Walls(Jerry, DOWN, 2);
	Jerry = { 1,7 };
	gGrids.Activate_Chain_Of_Walls(Jerry, UP, 15);

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
	//thread Test(Test_Animation, RED, WHITE);

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
	// test la vitesse d'affichage

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------o---------

	do
	{
		// MENU LOOP
		// *********
		
		do	// Affiche MENU
		{	
			//std::thread input(Detect_Input);	// Il semblerait que threader un input rend impossible l'utilisation de Get_Key_State
			//input.join();
			Detect_Input();
			Test_Animation(RED, WHITE);

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

void Test_Animation(Colors one, Colors two)	// So pretty...
{
	Coord crd = { 0, 2 };
	int max = 35;
	char sym = 178;

	while (crd.x <= max) {

		if(crd.x % 2 == 0)
			UI_Dsp_Char(crd, sym, one);
		else
			UI_Dsp_Char(crd, 178, two);
	
		crd.x++;
	}

}