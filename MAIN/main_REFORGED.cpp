
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
#include "../FONCTIONS/DB/database.h"


// test zone
#include "../FONCTIONS/lvls/lvl_1/msg_events/ev_arr_keys.h"
#include "../FONCTIONS/lvls/lvl_1/msg_events/ev_wasd.h"

using namespace std;

/*r
			TITRE DU JEU : WALL IN

			Description: "Wall in" est un jeu de puzzle de style top-down shooter ou le joueur doit empêcher des formes de traverser les frontière de son territoire.
			Il doit faire ceci en tirant des murs qui permettent de stopper ces formes.

			FAIT PAR : Laurent Montreuil
			
			HEURES CUMMULÉS : +/ [500 - 700]
			Environ + / -150 fichiers headers
*/




// ALL IN ONE PLACE MOTHERFUCKER!

void main()	// Le début!
{
	// SUPRA TESTING PLACE
	// *******************


	// Load la save file
	Load();

	// START STUFF LOOP
	// ***************
	Coord crd,crd2,crd3;
	Initialize_Rng();

	// some windows stuff
	Set_Input_Buffer_Handle();	
	Set_Dflt_WND();			// "Résolution" et autres

	// Initialisation du jeu
	MsgQueue::Register(PLS_INTIALIZE_LVL);	
	Initialize_Game();			

	// UI TESTING
	crd = { 13,1 };
	crd2 = { 45,1 }; 
	crd3 = { 61,1 };	

	float frameRate = 60.0f;	
	float fps = 1 / frameRate;
	bool loadBuffer = true;
	int frames = 0;

	GameLoopClock::Reset_Timer();	// Premier reset
	//thread *inputs = new thread(Input_Thread_Handler);	// Reminder d'une tentative de Multithreading


	while (GameLoopClock::Is_Running())	
	{
		GameLoopClock::Tick();	// Delta time est en seconde!!!
		
		if (GameLoopClock::Get_Delta_Time() >= fps) { // Si le DeltaTime atteint 60 fps		
			
			// Détect les inputs mah dude0										
			Read_Input_Buffer();
			
			// Update le jeu mah dude
			Update_Game();				


			// GARDER ICI POUR PÉNITENCE
			ConsoleRender::Render_String_Animation();	// Affiche les éléments des listes d'animation, solution très simplistes pour créer de l'animation linéaire, principalement pour les string.

			if (++frames == 60)	// update les infos à chaque X Frames
			{
				//ConsoleRender::Add_String(std::to_string(GameLoopClock::Get_Delta_Time()),crd);		// Affiche le temps écoulé pour 1 frame. 
				//ConsoleRender::Add_String(std::to_string(gLvlTime), crd, WHITE);	// Le temps actuel
				//ConsoleRender::Add_String("  ", crd);								// efface la dizaine
				//ConsoleRender::Add_String(std::to_string(/*(int)*/(1 / GameLoopClock::Get_Delta_Time())), crd);	// Le nombre de FRAMES en une seconde, soit le framerate : 60
				//ConsoleRender::Add_String(std::to_string(gAllBotMeta.alive), { crd3.x + 4, crd3.y });		// Nombre de bot en vie
				//ConsoleRender::Add_String(std::to_string(gCurrPuzzleStep), {crd3.x + 3, crd3.y });	// Nombre de cycles fais
				//ConsoleRender::Add_String(std::to_string(gCurrentPuzzle[gCurrentLevel - 1]), crd3);	// Le puzzle actuel
				frames = 0;
			}
			GameLoopClock::Reset_Timer();	// Reset la frame!
		}

		Update_Game_NOT_60FPS();	// à remove un jour lol
		ConsoleRender::Render();	// Fait tout les affichages
	}

	// SAVE FILE
	Save();

}	

