//
//#include <iostream>   // pour le cout
//#include <conio.h>   // pour le _getch()
//#include <thread>	// Pour multiplier les processus en simultané!
//#include <string>	// pour le string
//#include <iomanip> // pour les manipulateurs
//#include <windows.h> //pour le time, et toute sorte de shits.
//#include < ctime >	// pour utiliser la fonction clock()
//#include "WinUser.h"

// Pour certains affichages test
#include "../FONCTIONS/rng/rng.h"
#include "../FONCTIONS/grid/AllGrids.h"
#include "../FONCTIONS/grid/managegrids.h"
#include "../FONCTIONS/time/spawn_cycle.h"
#include "../FONCTIONS/bots/botmeta.h"
#include "../FONCTIONS/lvls/lvl_script.h"
#include "../FONCTIONS/UI/console_output/render_list.h"

#include "../FONCTIONS/update_game/update_game.h"
#include "../FONCTIONS/inputs/detect_input.h"
#include "../FONCTIONS/time/clock.h"
#include "../FONCTIONS/time/timerOP.h"
#include "../FONCTIONS/events/msg_dispatcher.h"
#include "../FONCTIONS/console/sweet_cmd_console.h"
#include "../FONCTIONS/game/initialize_game.h"

// test zone
#include "../FONCTIONS/lvls/lvl_1/msg_events/ev_arr_keys.h"
#include "../FONCTIONS/lvls/lvl_1/msg_events/ev_wasd.h"

using namespace std;

/*
			TITRE DU JEU : WALL IN

			Description: "Wall in" est un jeu d'adresse de style top-down shooter ou le joueur doit empêcher des formes de traverser les frontière de son territoire.
			Il doit faire ceci en  tirant des murs qui permettent de stopper ces formes.

			FAIT PAR : Laurent Montreuil
			
			HEURES CUMMULÉS : +/ [500 - 700]
			Environ + / -150 fichiers headers
*/




// ALL IN ONE PLACE MOTHERFUCKER!

void main()	// Le début!
{
	// START STUFF LOOP
	// ***************
	Coord crd;
	Initialize_Rng();

	// some windows stuff
	Set_Input_Buffer_Handle();	
	Set_Dflt_WND();			// Dimension de la window mon gars

	// Initialisation du jeu
	MsgQueue::Register(PLS_INTIALIZE_LVL);	// Hehe
	Initialize_Game();						// Initialize une bunch de crap
	ConsoleRender::Set_Animation_Delay();	// Comment en mode debug: Ceci rajoute du delay sur la méthode qui render l'animation queue


	// UI TESTING
	//Coord crd2 = { 45,1 }; ConsoleRender::Add_String("Spawn Waves: ", crd2 );
	Coord crd3 = { 61,1 };	// Update la combientième wave
	crd = { 13,1 };

	bool isRunning = true;
	float frameRate = 60.0f;	// f is for float, convertit la valeur en float au lieu d'un double quand tu écrit avec des décimales
	float fps = 1 / frameRate;
	float inputBuffer = fps / 3;
	bool loadBuffer = true;
	float lag = 0; 				// 	si ça dépasse le fps: lag = l'excédant. 	tu update une autre fois, mais AVEC la valeur de LAG à la place, pour rattraper
	int MS_PER_UPDATE = 10;	// Rythme à laquelle je vais update
	int loops = 0;
	int frames = 0;
	GameLoopClock::Reset_Timer();	// Premier reset
	//thread *inputs = new thread(Input_Thread_Handler);

	while (GameLoopClock::Is_Running())	// Cette loop sert de gameloop. Chaque tick représente une frame. si tu veux bouger quekchose, ta juste à multiplier la vitesse de ce quek chose par le temps écoulé entre chaque tick(deltatime)
	{
		GameLoopClock::Tick();	// Delta time est en seconde!!!
		GameLoopClock::UPD_Total_Time();	// Temps du niveau
		
		lag += GameLoopClock::Get_Delta_Time();

		// TEST DE BUFFER D'INPUT QUI MARCHE PAS
		//if (loadBuffer && GameLoopClock::Get_Delta_Time() >= inputBuffer)
		//{
		//	Load_Loop_Buffer();	// un tit buffer d'inputs
		//	loadBuffer = false;
		//}

		if (GameLoopClock::Get_Delta_Time() >= fps) { // Si le DeltaTime atteint 60 fps		
			
			// Détect les inputs mah dude0											//loadBuffer = true;
			Read_Input_Buffer();
			
			// Update le jeu mah dude
			Update_Game();				

			if (++frames == 10)	// update les infos à chaque X Frames
			{
				//cout << Timer->Get_Delta_Time() << "\t \t";		// Affiche le temps écoulé pour 1 frame. 
				//ConsoleRender::Add_String(std::to_string(gLvlTime), crd, WHITE);	// Le temps actuel
				//ConsoleRender::Add_String("  ", crd);	// efface la dizaine
				//ConsoleRender::Add_String(std::to_string(/*(int)*/(1 / GameLoopClock::Get_Delta_Time())), crd);	// Le nombre de FRAMES en une seconde, soit le framerate : 60
				//ConsoleRender::Add_String(std::to_string(gSpawnCycleTot), crd3);	// Nombre de cycles fais
				//ConsoleRender::Add_String(std::to_string(gAllBotMeta.alive), { crd3.x + 4, crd3.y });	// Nombre de bot en vie
				//ConsoleRender::Add_String(std::to_string(gAllBotMeta.spawned), { crd3.x + 8, crd3.y });	// Nombre de bot en vie
				frames = 0;
			}
			GameLoopClock::Reset_Timer();	// Reset la frame!
		}
		
		Update_Game_NOT_60FPS();	// à remove un jour lol
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

