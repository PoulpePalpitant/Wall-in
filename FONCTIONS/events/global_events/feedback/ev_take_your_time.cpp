
#include "ev_take_your_time.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../blast/blast_ammo_animator.h"
#include "../../../grid/AllGrids.h"
#include "ev_soothing_borders.h"


static Event ev_TakeYourTime(Ev_Take_Your_Time);

static std::string take = "Take your time...";
static Coord crd;


void Ev_Take_Your_Time()	// Le joueur doit prendre son temps pour faire ce puzzle
{
	if (!ev_TakeYourTime.Is_Active())
	{
		crd.x = Find_Ctr_Grid(take);
		crd.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y - 3;
		ConsoleRender::Add_String(take, crd, WHITE, TXT_SPD_DR / 3);
		Set_Ev_Soothing_Borders(1);

		ev_TakeYourTime.Activate();
		ev_TakeYourTime.Start(100);
	}
	else
		while (ev_TakeYourTime.delay.Tick())
		{

			switch (ev_TakeYourTime.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(take, crd, WHITE,TXT_SPD_ER,1);
				ev_TakeYourTime.Advance(500);
				break;
			}
		}
}

void Cancel_Ev_Take_Your_Time() {
	ev_TakeYourTime.Cancel();
	ConsoleRender::Add_String(take, crd, WHITE, TXT_SPD_ER, 1);

	Cancel_Ev_Soothing_Borders();

}