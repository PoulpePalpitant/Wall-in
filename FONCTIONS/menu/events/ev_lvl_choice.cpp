

#include "ev_lvl_choice.h"
#include "../../UI/console_output/render_list.h"
#include "../../UI/output_position.h"
#include "../../events/events.h"
#include "../../events/msg_dispatcher.h"
#include "../../choice/choice_time.h"
#include "../../console/sweet_cmd_console.h"

static Event ev_Dr_ChooseLvl(Ev_Dr_Choose_Lvl, 2);	// D�claration

static std::string skip = "Select Level";
static std::string pressNum = "(Press Number)";
static std::string recom[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 "};

static Coord crd;
static int numDist = 8;

void Ev_Dr_Choose_Lvl()
{
	if (!ev_Dr_ChooseLvl.Is_Active())
	{
		crd.y = 33;
		crd.x = Find_Ctr_X((int)skip.length());
		ev_Dr_ChooseLvl.Activate();
		ev_Dr_ChooseLvl.Start(0);
	}
	else
		while (ev_Dr_ChooseLvl.delay.Tick())
		{
			switch (ev_Dr_ChooseLvl.Get_Current_Step())
			{
			case 1:// do event stuff
				ConsoleRender::Add_String(skip, crd, WHITE, 120);
				ev_Dr_ChooseLvl.Advance(0);
				break;
			case 2:
				ConsoleRender::Add_String(pressNum, { crd.x - 1, crd.y + 1 }, GRAY, 0);

				crd.y += 5;
				crd.x = (gConWidth / 2) - (numDist * 8) / 2;	// distance entre chaque char
				crd.x -= 2;
				for (int i = 0; i < 7; i++)
				{
					crd.x += numDist;
					ConsoleRender::Add_String(recom[i], crd, WHITE, 0);

				}
				ev_Dr_ChooseLvl.Advance(0);
				break;
			}
		}
}

void Ev_Er_Choose_Lvl()	// efface le choix de lvl
{
	crd.y = 33;
	crd.x = Find_Ctr_X((int)skip.length());
	ConsoleRender::Add_String(skip, crd, WHITE, 0, true);
	ConsoleRender::Add_String(pressNum, { crd.x - 1, crd.y + 1 }, WHITE, 0, true);

	crd.y += 5;
	crd.x = 0;
	gotoxy(crd.x, crd.y);	clreol();	// oldschool stuff
}