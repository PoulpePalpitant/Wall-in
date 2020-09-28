
#include "ev_border_splash.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"


static Event ev_HorSplash(Ev_Horizontal_Splash); // Def //
static Event ev_VerSplash(Ev_Vertical_Splash); // Def //

DrawerQueue Q_ev_HorSplash(8, 9);		
DrawerQueue Q_ev_VerSplash(8, 9);		

void Ev_Vertical_Splash()
{
	static unsigned char line = 179;
	static unsigned char tear = 250;
	static Coord crd; 
	static int x; 

	if (!ev_VerSplash.Is_Active())
	{
		ev_VerSplash.Activate();
		ev_VerSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
			for (int i = 0; i < Q_ev_VerSplash.Get_Total(); i++)
			{
				while (Q_ev_VerSplash.queue[i].timer.Tick())
				{

					crd = Q_ev_VerSplash.queue[i].XY;
					x = crd.x;				// ne changera pas

					switch (Q_ev_VerSplash.queue[i].currStep)
					{
					case 1:
						ConsoleRender::Add_Char(crd, line);
						Q_ev_VerSplash.Step(i, 100000);
						break;
					case 2:
						ConsoleRender::Add_Char({ x,crd.y - 1 }, line);	//																 
						ConsoleRender::Add_Char({ x,crd.y + 1 }, line);	//																 
						Q_ev_VerSplash.Step(i, 80000);
						break;

					case 3:
						ConsoleRender::Add_Char(crd, tear);			// Modifie le milieu								    			 
						Q_ev_VerSplash.Step(i, 40000);
						break;

					case 4:
						ConsoleRender::Add_Char({ x,crd.y - 1 }, TXT_CONST.SPACE);		// efface										
						ConsoleRender::Add_Char({ x,crd.y + 1 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ x,crd.y - 2 }, line);	// draw										
						ConsoleRender::Add_Char({ x,crd.y + 2 }, line);
						ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// Modifie le milieu
						ConsoleRender::Stop_Queue();
						Q_ev_VerSplash.Step(i, 25000);
						break;

					case 5:
						ConsoleRender::Add_Char({ x,crd.y - 2 }, TXT_CONST.SPACE);	// erase																							
						ConsoleRender::Add_Char({ x,crd.y + 2 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ x,crd.y - 3 }, line, GRAY); // draw
						ConsoleRender::Add_Char({ x,crd.y + 3 }, line, GRAY);
						Q_ev_VerSplash.Step(i, 15000);
						break;

					case 6:
						ConsoleRender::Add_Char({ x,crd.y - 3 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ x,crd.y + 3 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ x,crd.y - 4 }, tear, GRAY);
						ConsoleRender::Add_Char({ x,crd.y + 4 }, tear, GRAY);
						Q_ev_VerSplash.Step(i, 10000);
						break;

					case 7:
						ConsoleRender::Add_Char({ x,crd.y - 4 }, TXT_CONST.SPACE);
						ConsoleRender::Add_Char({ x,crd.y + 4 }, TXT_CONST.SPACE);
						Q_ev_VerSplash.Step(i);
						Q_ev_VerSplash.Remove(i);
						break;
					}
				}
			}
			
			if (!Q_ev_VerSplash.Get_Total())
				ev_VerSplash.Cancel();

	}
}

void Ev_Horizontal_Splash()
{
	static Coord left;
	static Coord right;
	static Coord start;
	static unsigned char botLine = 196;
	static unsigned char tear = 250;
	static unsigned char end = '.';


	if (!ev_HorSplash.Is_Active())
	{
		ev_HorSplash.Activate();
		ev_HorSplash.Start(0);	// On ne tick pas ce timer
	}
	else
	{
		for (int i = 0; i < Q_ev_HorSplash.Get_Total(); i++)
		{
			while (Q_ev_HorSplash.queue[i].timer.Tick())
			{
				start = right = left = Q_ev_HorSplash.queue[i].XY;

				switch (Q_ev_HorSplash.queue[i].currStep)
				{
				case 1:
					ConsoleRender::Add_Char(start, botLine);		//	_
					Q_ev_HorSplash.Step(i, 100000);
					break;
				case 2:
					left.x -= 2;		ConsoleRender::Add_Char(left, botLine);
					right.x += 2;		ConsoleRender::Add_Char(right, botLine);	// _ _ _
					Q_ev_HorSplash.Step(i, 60000);
					break;

				case 3:
					ConsoleRender::Add_Char(start, tear);			// Modifie le milieu
					left.x-=3;		ConsoleRender::Add_Char(left, botLine);
					right.x+=3;		ConsoleRender::Add_Char(right, botLine);		//	__ . __						    			 
					Q_ev_HorSplash.Step(i, 50000);
					break;

				case 4:
					ConsoleRender::Add_Char({ start.x - 3, start.y }, TXT_CONST.SPACE);		//  ___  .  ___ 
					ConsoleRender::Add_Char({ start.x + 3, start.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ start.x - 2, start.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ start.x + 2, start.y }, TXT_CONST.SPACE);
					left.x-=4;		ConsoleRender::Add_Char(left, botLine , WHITE);		// draw
					right.x+=4;		ConsoleRender::Add_Char(right, botLine, WHITE);
					left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);
					right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
					left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);
					right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
					Q_ev_HorSplash.Step(i, 40000);
					break;

				case 5:
					ConsoleRender::Add_Char(start, TXT_CONST.SPACE);	// erase						
					left.x -= 6;				
					right.x += 6;	
					ConsoleRender::Add_Char({ left.x + 1,left.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ right.x - 1, right.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ left.x + 2,left.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ right.x - 2, right.y }, TXT_CONST.SPACE);
					left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);		// ___       ___
					right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
					Q_ev_HorSplash.Step(i,15000);
					break;

				case 6:
					left.x -= 6;right.x += 6; 	// .             .
					ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
					ConsoleRender::Add_Char(right, TXT_CONST.SPACE);			
					ConsoleRender::Add_Char({ left.x + 3,left.y }, TXT_CONST.SPACE);
					ConsoleRender::Add_Char({ right.x - 3, right.y }, TXT_CONST.SPACE);
					left.x--;	right.x++;
					ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
					ConsoleRender::Add_Char(right, TXT_CONST.SPACE);
					left.x--;		right.x++;
					ConsoleRender::Add_Char(left, tear, GRAY);
					ConsoleRender::Add_Char(right, tear, GRAY);
					Q_ev_HorSplash.Step(i, 10000);
					break;

				case 7:
					left.x -= 8;right.x += 8;
					ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
					ConsoleRender::Add_Char(right, TXT_CONST.SPACE);					// 

					Q_ev_HorSplash.Step(i);
					Q_ev_HorSplash.Remove(i);
					break;
				}
			}
		}

		if (!Q_ev_HorSplash.Get_Total())
			ev_HorSplash.Cancel();

	}
}


// ///////////////////////////////////////////		/OLD BUGGY FRAMRATE DEPENDANT VERSION
//static void Horizontal_Splash()
//{
//	// Superbe animation ici!!
//	// v1 Symmétrie
//	static Coord left;	left = startPos.coord;
//	static Coord right;	right = startPos.coord;
//	static unsigned char botLine = 196;
//	static unsigned char tear = 250;
//	static unsigned char end = '.';
//
//	ConsoleRender::Add_Char(startPos.coord, botLine);		//	_
//
//	ConsoleRender::Create_Animation_Queue(50, false);	// draw
//	left.x -= 2;		ConsoleRender::Add_Char(left, botLine);
//	right.x += 2;		ConsoleRender::Add_Char(right, botLine);	// _ _ _
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(45, false);	// draw
//	ConsoleRender::Add_Char(startPos.coord, tear);			// Modifie le milieu
//	left.x--;		ConsoleRender::Add_Char(left, botLine);
//	right.x++;		ConsoleRender::Add_Char(right, botLine);;		//	__ . __
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(38, false);
//	ConsoleRender::Add_Char({ startPos.coord.x - 3, startPos.coord.y }, TXT_CONST.SPACE);		//  __ _ . _ __ 
//	ConsoleRender::Add_Char({ startPos.coord.x + 3, startPos.coord.y }, TXT_CONST.SPACE);
//	left.x--;		ConsoleRender::Add_Char(left, botLine);		// draw
//	right.x++;		ConsoleRender::Add_Char(right, botLine);
//	left.x--;		ConsoleRender::Add_Char(left, botLine);
//	right.x++;		ConsoleRender::Add_Char(right, botLine);
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(20, false);
//	ConsoleRender::Add_Char(startPos.coord, TXT_CONST.SPACE);	// erase	
//	ConsoleRender::Add_Char({ startPos.coord.x - 2, startPos.coord.y }, TXT_CONST.SPACE);		// _ __       __ _
//	ConsoleRender::Add_Char({ startPos.coord.x + 2, startPos.coord.y }, TXT_CONST.SPACE);
//	left.x -= 2;		ConsoleRender::Add_Char(left, botLine, GRAY);
//	right.x += 2;		ConsoleRender::Add_Char(right, botLine, GRAY);
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(3, false);		// erase
//	ConsoleRender::Add_Char({ left.x + 2,left.y }, TXT_CONST.SPACE);								// .             .
//	ConsoleRender::Add_Char({ right.x - 2, right.y }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ left.x + 3,left.y }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ right.x - 3, right.y }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char(left, tear, GRAY);
//	ConsoleRender::Add_Char(right, tear, GRAY);
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(1, false);		// erase
//	ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char(right, TXT_CONST.SPACE);					// 
//	ConsoleRender::Stop_Queue();
//
//}
//
//static void Vertical_Splash()
//{
//	// Superbe animation ici!!
//	// v1 Symmétrie
//	static unsigned char line = 179;
//	static unsigned char tear = 250;
//	static Coord crd; crd = startPos.coord;	// Position centrale
//	static int x; x = crd.x;				// ne changera pas
//
//	ConsoleRender::Add_Char(crd, line);		//			|																	// style #1
//
//	ConsoleRender::Create_Animation_Queue(1200, false);			// draw																		  // 																	.	    .	    .	    
//	ConsoleRender::Add_Char({ x,crd.y - 1 }, line);	//																  // #1		#2		#3  	#4		   .			 #2	|	  #3 |	  #4	#5	|	#6		#7
//	ConsoleRender::Add_Char({ x,crd.y + 1 }, line);	//																  //	|						|	#6							  	 	|				
//	ConsoleRender::Stop_Queue();																									  //	|		|	 	|							|	|	 	 |							
//																																	  //	|		.													  	.		.				
//	ConsoleRender::Create_Animation_Queue(900, false);	// draw																				  //			|		 		 						|	  	 |							
//	ConsoleRender::Add_Char(crd, tear);			// Modifie le milieu								    			  //				 			 							  	 		|				
//	//ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 3 }, line);																  //					|									  	 |				|		
//	//ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 3 }, line);																  //				 													.		.		.
//	ConsoleRender::Stop_Queue();																									  //				 			|		
//																																	  //									.
//	ConsoleRender::Create_Animation_Queue(300, false);																						  //							
//	ConsoleRender::Add_Char({ x,crd.y - 1 }, TXT_CONST.SPACE);		// efface													
//	ConsoleRender::Add_Char({ x,crd.y + 1 }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ x,crd.y - 2 }, line);	// draw										
//	ConsoleRender::Add_Char({ x,crd.y + 2 }, line);
//	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// Modifie le milieu
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(500, false);
//	ConsoleRender::Add_Char({ x,crd.y - 2 }, TXT_CONST.SPACE);	// erase																							
//	ConsoleRender::Add_Char({ x,crd.y + 2 }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ x,crd.y - 3 }, line, GRAY); // draw
//	ConsoleRender::Add_Char({ x,crd.y + 3 }, line, GRAY);
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(200, false);
//	ConsoleRender::Add_Char({ x,crd.y - 3 }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ x,crd.y + 3 }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ x,crd.y - 4 }, tear, GRAY);
//	ConsoleRender::Add_Char({ x,crd.y + 4 }, tear, GRAY);
//	ConsoleRender::Stop_Queue();
//
//	ConsoleRender::Create_Animation_Queue(100, false);		// erase																	
//	ConsoleRender::Add_Char({ x,crd.y - 4 }, TXT_CONST.SPACE);
//	ConsoleRender::Add_Char({ x,crd.y + 4 }, TXT_CONST.SPACE);
//	ConsoleRender::Stop_Queue();
//
//}


void Add_Border_Splash()	// Fait une animation de splash quand tu tir sur la bordure
{
	static CoordIncrementor startPos;

	startPos = *blastP1.Get_Front_XY();	 // Trouvons l'axe maintenant, pour trouver la bonne bordure
	startPos.Increment_Coord();			// avance la coord d'une case, pour sortir de la map

	if (blastP1.Get_Distance_Travelled() == 0)	// dumb, but fixed
		startPos.Increment_Coord();			// avance la coord d'une case, pour sortir de la map

	switch (blastP1.Get_Dir())
	{
	case 0:  case 2:Q_ev_HorSplash.Add(startPos.coord);  Ev_Horizontal_Splash();   break; //Horizontal_Splash
	case 1:  case 3:Q_ev_VerSplash.Add(startPos.coord);	 Ev_Vertical_Splash();	break; /*  Vertical_Splash();*/
	}
}



