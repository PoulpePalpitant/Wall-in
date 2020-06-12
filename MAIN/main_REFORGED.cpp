//
#include <iostream>   // pour le cout
#include <conio.h>   // pour le _getch()
#include <thread>	// Pour multiplier les processus en simultané!
//#include <string>	// pour le string
//#include <iomanip> // pour les manipulateurs
//#include <windows.h> //pour le time, et toute sorte de shits.
//#include < ctime >	// pour utiliser la fonction clock()
//#include "WinUser.h"

#include "../FONCTIONS/rng/rng.h"
#include "../FONCTIONS/time/clock.h"
#include "../FONCTIONS/grid/managegrids.h"
#include "../FONCTIONS/structure_manager/structure_manager.h"
#include "../FONCTIONS/grid/AllGrids.h"
#include "../FONCTIONS/link/link.h"
#include "../FONCTIONS/bots/botlist.h"
#include "../FONCTIONS/bots/bot.h"
#include "../FONCTIONS/bots/botinitialize/bot_intializer.h"
#include "../FONCTIONS/bots/botmove.h"
#include "../FONCTIONS/spawns/spawn_bot.h"
#include "../FONCTIONS/spawns/bots_to_spawn.h"
#include "../FONCTIONS/spawns/valid_spwn_intervals.h"

#include "../FONCTIONS/UI/console_output/dsp_char.h"
#include "../FONCTIONS/UI/console_output/dsp_string.h"


#include "../FONCTIONS/inputs/detect_input.h"
using namespace std;


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le début!
{
	// START STUFF LOOP
	// ***************

	Initialize_Rng();

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

	/*CONCLUSION: C'est impossible. La liste chaîné prend de l'espace mémoire non-sucessive. Ce qui veut dire que chaques adresses peuvent être n'importe où.*/


	/* test les spawns bot*/
	ValidSpwnIntervals::Initialize_Valid_Spawn_List();	// Doit Initialiser les listes d'ABORD!

	/* Attributs généraux testé*/
	//bots_to_spawn::gBoxSide = LEFT;		// ça essaie de spawn à gauche 

	bots_to_spawn::Add_Spwns(6);
	bots_to_spawn::Set_Interval(LEFT, 5, 8);
	//bots_to_spawn::Set_Interval(RIGHT, 5, 8);

	bots_to_spawn::Set_Randomness();
	Spawn_Bot();
	BotMove::Move_Bots();	// we show where they are
	bots_to_spawn::Reset_To_Default();
	bots_to_spawn::gNumSpawnTOT = 10;	// repeat, pour vérifier si sa block
	bots_to_spawn::gHorizontalBorder = true;		// vertical 
	bots_to_spawn::Set_Interval(LEFT, 3, 13);	// interval trop grand
	bots_to_spawn::gRandomSpwn = false;
	bots_to_spawn::Add_Specific(RIGHT, -1);
	gCustomBot.is = true;		
	gCustomBot.health = 100;		// thats strongk!
	Spawn_Bot();

	BotMove::Move_Bots();	// we show where they are

	/* test les spawns bot*/



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

