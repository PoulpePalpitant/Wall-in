
#include "txtstyle.h"

#include "../console/sweet_cmd_console.h"
#include "map.h"
#include "../grid/AllGrids.h"


TextConstant TXT_CONST;	

extern Colors gCurrentColor = WHITE;	// La couleur actuelle d'output dans la console. 
Colors gBossClr = LIGHT_RED;
Colors gJerClr = LIGHT_AQUA;

const int TXT_SPD_DR = 27000; // vitesse de défilement du texte par défaut
const int TXT_SPD_ER = 35000; 
const int TXT_SPD_FAST = 42000; 


void Change_Color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);	
	gCurrentColor = (Colors)c;										
}

Colors Get_Current_Color()	
{
	return gCurrentColor;   
}

int Find_Ctr_X(int size)		
{
	return (gConWidth - size) / 2;
}

int Find_Ctr_String_X(std::string txt)	
{
	return (gConWidth - (int)txt.size()) / 2;

}
int Half_String(std::string txt)	
{
	return ((int)txt.size() / 2);
}
int Find_Ctr_Grid(std::string txt)	
{
	return map.Get_Limit(LEFT) + (map.Get_Length() / 2) - Half_String(txt);
}

/* Voici mes efforts pour uniformiser l'emplacement des crd dans le jeu pour afficher du texte*/

														/* BEHOLD! YOU NOW ENTER THE REALM OF COPY PASTE*/


// Le texte en HAUt ava être centré, et sur les lignes 3,4 et 5
Coord Up_Txt_1(std::string txt)	
{
	return { Find_Ctr_Grid(txt), map.Get_Limit(UP) - 5 };
}	

Coord Up_Txt_2(std::string txt) 
{
	return { Find_Ctr_Grid(txt),map.Get_Limit(UP) - 4 };
}	

Coord Up_Txt_3(std::string txt)
{
	return { Find_Ctr_Grid(txt),map.Get_Limit(UP) - 3 };
}


// Affiche un title à la con
void Dr_Or_Er_Title(const std::string* title, Coord start, int layers, Colors clr, bool erase)
{
	Coord crd;
	int size = (int)title[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = start;

		for (int sym = 0; sym < size; sym++, crd.x++)
		{

			if (title[line][sym] == TXT_CONST.MINUS)
				continue;
			else
			{
				if (erase)
					symbol = TXT_CONST.SPACE;
				else
					symbol = title[line][sym];
			}

			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, clr);
		}
	}
}

// Affiche un title à la con, mais juste 1 ligne de celle-ci, et selon une vitesse, et créer 1 string à chaque fois pour effacer les tirets de merde, et semble vraiment slow
void Dr_Or_Er_Title_Line(const std::string* title, Coord start, int line, Colors clr, int speed, bool erase)
{
	int size = (int)title[0].length();
	char symbol = 0;
	std::string txt = "";	

	for (int sym = 0; sym < size; sym++)
	{
		if (title[line][sym] == TXT_CONST.MINUS || erase)
			txt += TXT_CONST.SPACE;
		else
			txt += title[line][sym];
	}

	ConsoleRender::Add_String(txt, { start.x, start.y + line }, clr, speed, erase);
}