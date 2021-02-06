
#include "ev_good_job.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../blast/blast_ammo_animator.h"
#include "../../../console/sweet_cmd_console.h"


static const short NUM_COLOR = 6;
static Event ev_PerfectVictory(Ev_Perfect_Victory);
static Event ev_GoodJob(Ev_Good_Job, NUM_COLOR * 3);

static Event ev_GG(Ev_GG,1);
static Event ev_BigGG(Ev_Big_GG,1);

const short NUM_CONGRATULATIONS = 17;
const short NUM_RARE_GRATS = 3;

const static std::string CONGRATULATIONS[NUM_CONGRATULATIONS] = { "- EXTRAORDINARY -", " - FANTASTIC -", "- WELL DONE -", "- THAT WAS INCREDIBLE -","- SUPER! -" ,
"- KEEP IT UP -", "- GREAT WORK -", "- SWEET MOVES -", "- SPLENDID -", "- BRAVISSIMO -" , "- EXCELLENTISSIMO -","- DAZZLING PERFORMANCE -",
"- GOOD JOB -", "- SUPERBLY EXECUTED -","- SUCCESS -", "- NICE ONE -","- DELICIOUS -",  };

const static std::string RARE_GRATS[NUM_RARE_GRATS] = { "- THIS IS A GRATIFYING COMMENT -", "- FIRST TRY ;p -","- THIS  IS ALL TOO EASY -"};



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
		crd.y = gConHeight / 2;
		crd.x = Find_Ctr_String_X(grats);

		//crd.y =  Heart_Txt_Crd_Left("brrp").y;
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
											   
			ConsoleRender::Add_String(grats, { Up_Txt_2(grats)}, clr);
			ConsoleRender::Add_String(grats, { Find_Ctr_Grid(grats), map.Get_Limit(DOWN) + 4}, clr);

			if (erOrDr)
				erOrDr = false;
			else
				erOrDr = true;

			ev_GoodJob.Advance(spd);

			if (!ev_GoodJob.Is_Active())
			{
				ConsoleRender::Add_String(grats, { Up_Txt_2(grats) }, clr, 0,1);
				ConsoleRender::Add_String(grats, { Find_Ctr_Grid(grats), map.Get_Limit(DOWN) + 4 }, clr,0,1);
			}
		}
}

void Ev_Perfect_Victory(){}


void Cancel_Ev_Good_Job()	// permet de cancel cet event for the sake of speed
{
	return;
}

static std::string gg[16] = {
"        GGGGGGGGGGGGG             GGGGGGGGGGGGG",
"     GGG::::::::::::G          GGG::::::::::::G",
"   GG:::::::::::::::G        GG:::::::::::::::G",
"  G:::::GGGGGGGG::::G       G:::::GGGGGGGG::::G",
" G:::::G       GGGGGG      G:::::G       GGGGGG",
"G:::::G                   G:::::G              ",
"G:::::G                   G:::::G              ",
"G:::::G    GGGGGGGGGG     G:::::G    GGGGGGGGGG",
"G:::::G    G::::::::G     G:::::G    G::::::::G",
"G:::::G    GGGGG::::G     G:::::G    GGGGG::::G",
"G:::::G        G::::G     G:::::G        G::::G",
" G:::::G       G::::G      G:::::G       G::::G",
"  G:::::GGGGGGGG::::G       G:::::GGGGGGGG::::G",
"   GG:::::::::::::::G        GG:::::::::::::::G",
"     GGG::::::GGG:::G          GGG::::::GGG:::G",
"        GGGGGG   GGGG             GGGGGG   GGGG",
};

void Ev_Big_GG() {

	static int length = (int)gg[0].size();
	static Coord xy;
	static int r, c;
	static int speed = 800000;

	static unsigned long long clrNum = 0;
	static Colors clr;

	if (!ev_BigGG.Is_Active())
	{
		xy = { Find_Ctr_String_X(gg[0]),13 };

		clrNum++;

		switch (clrNum % NUM_COLOR)
		{
		case 0:	clr = LIGHT_RED;	 break;
		case 1:	clr = LIGHT_YELLOW;  break;
		case 2:	clr = LIGHT_GREEN;	 break;
		case 3:	clr = LIGHT_PURPLE;  break;
		case 4:	clr = BRIGHT_WHITE;   break;
		case 5:	clr = LIGHT_AQUA;	break;
		}

		ev_BigGG.Activate();
		ev_BigGG.Start(0);
		ev_BigGG.delay.Start_Timer(speed, 1, true);
	}
	else
		while (ev_BigGG.delay.Tick())
		{
			if (++r >= 16)
			{
				r = 0;
				if (++c >= length)
				{
					c = 0;
					ev_BigGG.Cancel();
					return;
				}
			}

			if (gg[r][c] != TXT_CONST.SPACE)
				if (gg[r][c] == TXT_CONST.DOTDOT)
					ConsoleRender::Add_Char({ xy.x + c,xy.y + r }, gg[r][c], BRIGHT_WHITE);
				else
					ConsoleRender::Add_Char({ xy.x + c,xy.y + r }, gg[r][c], clr);
		}
}


void Ev_GG()
{
	static std::string grats;
	static Colors clr;
	static unsigned long long clrNum;
	static const int spd = 10000;
	static Coord crd;

	if (!ev_GG.Is_Active())
	{
		clrNum = 0;
		ev_GG.Activate();
		ev_GG.Start(spd);
		ev_GG.delay.Start_Timer(spd,1,true);
	}
	else
		while (ev_GG.delay.Tick())
		{
			clrNum++;
			
			grats = "GG";//CONGRATULATIONS[rand() % NUM_CONGRATULATIONS];

			if (clrNum > 80)
			{
				switch (clrNum % NUM_COLOR)
				{
				case 0:	clr = LIGHT_RED;	 break;
				case 1:	clr = LIGHT_YELLOW;  break;
				case 2:	clr = LIGHT_GREEN;	 break;
				case 3:	clr = LIGHT_PURPLE;  break;
				case 4:	clr = BRIGHT_WHITE;  break;
				case 5:	clr = LIGHT_AQUA;    break;
				}

				crd = { rand() % gConWidth - 1,rand() % gConHeight - 1 };

				if (crd.x + grats.size() >= gConWidth - 1)
					crd.x -= (int)grats.size();
				else
					if (crd.x <= 5)
						crd.x += 5;

				if (crd.y <= 3)
					crd.y = crd.y += 3;


				if (clrNum < 1000)
					if (clrNum % 10 == 0)
						ConsoleRender::Add_String(grats, crd, clr, 0, 1);
					else
						ConsoleRender::Add_String(grats, crd, clr);
				else
					ConsoleRender::Add_String(grats, crd, clr);
			}
			
			if(ev_BigGG.Is_Active() == false)
				Ev_Big_GG();
		}
}
