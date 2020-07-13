#pragma once

#include <string>


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
	SIXTEEN = 16,
	SEVENTEEN = 17,
	EIGHTTEEN = 18,
	NINETEEN = 19,
	TWENTY = 20,
	THIRTY = 30,
	FORTY = 40
};

extern Colors gCurrentColor;	// La couleur actuelle d'output dans la console. 


Colors Get_Current_Color();// Si on veut affiché quoi que ce soit, on utilise ceci pour vérifier si on a besoin, oui ou non de changer la couleur de l'output de la console
void Change_Color(int c);		// Permet de changer la couleur des prochains output de textes dans la console


int Find_Ctr_X(int size = 0);		// Trouve la crd en x qui permettrait d'output un char au centre
