

#include "dr_tuto_choice.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "../../choice/choice_time.h"
#include "../../console/sweet_cmd_console.h"

static std::string skip = "Play Tutorial?";
static std::string yes = "\"Y\" : Yes";
static std::string yes_2 = "( Play With Story )";
static std::string no = "\"N\" : No";
static std::string no_2 = "( Skip The Story )";
static std::string notRecom = "( If You Don't Know The Game )";
static std::string recom = "( You Are Confident )";
//static std::string recom = "(Recommended If You Did The LvL Tutorial)";


static int numDist = 5;

void Dr_Tuto_Choice()
{
	static Coord crd;
	crd.y = 33;
	crd.x = Find_Ctr_X((int)skip.length());
	ConsoleRender::Add_String(skip, crd, WHITE);
	ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, LIGHT_GREEN );
	ConsoleRender::Add_String(no, { crd.x + 18, crd.y + 4 }, LIGHT_RED);
	ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY);
	ConsoleRender::Add_String(recom, { crd.x + 13, crd.y + 6 }, GRAY);
	//ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY);
	//ConsoleRender::Add_String(recom, { crd.x + 25, crd.y + 6 }, GRAY);
}

void Er_Tuto_Choice()	// efface le choix de lvl
{
	static Coord crd;
	crd.y = 33;
	crd.x = Find_Ctr_X((int)skip.length());
	ConsoleRender::Add_String(skip, crd, WHITE, 0, true);
	ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, WHITE,  0, true);
	ConsoleRender::Add_String(no, { crd.x + 18, crd.y + 4 }, WHITE	 ,0,	true);
	ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, WHITE,0,	true);
	ConsoleRender::Add_String(recom, { crd.x + 13, crd.y + 6 }, WHITE, 0,	true);
	//ConsoleRender::Add_String(yes, { crd.x - 15, crd.y + 4 }, LIGHT_GREEN, 2,true);
	//ConsoleRender::Add_String(no, { crd.x + 35, crd.y + 4 }, LIGHT_RED,   15,true);
	//ConsoleRender::Add_String(notRecom, { crd.x - 25, crd.y + 6 }, GRAY,  12,true);
	//ConsoleRender::Add_String(recom, { crd.x + 25, crd.y + 6 }, GRAY,     18,true);

}