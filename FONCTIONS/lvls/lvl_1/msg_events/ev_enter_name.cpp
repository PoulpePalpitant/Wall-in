

#include "ev_enter_name.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../player/player.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../inputs/action_input.h"
#include "../../../player/player.h"

static Event ev_EnterName(Ev_Enter_Name, 3);
//static Event ev_Er_NewGoal(Ev_Er_New_Goal);
static std::string insertName = "INSERT NAME HERE ";
static std::string here = "_ _ _ _ _ _ _ ";



void Ev_Enter_Name()			// Accueil Le joueur quand il sort de son répit
{
	if (!ev_EnterName.Is_Active())
	{
		gTypeTime = true;
		MsgQueue::Register(BLOCK_ALL_INPUTS);
		ConsoleRender::Add_Char(P1.Get_XY(), TXT_CONST.SPACE);	// efface le joueur

		ev_EnterName.Activate();
		ev_EnterName.Start(500);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
 		while (ev_EnterName.delay.Tick())
			switch (ev_EnterName.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_Char(P1.Get_XY(), TXT_CONST.SPACE);	// efface le joueur
				ConsoleRender::Add_String(insertName, { Find_Ctr_X((int)insertName.size()), 28 }, BRIGHT_WHITE, 300);
				ConsoleRender::Add_String(here, { Find_Ctr_X((int)here.size()), 32 }, BRIGHT_WHITE, 300);
				ev_EnterName.Advance(500);
				break;

			case 2:

				MsgQueue::Register(UNBLOCK_ALL_INPUTS);
				ev_EnterName.Advance(0);
				ev_EnterName.delay.Start_Timer(50000, 1, true);// attend que le joueur touche  à une touche vlavier
				break; 

			case 3:
				if (!gTypeTime)
				{
					ConsoleRender::Add_String(insertName, { Find_Ctr_X((int)insertName.size()), 28 }, BRIGHT_WHITE, 300, true);
					ConsoleRender::Add_String(here, { Find_Ctr_X((int)here.size()), 32 }, BRIGHT_WHITE, 300, true);


					Beep(250, 100); // avertit le joueur que ce sera pas vrai
					MsgQueue::Register(FREE_PLAYER);
					P1.Dr_Player();	// réaffichje le joueur

					ev_EnterName.Cancel();	// finito
					break;
				}
			}
	}
}
