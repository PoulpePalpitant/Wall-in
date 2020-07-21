#pragma once

#include <string>
#include "coord.h"

// Constantes de symboles souvent utulisés
struct TextConstant
{
	const char MINUS = '-';
	const char PLUS = '+';
	const char SPACE = ' ';
	const char PARENTHESIS_OPEN = '(';
	const char PARENTHESIS_CLOSE = ')';
	const unsigned char VER_BAR = '|';
	const std::string EMPTY = "";		// EMPTY c'est le 'string' rebel
	const std::string R_ARROW = "->";		// nope, deux autres :`)
	const std::string L_ARROW = "<-";		// nope
	const std::string DOTDOTDOT = ". . .";
	const unsigned char DOT = 250;
};

extern TextConstant TXT_CONST;

// Des couleurs
enum Colors
{
	BLACK = 0, GRAY = 8,
	BLUE = 1, LIGHT_BLUE = 9,
	GREEN = 2, LIGHT_GREEN = 10,
	AQUA = 3, LIGHT_AQUA = 11,							// Numbers after 15 include background colors
	RED = 4, LIGHT_RED = 12,
	PURPLE = 5, LIGHT_PURPLE = 13,
	YELLOW = 6, LIGHT_YELLOW = 14,
	WHITE = 7, BRIGHT_WHITE = 15,

	BG_WH_LIGHT_GREEN = 250,	// BG_WH	= Background White
	BG_WH_LIGHT_RED = 252,		// BG_WH	= Background White
	BG_WH_LIGHT_PURPLE = 253,	// BG_WH	= Background White
};

extern Colors gCurrentColor;	// La couleur actuelle d'output dans la console. 
extern Colors gBossClr;
extern Colors gJerClr;

extern const unsigned short TXT_SPD_DR; // vitesse d'affichage
extern const unsigned short TXT_SPD_ER; // vitesse d'effacement


Colors Get_Current_Color();// Si on veut affiché quoi que ce soit, on utilise ceci pour vérifier si on a besoin, oui ou non de changer la couleur de l'output de la console
void Change_Color(int c);		// Permet de changer la couleur des prochains output de textes dans la console

int Find_Ctr_X(int size = 0);		// Trouve la crd en x qui permettrait d'output un char au centre

Coord Up_Txt_1(std::string txt);	// Pour afficher du texte en Haut sur la première ligne
Coord Up_Txt_2(std::string txt);	// Pour afficher du texte en Haut sur la 2e ligne
Coord Up_Txt_3(std::string txt);	// Pour afficher du texte en Haut sur la 3e ligne

Coord Heart_Txt_Crd(int line = 0);	// Affiche du texte à la droite du coeur

Coord Boss_Txt_Crd (std::string txt, int line = 0);	// Affiche du texte à l'emplacement du personnage du boss
Coord Jerry_Txt_Crd(std::string txt, int line = 0);	// Affiche du texte à l'emplacement du personnage de Jimmy