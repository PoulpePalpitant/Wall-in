
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
// Le Min d'un intervalle(par défaut)  = au premier charactère de la string à gauche
// Le max d'un intervalle(par défaut) = au dernier charactère de la string à droite
// Pour exclure une valeur de l'intervalle, on considère le 0 et on ignore le max

// Le contour va avoir 1 string en haut en bas à gauche et à droite de plus que le dedans
static Intervals::ManageIntervalLists outside(8,0,19); // L'extérieur du coeur, son contour, ce périmètre contient une limite sous forme de carrée
static Intervals::ManageIntervalLists inside(6, 0, 16);		// Tout Les char qui représente le coeur, sans les contours extérieurs. Sidenote, tu dois inclure le nombre max somehow?

static Coord xy;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la première est blanche, l'autre représente la couleur du coeur
static int drawnOut;	// Nombre de char qui sont draw outside du char actuellement. Quand ça reach, genre 5, on arrête de draw outside
static int c, r;        // Pour s'orienter dans les string
static int HP;			// Dicte que stade d'hp on se trouve
static bool fastDraw = true;	// Vitesse à laquelle on va afficher les coeurs
static int drawSpeed[2];	/// 2 vitesse d'affichages : 1 pour la première phase, 2 pour la 2e phase
static const int DFLT_FAST_SPEED[2] = {300000, 100000};	// same logic 
static const int DFLT_SLOW_SPEED[2] = {60000, 42000};	// same logic 


static Colors clrFlash;	// Fait flasher le coueur d'une certaine couleur 
static const int distUnderGrid = 4;
static Event ev_DrHeart(Ev_Dr_Heart, 3);

static const std::string heart_4[] = {	// do this now
"  ,;;;;, ,;;;;,  ",
" ;;;*::*;*::*;;; ",
" ;;;*:::*:::*;;; ",
"  ';;*:::::*;;'  ",
"    ';*;:;*;'    ",
"      `';'`      "
};

static const std::string heart_3[] ={
"   ,;;;, ,;;;,   ",
"  ;;;' ';' ';;;  ",
"  ;;;       ;;;  ",
"   ';;,   ,;;'   ",
"     ';;,;;'     ",
"       ';'       "
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
"  ;'';' ';  ",
"  ;     ;;  ",
"  ;,  ,;'   ",
"    ,;'     ",
"     ;      ",
};

static const std::string heart_dead[] = {	// the void
"----------------------",
"----------------------",
"----------------------",
"----------------------",
"----------------------",
"----------------------",
"----------------------",
"----------------------",
"----------------------"
};
static const std::string* allHearts[5] = { heart_dead, heart_1, heart_2, heart_3, heart_4 };	// all of the hearts

//"   .';' ';	 ",	// v2
//"  ; .   ;	 ",
//"  ;,  ,'	 ",
//"    ,;'	",
//"     ;		"

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

Coord Find_Heart_Ori_XY()	 // position de départ pour draw le coeur
{
	return { Find_Ctr_String_X(heart_dead[0]), linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y + distUnderGrid };
}

void Just_Dr_Heart(int hp)
{
	// initialisation, la console doit être setté pour utiliser ça, ainsi que le grid
	ori = Find_Heart_Ori_XY();

	for (int i = 0; i < 6; i++)	// Affiche tout les char du coeur
	{
		if(hp == 3)
			ConsoleRender::Add_String(heart_3[i], { ori.x, ori.y + i }, LIGHT_GREEN);
		else
			if(hp == 2)
				ConsoleRender::Add_String(heart_2[i], { ori.x, ori.y + i }, LIGHT_YELLOW);
			else
				if(hp==1)
					ConsoleRender::Add_String(heart_1[i], { ori.x, ori.y + i }, LIGHT_RED);
	}
}


void Exclude_Outside_From_Heart(int hp)
{
	if (hp == 4)
	{
		inside.Resize(6, 0, 17);	 // Default
		// la je doit exclure tout le dedans

//"*  ,;;;, ,;;;,  *",
//"  ;;;:::;:::;;;  ",
//"  ;;;:::::*:;;;  ",
//"*  ';;:::::;;'   ",
//"     ';;:;;'  *  ",
//"  *    ';'       "
		//Exclusion lignes par lignes des charactères qui composent l'ext du coeur
		
	///*inside.Exclude_Interval_From_List(0, 1, 2);*/
	//inside.Exclude_Interval_From_List(0, 14, 15); 	
	//inside.Exclude_Interval_From_List(1, 0, 1);		inside.Exclude_Interval_From_List(1, 15, 17);
	//inside.Exclude_Interval_From_List(2, 0, 1);		inside.Exclude_Interval_From_List(2, 15, 17);
	///*inside.Exclude_Interval_From_List(3, 0, 2);*/	inside.Exclude_Interval_From_List(3, 14, 17);	
	//inside.Exclude_Interval_From_List(4, 1, 4);/*	inside.Exclude_Interval_From_List(4, 12, 14);	*/
	///*inside.Exclude_Interval_From_List(5, 4, 6);*/	inside.Exclude_Interval_From_List(5, 10, 17);	

	}

	if (hp == 3)
	{
		inside.Resize(6, 0, 17);	 // Default
		// la je doit exclure tout l'ext
//"   ,;;;, ,;;;,   ",
//"  ;;;' ';' ';;;  ",
//"  ;;;       ;;;  ",
//"   ';;,   ,;;'	  ",
//"     ';;,;;'     ",
//"       ';'       "


		//// Exclusion lignes par lignes des charactères qui composent l'ext du coeur
		inside.Exclude_Interval_From_List(0, 0, 2);	inside.Exclude_Interval_From_List(0, 14, 16); 
		inside.Exclude_Interval_From_List(1, 0, 1);	inside.Exclude_Interval_From_List(1, 15, 16);	
		inside.Exclude_Interval_From_List(2, 0, 1);	inside.Exclude_Interval_From_List(2, 15, 16); 
		inside.Exclude_Interval_From_List(3, 0, 2);	inside.Exclude_Interval_From_List(3, 14, 16); 
		inside.Exclude_Interval_From_List(4, 0, 4);	inside.Exclude_Interval_From_List(4, 12, 16); 
		inside.Exclude_Interval_From_List(5, 0, 6);	inside.Exclude_Interval_From_List(5, 10, 16); 
	}
	if (hp == 2)
	{
		inside.Resize(6, 0, 16);	 // Default

		inside.Exclude_Interval_From_List(0, 0, 2);	inside.Exclude_Interval_From_List(0, 12, 16);
		inside.Exclude_Interval_From_List(1, 0, 1);	inside.Exclude_Interval_From_List(1, 13, 16);	// AIS-JE VRAIMENT BESOIN D'EXCLURE LE DEHORS QUAND J'AFFICHE PAS LES CHARACTÈRES VIDE?
		inside.Exclude_Interval_From_List(2, 0, 1);	inside.Exclude_Interval_From_List(2, 13, 16);	// . . . oui
		inside.Exclude_Interval_From_List(3, 0, 2);	inside.Exclude_Interval_From_List(3, 11, 16);
		inside.Exclude_Interval_From_List(4, 0, 4);	inside.Exclude_Interval_From_List(4, 9, 16);
		inside.Exclude_Interval_From_List(5, 0, 5);	inside.Exclude_Interval_From_List(5, 7, 16);

		/*  "   , ., ,;;.    ",
			"  ';' ';' ';'   ",
			"  ';       ;'   ",
			"   ';    ,;     ",
			"     ;,;'       ",
			"      '         "*/
	}

	if (hp == 1)
	{
		inside.Resize(5, 0, 12);	 // Default

		inside.Add_Interval_On_Top(0, 0, 1);		inside.Exclude_Interval_From_List(0, 10, 12);
		inside.Exclude_Interval_From_List(1, 0, 1);	inside.Exclude_Interval_From_List(1, 10, 12);	// AIS-JE VRAIMENT BESOIN D'EXCLURE LE DEHORS QUAND J'AFFICHE PAS LES CHARACTÈRES VIDE?
		inside.Exclude_Interval_From_List(2, 0, 1);	inside.Exclude_Interval_From_List(2, 9, 12);	// . . . oui
		inside.Exclude_Interval_From_List(3, 0, 3);	inside.Exclude_Interval_From_List(3, 7, 12);
		inside.Exclude_Interval_From_List(4, 0, 4);	inside.Exclude_Interval_From_List(4, 6,  12);
//"  ;'';' ';    ",
//"  ;     ;;    ",
//"  ;,  ,;'     ",
//"    ,;'       ",
//"     ;        ",
//
//		};
	}

	if (hp == 0)
	{
		inside.Resize(9, 0,(int)heart_dead[0].size());	 // Default

		// Ya pas de coeur à 0 hp. Par contre, on fill le carrée quand même, en enlevant quelques chars pour rendre ça glitchy
		inside.Exclude_Interval_From_List(0, 0, 5);	//inside.Exclude_Interval_From_List(0, 14, 16);
		inside.Exclude_Interval_From_List(1, 0, 1);	inside.Exclude_Interval_From_List(1, 17, 22);	
		inside.Exclude_Interval_From_List(2, 0, 3);	inside.Exclude_Interval_From_List(2, 19, 22);
		inside.Exclude_Interval_From_List(3, 0, 4);	inside.Exclude_Interval_From_List(3, 20, 22);
		inside.Exclude_Interval_From_List(4, 0, 2);
		inside.Exclude_Interval_From_List(5, 0, 5);	inside.Exclude_Interval_From_List(5, 21, 22);
		inside.Exclude_Interval_From_List(6, 0, 7);	inside.Exclude_Interval_From_List(6, 20, 22);
		inside.Exclude_Interval_From_List(7, 0, 7);	inside.Exclude_Interval_From_List(7, 21, 22);
		inside.Exclude_Interval_From_List(8, 0, 6);	inside.Exclude_Interval_From_List(8, 16, 22);
//"                ",
//"                ",
//"                ",
//"                ",
//"                ",
//"                "
	}

}


void Exclude_Inside(int hp)
{	
	outside.Reset_All_Lists(); // 

	outside.Resize(8, 0, 20);	 // Default

	if (hp == 4)
	{
		// Exclusion lignes par lignes des charactères qui composent l'intérieur du coeur
		outside.Remove_Value(1,2);outside.Remove_Value(1, 17);  outside.Exclude_Interval_From_List(1, 4, 14);
		outside.Exclude_Interval_From_List(2, 3, 15);
		outside.Exclude_Interval_From_List(3, 3, 15);
		outside.Remove_Value(4, 2);outside.Exclude_Interval_From_List(4, 4, 14);
		outside.Remove_Value(5, 15);outside.Exclude_Interval_From_List(5, 6, 12);
		outside.Remove_Value(6, 5);outside.Exclude_Interval_From_List(6, 8, 10);
		// Exclusion lignes par lignes des charactères qui composent l'intérieur du coeur
		outside.Exclude_Interval_From_List(1, 3, 15);
		outside.Exclude_Interval_From_List(2, 2, 16);
		outside.Exclude_Interval_From_List(3, 2, 16);
		outside.Exclude_Interval_From_List(4, 3, 15);
		outside.Exclude_Interval_From_List(5, 5, 13);
		outside.Exclude_Interval_From_List(6, 7, 11);

//" * ,;;;, ,;;;,  *",
//"  ;;;:::;:::;;;  ",
//"  ;;;:::::*:;;;  ",
//" * ';;:::::;;'   ",
//"     ';;:;;'  *  ",
//"    *  ';'       "
	}

	if (hp == 3)
	{

		// Exclusion lignes par lignes des charactères qui composent l'intérieur du coeur
		outside.Exclude_Interval_From_List(1, 4, 14);	
		outside.Exclude_Interval_From_List(2, 3, 15);	
		outside.Exclude_Interval_From_List(3, 3, 15);	
		outside.Exclude_Interval_From_List(4, 4, 14);	
		outside.Exclude_Interval_From_List(5, 6, 12);	
		outside.Exclude_Interval_From_List(6, 8, 10);	
	}
	if (hp == 2)
	{
		outside.Exclude_Interval_From_List(1, 4, 12);
		outside.Exclude_Interval_From_List(2, 3, 13);
		outside.Exclude_Interval_From_List(3, 3, 13);
		outside.Exclude_Interval_From_List(4, 4, 11);
		outside.Exclude_Interval_From_List(5, 6, 9);
		outside.Exclude_Interval_From_List(6, 7, 7);

//"   , ., ,;;.    ",
//"  ';' ';' ';'   ",
//"  ';       ;'   ",
//"   ';    ,;     ",
//"     ;,;'       ",
//"      '         "
//};
	}
	if (hp == 1)
	{

		outside.Exclude_Interval_From_List(1, 3, 10);
		outside.Exclude_Interval_From_List(2, 3, 10);
		outside.Exclude_Interval_From_List(3, 3, 9);
		outside.Exclude_Interval_From_List(4, 5, 7);
		outside.Exclude_Interval_From_List(5, 6, 6);
//"  ;'';' ';  ",
//"  ;     ;;  ",
//"  ;,  ,;'   ",
//"    ,;'     ",
//"     ;      ",
	}
}

void Set_Speed_Draw(bool slow)	// permet de rendre la vitesse d'affichage du coeur bcp plus lente
{
	if (slow)
	{
		drawSpeed[0] = DFLT_SLOW_SPEED[0];
		drawSpeed[1] = DFLT_SLOW_SPEED[1];
		fastDraw = false;	// 
	}
	else
	{
		drawSpeed[0] = DFLT_FAST_SPEED[0];
		drawSpeed[1] = DFLT_FAST_SPEED[1];
		fastDraw = true;	// Probablement pas nécessaire, mais safety
	}
}

void Fill_Outside_Heart(bool fill)
{
	// Erase tout le contours du coeur
	if (fill)
	{
		for (int i = 0; i < 2; i++)
		{
			if (outside.Pick_From_Lists(r, c, true, true, Intervals::RDM_ALL)) // r et c garde les valeurs trouvés dnas les intervalles
			{
				ConsoleRender::Add_Char({ ori.x - 1 + c, ori.y - 1 + r }, TXT_CONST.SPACE); // Erase!
			}
		}		
	}
	else
	{
		// Fait apparaître des tits sym un peu partout autours
		c = rand() % outside.Get_Default_Max();
		r = rand() % outside.Get_Max_Available_Lists();

		if (outside.Find_Value(r, c))
		{
			ConsoleRender::Add_Char({ ori.x - 1 + c, ori.y - 1 + r }, COOL_CHARS[rand() % NUM_COOL_CHARS], fillClr[0]);
			drawnOut++;
		}
	}
}

void Fill_Heart_Randomly(bool rdmChars)
{
	if (!inside.Pick_From_Lists(r, c, true, true, Intervals::RDM_ALL)) // r et c garde les valeurs trouvés dnas les intervalles
		return;

	if (rdmChars)
	{
		if (allHearts[HP][r][c] != TXT_CONST.SPACE)
			ConsoleRender::Add_Char({ ori.x + c, ori.y + r }, COOL_CHARS[rand() % NUM_COOL_CHARS], fillClr[0]); // Fill uniquement les chars qui forment le coueur, pas la vide au milieu
	}
	else
	{
		if (HP == 4)	// special colors
		{
			if(allHearts[HP][r][c] == TXT_CONST.DOTDOT)
				ConsoleRender::Add_Char({ ori.x + c, ori.y + r }, allHearts[HP][r][c], LIGHT_AQUA); // dedans 
			else
				if(allHearts[HP][r][c] == TXT_CONST.ASTERISK)
					ConsoleRender::Add_Char({ ori.x + c, ori.y + r }, allHearts[HP][r][c], LIGHT_YELLOW); // éclat 
				else
					ConsoleRender::Add_Char({ ori.x + c, ori.y + r }, allHearts[HP][r][c], fillClr[1]); // Fill aussi le vide au milieu
		}
		else
			ConsoleRender::Add_Char({ ori.x + c, ori.y + r }, allHearts[HP][r][c], fillClr[1]); // Fill aussi le vide au milieu
	}
}

void Set_Up_Drawers(int hp, bool slow)		 // Setup les intervalles pour l'affichage
{
	Exclude_Inside(hp);
	Exclude_Outside_From_Heart(hp);

	switch (hp)
	{
	case 0:fillClr[1] = LIGHT_RED; break;
	case 1:fillClr[1] = LIGHT_RED; break;
	case 2:fillClr[1] = LIGHT_YELLOW; break;
	case 3:fillClr[1] = LIGHT_GREEN; break;
	case 4:fillClr[1] = LIGHT_GREEN/*LIGHT_AQUA*/; break;
	}

	//if (slow)
	//	fillClr[0] = WHITE;	// Quand c'est slow, on affiche des lignes blanches
	//else
		fillClr[0] = fillClr[1];	// same couleur

	
	HP = hp;
}

void Start_Ev_Dr_Heart(int hp, bool slow)		 // Setup l'event Précédent
{
	if (hp <= 4)
	{
		if (ev_DrHeart.Is_Active())
			ev_DrHeart.Cancel(); // Stop l'animation

		Set_Up_Drawers(hp, slow); // change les intervalles inside et outside
		Set_Speed_Draw(slow);
		Ev_Dr_Heart();		// Le nouveau coueur à dessiner
	}
}

void Ev_Dr_Heart()		 // Affiche le coueur à ses différents stades
{
	static int boringNum;
	static int rdmFill;
	if (!ev_DrHeart.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		ori = Find_Heart_Ori_XY();
		rdmFill = 15;	// nombre de ill random à l'etéreieur du coeur
		if (HP == 0) // repositionnnement
		{
			ori.x -= 6;
			ori.y -= 3;
		}
		if (HP == 1)
		{
			rdmFill * 3;
			fastDraw = false;
			ori.x += 2;
		}

		boringNum = drawnOut = 0; // Pour un peu de random

		if (fastDraw)
			Set_Speed_Draw();

		ev_DrHeart.Activate();
		ev_DrHeart.Start(0);
		ev_DrHeart.delay.Start_Timer(drawSpeed[0],1, true );	// Le coueur sera affiché à cette vitesse
	}
	else
		while (ev_DrHeart.delay.Tick())
		{
			switch (ev_DrHeart.Get_Current_Step())
			{
			case 1:
				if (!inside.Is_All_Empty())
				{
					// Draw quelques char cool un peu à l'ext du coeur, d'in fois
					if(drawnOut < rdmFill)
						if (boringNum % 6 == 0)
							Fill_Outside_Heart(false);
					
					boringNum += 7;

					Fill_Heart_Randomly(true);
				}
				else
				{
					ev_DrHeart.delay.Stop();
					ev_DrHeart.Advance(5000);
				}
				break;

			case 2: // tit break
				if (HP == 0)
					ev_DrHeart.Cancel();	// Arrête l'event right here
				else {
					Exclude_Outside_From_Heart(HP);
					ev_DrHeart.Advance(0);
					ev_DrHeart.delay.Start_Timer(drawSpeed[1], 1, true);	// Le coueur sera affiché à cette vitesse
					break;
				}
			case 3:
				if (!outside.Is_All_Empty() || !inside.Is_All_Empty() ) // On attend que l'ext et lintérieur est finis d'afficher
				{
					Fill_Outside_Heart(true);
					Fill_Heart_Randomly(false);
				}
				else
				{
					ev_DrHeart.delay.Stop();
					ev_DrHeart.Advance(0); // end of the line pal
				}
				break;
			}
		}
}
