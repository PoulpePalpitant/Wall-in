

#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "Ev_Game_Title.h"
#include "../../events/msg_dispatcher.h"
#include "../dispatch_msg_to_menu.h"
#include "../../lvls/lvl_script.h"
#include "../../console/sweet_cmd_console.h"

static std::string skip = "Select Level";
static std::string author = "by Laurent Montreuil";

static void Ev_Dr_Game_Title();
static void Ev_Er_Game_Title();

Event ev_Dr_GameTitle(Ev_Dr_Game_Title); // Def
Event ev_Er_GameTitle(Ev_Er_Game_Title, 2);


void Ev_Dr_Game_Title()
{
	int x = Find_Ctr_X(sizeof("                                                                                                         "));
	int y = 12;
	
	Colors clr = gameCompleted ? LIGHT_YELLOW : WHITE;

	ConsoleRender::Add_String("WWWWWWWW                           WWWWWWWW                lllllll lllllll     IIIIIIIIII                ",{x,y}, clr);y++;
	ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ",{x,y}, clr);y++;
	ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ",{x,y}, clr);y++;
	ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     II::::::II                ",{x,y}, clr);y++;
	ConsoleRender::Add_String(" W:::::W           WWWWW           W:::::Waaaaaaaaaaaaa     l::::l  l::::l       I::::Innnn  nnnnnnnn    ",{x,y}, clr);y++;
	ConsoleRender::Add_String("  W:::::W         W:::::W         W:::::W a::::::::::::a    l::::l  l::::l       I::::In:::nn::::::::nn  ",{x,y}, clr);y++;
	ConsoleRender::Add_String("   W:::::W       W:::::::W       W:::::W  aaaaaaaaa:::::a   l::::l  l::::l       I::::In::::::::::::::nn ",{x,y}, clr);y++;
	ConsoleRender::Add_String("    W:::::W     W:::::::::W     W:::::W            a::::a   l::::l  l::::l       I::::Inn:::::::::::::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("     W:::::W   W:::::W:::::W   W:::::W      aaaaaaa:::::a   l::::l  l::::l       I::::I  n:::::nnnn:::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("      W:::::W W:::::W W:::::W W:::::W     aa::::::::::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("       W:::::W:::::W   W:::::W:::::W     a::::aaaa::::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("        W:::::::::W     W:::::::::W     a::::a    a:::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("         W:::::::W       W:::::::W      a::::a    a:::::a  l::::::ll::::::l    II::::::IIn::::n    n::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("          W:::::W         W:::::W       a:::::aaaa::::::a  l::::::ll::::::l    I::::::::In::::n    n::::n",{x,y}, clr);y++;
	ConsoleRender::Add_String("           W:::W           W:::W         a::::::::::aa:::a l::::::ll::::::l    I::::::::In::::n    n::::n",{x,y}, clr);            
		
	ConsoleRender::Add_String(author, { gConWidth - 25, gConHeight }, GRAY);

	ev_Dr_GameTitle.Deactivate();

}


void OBS_Draw_Game_Title()
{
	ev_Dr_GameTitle.Activate();	
}

// Efface le titre comme des feuilles sous la force d'une délicate brise 

void Ev_Er_Game_Title()
{
	if (!ev_Er_GameTitle.Is_Active())
		ev_Er_GameTitle.Activate();
	else
		while (ev_Er_GameTitle.delay.Tick())
		{
			int x = Find_Ctr_X(sizeof("                                                                                                         "));
			int y = 12;

			switch (ev_Er_GameTitle.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String("WWWWWWWW                           WWWWWWWW                lllllll lllllll     IIIIIIIIII                ", { x,y }, WHITE,  80 * 1200, true);y++;
				ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ", { x,y }, WHITE, 150 * 1200, true);y++;
				ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ", { x,y }, WHITE,  70 * 1200, true);y++;
				ConsoleRender::Add_String("W::::::W                           W::::::W                l:::::l l:::::l     II::::::II                ", { x,y }, WHITE, 200 * 1200, true);y++;
				ConsoleRender::Add_String(" W:::::W           WWWWW           W:::::Waaaaaaaaaaaaa     l::::l  l::::l       I::::Innnn  nnnnnnnn    ", { x,y }, WHITE, 100 * 1200, true);y++;
				ConsoleRender::Add_String("  W:::::W         W:::::W         W:::::W a::::::::::::a    l::::l  l::::l       I::::In:::nn::::::::nn  ", { x,y }, WHITE, 170 * 1200, true);y++;
				ConsoleRender::Add_String("   W:::::W       W:::::::W       W:::::W  aaaaaaaaa:::::a   l::::l  l::::l       I::::In::::::::::::::nn ", { x,y }, WHITE,  75 * 1200, true);y++;
				ConsoleRender::Add_String("    W:::::W     W:::::::::W     W:::::W            a::::a   l::::l  l::::l       I::::Inn:::::::::::::::n", { x,y }, WHITE,  80 * 1200, true);y++;
				ConsoleRender::Add_String("     W:::::W   W:::::W:::::W   W:::::W      aaaaaaa:::::a   l::::l  l::::l       I::::I  n:::::nnnn:::::n", { x,y }, WHITE, 150 * 1200, true);y++;
				ConsoleRender::Add_String("      W:::::W W:::::W W:::::W W:::::W     aa::::::::::::a   l::::l  l::::l       I::::I  n::::n    n::::n", { x,y }, WHITE,  80 * 1200, true);y++;
				ConsoleRender::Add_String("       W:::::W:::::W   W:::::W:::::W     a::::aaaa::::::a   l::::l  l::::l       I::::I  n::::n    n::::n", { x,y }, WHITE, 100 * 1200, true);y++;
				ConsoleRender::Add_String("        W:::::::::W     W:::::::::W     a::::a    a:::::a   l::::l  l::::l       I::::I  n::::n    n::::n", { x,y }, WHITE, 200 * 1200, true);y++;
				ConsoleRender::Add_String("         W:::::::W       W:::::::W      a::::a    a:::::a  l::::::ll::::::l    II::::::IIn::::n    n::::n", { x,y }, WHITE,  70 * 1200, true);y++;
				ConsoleRender::Add_String("          W:::::W         W:::::W       a:::::aaaa::::::a  l::::::ll::::::l    I::::::::In::::n    n::::n", { x,y }, WHITE, 200 * 1200, true);y++;
				ConsoleRender::Add_String("           W:::W           W:::W         a::::::::::aa:::a l::::::ll::::::l    I::::::::In::::n    n::::n", { x,y }, WHITE, 110 * 1200, true);
				ConsoleRender::Add_String("                                                                                                         ", { x,y }, WHITE, 110 * 1200, true);
				ev_Er_GameTitle.Advance(400);
				break;

			case 2:
				clrscr();
				gCurrentLevel = choosenLvl;
				MsgQueue::Register(PLS_INTIALIZE_LVL);	// Start le niveau sélectionné mon gars
				ev_Er_GameTitle.Advance(0);
				break;
			}
		}
}

void OBS_Erase_Game_Title()
{
	ev_Er_GameTitle.Activate();
	ev_Er_GameTitle.Start(0);

}
