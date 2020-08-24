
#include "ev_victory_screen.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"

#include "../../grid/AllGrids.h"
#include "../../lvls/lvl_script.h"
#include "../../math/manage_interval.h" 
#include "../../structure_manager/structure_manager.h"
#include "../../player/player.h"
#include "ev_to_proceed.h"
#include "../global_events/clear_all_states.h"

static Event ev_VictoryScreen(Ev_Victory_Screen, 5);

static Coord xy;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la première est blanche, l'autre représente la couleur du coeur
static const int DFLT_FAST_SPEED[2] = {300000, 100000};	// same logic 
static const int DFLT_SLOW_SPEED[2] = {60000, 42000};	// same logic 

static std::string GG_1 = "- YOU HAVE SURVIVED -";

// Comment faire du ascii art
static const std::string bigDAY[] = 
{
	"DDDDDDDDDDDDD                 AAA          YYYYYYY       YYYYYYY",
	"D::::::::::::DDD             A:::A         Y:::::Y       Y:::::Y",
	"D:::::::::::::::DD          A:::::A        Y:::::Y       Y:::::Y",
	"DDD:::::DDDDD:::::D        A:::::::A       Y::::::Y     Y::::::Y",
	"  D:::::D    D:::::D      A:::::::::A      YYY:::::Y   Y:::::YYY",
	"  D:::::D     D:::::D    A:::::A:::::A        Y:::::Y Y:::::Y   ",
	"  D:::::D     D:::::D   A:::::A A:::::A        Y:::::Y:::::Y    ",
	"  D:::::D     D:::::D  A:::::A   A:::::A        Y:::::::::Y     ",
	"  D:::::D     D:::::D A:::::A     A:::::A        Y:::::::Y      ",
	"  D:::::D     D:::::DA:::::AAAAAAAAA:::::A        Y:::::Y       ",
	"  D:::::D     D:::::A:::::::::::::::::::::A       Y:::::Y       ",
	"  D:::::D    D:::::A:::::AAAAAAAAAAAAA:::::A      Y:::::Y       ",
	"DDD:::::DDDDD:::::A:::::A             A:::::A     Y:::::Y       ",
	"D:::::::::::::::DA:::::A               A:::::A YYYY:::::YYYY    ",
	"D::::::::::::DDDA:::::A                 A:::::AY:::::::::::Y    ",
	"DDDDDDDDDDDDD  AAAAAAA                   AAAAAAYYYYYYYYYYYYY    "
};
static const std::string bigSurvived[] = 
{
"   SSSSSSSSSSSSSSSUUUUUUUU     UUUUUUURRRRRRRRRRRRRRRRR  VVVVVVVV           VVVVVVVIIIIIIIIIVVVVVVVV           VVVVVVVEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD        ",
" SS:::::::::::::::U::::::U     U::::::R::::::::::::::::R V::::::V           V::::::I::::::::V::::::V           V::::::E::::::::::::::::::::D::::::::::::DDD     ",
"S:::::SSSSSS::::::U::::::U     U::::::R::::::RRRRRR:::::RV::::::V           V::::::I::::::::V::::::V           V::::::E::::::::::::::::::::D:::::::::::::::DD   ",
"S:::::S     SSSSSSUU:::::U     U:::::URR:::::R     R:::::V::::::V           V::::::II::::::IV::::::V           V::::::EE::::::EEEEEEEEE::::DDD:::::DDDDD:::::D  ",
"S:::::S            U:::::U     U:::::U  R::::R     R:::::RV:::::V           V:::::V  I::::I  V:::::V           V:::::V  E:::::E       EEEEEE D:::::D    D:::::D ",
"S:::::S            U:::::D     D:::::U  R::::R     R:::::R V:::::V         V:::::V   I::::I   V:::::V         V:::::V   E:::::E              D:::::D     D:::::D",
" S::::SSSS         U:::::D     D:::::U  R::::RRRRRR:::::R   V:::::V       V:::::V    I::::I    V:::::V       V:::::V    E::::::EEEEEEEEEE    D:::::D     D:::::D",
"  SS::::::SSSSS    U:::::D     D:::::U  R:::::::::::::RR     V:::::V     V:::::V     I::::I     V:::::V     V:::::V     E:::::::::::::::E    D:::::D     D:::::D",
"    SSS::::::::SS  U:::::D     D:::::U  R::::RRRRRR:::::R     V:::::V   V:::::V      I::::I      V:::::V   V:::::V      E:::::::::::::::E    D:::::D     D:::::D",
"       SSSSSS::::S U:::::D     D:::::U  R::::R     R:::::R     V:::::V V:::::V       I::::I       V:::::V V:::::V       E::::::EEEEEEEEEE    D:::::D     D:::::D",
"            S:::::SU:::::D     D:::::U  R::::R     R:::::R      V:::::V:::::V        I::::I        V:::::V:::::V        E:::::E              D:::::D     D:::::D",
"            S:::::SU::::::U   U::::::U  R::::R     R:::::R       V:::::::::V         I::::I         V:::::::::V         E:::::E       EEEEEE D:::::D    D:::::D ",
"SSSSSSS     S:::::SU:::::::UUU:::::::URR:::::R     R:::::R        V:::::::V        II::::::II        V:::::::V        EE::::::EEEEEEEE:::::DDD:::::DDDDD:::::D  ",
"S::::::SSSSSS:::::S UU:::::::::::::UU R::::::R     R:::::R         V:::::V         I::::::::I         V:::::V         E::::::::::::::::::::D:::::::::::::::DD   ",
"S:::::::::::::::SS    UU:::::::::UU   R::::::R     R:::::R          V:::V          I::::::::I          V:::V          E::::::::::::::::::::D::::::::::::DDD     ",
"SSSSSSSSSSSSSSS         UUUUUUUUU     RRRRRRRR     RRRRRRR           VVV           IIIIIIIIII           VVV           EEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD         "
};

static int length[2] = { bigDAY[0].size(), bigSurvived[0].size() };
static int height = 16;


// Le contour va avoir 1 string en haut en bas à gauche et à droite de plus que le dedans
static Intervals::ManageIntervalLists day(height, 0, length[0]); 
static Intervals::ManageIntervalLists survived(6, 0, length[1]);

static const std::string* victoryWords[2] = { bigDAY, bigSurvived };	// all of the hearts

// CHOIX DE DESIGN
// . . .


/*


													DDDDDDDDDDDDD                 AAA          YYYYYYY       YYYYYYY  
													D::::::::::::DDD             A:::A         Y:::::Y       Y:::::Y  
													D:::::::::::::::DD          A:::::A        Y:::::Y       Y:::::Y  
													DDD:::::DDDDD:::::D        A:::::::A       Y::::::Y     Y::::::Y  
													  D:::::D    D:::::D      A:::::::::A      YYY:::::Y   Y:::::YYY  
													  D:::::D     D:::::D    A:::::A:::::A        Y:::::Y Y:::::Y     
													  D:::::D     D:::::D   A:::::A A:::::A        Y:::::Y:::::Y      
													  D:::::D     D:::::D  A:::::A   A:::::A        Y:::::::::Y       
													  D:::::D     D:::::D A:::::A     A:::::A        Y:::::::Y        
													  D:::::D     D:::::DA:::::AAAAAAAAA:::::A        Y:::::Y         
													  D:::::D     D:::::A:::::::::::::::::::::A       Y:::::Y         
													  D:::::D    D:::::A:::::AAAAAAAAAAAAA:::::A      Y:::::Y         
													DDD:::::DDDDD:::::A:::::A             A:::::A     Y:::::Y         
													D:::::::::::::::DA:::::A               A:::::A YYYY:::::YYYY      
													D::::::::::::DDDA:::::A                 A:::::AY:::::::::::Y      
													DDDDDDDDDDDDD  AAAAAAA                   AAAAAAYYYYYYYYYYYYY      


      SSSSSSSSSSSSSSSUUUUUUUU     UUUUUUURRRRRRRRRRRRRRRRR  VVVVVVVV           VVVVVVVIIIIIIIIIVVVVVVVV           VVVVVVVEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD		     !!:!!
	SS:::::::::::::::U::::::U     U::::::R::::::::::::::::R V::::::V           V::::::I::::::::V::::::V           V::::::E::::::::::::::::::::D::::::::::::DDD	     !:::!
   S:::::SSSSSS::::::U::::::U     U::::::R::::::RRRRRR:::::RV::::::V           V::::::I::::::::V::::::V           V::::::E::::::::::::::::::::D:::::::::::::::DD     !:::!
   S:::::S     SSSSSSUU:::::U     U:::::URR:::::R     R:::::V::::::V           V::::::II::::::IV::::::V           V::::::EE::::::EEEEEEEEE::::DDD:::::DDDDD:::::D    !:::!
   S:::::S            U:::::U     U:::::U  R::::R     R:::::RV:::::V           V:::::V  I::::I  V:::::V           V:::::V  E:::::E       EEEEEE D:::::D    D:::::D   !:::!
   S:::::S            U:::::D     D:::::U  R::::R     R:::::R V:::::V         V:::::V   I::::I   V:::::V         V:::::V   E:::::E              D:::::D     D:::::D  !:::!
	S::::SSSS         U:::::D     D:::::U  R::::RRRRRR:::::R   V:::::V       V:::::V    I::::I    V:::::V       V:::::V    E::::::EEEEEEEEEE    D:::::D     D:::::D  !:::!
	 SS::::::SSSSS    U:::::D     D:::::U  R:::::::::::::RR     V:::::V     V:::::V     I::::I     V:::::V     V:::::V     E:::::::::::::::E    D:::::D     D:::::D  !:::!
	   SSS::::::::SS  U:::::D     D:::::U  R::::RRRRRR:::::R     V:::::V   V:::::V      I::::I      V:::::V   V:::::V      E:::::::::::::::E    D:::::D     D:::::D  !:::!
		  SSSSSS::::S U:::::D     D:::::U  R::::R     R:::::R     V:::::V V:::::V       I::::I       V:::::V V:::::V       E::::::EEEEEEEEEE    D:::::D     D:::::D  !!:!!
			   S:::::SU:::::D     D:::::U  R::::R     R:::::R      V:::::V:::::V        I::::I        V:::::V:::::V        E:::::E              D:::::D     D:::::D   !!!
			   S:::::SU::::::U   U::::::U  R::::R     R:::::R       V:::::::::V         I::::I         V:::::::::V         E:::::E       EEEEEE D:::::D    D:::::D   
   SSSSSSS     S:::::SU:::::::UUU:::::::URR:::::R     R:::::R        V:::::::V        II::::::II        V:::::::V        EE::::::EEEEEEEE:::::DDD:::::DDDDD:::::D     !!!
   S::::::SSSSSS:::::S UU:::::::::::::UU R::::::R     R:::::R         V:::::V         I::::::::I         V:::::V         E::::::::::::::::::::D:::::::::::::::DD     !!:!!
   S:::::::::::::::SS    UU:::::::::UU   R::::::R     R:::::R          V:::V          I::::::::I          V:::V          E::::::::::::::::::::D::::::::::::DDD	      !!!
	SSSSSSSSSSSSSSS        UUUUUUUUU     RRRRRRRR     RRRRRRR           VVV           IIIIIIIIII           VVV           EEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD		      !!!














*/
static void Dr_Victory_Phrase()
{
	Coord crd = { Find_Ctr_X(length[0]), 10 };
	for (int word = 0; word < 2; word++)
	{
		for (int line = 0; line < 16; line++)
		{			
			ConsoleRender::Add_String(victoryWords[word][line], crd);
			crd.y++;
		}
		crd.y++;
		crd.x = 4;
		Sleep(1000);
	}
}

static void Dr_Day()
{
	Coord crd = { Find_Ctr_X(length[0]), 12 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(bigDAY[line], { crd.x, crd.y + line });

}
static void Dr_Victory()
{
	Coord crd = { 5, 30 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(bigSurvived[line], { crd.x, crd.y + line });

}

 void Ev_Victory_Screen()				 // Affiche un écran qui gratifiant		 // Affiche le coueur à ses différents stades
{
	 static int rng[2];
	 static int rdmLength[2];
	 static int rdmClr[2];
	 static int rdmHeight[2];

	if (!ev_VictoryScreen.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X() - 8;		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y;

		Clear_All_States(false);
		ev_VictoryScreen.Activate();
		ev_VictoryScreen.Start(400);
	}
	else
		while (ev_VictoryScreen.delay.Tick())
		{
			switch (ev_VictoryScreen.Get_Current_Step())
			{
			case 1:
				
				Dr_Day();
				//Dr_Victory_Phrase();
				//ListsOfChainToModify::Annihilate_All_Links();
				//P1.Er_Player(); // efface joueur
				ev_VictoryScreen.Advance(500);
				break;

			case 2: // tit break
				Dr_Victory();
				ev_VictoryScreen.Advance(1000);
				break;

			case 3:
			//	ConsoleRender::Add_String(GG_1, ori, LIGHT_GREEN, 450);
				ev_VictoryScreen.Advance(500); 
				break;

			case 4:
				Press_X_To_Proceed(0);
				ev_VictoryScreen.Advance(00); 
				ev_VictoryScreen.delay.Start_Timer(1000000, 1 ,true); 
				break;

			case 5:
				//rng[0] = rand();
				//rng[1] = rng[0] + 7;
				//rdmHeight[0] = rng[0] % 16;
				//rdmHeight[1] = rng[1] % 16;
				//rdmLength[0] = rng[0] % length[0];
				//rdmLength[1] = rng[1] % length[1];
				//rdmClr[0] = (rng[0] % 16) +1;
				//rdmClr[1] = (rng[1] % 16) +1;

				//if(bigDAY[rdmHeight[0]][rdmLength[0]] != TXT_CONST.SPACE && bigDAY[rdmHeight[0]][rdmLength[0]] != ':')
				//	ConsoleRender::Add_Char({ Find_Ctr_X(length[0]) + rdmLength[0], 10 + rdmHeight[0] },bigDAY[rdmHeight[0]][rdmLength[0]], (Colors)rdmClr[0]);
				//
				//if (bigSurvived[rdmHeight[1]][rdmLength[1]] != TXT_CONST.SPACE && bigSurvived[rdmHeight[1]][rdmLength[1]] != ':')
				//	ConsoleRender::Add_Char({ 4+ rdmLength[1] , 26 + rdmHeight[1] },bigSurvived[rdmHeight[1]][rdmLength[1]], (Colors)rdmClr[1]);
				break;
			}
		}
}
