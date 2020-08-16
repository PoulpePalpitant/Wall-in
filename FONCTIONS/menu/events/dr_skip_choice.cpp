

#include "dr_skip_choice.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "../../choice/choice_time.h"
#include "../../console/sweet_cmd_console.h"

static std::string skip = "Play With Tutorial and Story?";
static std::string yes = "\"Y\" : Yes";
static std::string no = "\"N\" : No";
static std::string notRecom = "( If You Don't Know The Game )";
static std::string recom = "( You Played That Lvl Already )";
//static std::string recom = "(Recommended If You Did The LvL Tutorial)";

static Coord crd;
static int numDist = 5;

void Dr_Skip_Story_Choice()
{
	crd.y = 33;
	crd.x = Find_Ctr_X((int)skip.length());
	ConsoleRender::Add_String(skip, crd, WHITE);
	ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, LIGHT_GREEN);
	ConsoleRender::Add_String(no, { crd.x + 35, crd.y + 4 }, LIGHT_RED);
	ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY);
	ConsoleRender::Add_String(recom, { crd.x + 25, crd.y + 6 }, GRAY);	//ConsoleRender::Add_String(skip, crd, WHITE, 5);
	//ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, LIGHT_GREEN, 15);
	//ConsoleRender::Add_String(no, { crd.x + 35, crd.y + 4 }, LIGHT_RED, 20);
	//ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY, 10);
	//ConsoleRender::Add_String(recom, { crd.x + 25, crd.y + 6 }, GRAY, 10);
}

void Er_Skip_Story_Choice()	// efface le choix de lvl
{
	crd.y = 33;
	crd.x = Find_Ctr_X((int)skip.length());
	ConsoleRender::Add_String(skip, crd, WHITE, 15, true);
	ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, LIGHT_GREEN, 2, true);
	ConsoleRender::Add_String(no, { crd.x + 35, crd.y + 4 }, LIGHT_RED, 15, true);
	ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY, 12, true);
	ConsoleRender::Add_String(recom, { crd.x + 25, crd.y + 6 }, GRAY, 18, true);

}