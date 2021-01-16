
#include "ev_good_job.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../blast/blast_ammo_animator.h"


static const short NUM_COLOR = 6;
static Event ev_PerfectVictory(Ev_Perfect_Victory);
static Event ev_GoodJob(Ev_Good_Job, NUM_COLOR * 3);

const short NUM_CONGRATULATIONS = 16;
const short NUM_RARE_GRATS = 2;

const static std::string CONGRATULATIONS[NUM_CONGRATULATIONS] = { "- EXTRAORDINARY -", " - FANTASTIC -", "- WELL DONE -", "- THAT WAS INCREDIBLE -","- SUPER! -" ,
"- KEEP IT UP -", "- GREAT WORK -", "- SWEET MOVES -", "- SPLENDID -", "- BRAVISSIMO -" , "- EXCELLENTISSIMO -","- DAZZLING PERFORMANCE -","- GOOD JOB -", "- SUPERBLY EXECUTED -","- SUCCESS -", "- NICE ONE -" };

const static std::string RARE_GRATS[NUM_RARE_GRATS] = { "- THIS IS A GRATIFYING COMMENT -", "- FIRST TRY ;p -" };

static Coord crd;


void Ev_Good_Job()	// Affiche 1 warning que le joueur n'a plus d'ammo
{
	static bool erOrDr;	// erase ou draw
	static std::string grats;
	static Colors clr;
	static const int spd = 5700;


	if (!ev_GoodJob.Is_Active())
	{
		grats = CONGRATULATIONS[rand() % NUM_CONGRATULATIONS];
		
		if (rand() % 100 == 1)
			grats = RARE_GRATS[rand() % NUM_RARE_GRATS];


		erOrDr = false;
		crd.y = Heart_Txt_Crd_Left("brrp").y;
		ev_GoodJob.Activate();
		ev_GoodJob.Start(spd);
	}
	else
		while (ev_GoodJob.delay.Tick())
		{

			switch (ev_GoodJob.Get_Current_Step() % NUM_COLOR)
			{
			case 0:	clr = LIGHT_RED;	 break;
			case 1:	clr = LIGHT_YELLOW;  break;
			case 2:	clr = LIGHT_GREEN;	 break;
			case 3:	clr = LIGHT_PURPLE;  break;
			case 4:	clr = BRIGHT_WHITE;    break;
			case 5:	clr = LIGHT_AQUA;    break;
			}

				ConsoleRender::Add_String(grats, Heart_Txt_Crd_Left(grats), clr);
				ConsoleRender::Add_String(grats, { Heart_Txt_Crd_Right(grats).x, crd.y }, clr);

				if (erOrDr)
					erOrDr = false;
				else
					erOrDr = true;

				ev_GoodJob.Advance(spd);

				if (!ev_GoodJob.Is_Active())
				{
					ConsoleRender::Add_String(grats, Heart_Txt_Crd_Left(grats), clr,0,1);
					ConsoleRender::Add_String(grats, { Heart_Txt_Crd_Right(grats).x, crd.y }, clr,0,1);
				}
		}
}

void Ev_Perfect_Victory(){}


void Cancel_Ev_Good_Job()	// permet de cancel cet event for the sake of speed
{
	return;
}