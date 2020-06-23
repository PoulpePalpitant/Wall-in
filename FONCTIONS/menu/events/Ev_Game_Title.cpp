

#include "../../UI/console_output/render_list.h"
#include "Ev_Game_Title.h"

 EventInfo gDrawTitle;
 EventInfo gEraseTitle;



void Ev_Draw_Game_Title()
{


	if (gDrawTitle.ignore)
		return;

	int x = 17;
	int y = 12;
	ConsoleRender::Add_String_To_Render_List("WWWWWWWW                           WWWWWWWW               lllllll lllllll      IIIIIIIIII                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W               l:::::l l:::::l      I::::::::I                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W               l:::::l l:::::l      I::::::::I                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("W::::::W                           W::::::W               l:::::l l:::::l      II::::::II                ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List(" W:::::W           WWWWW           W:::::Waaaaaaaaaaaaa    l::::l  l::::l        I::::Innnn  nnnnnnnn    ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("  W:::::W         W:::::W         W:::::W a::::::::::::a   l::::l  l::::l        I::::In:::nn::::::::nn  ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("   W:::::W       W:::::::W       W:::::W  aaaaaaaaa:::::a  l::::l  l::::l        I::::In::::::::::::::nn ",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("    W:::::W     W:::::::::W     W:::::W            a::::a  l::::l  l::::l        I::::Inn:::::::::::::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("     W:::::W   W:::::W:::::W   W:::::W      aaaaaaa:::::a  l::::l  l::::l        I::::I  n:::::nnnn:::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("      W:::::W W:::::W W:::::W W:::::W     aa::::::::::::a  l::::l  l::::l        I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("       W:::::W:::::W   W:::::W:::::W     a::::aaaa::::::a  l::::l  l::::l        I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("        W:::::::::W     W:::::::::W     a::::a    a:::::a  l::::l  l::::l        I::::I  n::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("         W:::::::W       W:::::::W      a::::a    a:::::a l::::::ll::::::l     II::::::IIn::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("          W:::::W         W:::::W       a:::::aaaa::::::a l::::::ll::::::l     I::::::::In::::n    n::::n",{x,y}, WHITE);y++;
	ConsoleRender::Add_String_To_Render_List("           W:::W           W:::W         a::::::::::aa:::al::::::ll::::::l     I::::::::In::::n    n::::n",{x,y}, WHITE);            
		
	ConsoleRender::Add_String_To_Render_List("Start", { 68,38 }, BRIGHT_WHITE);


	gDrawTitle.ignore = true;
}
void Ev_Erase_Game_Title()
{

	if (gEraseTitle.ignore)
		return;
	int x = 17;
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

	ConsoleRender::Add_String_To_Render_List("     ", { 68,38 }, BRIGHT_WHITE, 20);

	gEraseTitle.ignore = true;
}