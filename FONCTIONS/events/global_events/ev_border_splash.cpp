
#include "ev_border_splash.h"

#include "../../UI/map.h"
#include "../../blast/blast.h"
#include "../../UI/console_output/render_list.h"


static CoordIncrementor startPos;


static void Horizontal_Splash()		
{
	// Superbe animation ici!!
	// v1 Symmétrie
	static Coord left;	left = startPos.coord;
	static Coord right;	right = startPos.coord;
	static unsigned char botLine = 196;
	static unsigned char tear = 250;
	static unsigned char end = '.';

	ConsoleRender::Add_Char_To_Render_List(startPos.coord,botLine);		//	_


	ConsoleRender::Create_Queue(100, false);	// draw
	left.x-=2;		ConsoleRender::Add_Char_To_Render_List(left,botLine );
	right.x+=2;		ConsoleRender::Add_Char_To_Render_List(right,botLine);	// _ _ _
	ConsoleRender::Stop_Queue();

	ConsoleRender::Create_Queue(200, false);	// draw
	ConsoleRender::Add_Char_To_Render_List(startPos.coord, tear);			// Modifie le milieu
	left.x--;		ConsoleRender::Add_Char_To_Render_List(left, botLine);
	right.x++;		ConsoleRender::Add_Char_To_Render_List(right, botLine);;		//	__ . __
	ConsoleRender::Stop_Queue();

	ConsoleRender::Create_Queue(300, false);	
	ConsoleRender::Add_Char_To_Render_List({ startPos.coord.x - 3, startPos.coord.y }, TXT_CONST.SPACE);		//  __ _ . _ __ 
	ConsoleRender::Add_Char_To_Render_List({ startPos.coord.x + 3, startPos.coord.y }, TXT_CONST.SPACE);
	left.x--;		ConsoleRender::Add_Char_To_Render_List( left, botLine);		// draw
	right.x++;		ConsoleRender::Add_Char_To_Render_List(right, botLine);
	left.x--;		ConsoleRender::Add_Char_To_Render_List(left, botLine);
	right.x++;		ConsoleRender::Add_Char_To_Render_List(right, botLine);
	ConsoleRender::Stop_Queue();

	ConsoleRender::Create_Queue(500, false);
	ConsoleRender::Add_Char_To_Render_List(startPos.coord, TXT_CONST.SPACE);	// erase	
	ConsoleRender::Add_Char_To_Render_List({ startPos.coord.x - 2, startPos.coord.y }, TXT_CONST.SPACE);		// _ __       __ _
	ConsoleRender::Add_Char_To_Render_List({ startPos.coord.x + 2, startPos.coord.y }, TXT_CONST.SPACE);
	left.x -= 2;		ConsoleRender::Add_Char_To_Render_List(left, botLine, GRAY);
	right.x +=2;		ConsoleRender::Add_Char_To_Render_List(right, botLine, GRAY);
	ConsoleRender::Stop_Queue();

	ConsoleRender::Create_Queue(900, false);		// erase
	ConsoleRender::Add_Char_To_Render_List({ left.x + 2,left.y }, TXT_CONST.SPACE);								// .             .
	ConsoleRender::Add_Char_To_Render_List({ right.x - 2, right.y }, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List({ left.x + 3,left.y }, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List({ right.x - 3, right.y }, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List(left, tear, GRAY);
	ConsoleRender::Add_Char_To_Render_List(right, tear, GRAY);
	ConsoleRender::Stop_Queue();

	ConsoleRender::Create_Queue(1200, false);		// erase
	ConsoleRender::Add_Char_To_Render_List(left, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List(right, TXT_CONST.SPACE);					// 
	ConsoleRender::Stop_Queue();

}
static void Vertical_Splash()
{


	// Superbe animation ici!!
	// v1 Symmétrie
	static unsigned char line = 179;
	static unsigned char tear = 250;
	static Coord crd; crd = startPos.coord;	// Position centrale
	static int x; x = crd.x;				// ne changera pas

	ConsoleRender::Add_Char_To_Render_List(crd, line);		//			|																	// style #1

	ConsoleRender::Create_Queue(100, false);			// draw																		  // 																	.	    .	    .	    
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 1 }, line);	//																  // #1		#2		#3  	#4		   .			 #2	|	  #3 |	  #4	#5	|	#6		#7
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 1 }, line);	//																  //	|						|	#6							  	 	|				
	ConsoleRender::Stop_Queue();																									  //	|		|	 	|							|	|	 	 |							
																																	  //	|		.													  	.		.				
	ConsoleRender::Create_Queue(200, false);	// draw																				  //			|		 		 						|	  	 |							
	ConsoleRender::Add_Char_To_Render_List(crd, tear);			// Modifie le milieu								    			  //				 			 							  	 		|				
	//ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 3 }, line);																  //					|									  	 |				|		
	//ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 3 }, line);																  //				 													.		.		.
	ConsoleRender::Stop_Queue();																									  //				 			|		
																																	  //									.
	ConsoleRender::Create_Queue(300, false);																						  //							
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 1 }, TXT_CONST.SPACE);		// efface													
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 1 }, TXT_CONST.SPACE);	
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 2 }, line);	// draw										
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 2 }, line);																															
	ConsoleRender::Add_Char_To_Render_List(crd, TXT_CONST.SPACE);	// Modifie le milieu
	ConsoleRender::Stop_Queue(); 																								
																																									
	ConsoleRender::Create_Queue(500, false);																														
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 2 },  TXT_CONST.SPACE);	// erase																							
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 2 },  TXT_CONST.SPACE);	
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 3 }, line, GRAY); // draw
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 3 }, line, GRAY);
	ConsoleRender::Stop_Queue();																								
										
	ConsoleRender::Create_Queue(800, false);							
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 3 }, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 3 }, TXT_CONST.SPACE);
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 4 }, tear, GRAY);
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 4 }, tear, GRAY);
	ConsoleRender::Stop_Queue();
		
	ConsoleRender::Create_Queue(1200, false);		// erase																	
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y - 4 }, TXT_CONST.SPACE);													
	ConsoleRender::Add_Char_To_Render_List({ x,crd.y + 4 }, TXT_CONST.SPACE);													
	ConsoleRender::Stop_Queue();																								
																																	  
}


void Ev_Border_Splash()	// Fait une animation de splash quand tu tir sur la bordure
{

	startPos = *blastP1.Get_Front_XY();	 // Trouvons l'axe maintenant, pour trouver la bonne bordure
	startPos.Increment_Coord();			// avance la coord d'une case, pour sortir de la map

	if (blastP1.Get_Distance_Travelled() == 0)	// dumb, but fixed
		startPos.Increment_Coord();			// avance la coord d'une case, pour sortir de la map
	
	switch (blastP1.Get_Dir())
	{
	case 0:  case 2:Horizontal_Splash();   break;
	case 1:  case 3:Vertical_Splash();	   break;
	}
}



