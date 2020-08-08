
#include "ev_update_heart.h"


#include "../../player/player.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../UI/console_output/dsp_string.h"

static Coord crd;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors clrFlash;	// Fait flasher le coueur d'une certaine couleur 
static const int distUnderGrid = 4;
static Event ev_DrHeart3(Ev_Dr_Heart_3, 1);
static Event ev_DrHeart2(Ev_Dr_Heart_2, 1);
static Event ev_DrHeart1(Ev_Dr_Heart_1, 1);

static const std::string heart_3[] ={
"   ,;;;, ,;;;,	  ",
"  ;;;' ';' ';;;  ",
"  ;;;       ;;;  ",
"   ';;,   ,;;'	  ",
"     ';;,;;'	  ",
"       ';'		  "
};
static const std::string heart_2[] = {
"   , ., ,;;.	 ",
"  ';' ';' ';'	 ",
"  ';       ;'	 ",
"   ';    ,;	 ",
"     ;,;'       ",
"      '		 "
};
static const std::string heart_1[] = {
"  ;'';' ';	 ",
"  ;     ;;	 ",
"  ;,  ,;'	 ",
"    ,;'     ",
" 	  ;     ",
"       "

};


//"   .';' ';	 ",	// v2
//"  ; .   ;	 ",
//"  ;,  ,'	 ",
//"    ,;'	",
//"     ;		"

void Ev_Dr_Heart_1();	// 
void Ev_Er_Heart();		// Efface le coueur
void Ev_Add_Excess_Health();	// Si le joueur à plus que 3 de vie, on ajoute un tit +"nombre" à côté
void Ev_Rmv_Excess_Health();	// Même principe, sauf que retire le tit + 



/* CHOIX DE DESIGN

  ,d88b.d88b,	   
  88888888888	   
  `Y8888888Y'	   
 	`Y888Y'    	   
 	  `Y'		   

  ,;;;, ,;;;,	   
 ;;;' ';' ';;;	   
 ;;;       ;;;	   
  ';;,   ,;;'	   
    ';;,;;'		   
 	  ';'		   

 		   ,ae,	   // sad, but too big
 		 ,88888e   
  ,a888b.9888888i	
  888888888888888  
  88888888 88888Y  
  '8888888888888'  
 	"S888888888"   
 	  "7888888Y	   
 		 "e88j	   
 		   "Y	   


*/

void Ev_Dr_Heart_3()		 // Affiche le coueur à ses différents stades
{
	if (!ev_DrHeart3.Is_Active())
	{
		// initialisation, la console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y + distUnderGrid;	// Lignes en dessous du grid
		
		ev_DrHeart3.Activate();
		ev_DrHeart3.Start(0);
	}
	else
		while (ev_DrHeart3.delay.Tick())
		{
			switch (ev_DrHeart3.Get_Current_Step())
			{
			case 1:
				for (int i = 0; i < 10; i++)
				{
					if (i % 2 == 0)
						clrFlash = BRIGHT_WHITE;
					else
						clrFlash = LIGHT_GREEN;

					for (int i = 0; i < 6; i++)	// Affiche tout les char du coeur
					{
						UI_Dsp_String( { ori.x - 9, ori.y + i }, heart_3[i], clrFlash);
						Sleep(20);
						//ConsoleRender::Add_String(heart_3[i], { ori.x - 9, ori.y + i }, clrFlash);
					}
				}
				//Ev_Dr_Heart_2();
				ev_DrHeart3.Advance(0);
				break;

			case 2:
				ConsoleRender::Add_String(heart_3[1], { ori.x, ori.y + 1 }, LIGHT_GREEN);
				ev_DrHeart3.Advance(10000);
				break;

			case 3:
				ConsoleRender::Add_String(heart_3[2], { ori.x, ori.y + 2 }, LIGHT_GREEN);
				ev_DrHeart3.Advance(10000);
				break;

			case 4:
				ConsoleRender::Add_String(heart_3[3], { ori.x, ori.y + 3 }, LIGHT_GREEN);
				ev_DrHeart3.Advance(10000);
				break;

			case 5:
				ConsoleRender::Add_String(heart_3[4], { ori.x, ori.y + 4 }, LIGHT_GREEN);
				ev_DrHeart3.Advance(10000);
				break;

			case 6:
				ConsoleRender::Add_String(heart_3[5], { ori.x, ori.y + 5 }, LIGHT_GREEN);
				ev_DrHeart3.Advance(10000);
				break;

			case 7:
				ConsoleRender::Add_Char(crd, 197, GRAY);
				ev_DrHeart3.Advance(2000);
				break;

			case 8:
				ConsoleRender::Add_Char(crd, 197, WHITE);
				ev_DrHeart3.Advance(2500);
				break;

			case 9:
				ConsoleRender::Add_Char(crd, 197, BRIGHT_WHITE);
				ev_DrHeart3.Advance(4000);
				break;

			case 10:
				ConsoleRender::Add_Char(crd, 197, LIGHT_GREEN);
				ev_DrHeart3.Advance(0);
				break;
			}
		}
}
void Just_Dr_Heart(int hp)
{
	// initialisation, la console doit être setté pour utiliser ça
	ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
	ori.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y + distUnderGrid;	// Lignes en dessous du grid

	for (int i = 0; i < 6; i++)	// Affiche tout les char du coeur
	{
		if(hp == 3)
			ConsoleRender::Add_String(heart_3[i], { ori.x - 9, ori.y + i }, LIGHT_GREEN);
		else
			if(hp == 2)
				ConsoleRender::Add_String(heart_2[i], { ori.x - 9, ori.y + i }, LIGHT_YELLOW);
			else
				if(hp==1)
					ConsoleRender::Add_String(heart_1[i], { ori.x - 9, ori.y + i }, LIGHT_RED);
	}
}





void Ev_Dr_Heart_2()	// 
{
	if (!ev_DrHeart2.Is_Active())
	{
		// initialisation, la console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y + distUnderGrid;	// Lignes en dessous du grid

		ev_DrHeart2.Activate();
		ev_DrHeart2.Start(0);
	}
	else
		while (ev_DrHeart2.delay.Tick())
		{
			switch (ev_DrHeart2.Get_Current_Step())
			{
			case 1:
				for (int i = 0; i < 10; i++)
				{
					if (i % 2 == 0)
						clrFlash = BRIGHT_WHITE;
					else
						clrFlash = LIGHT_YELLOW;

					for (int i = 0; i < 6; i++)	// Affiche tout les char du coeur
					{
						UI_Dsp_String({ ori.x - 7, ori.y + i }, heart_2[i], clrFlash);
						Sleep(20);
						//ConsoleRender::Add_String(heart_2[i], { ori.x - 7, ori.y + i }, clrFlash);
					}
				}

				//Ev_Dr_Heart_1();
				ev_DrHeart2.Advance(0);
				break;


			}
		}
}


void Ev_Dr_Heart_1()	// 
{
	if (!ev_DrHeart1.Is_Active())
	{
		// initialisation, la console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y + distUnderGrid;	// Lignes en dessous du grid

		ev_DrHeart1.Activate();
		ev_DrHeart1.Start(0);
	}
	else
		while (ev_DrHeart1.delay.Tick())
		{
			switch (ev_DrHeart1.Get_Current_Step())
			{
			case 1:
				for (int i = 0; i < 10; i++)
				{
					if (i % 2 == 0)
						clrFlash = BRIGHT_WHITE;
					else
						clrFlash = LIGHT_RED;

					for (int i = 0; i < 6; i++)	// Affiche tout les char du coeur
					{

						UI_Dsp_String({ ori.x - 6, ori.y + i }, heart_1[i], clrFlash);
						Sleep(20);
					}
				}
				
					//ConsoleRender::Add_String(heart_1[i], { ori.x - 6, ori.y + i }, LIGHT_RED);

				
				ev_DrHeart1.Advance(0);
				break;
			}
		}
}