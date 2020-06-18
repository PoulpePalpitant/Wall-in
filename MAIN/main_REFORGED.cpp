//
#include <iostream>   // pour le cout
#include <conio.h>   // pour le _getch()
#include <thread>	// Pour multiplier les processus en simultan�!
//#include <string>	// pour le string
//#include <iomanip> // pour les manipulateurs
//#include <windows.h> //pour le time, et toute sorte de shits.
//#include < ctime >	// pour utiliser la fonction clock()
//#include "WinUser.h"

#include "../FONCTIONS/rng/rng.h"
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

#include "../FONCTIONS/update_game/update_game.h"
#include "../FONCTIONS/inputs/detect_input.h"
#include "../FONCTIONS/time/clock.h"
#include "../FONCTIONS/time/timerOP.h"
#include "../FONCTIONS/bots/botmeta.h"
using namespace std;


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le d�but!
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
			UI_Dsp_String(crd, std::to_string(j), (Colors)j);	// Ceci pourrait �tre une fonction d'affichage


		}
	}

	/*CONCLUSION: C'est impossible. La liste cha�n� prend de l'espace m�moire non-sucessive. Ce qui veut dire que chaques adresses peuvent �tre n'importe o�.*/


	///* test les spawns bot*/
	//ValidSpwnIntervals::Initialize_Valid_Spawn_List();	// Doit Initialiser les listes d'ABORD!

	///* Attributs g�n�raux test�*/
	////bots_to_spawn::gBoxSide = LEFT;		// �a essaie de spawn � gauche 

	//bots_to_spawn::Reset_To_Default();
	//bots_to_spawn::Add_Spwns(0);
	//bots_to_spawn::Set_Interval(DOWN, 5, 10);
	//bots_to_spawn::Add_Specific(DOWN, 9);
	//bots_to_spawn::gVerticalBorder = true;

	//bots_to_spawn::Set_Randomness();Spawn_Bots();bots_to_spawn::Reset_To_Default();
	//
	//
	//BotMove::Move_Bots();	// we show where they are
	//bots_to_spawn::Add_Spwns(300);	// repeat, pour v�rifier si sa block
	//bots_to_spawn::Set_Interval(LEFT, 3, 100);	// interval trop grand, il ne sera m�me pas consid�r� mon vieux :)
	//gCustomBot.is = true;		
	//gCustomBot.health = 100;		// thats strongk!
	//bots_to_spawn::Set_Randomness();Spawn_Bots();bots_to_spawn::Reset_To_Default();


	//BotMove::Move_Bots();	// we show where they are
	///* test les spawns bot*/



	// CLOCK TESTING
	Coord crd2 = { 45,1 }; UI_Dsp_String(crd2, "Bots Alive");
	Coord crd3 = { 59,1 };	// Update bot alive count

	GameClock LvlClock;
	LvlClock.clockName = "Swag Clock";
	crd = { 0,1 };
	LvlClock.Dsp_Name(crd);
	crd = { 13,1 };
	LvlClock.Start_Clock();	// Start l'horologe en bakcground!




	// La clock du dude    #include "timerOp"

	bool isRunning = true;
	float frameRate = 60.0f;// f is for float, convertit la valeur en float au lieu d'un double quand tu �crit avec des d�cimales
	float fps = 1 / frameRate;


	TimerOP* Timer = TimerOP::Set_Instance();

	while (isRunning)	// Cette loop sert de gameloop. Chaque tick repr�sente une frame. si tu veux bouger quekchose, ta juste � multiplier la vitesse de ce quek chose par le temps �coul� entre chaque tick(deltatime)
	{
		Timer->Tick();	// Delta time est en seconde!!!
		//Timer->Reset_Timer();				// Dur�e entre End-Start
		gLvlTime += Timer->Get_Delta_Time();	// Update du temps actuel
		

		if (Timer->Get_Delta_Time() >= fps) { // Si le DeltaTime atteint 60 fps			
		Timer->Reset_Timer();	// Reset la frame!

		Detect_Input();		// D�tect les inputs mah dude0
		Update_Game();		// Update le jeu mah dude
		//// render stuff	// Fait tout les affichages

			//cout << Timer->Get_Delta_Time() << "\t \t";		// Affiche le temps �coul� pour 1 frame. 
			//cout << 1 / Timer->Get_Delta_Time() << "\t \t";	// Le nombre de FRAMES en une seconde, soit le framerate : 60
			// OU cout << gLvlTime << endl;		// Temps total �coul�
		
		UI_Dsp_String(crd, std::to_string(gLvlTime));	
		if(gAllBotMeta.alive > 30)
			UI_Dsp_String(crd3, std::to_string(gAllBotMeta.alive));	

		}
	}

	Timer->Release(); // Release da timer

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------o---------
		// GAME LOOP DES INTERNETS!


		//double previous = getCurrentTime();
		//double lag = 0.0;
		//while (true)
		//{
		//	double current = getCurrentTime();
		//	double elapsed = current - previous;
		//	previous = current;
		//	lag += elapsed;

		//	processInput();

		//	while (lag >= MS_PER_UPDATE)
		//	{
		//		update();
		//		lag -= MS_PER_UPDATE;
		//	}

		//	render();
		//}


		// POUR PASSER une r�f�rence dans un thread, tu es obliger d'utiliser		std::ref("mavariable")
	//	Exemple fonctionel : std::thread destroyTHREAD(&DestroyChainOfWalls::LameStaticFunction, false, std::ref(fuck), swag);

	//LOAD FILES

	// GAME LOOP	MENU LOOP	
	// *********	*********


	gameClockTEST.Start_Clock(); 	// time test 

	while (gIsRunning)	// Le jeu est ouvert
	{
		gameClockTEST.Tick();	// va ajouter du temps � chaque loop � la place
		gameClockTEST.Dsp_Time(crd);

		Detect_Input();		// D�tect les inputs mah dude0
		Update_Game();		// Update le jeu mah dude

	}

	// SAVE FILES

}	// OU :)

