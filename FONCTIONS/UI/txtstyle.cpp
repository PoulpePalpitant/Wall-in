
#include <Windows.h>
#include "txtstyle.h"

#include "../console/sweet_cmd_console.h"
#include "map.h"
#include "../events/global_events/ev_update_heart.h"
#include "../grid/AllGrids.h"


TextConstant TXT_CONST;	// Symboles constants et souvant utilisés pour l'affichage

extern Colors gCurrentColor = WHITE;	// La couleur actuelle d'output dans la console. 
Colors gBossClr = LIGHT_RED;
Colors gJerClr = LIGHT_AQUA;

const unsigned short TXT_SPD_DR = 200; // vitesse de défilement du texte par défaut
const unsigned short TXT_SPD_FAST = 70; // vitesse d'affichage
const unsigned short TXT_SPD_ER = 50; // vitesse d'éffacement du texte par défaut

// Changer la couleur
void Change_Color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);	// Change la couleur dans la console
	gCurrentColor = (Colors)c;										// Update la nouvelle couleur d'output
}

// Retourne la couleur d'affichage actuelle de la console
Colors Get_Current_Color()// Si on veut affiché quoi que ce soit, on utilise ceci pour vérifier si on a besoin, oui ou non de changer la couleur de l'output de la console
{
	return gCurrentColor;   
}

// Trouve la crd en x qui permettrait d'output une string au centre
int Find_Ctr_X(int size)		
{
	return (gConWidth - size) / 2;
}

int Find_Ctr_String_X(std::string txt)	// version un peu différente de celle en haut
{
	return (gConWidth - (int)txt.size()) / 2;

}
int Half_String(std::string txt)	// J'aurais du y penser plus tôt xD
{
	return ((int)txt.size() / 2);
}
int Find_Ctr_Grid(std::string txt)		// Affiche au centre du grid			
{
	return map.Get_Box_Limit(LEFT) + (map.Get_Length() / 2) - Half_String(txt);
}
/* Voici mes efforts pour uniformiser l'emplacement des crd dans le jeu pour afficher du texte*/


														/* BEHOLD! YOU NOW ENTER THE REALM OF COPY PASTE*/


// Le texte en HAUt ava être centré, et sur les lignes 3,4 et 5
Coord Up_Txt_1(std::string txt)	// Pour afficher du texte en Haut
{
	return { Find_Ctr_X((int)std::size(txt)), map.Get_Box_Limit(UP) - 5 };
}	

Coord Up_Txt_2(std::string txt) 
{
	return { Find_Ctr_X((int)std::size(txt)),map.Get_Box_Limit(UP) - 4 };
}	

Coord Up_Txt_3(std::string txt)// Pour afficher du texte en Haut sur la 2e ligne
{
	return { Find_Ctr_X((int)std::size(txt)),map.Get_Box_Limit(UP) - 3 };
}

// Le text à droite du coeur
Coord Heart_Txt_Crd_Right(std::string txt ,int line)
{
	int txtSize = (int)txt.size();

	Coord crd = Find_Heart_Ori_XY();

	if(line < 10)
		return { (crd.x - (txtSize / 2)) + 26 , crd.y + 2 + line };
	else
		return { 0,0 };	// hehe
}

Coord Heart_Txt_Crd_Left(std::string txt, int line)
{
	int txtSize = (int)txt.size();

	Coord crd = Find_Heart_Ori_XY();

	if (line < 10)
		return { (crd.x + (txtSize / 2)) - 37 , crd.y + 2 + line };
	else
		return { 0,0 };	// hehe
}

int Boss_Txt_X()
{
	//return  (gConWidth - (gConWidth / 5));	//v1
	return  map.Get_Box_Limit(RIGHT) + 30;	//v2
}

int Boss_Txt_Y(int line)
{
	//return  (gConHeight / 2) - 7 + line;
	return   map.Get_Box_Limit(UP) + 7 + line;
}

Coord Boss_Txt_Crd(std::string txt, int line )	// Affiche du texte à l'emplacement du personnage du boss
{
	if(line < 6)	// 4/5 de l'écran
		return { Boss_Txt_X() - ((int)std::size(txt) / 2),Boss_Txt_Y(line)}; // au trois quart à droite
	else
		return { 0,0 };	// hehe
}

void Erase_All_Boss_Txt(bool slow)
{
	std::string bigEraser = "                                                                          ";

	for (int i = 0; i < 6; i++)
	{
		if (slow)
			ConsoleRender::Add_String(bigEraser, { map.Get_Box_Limit(RIGHT) + 2, Boss_Txt_Y(i) }, WHITE, 50, true);
		else
		{
			gotoxy(map.Get_Box_Limit(RIGHT) + 2, Boss_Txt_Y(i));
			clreol();
		}
	}
}

int Jerry_Txt_X()
{
	return  map.Get_Box_Limit(RIGHT) + 18;	//v2
	//return  (gConWidth - (gConWidth / 5));
}

int Jerry_Txt_Y(int line)
{
	//return  (gConHeight / 2) - 12 + line;
	return   map.Get_Box_Limit(UP) + line;// v2

}

Coord Jerry_Txt_Crd(std::string txt, int line)	// Affiche du texte à l'emplacement du personnage de Jimmy
{
	if (line < 15)	// plus que 5 et tu empile sur le boss crd
		return { Jerry_Txt_X() - ((int)std::size(txt) / 2),Jerry_Txt_Y(line)}; // au trois quart à droite
	else
		return { 0,0 };	// hehe
}

void Erase_All_Jerry_Txt()
{
	for (int i = -1; i < 5; i++)
	{
		gotoxy(map.Get_Box_Limit(RIGHT) + 1, Jerry_Txt_Y(i));
		clreol();
	}
}

void Erase_Right_Text()
{
	Erase_All_Jerry_Txt();
	Erase_All_Boss_Txt();
}