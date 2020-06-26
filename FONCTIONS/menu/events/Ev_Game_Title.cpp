

#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "Ev_Game_Title.h"


static void Ev_Draw_Game_Title()
{
	int x = Find_Ctr_X(sizeof("                                                                                                         "));
	int y = 12;
	ConsoleRender::Add_String_To_Render_List("WWWWWWWW                           WWWWWWWW                lllllll lllllll     IIIIIIIIII                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W                l:::::l l:::::l     I::::::::I                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W                l:::::l l:::::l     II::::::II                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List(" W:::::W           WWWWW           W:::::Waaaaaaaaaaaaa     l::::l  l::::l       I::::Innnn  nnnnnnnn    ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("  W:::::W         W:::::W         W:::::W a::::::::::::a    l::::l  l::::l       I::::In:::nn::::::::nn  ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("   W:::::W       W:::::::W       W:::::W  aaaaaaaaa:::::a   l::::l  l::::l       I::::In::::::::::::::nn ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("    W:::::W     W:::::::::W     W:::::W            a::::a   l::::l  l::::l       I::::Inn:::::::::::::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("     W:::::W   W:::::W:::::W   W:::::W      aaaaaaa:::::a   l::::l  l::::l       I::::I  n:::::nnnn:::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("      W:::::W W:::::W W:::::W W:::::W     aa::::::::::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("       W:::::W:::::W   W:::::W:::::W     a::::aaaa::::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("        W:::::::::W     W:::::::::W     a::::a    a:::::a   l::::l  l::::l       I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("         W:::::::W       W:::::::W      a::::a    a:::::a  l::::::ll::::::l    II::::::IIn::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("          W:::::W         W:::::W       a:::::aaaa::::::a  l::::::ll::::::l    I::::::::In::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("           W:::W           W:::W         a::::::::::aa:::a l::::::ll::::::l    I::::::::In::::n    n::::n",{x,y}, WHITE);            
		
	ConsoleRender::Add_String_To_Render_List("Start", { Find_Ctr_X(sizeof("Start")) ,38 }, BRIGHT_WHITE);

	//	//	//	//	//	//	//	//	//	//	//	
	//	//	//	//	//	//	//	//	//	//	//
	//	//	//	//	//	//	//	//	//	//	//
	// 	/	/	/	/	/	/	/	/	/	/

	// On Unregister l'event, pour ne plus l'updater
	EV_DrawGameTitle.Deactivate();

}


void OBS_Draw_Game_Title()
{
	EV_DrawGameTitle.Activate();	
}

// Efface le titre comme des feuilles sous la force d'une délicate brise 

static void EV_Ers_Game_Title()
{
	int x = Find_Ctr_X(sizeof("                                                                                                         "));
	int y = 12;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 5);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN,	15);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 4);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 20);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 7);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 17);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 2);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 5);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 15);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 5);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 10);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 20);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 4);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN, 20);y++;
	ConsoleRender::Add_String_To_Render_List("                                                                                                         ", { x,y }, LIGHT_GREEN,11);

	ConsoleRender::Add_String_To_Render_List("     ", { Find_Ctr_X(sizeof("Start")),38 }, BRIGHT_WHITE, 20);	// le piton start aussi est effacé

	// On Unregister l'event, pour ne plus updater
	EV_EraGameTitle.Deactivate();
}

void OBS_Erase_Game_Title()
{
	EV_EraGameTitle.Activate();
}

// EVENTS AT THE BOTTOM, GET USED TO IT

Event EV_DrawGameTitle(Ev_Draw_Game_Title); // Def
Event EV_EraGameTitle(EV_Ers_Game_Title);
