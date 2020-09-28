#include "Test.h"
#include "../../events/events.h"
#include "render_list.h"

static Event ev_Test(Ev_Test_Affichage, 20); // Def //
static int y;
static const int SLEEP = 1000;
/// Testy stuff
std::string test = "Ceci est un test: BLAAAAAAAAAAAAAAAAAAAAAAAARG";


void Ev_Test_Affichage()
{
	if (!ev_Test.Is_Active())
	{
		y = 0;
		ev_Test.Activate();
		ev_Test.Start(0);
	}
	else
		while (ev_Test.delay.Tick())
		{
			switch (ev_Test.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(test, { 0,0 }, WHITE, 0);
				ev_Test.Advance(SLEEP);
				break;
			case 2:
				ConsoleRender::Add_String(test, { 0,1 }, WHITE, 1);
				ev_Test.Advance(SLEEP);
				break;

			case 3:
				ConsoleRender::Add_String(test, { 0,2 }, WHITE, 10);
				ev_Test.Advance(SLEEP);
				break;

			case 4:
				ConsoleRender::Add_String(test, { 0,3 }, WHITE, 11);
				ev_Test.Advance(SLEEP);
				break;

			case 5:
				ConsoleRender::Add_String(test, { 0,4 }, WHITE, 15);
				ev_Test.Advance(SLEEP);
				break;

			case 6:
				ConsoleRender::Add_String(test, { 0,5 }, WHITE, 20);
				ev_Test.Advance(SLEEP);
				break;

			case 7:
				ConsoleRender::Add_String(test, { 0,6 }, WHITE, 25);
				ev_Test.Advance(SLEEP);
				break;
			case 8:
				ConsoleRender::Add_String(test, { 0,7 }, WHITE, 30);
				ev_Test.Advance(SLEEP);
				break;
			}
		}
}



