
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
#include "ev_make_it_rain.h"
#include "../../console/sweet_cmd_console.h"
#include "../../blast/blast_ammo_animator.h"

static Event ev_VictoryScreen(Ev_Victory_Screen, 5);

static Coord xy;
static Coord ori;		// Coordonn�e d'origine, servira de r�f�rence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la premi�re est blanche, l'autre repr�sente la couleur du coeur
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

static const std::string level[] = {
    "LLLLLLLLLLL                                                                              lllllll ",
	"L:::::::::L                                                                              l:::::l ",
	"L:::::::::L                                                                              l:::::l ",
	"LL:::::::LL                                                                              l:::::l ",
	"  L:::::L                   eeeeeeeeeeee    vvvvvvv           vvvvvvv    eeeeeeeeeeee     l::::l ",
	"  L:::::L                 ee::::::::::::ee   v:::::v         v:::::v   ee::::::::::::ee   l::::l ",
	"  L:::::L                e::::::eeeee:::::ee  v:::::v       v:::::v   e::::::eeeee:::::ee l::::l ",
	"  L:::::L               e::::::e     e:::::e   v:::::v     v:::::v   e::::::e     e:::::e l::::l ",
	"  L:::::L               e:::::::eeeee::::::e    v:::::v   v:::::v    e:::::::eeeee::::::e l::::l ",
	"  L:::::L               e:::::::::::::::::e      v:::::v v:::::v     e:::::::::::::::::e  l::::l ",
	"  L:::::L               e::::::eeeeeeeeeee        v:::::v:::::v      e::::::eeeeeeeeeee   l::::l ",
	"  L:::::L         LLLLLLe:::::::e                  v:::::::::v       e:::::::e            l::::l ",
	"LL:::::::LLLLLLLLL:::::Le::::::::e                  v:::::::v        e::::::::e          l::::::l",
	"L::::::::::::::::::::::L e::::::::eeeeeeee           v:::::v          e::::::::eeeeeeee  l::::::l",
	"L::::::::::::::::::::::L  ee:::::::::::::e            v:::v            ee:::::::::::::e  l::::::l",
	"LLLLLLLLLLLLLLLLLLLLLLLL    eeeeeeeeeeeeee             vvv               eeeeeeeeeeeeee  llllllll"

};

static const std::string complete[] = {
	"     CCCCCCCCCCCCC                                                              lllllll                              tttt                                ",
	"    CCC::::::::::::C                                                             l:::::l                           ttt:::t                               ",
	"   CC:::::::::::::::C                                                             l:::::l                           t:::::t                              ",
	"  C:::::CCCCCCCC::::C                                                             l:::::l                           t:::::t                              ",
	" C:::::C       CCCCCC   ooooooooooo      mmmmmmm    mmmmmmm   ppppp   ppppppppp    l::::l     eeeeeeeeeeee    ttttttt:::::ttttttt        eeeeeeeeeeee    ",
	"C:::::C               oo:::::::::::oo  mm:::::::m  m:::::::mm p::::ppp:::::::::p   l::::l   ee::::::::::::ee  t:::::::::::::::::t      ee::::::::::::ee  ",
	"C:::::C              o:::::::::::::::om::::::::::mm::::::::::mp:::::::::::::::::p  l::::l  e::::::eeeee:::::eet:::::::::::::::::t     e::::::eeeee:::::ee",
	"C:::::C              o:::::ooooo:::::om::::::::::::::::::::::mpp::::::ppppp::::::p l::::l e::::::e     e:::::etttttt:::::::tttttt    e::::::e     e:::::e",
	"C:::::C              o::::o     o::::om:::::mmm::::::mmm:::::m p:::::p     p:::::p l::::l e:::::::eeeee::::::e      t:::::t          e:::::::eeeee::::::e",
	"C:::::C              o::::o     o::::om::::m   m::::m   m::::m p:::::p     p:::::p l::::l e:::::::::::::::::e       t:::::t          e:::::::::::::::::e ",
	"C:::::C              o::::o     o::::om::::m   m::::m   m::::m p:::::p     p:::::p l::::l e::::::eeeeeeeeeee        t:::::t          e::::::eeeeeeeeeee  ",
	" C:::::C       CCCCCCo::::o     o::::om::::m   m::::m   m::::m p:::::p    p::::::p l::::l e:::::::e                 t:::::t    tttttte:::::::e           ",
	"  C:::::CCCCCCCC::::Co:::::ooooo:::::om::::m   m::::m   m::::m p:::::ppppp:::::::pl::::::le::::::::e                t::::::tttt:::::te::::::::e          ",
	"   CC:::::::::::::::Co:::::::::::::::om::::m   m::::m   m::::m p::::::::::::::::p l::::::l e::::::::eeeeeeee        tt::::::::::::::t e::::::::eeeeeeee  ",
	"    CCC::::::::::::C oo:::::::::::oo m::::m   m::::m   m::::m p::::::::::::::pp  l::::::l  ee:::::::::::::e          tt:::::::::::tt  ee:::::::::::::e	  ",
	"     CCCCCCCCCCCCC   ooooooooooo   mmmmmm   mmmmmm   mmmmmm p::::::pppppppp    llllllll    eeeeeeeeeeeeee              ttttttttttt      eeeeeeeeeeeeee	  ",
	"                                                              p:::::p                                                                                    ",
	"                                                              p:::::p                                                                                    ",
	"                                                             p:::::::p                                                                                   ",
	"                                                             p:::::::p                                                                                   ",
	"                                                             p:::::::p                                                                                   ",
	"                                                             ppppppppp                                                                                   ",
};

static int length[2] = { (int)(bigDAY[0].size()), (int)(bigSurvived[0].size()) };
static int length2[2] = { (int)(level[0].size()), (int)(complete[0].size()) };
static int height = 16;

static const std::string* victoryWords[2] = { bigDAY, bigSurvived };	
static const std::string* victoryWords2[2] = { level, complete};


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
	Coord crd = { Find_Ctr_X(length[1]), 12+ height+ 4 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(bigSurvived[line], { crd.x, crd.y + line });

}

static void Dr_Level()
{
	Coord crd = { Find_Ctr_X(length2[0]), 10 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(level[line], { crd.x, crd.y + line });

}
static void Dr_Complete()
{
	Coord crd = { Find_Ctr_X(length2[1]), 10 + height + 4 };
	for (int line = 0; line < 22; line++)
		ConsoleRender::Add_String(complete[line], { crd.x, crd.y + line });

}


 void Ev_Victory_Screen()				 // Affiche un �cran qui gratifiant		 // Affiche le coueur � ses diff�rents stades
{
	 static int rng[2];
	 static int rdmLength[2];
	 static int rdmClr[2];
	 static int rdmHeight[2];

	if (!ev_VictoryScreen.Is_Active())
	{
		// La console doit �tre sett� pour utiliser �a
		ori.x = Find_Ctr_X() - 8;		// L'afficahge du coeur se fera � partir d'un point central, situ� en plein milieu de la fen�tre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y;

		Clear_All_States(false);
		DrawBlastAmmo:: Dr_Ammo_Title(false);

		ev_VictoryScreen.Activate();
		ev_VictoryScreen.Start(600);
	}
	else
		while (ev_VictoryScreen.delay.Tick())
		{
			switch (ev_VictoryScreen.Get_Current_Step())
			{
			case 1:
				
				Dr_Level();
				ev_VictoryScreen.Advance(500);
				break;

			case 2: // tit break
				Dr_Complete();
				ev_VictoryScreen.Advance(10000);
				break;

			case 3:
				Press_X_To_Proceed(0);
				ev_VictoryScreen.Advance(0); 
				ev_VictoryScreen.delay.Start_Timer(rainSpd, 1 ,true);
				Ev_Make_It_Rain();				// fais l'event
				break;

			case 4:
				Q_ev_MakeItRain.Add({});		// ajoute un symbole de cash!
				break;

			case 5:
				break;
			}
		}
}

 bool Is_Ev_Victory_Screen_Active()
 {
	 return ev_VictoryScreen.Is_Active();

 }
