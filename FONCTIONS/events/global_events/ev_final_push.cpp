#include "ev_final_push.h"

#include "../events.h"
#include "../../time/cycles.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"

static Event ev_FinalPush(Ev_Final_Push, 10);
static std::string msg_1 = "FINAL PUSH";
static Coord crd;

// Avertit le joueur que le final push arrive!
void  Ev_Final_Push()
{
	if (!ev_FinalPush.Is_Active())
	{
		// initialisation
		crd = { Find_Ctr_X((int)msg_1.size()),2 };

		ev_FinalPush.Activate();
		ev_FinalPush.Start(1000);
	}
	else
		while (ev_FinalPush.delay.Tick())
		{
			switch (ev_FinalPush.Get_Current_Step())
			{
			case 1:case 3: case 5: case 7: case 9:
				ConsoleRender::Add_String(msg_1, crd);//Affiche
				ev_FinalPush.Advance(1000);
				break;

			case 2:case 4: case 6: case 8: case 10:
				ConsoleRender::Add_String(msg_1, crd, WHITE, 0, true);// efface
				ev_FinalPush.Advance(1000);
				break;
			}
		}
	
}
