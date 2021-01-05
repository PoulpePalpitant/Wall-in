

#include "dr_quit_button.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "../../console/sweet_cmd_console.h"

static std::string quit = "(Q)UIT GAME";


void  Dr_Quit_Button(bool erase )
{
	Coord crd = { Find_Ctr_X((int)quit.length()), 57 };
	if (erase)
		ConsoleRender::Add_String(quit, crd, RED, TXT_SPD_ER,erase);
	else
		ConsoleRender::Add_String(quit, crd, RED);
}
