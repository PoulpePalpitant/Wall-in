
#include "ev_blast_splash.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"


static Event ev_UpBlastSplash(Ev_Up_Blast_Splash); 
static Event ev_DownBlastSplash(Ev_Down_Blast_Splash);
static Event ev_LeftBlastSplash(Ev_Left_Blast_Splash);
static Event ev_RightBlastSplash(Ev_Right_Blast_Splash);

DrawerQueue Q_ev_UpBlastSplash(8, 9);
DrawerQueue Q_ev_DownBlastSplash(8, 9);
DrawerQueue Q_ev_RightBlastSplash(8, 9);
DrawerQueue Q_ev_LeftBlastSplash(8, 9);


void Ev_Up_Blast_Splash()
{
	static int X, Y;


	if (!ev_UpBlastSplash.Is_Active())
	{
		ev_UpBlastSplash.Activate();
		ev_UpBlastSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
			for (int i = 0; i < Q_ev_UpBlastSplash.Get_Total(); i++)
			{
				while (Q_ev_UpBlastSplash.queue[i].timer.Tick())
				{
					X = Q_ev_UpBlastSplash.queue[i].XY.x;
					Y = Q_ev_UpBlastSplash.queue[i].XY.y;

					switch (Q_ev_UpBlastSplash.queue[i].currStep)
					{
					case 1:
						ConsoleRender::Add_Char({ X + 1,Y - 1  }, '/', GRAY);
						ConsoleRender::Add_Char({ X - 1,Y - 1  }, '\\', GRAY);
						Q_ev_UpBlastSplash.Step(i, 100000);
						break;

					case 2:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', WHITE);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', WHITE);
						Q_ev_UpBlastSplash.Step(i, 60000);
						break;

					case 3:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', BRIGHT_WHITE);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', BRIGHT_WHITE);
						Q_ev_UpBlastSplash.Step(i, 50000);
						break;

					case 4:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
						Q_ev_UpBlastSplash.Step(i, 40000);
						break;

					case 5:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.DOT, WHITE);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.DOT, WHITE);

						Q_ev_UpBlastSplash.Step(i, 15000);
						break;

					case 6:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.DOT, GRAY);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.DOT, GRAY);
						Q_ev_UpBlastSplash.Step(i, 10000);
						break;

					case 7:
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.SPACE);
						Q_ev_UpBlastSplash.Step(i);
						Q_ev_UpBlastSplash.Remove(i);
						break;
					}
				}
			}
			
			if (!Q_ev_UpBlastSplash.Get_Total())
				ev_UpBlastSplash.Cancel();
	}
}


void Ev_Down_Blast_Splash()
{
	static int X, Y;

	if (!ev_DownBlastSplash.Is_Active())
	{
		ev_DownBlastSplash.Activate();
		ev_DownBlastSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
		for (int i = 0; i < Q_ev_DownBlastSplash.Get_Total(); i++)
		{
			while (Q_ev_DownBlastSplash.queue[i].timer.Tick())
			{
				X = Q_ev_DownBlastSplash.queue[i].XY.x;
				Y = Q_ev_DownBlastSplash.queue[i].XY.y;

				switch (Q_ev_DownBlastSplash.queue[i].currStep)
				{
				case 1:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', GRAY);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', GRAY);
					Q_ev_DownBlastSplash.Step(i, 100000);
					break;

				case 2:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', WHITE);
					Q_ev_DownBlastSplash.Step(i, 60000);
					break;

				case 3:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', BRIGHT_WHITE);
					Q_ev_DownBlastSplash.Step(i, 50000);
					break;

				case 4:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					Q_ev_DownBlastSplash.Step(i, 40000);
					break;

				case 5:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, TXT_CONST.DOT, GRAY);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.DOT, GRAY);

					Q_ev_DownBlastSplash.Step(i, 15000);
					break;

				case 6:
					ConsoleRender::Add_Char({ X - 1,Y + 1 }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.SPACE);
					Q_ev_DownBlastSplash.Step(i, 10000);
					break;

				case 7:
					Q_ev_DownBlastSplash.Step(i);
					Q_ev_DownBlastSplash.Remove(i);
					break;
				}
			}
		}
		if (!Q_ev_DownBlastSplash.Get_Total())
			ev_DownBlastSplash.Cancel();
	}
}

void Ev_Right_Blast_Splash()
{
	static int X, Y;

	if (!ev_RightBlastSplash.Is_Active())
	{
		ev_RightBlastSplash.Activate();
		ev_RightBlastSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
		for (int i = 0; i < Q_ev_RightBlastSplash.Get_Total(); i++)
		{
			while (Q_ev_RightBlastSplash.queue[i].timer.Tick())
			{
				X = Q_ev_RightBlastSplash.queue[i].XY.x;
				Y = Q_ev_RightBlastSplash.queue[i].XY.y;

				switch (Q_ev_RightBlastSplash.queue[i].currStep)
				{
				case 1:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', GRAY);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', GRAY);
					Q_ev_RightBlastSplash.Step(i, 100000);
					break;

				case 2:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', WHITE);
					Q_ev_RightBlastSplash.Step(i, 60000);
					break;

				case 3:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', BRIGHT_WHITE);
					Q_ev_RightBlastSplash.Step(i, 50000);
					break;

				case 4:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					Q_ev_RightBlastSplash.Step(i, 40000);
					break;

				case 5:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.DOT, GRAY);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.DOT, GRAY);
					Q_ev_RightBlastSplash.Step(i, 15000);
					break;

				case 6:
					ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.SPACE);
					Q_ev_RightBlastSplash.Step(i, 10000);
					break;

				case 7:
					Q_ev_RightBlastSplash.Step(i);
					Q_ev_RightBlastSplash.Remove(i);
					break;
				}
			}
		}

		if (!Q_ev_RightBlastSplash.Get_Total())
			ev_RightBlastSplash.Cancel();
	}
}

void Ev_Left_Blast_Splash()
{
	static int X, Y;

	if (!ev_LeftBlastSplash.Is_Active())
	{
		ev_LeftBlastSplash.Activate();
		ev_LeftBlastSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
		for (int i = 0; i < Q_ev_LeftBlastSplash.Get_Total(); i++)
		{
			while (Q_ev_LeftBlastSplash.queue[i].timer.Tick())
			{
				X = Q_ev_LeftBlastSplash.queue[i].XY.x;
				Y = Q_ev_LeftBlastSplash.queue[i].XY.y;


				switch (Q_ev_LeftBlastSplash.queue[i].currStep)
				{
				case 1:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, '/',  GRAY);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, '\\', GRAY);
					Q_ev_LeftBlastSplash.Step(i, 100000);
					break;

				case 2:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, '/', WHITE);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, '\\', WHITE);
					Q_ev_LeftBlastSplash.Step(i, 60000);
					break;

				case 3:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, '/', BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, '\\', BRIGHT_WHITE);
					Q_ev_LeftBlastSplash.Step(i, 50000);
					break;

				case 4:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, TXT_CONST.DOT, BRIGHT_WHITE);
					Q_ev_LeftBlastSplash.Step(i, 40000);
					break;

				case 5:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, TXT_CONST.DOT, WHITE);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, TXT_CONST.DOT, WHITE);
					Q_ev_LeftBlastSplash.Step(i,15000);
					break;

				case 6:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, TXT_CONST.DOT,GRAY);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, TXT_CONST.DOT,GRAY);
					Q_ev_LeftBlastSplash.Step(i, 10000);
					break;

				case 7:
					ConsoleRender::Add_Char({ X - 1  ,Y + 1 }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ X - 1  ,Y - 1 }, TXT_CONST.SPACE);
					Q_ev_LeftBlastSplash.Step(i);
					Q_ev_LeftBlastSplash.Remove(i);
					break;
				}
			}
		}

		if (!Q_ev_LeftBlastSplash.Get_Total())
			ev_LeftBlastSplash.Cancel();

	}
}


void Add_Blast_Splash(Direction dir, Coord impactCrd)// Fait une animation de splash quand le blast atteint quekchose et créer un link
{
	switch (blastP1.Get_Dir())
	{
	case UP:	Q_ev_UpBlastSplash.Add(impactCrd); Ev_Up_Blast_Splash(); break;
	case DOWN:	Q_ev_DownBlastSplash.Add(impactCrd);Ev_Down_Blast_Splash();break;
	case LEFT:	Q_ev_LeftBlastSplash.Add(impactCrd);Ev_Left_Blast_Splash();break;
	case RIGHT:	Q_ev_RightBlastSplash.Add(impactCrd);Ev_Right_Blast_Splash();break;
	}
}



