
#include "txtstyle.h"

#include "../console/sweet_cmd_console.h"
#include "map.h"
#include <Windows.h>


TextConstant TXT_CONST;	// Symboles constants et souvant utilisés pour l'affichage

extern Colors gCurrentColor = WHITE;	// La couleur actuelle d'output dans la console. 
Colors gBossClr = LIGHT_RED;
Colors gJerClr = LIGHT_YELLOW;

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
/* Voici mes efforts pour uniformiser l'emplacement des crd dans le jeu pour afficher du texte*/

// Le texte en HAUt ava être centré, et sur les lignes 3,4 et 5
Coord Up_Txt_1(std::string txt)	// Pour afficher du texte en Haut
{
	return { Find_Ctr_X((int)std::size(txt)), 3 };
}	

Coord Up_Txt_2(std::string txt) 
{
	return { Find_Ctr_X((int)std::size(txt)), 4 };
}	

Coord Up_Txt_3(std::string txt)// Pour afficher du texte en Haut sur la 2e ligne
{
	return { Find_Ctr_X((int)std::size(txt)),5 };
}

// Le text à côté du coeur
Coord Heart_Txt_Crd(std::string txt ,int line)
{
	int txtSize = (int)txt.size();

	if(line < 10)
		return { (gConWidth - txtSize) / 2 + 22 , (gConHeight - 7 ) + line };
	else
		return { 0,0 };	// hehe
}

Coord Boss_Txt_Crd(std::string txt, int line )	// Affiche du texte à l'emplacement du personnage du boss
{
	if(line < 6)
		return { (gConWidth - 30) - ((int)std::size(txt) / 2), 12 + line }; // au trois quart à droite
	else
		return { 0,0 };	// hehe
}
int Boss_Txt_X()	
{
	return  (gConWidth - 30);
}

int Boss_Txt_Y(int line)	
{
	return 12 + line; 
}

void Erase_All_Boss_Txt()
{
	for (int i = 0; i < 6; i++)
	{
		gotoxy(map.Get_Box_Limit(RIGHT) + 1, 12 + i);
		clreol();
	}
}

Coord Jerry_Txt_Crd(std::string txt, int line)	// Affiche du texte à l'emplacement du personnage de Jimmy
{
	if (line < 4)
		return { (gConWidth - 31) - ((int)std::size(txt) / 2), 7 + line }; // au trois quart à droite
	else
		return { 0,0 };	// hehe

}

int Jerry_Txt_X()
{
	return  (gConWidth - 31);
}

int Jerry_Txt_Y(int line)
{
	return 7 + line;
}

void Erase_All_Jerry_Txt()
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(map.Get_Box_Limit(RIGHT) + 1, 7 + i);
		clreol();
	}
}

void Erase_Right_Text()
{
	Erase_All_Jerry_Txt();
	Erase_All_Boss_Txt();
}