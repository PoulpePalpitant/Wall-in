
#include "ev_spwn_player.h"


#include "../../player/player.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"

static Event ev_SpawnPlayer(Ev_Spawn_Player, 10);
static Coord crd;
static float speedRatio = 1;	
static bool drawTips = true;	

void Ev_Spawn_Player()		// Fait appara^tre le joueur lentement sur le grid
{

	if (!ev_SpawnPlayer.Is_Active())
	{
		MsgQueue::Register(LOCK_PLAYER);	// It has to be done
		//MsgQueue::Register(PLAYER_SPAWNED);
		// initialisation
		crd = P1.Get_XY();	// Le player doit être setté sur le grid avant de le spawn
		ev_SpawnPlayer.Activate();
		ev_SpawnPlayer.Start(650 * speedRatio > 1 ? 0 : 1);
	}
	else
		while (ev_SpawnPlayer.delay.Tick())
		{

			crd = P1.Get_XY();	// si le player change de position on est foutu

			switch (ev_SpawnPlayer.Get_Current_Step())
			{
			case 1:
				if (drawTips)
				{
					ConsoleRender::Add_Char({ crd.x - 3, crd.y }, 250, GRAY);
					ConsoleRender::Add_Char({ crd.x + 3, crd.y }, 250, GRAY);
					ConsoleRender::Add_Char({ crd.x, crd.y - 3 }, 250, GRAY);
					ConsoleRender::Add_Char({ crd.x, crd.y + 3 }, 250, GRAY);
				}
				ev_SpawnPlayer.Advance(3000 * speedRatio);break;

			case 2:
				ConsoleRender::Add_Char({ crd.x - 2, crd.y }, 196, WHITE);
				ConsoleRender::Add_Char({ crd.x + 2, crd.y }, 196, WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 2 }, 179, WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 2 }, 179, WHITE);
				ev_SpawnPlayer.Advance(7000 * speedRatio);break;
			case 3:
				ConsoleRender::Add_Char({ crd.x, crd.y }, 250, GRAY);

				ConsoleRender::Add_Char({ crd.x - 1, crd.y }, 196, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x + 1, crd.y }, 196, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, 179, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, 179, BRIGHT_WHITE);
				if (drawTips)
				{
					ConsoleRender::Add_Char({ crd.x - 3, crd.y }, 250, GRAY);	// Erase
					ConsoleRender::Add_Char({ crd.x + 3, crd.y }, 250, GRAY);
					ConsoleRender::Add_Char({ crd.x, crd.y - 3 }, 250, GRAY);
					ConsoleRender::Add_Char({ crd.x, crd.y + 3 }, 250, GRAY);
				}
				ev_SpawnPlayer.Advance(9000 * speedRatio);break;
			case 4:
				if (drawTips)
				{
					ConsoleRender::Add_Char({ crd.x - 3, crd.y }, TXT_CONST.SPACE);	// Erase
					ConsoleRender::Add_Char({ crd.x + 3, crd.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ crd.x, crd.y - 3 }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ crd.x, crd.y + 3 }, TXT_CONST.SPACE);
				}
				ConsoleRender::Add_Char({ crd.x - 2, crd.y }, 250, WHITE);
				ConsoleRender::Add_Char({ crd.x + 2, crd.y }, 250, WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 2 }, 250, WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 2 }, 250, WHITE);
				ev_SpawnPlayer.Advance(9000 * speedRatio);break;
			case 5:
				ConsoleRender::Add_Char({ crd.x - 2, crd.y }, TXT_CONST.SPACE);	// erase
				ConsoleRender::Add_Char({ crd.x + 2, crd.y }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 2 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 2 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ crd.x - 1, crd.y }, 250, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x + 1, crd.y }, 250, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, 250, BRIGHT_WHITE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, 250, BRIGHT_WHITE);
				ev_SpawnPlayer.Advance(5000 * speedRatio);break;
			case 6:
				ConsoleRender::Add_Char({ crd.x - 1, crd.y }, TXT_CONST.SPACE);	// ERASE
				ConsoleRender::Add_Char({ crd.x + 1, crd.y }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ crd.x, crd.y - 1 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ crd.x, crd.y + 1 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char(crd, '+', GRAY);
				ev_SpawnPlayer.Advance(2000 * speedRatio);
				break;

			case 7:
				ConsoleRender::Add_Char(crd, 197, GRAY);
				ev_SpawnPlayer.Advance(2000 * speedRatio);
				break;

			case 8:
				ConsoleRender::Add_Char(crd, 197, WHITE);
				ev_SpawnPlayer.Advance(2500 * speedRatio);
				break;

			case 9:
				ConsoleRender::Add_Char(crd, 197, BRIGHT_WHITE);
				ev_SpawnPlayer.Advance(4000 * speedRatio);
				break;

			case 10:
				ConsoleRender::Add_Char(crd, 197, LIGHT_GREEN);
				MsgQueue::Register(PLAYER_SPAWNED);
				MsgQueue::Register(FREE_PLAYER);
				ev_SpawnPlayer.Advance(0);

			}
		}





	/* Pré-Spawn*/

	//Colors clr = GRAY;

	// LE DÉFAUT DE CETTE MÉTHODE: NE PEUT PAS CRÉER DE PAUSE ENTRE LES ANIMATIONS!!!


	//if (speed == true)		// FAST
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		switch (i)
	//		{
	//		case 0:		case 1:		clr = GRAY; break;
	//		case 2:		case 3:		clr = WHITE; break;
	//		case 4:		case 5:		clr = BRIGHT_WHITE; break;
	//		case 6:		case 7:
	//		case 8:		case 9:		clr = LIGHT_GREEN;
	//		}

	//		ConsoleRender::Create_Animation_Queue(15);	// Draw
	//		ConsoleRender::Add_Char({ crd.x, crd.y }, 191, clr);
	//		ConsoleRender::Add_Char({ crd.x, crd.y }, 192, clr);
	//		ConsoleRender::Add_Char({ crd.x, crd.y }, 217, clr);
	//		ConsoleRender::Add_Char({ crd.x, crd.y }, 218, clr);
	//		ConsoleRender::Stop_Queue();
	//	}

	//}
}

void Set_Ev_Spawn_Player(float speed, bool noTips)		// Animation de spawnage du joueur
{
	drawTips = noTips;
	speedRatio = speed;
	Ev_Spawn_Player();	// Ne cancel pas l'animation
}