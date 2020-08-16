
#include "ev_update_heart.h"


#include "../../player/player.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../UI/console_output/dsp_string.h"

#include "../../math/manage_interval.h" // Pour dessiner le coeur 
#include "../../math/intervals.h" // Pour dessiner le coeur 

// Pour l'affichage du coeur dans une string d'intervalle
// Liste d'intervalle = le nombre de rows de string
// Le Min d'un intervalle(par d�faut)  = au premier charact�re de la string � gauche
// Le max d'un intervalle(par d�faut) = au dernier charact�re de la string � droite

// Le contour va avoir 1 string en haut en bas � gauche et � droite de plus que le dedans
static Intervals::ManageIntervalLists outside(8,0,18); // L'ext�rieur du coeur, son contour, ce p�rim�tre contient une limite sous forme de carr�e
static Intervals::ManageIntervalLists inside(6, 0, 16); // Tout Les char qui repr�sente le coeur, sans les contours ext�rieurs

static Coord crd;
static Coord ori;		// Coordonn�e d'origine, servira de r�f�rence pour TOUT les affichages
static Colors clrFlash;	// Fait flasher le coueur d'une certaine couleur 
static const int distUnderGrid = 4;
static Event ev_DrHeart3(Ev_Dr_Heart_3, 1);

static const std::string heart_3[] ={
"   ,;;;, ,;;;,	  ",
"  ;;;' ';' ';;;  ",
"  ;;;       ;;;  ",
"   ';;,   ,;;'	  ",
"     ';;,;;'	  ",
"       ';'		  "
};
static const std::string heart_2[] = {
"   , ., ,;;.    ",
"  ';' ';' ';'   ",
"  ';       ;'   ",
"   ';    ,;     ",
"     ;,;'       ",
"      '         "
};
static const std::string heart_1[] = {
"  ;'';' ';	 ",
"  ;     ;;	 ",
"  ;,  ,;'	 ",
"    ,;'     ",
" 	  ;     ",

};


//"   .';' ';	 ",	// v2
//"  ; .   ;	 ",
//"  ;,  ,'	 ",
//"    ,;'	",
//"     ;		"

void Ev_Dr_Heart_1();	// 
void Ev_Er_Heart();		// Efface le coueur
void Ev_Add_Excess_Health();	// Si le joueur � plus que 3 de vie, on ajoute un tit +"nombre" � c�t�
void Ev_Rmv_Excess_Health();	// M�me principe, sauf que retire le tit + 



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

void Ev_Dr_Heart_3()		 // Affiche le coueur � ses diff�rents stades
{
	if (!ev_DrHeart3.Is_Active())
	{
		// initialisation, la console doit �tre sett� pour utiliser �a
		ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera � partir d'un point central, situ� en plein milieu de la fen�tre windows
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
	// initialisation, la console doit �tre sett� pour utiliser �a
	ori.x = Find_Ctr_X();		// L'afficahge du coeur se fera � partir d'un point central, situ� en plein milieu de la fen�tre windows
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


void Exclude_Outside_From_Heart(int hp)
{
	//static Intervals::ManageIntervalLists outside(8, 0, 18); // L'ext�rieur du coeur, son contour, ce p�rim�tre contient une limite sous forme de carr�e
//static Intervals::ManageIntervalLists inside(6, 0, 16); // Tout Les char qui repr�sente le coeur, sans les contours ext�rieurs

	if (hp == 3 || hp == 22)
	{
		inside.Resize(6, 0, 16);	 // Default
		// la je doit exclure tout le dedans
		static const std::string heart_3[] = {
"   ,;;;, ,;;;,	  ",
"  ;;;' ';' ';;;  ",
"  ;;;       ;;;  ",
"   ';;,   ,;;'	  ",
"     ';;,;;'	  ",
"       ';'		  "
		};

		inside.Exclude_Interval_From_List(0, 0, 2);
		inside.Exclude_Interval_From_List(0, 14, 18);




	}
	//if (hp == 2)
	//{
	//}

	if (hp == 1)
	{
		inside.Resize(5, 0, 12);	 // Default
		static const std::string heart_1[] = {
"  ;'';' ';	 ",
"  ;     ;;	 ",
"  ;,  ,;'	 ",
"    ,;'     ",
" 	  ;     ",

		};
		// Exclut tout ce qui se trouve � l'ext�rieur
		inside.Exclude_Interval_From_List(0, 0, 3);
	}

}


void Exclude_Heart_From_Outside(int hp)
{
	//static Intervals::ManageIntervalLists outside(8, 0, 18); // L'ext�rieur du coeur, son contour, ce p�rim�tre contient une limite sous forme de carr�e
	//static Intervals::ManageIntervalLists inside(6, 0, 16); // Tout Les char qui repr�sente le coeur, sans les contours ext�rieurs

	if (hp == 3)
	{
		outside.Resize(8, 0, 18);	 // Default
		// la je doit exclure tout le dedans

	}
	if (hp == 2)
	{
	}
	if (hp == 1)
	{

	}
}


void Set_Up_Drawers(int hp)		 // Setup les intervalles pour l'affichage
{
	Exclude_Heart_From_Outside(hp);
	Exclude_Outside_From_Heart(hp);

	/*if(hp == 3)
	if(hp == 2)
	if(hp == 1)*/
	Coord xy;
	Coord origin = { 20, 20 };

	for (int r = 0; r < /*inside.Get_Max_Available_Lists()*/1; r++)
	{
		for (int c = 0; c < inside.Get_Default_Max(); c++)
		{
			xy.x = c;
			xy.y = r;

			if (inside.Find_Value(r, c)) // Si �choue � trouver la valeur, on continue
			{
				xy.x += origin.x;
				xy.y += origin.y;
				ConsoleRender::Add_Char(xy, heart_3[r][c], LIGHT_GREEN);

			}
		}
	}
}


