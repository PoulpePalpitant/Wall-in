

#include "../inputs/action_input.h"
#include "blast.h"
#include "../UI/console_output/render_list.h"


#include "change_blast.h"


void Change_Blast()
{
	switch (blastP1.wallType)
	{
	case WallType::REGULAR:blastP1.wallType = WallType::STRONG;	ConsoleRender::Add_String("Stronk!", { 72,45 },LIGHT_YELLOW); break;
	case WallType::STRONG: blastP1.wallType = WallType::REGULAR;ConsoleRender::Add_String("Regular", { 72,45 }, WHITE); break;
	}
	blastP1.Setup_Blast_UI();

}