
#include "ev_health_is_ammo.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"


static Event ev_HealthIsAmmo(Ev_Health_Is_Ammo, 2);
static Coord crd;
static std::string tip_01 = "Health Is Ammo ->";


 void Ev_Health_Is_Ammo()
{
	 static int y;

	if (!ev_HealthIsAmmo.Is_Active())
	{
		y = Heart_Txt_Crd_Right("  ").y - 2;
		ev_HealthIsAmmo.Activate();
		ev_HealthIsAmmo.Start(0);
	}
	else
	{
		while (ev_HealthIsAmmo.delay.Tick())
			switch (ev_HealthIsAmmo.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(tip_01, { Heart_Txt_Crd_Left(TXT_CONST.DOTDOTDOT).x + 11 ,y }, WHITE, TXT_SPD_DR);
				ev_HealthIsAmmo.Advance(100);	// Delay 
				break;
				
			case 2:
				ConsoleRender::Add_String(tip_01, { Heart_Txt_Crd_Left(TXT_CONST.DOTDOTDOT).x + 11 ,y }, WHITE, TXT_SPD_DR, 1);
				ev_HealthIsAmmo.Advance(0);	// finito
				break;
			}
	}
}