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
#include "../FONCTIONS/math/manage_interval.h"
#include "../FONCTIONS/time/spawn_cycle.h"
// test//
#include "../FONCTIONS/events/global_events/ev_update_heart.h"
//
#include "../FONCTIONS/UI/console_output/dsp_char.h"
#include "../FONCTIONS/UI/console_output/dsp_string.h"

#include "../FONCTIONS/update_game/update_game.h"
#include "../FONCTIONS/UI/console_output/render_list.h"
#include "../FONCTIONS/inputs/detect_input.h"
#include "../FONCTIONS/time/clock.h"
#include "../FONCTIONS/time/timerOP.h"
#include "../FONCTIONS/bots/botmeta.h"
#include "../FONCTIONS/inputs/action_input.h"
#include "../FONCTIONS/events/msg_dispatcher.h"
#include "../FONCTIONS/console/sweet_cmd_console.h"

#include "../FONCTIONS/game/initialize_game.h"

using namespace std;


// ALL IN ONE PLACE MOTHERFUCKER!

int main()	// Le début!
{
	// START STUFF LOOP
	// ***************
	Coord crd;
	Initialize_Rng();


	// test the all grids
	////------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//char UI; int maxC, maxR;

	Resize_Grids_To_Level(gGrids, 1);	// Woorks ^^



	//// AFFICHE TOUS LES GRIDS 
	//maxC = gGrids.linkGrd.Get_Cols();
	//maxR = gGrids.linkGrd.Get_Rows();
	//UI = LinkSym::PARENT;

	//for (int i = 0; i < maxC; i++)	// Affiche Le Link grid
	//{
	//	for (int j = 0; j < maxR; j++)
	//	{
	//		crd = gGrids.linkGrd.link[i][j].Get_XY(); gotoxy(crd.x, crd.y); cout << UI;
	//	}
	//}

	//maxC = gGrids.wallGrdHor.Get_Cols();
	//maxR = gGrids.wallGrdVer.Get_Cols();

	//for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	//{
	//	for (int j = 0; j < maxR; j++)
	//	{
	//		UI = gGrids.wallGrdHor.wall[i][j].Get_Sym();crd = gGrids.wallGrdHor.wall[i][j].Get_XY();

	//		UI_Dsp_Char(crd, UI, (Colors)j);


	//	}
	//}

	//maxC = gGrids.wallGrdVer.Get_Cols();
	//maxR = gGrids.wallGrdVer.Get_Rows();

	//for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
	//{
	//	for (int j = 0; j < maxR; j++)
	//	{
	//		UI = gGrids.wallGrdVer.wall[i][j].Get_Sym();crd = gGrids.wallGrdVer.wall[i][j].Get_XY();	UI_Dsp_Char(crd, UI, (Colors)i);

	//	}
	//}

	//for (int i = 0; i < 4; i++)	// Affiche Le spawn Grid
	//{
	//	for (int j = 0; j < gGrids.spawnGrd.border[i].Get_Num_Spawns(); j++)
	//	{
	//		//spawnGrid->border[i].spawn[j]->GetSpawnXY(crd); 
	//		crd = gGrids.spawnGrd.border[i].spawn[j].Get_XY();
	//		ConsoleRender::Add_String(std::to_string(j),crd,(Colors)j);


	//	}
	//}

	//Coord XYCOLOR = { 0,0 };
	//for (int i = 0; i < 500; i++)
	//{
	//	Change_Color(i);
	//	XYCOLOR.x++;

	//	cout << i;

	//	if (XYCOLOR.x == 20)
	//	{
	//		XYCOLOR.x = 0;
	//		XYCOLOR.y++;
	//	}
	//}



	Intervals::ManageIntervalLists itemSpwLocations(linkGrid->Get_Cols(), 0, linkGrid->Get_Rows());
	itemSpwLocations.Empty_List(4);	// Vide la colonne #4
	itemSpwLocations.Add_Interval_On_Top(2, -7, 12);
	itemSpwLocations.Exclude_Interval_From_List(5, -7, 12);
	itemSpwLocations.Remove_Value(7, 3);
	int col = 0, row = 0;	itemSpwLocations.Pick_From_Lists(col, row, true, false, Intervals::RDM_ALL);

	itemSpwLocations.Resize(linkGrid->Get_Cols(), 0, 2);

	while (!itemSpwLocations.Is_All_Empty())	// breaking time
	{
		itemSpwLocations.Pick_From_Lists(col, row, true, true, Intervals::RDM_ALL);
	}

	itemSpwLocations.Reset_All_Lists();
	itemSpwLocations.~ManageIntervalLists();

	Intervals::ManageIntervalLists* itemSpwLocations2 = new Intervals::ManageIntervalLists(linkGrid->Get_Cols(), 0, linkGrid->Get_Rows());

	/*CONCLUSION: C'est impossible. La liste chaîné prend de l'espace mémoire non-sucessive. Ce qui veut dire que chaques adresses peuvent être n'importe où.*/



	/* test manual wall creation*/

	//gGrids.Activate_Chain_Of_Walls({ 8,6 }, LEFT, 5);
	//gGrids.Activate_Chain_Of_Walls({ 6,5 }, UP, 6);
	//gGrids.Activate_Chain_Of_Walls({ 6,7 }, DOWN, 6);


	// some windows stuff
	Set_Input_Buffer_Handle();	


	Setup_Console_Window();	// Titre et curseur
	MsgQueue::Register(PLS_INTIALIZE_LVL);	// Hehe
	Set_Dflt_WND();			// Dimension de la window mon gars
	Initialize_Game();		// Initialize une bunch de crap

	// CLOCK TESTING
	Coord crd2 = { 45,1 }; UI_Dsp_String(crd2, "Spawn Waves: ");
	Coord crd3 = { 61,1 };	// Update la combientième wave

	//GameClock LvlClock;
	//LvlClock.clockName = "Swag Clock";crd = { 0,1 };LvlClock.Dsp_Name(crd);
	crd = { 13,1 };
	//LvlClock.Start_Clock();	// Start l'horloge 

	bool isRunning = true;
	float frameRate = 60.0f;// f is for float, convertit la valeur en float au lieu d'un double quand tu écrit avec des décimales
	float fps = 1 / frameRate;
	float inputBuffer = fps / 3;
	bool loadBuffer = true;
	float lag = 0;
	int MS_PER_UPDATE = 10;	// Rythme à laquelle je veais ttout update
	int loops = 0;
	int frames = 0;
	
	GameLoopClock::Reset_Timer();	// Premier reset
	//thread *inputs = new thread(Input_Thread_Handler);

	while (GameLoopClock::Is_Running())	// Cette loop sert de gameloop. Chaque tick représente une frame. si tu veux bouger quekchose, ta juste à multiplier la vitesse de ce quek chose par le temps écoulé entre chaque tick(deltatime)
	{
		GameLoopClock::Tick();	// Delta time est en seconde!!!
		GameLoopClock::UPD_Total_Time();	// Temps du niveau
		
		lag += GameLoopClock::Get_Delta_Time();

		if (loadBuffer && GameLoopClock::Get_Delta_Time() >= inputBuffer)
		{
			Load_Loop_Buffer();	// un tit buffer d'inputs
			loadBuffer = false;
		}


		if (GameLoopClock::Get_Delta_Time() >= fps) { // Si le DeltaTime atteint 60 fps		
			
			loadBuffer = true;
			Read_Input_Buffer();
			//Detect_Input();				// Détect les inputs mah dude0

				/*
				si ça dépasse le fps: lag = l'excédant
				tu update une autre fois, mais AVEC la valeur de LAG à la place, pour rattraper
				*/
			Update_Game();				// Update le jeu mah dude

			/* pour tester si ça work for real*/
			//cout << Timer->Get_Delta_Time() << "\t \t";		// Affiche le temps écoulé pour 1 frame. 
			if (++frames == 25)	// update les infos à chaque X Frames
			{
			//	ConsoleRender::Add_String(std::to_string(gLvlTime), crd, WHITE);	// Le temps actuel
				ConsoleRender::Add_String(std::to_string((int)(1 / GameLoopClock::Get_Delta_Time())), crd);	// Le nombre de FRAMES en une seconde, soit le framerate : 60
				ConsoleRender::Add_String(std::to_string(gSpawnCycleTot), crd3);	// Nombre de cycles fais
				ConsoleRender::Add_String(std::to_string(gAllBotMeta.alive), { crd3.x + 4, crd3.y });	// Nombre de bot en vie
				ConsoleRender::Add_String(std::to_string(gAllBotMeta.spawned), { crd3.x + 8, crd3.y });	// Nombre de bot en vie

				frames = 0;
			}
			GameLoopClock::Reset_Timer();	// Reset la frame!
		}
		
		Update_Game_NOT_60FPS();	// à remove un jour	
		ConsoleRender::Render();	// Fait tout les affichages
	}

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
	

	// SAVE FILES

}	// OU :)

