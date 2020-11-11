
#include "ev_thank_you.h"

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
#include "../../time/timerOP.h"

static Event ev_ThksForPlaying(Ev_Thks_For_Playing, 5);

static Coord xy;
static Coord crdTy;		// Coordonnée d'origine, servira de référence pour TOUT les affichages

static std::string ty = "Thank you for playing";

// Comment faire du ascii art
static const std::string YOU[] = 
{
"YYYYYYY       YYYYYYY     OOOOOOOOO     UUUUUUUU     UUUUUUUU",                   
"Y:::::Y       Y:::::Y   OO:::::::::OO   U::::::U     U::::::U",                   
"Y:::::Y       Y:::::Y OO:::::::::::::OO U::::::U     U::::::U",                   
"Y::::::Y     Y::::::YO:::::::OOO:::::::OUU:::::U     U:::::UU",                   
"YYY:::::Y   Y:::::YYYO::::::O   O::::::O U:::::U     U:::::U ",                   
"   Y:::::Y Y:::::Y   O:::::O     O:::::O U:::::D     D:::::U ",                   
"    Y:::::Y:::::Y    O:::::O     O:::::O U:::::D     D:::::U ",                   
"     Y:::::::::Y     O:::::O     O:::::O U:::::D     D:::::U ",                   
"      Y:::::::Y      O:::::O     O:::::O U:::::D     D:::::U ",                   
"       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U ",                   
"       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U ",                   
"       Y:::::Y       O::::::O   O::::::O U::::::U   U::::::U ",                   
"       Y:::::Y       O:::::::OOO:::::::O U:::::::UUU:::::::U ",                   
"    YYYY:::::YYYY     OO:::::::::::::OO   UU:::::::::::::UU  ",                   
"    Y:::::::::::Y       OO:::::::::OO       UU:::::::::UU    ",                   
"    YYYYYYYYYYYYY         OOOOOOOOO           UUUUUUUUU      "                   
};
static const std::string ROCK[] = 
{
"RRRRRRRRRRRRRRRRR        OOOOOOOOO             CCCCCCCCCCCCC KKKKKKKKK    KKKKKKK !!:!!",
"R::::::::::::::::R     OO:::::::::OO        CCC::::::::::::C K:::::::K    K:::::K !:::!",
"R::::::RRRRRR:::::R  OO:::::::::::::OO    CC:::::::::::::::C K:::::::K    K:::::K !:::!",
"RR:::::R     R:::::RO:::::::OOO:::::::O  C:::::CCCCCCCC::::C K:::::::K   K::::::K !:::!",
"  R::::R     R:::::RO::::::O   O::::::O C:::::C       CCCCCC KK::::::K  K:::::KKK !:::!",
"  R::::R     R:::::RO:::::O     O:::::OC:::::C                 K:::::K K:::::K    !:::!",
"  R::::RRRRRR:::::R O:::::O     O:::::OC:::::C                 K::::::K:::::K     !:::!",
"  R:::::::::::::RR  O:::::O     O:::::OC:::::C                 K:::::::::::K      !:::!",
"  R::::RRRRRR:::::R O:::::O     O:::::OC:::::C                 K:::::::::::K      !:::!",
"  R::::R     R:::::RO:::::O     O:::::OC:::::C                 K::::::K:::::K     !!:!!",
"  R::::R     R:::::RO:::::O     O:::::OC:::::C                 K:::::K K:::::K     !!! ",
"  R::::R     R:::::RO::::::O   O::::::O C:::::C       CCCCCC KK::::::K  K:::::KKK      ",
"RR:::::R     R:::::RO:::::::OOO:::::::O  C:::::CCCCCCCC::::C K:::::::K   K::::::K  !!! ",
"R::::::R     R:::::R OO:::::::::::::OO    CC:::::::::::::::C K:::::::K    K:::::K !!:!!",
"R::::::R     R:::::R   OO:::::::::OO        CCC::::::::::::C K:::::::K    K:::::K  !!! ",
"RRRRRRRR     RRRRRRR     OOOOOOOOO             CCCCCCCCCCCCC KKKKKKKKK    KKKKKKK  !!! "
};

static int length[2] = { (int)(YOU[0].size()), (int)ROCK[0].size() };
static int height = 16;
static const std::string* victoryWords[2] = { YOU, ROCK };	



static void Dr_YOU()
{
	Coord crd = { Find_Ctr_X(length[0]), 12 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(YOU[line], { crd.x, crd.y + line });

}
static void Dr_ROCK()
{
	Coord crd = { Find_Ctr_X(length[1]), 33 };
	for (int line = 0; line < 16; line++)
		ConsoleRender::Add_String(ROCK[line], { crd.x, crd.y + line }, LIGHT_GREEN);

}

void Ev_Thks_For_Playing()				 // Affiche un écran  gratifiant
{

	if (!ev_ThksForPlaying.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		crdTy.x = Find_Ctr_X((int)ty.size());		
		crdTy.y = 31;
		clrscr();
		Clear_All_States();
		ConsoleRender::Add_String(ty, crdTy, BRIGHT_WHITE, TXT_SPD_DR);
		ev_ThksForPlaying.Activate();
		ev_ThksForPlaying.Start(300);
	}
	else
		while (ev_ThksForPlaying.delay.Tick())
		{
			switch (ev_ThksForPlaying.Get_Current_Step())
			{
			case 1:
				Dr_YOU();
				ev_ThksForPlaying.Advance(500);
				break;

			case 2: // tit break
				Dr_ROCK();
				ev_ThksForPlaying.Advance(200);
				break;

			case 3:
				GameLoopClock::Stop();	// stop de game right here folks
			}
		}
}
