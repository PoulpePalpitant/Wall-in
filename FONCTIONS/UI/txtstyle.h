#pragma once

#include <string>
#include "coord.h"


const int NUM_COOL_CHARS = 23;
const int NUM_RECT_CHARS = 7;
const int COOL_CHARS[NUM_COOL_CHARS] = { 170,193,196,197,194,191,192,195,213,217,218,201,204,200,203,206,205,202,187,186,240,238,242 };
const int RECT_CHARS[NUM_RECT_CHARS] = { 176,178,177,220,219,223,254 };

// Constantes de symboles souvent utulisés
struct TextConstant
{
	const char MINUS = '-';
	const char PLUS = '+';
	const char SPACE = ' ';
	const char ASTERISK = '*';
	const char CASH = '$';
	const char O = 'O';
	const unsigned char SPACE_FILL = 219;
	const char PARENTHESIS_OPEN = '(';
	const char PARENTHESIS_CLOSE = ')';
	const unsigned char VER_BAR = '|';
	const std::string EMPTY = "";		// EMPTY c'est le 'string' rebel
	const std::string SPACE_STRING = " ";	// 
	const std::string R_ARROW = "->";		// nope, deux autres :`)
	const std::string L_ARROW = "<-";		// nope
	const std::string DOTDOTDOT = ". . .";
	const unsigned char DOT = 250;	// middle dot
	const unsigned char DOTDOT = ':';	// double point
	const unsigned char LINE_HOR = 196;// HORIZONTAL LINE
	const unsigned char LINE_VER = 179;// VERTICAL LINE
};
extern TextConstant TXT_CONST;


const int STANDARD_ASCII_SIZE = 6;

//struct TextArt
//{
//
//
//	const std::string DAY_1_V2[STANDARD_ASCII_SIZE] = {
//
//" ____             ___   _                _____    _____                 __     _   ",
//"|    \ ___ _ _   |_  | |_|              |  _  |  |   | |___ _ _ _    __|  |___| |_ ",
//"|  |  | .'| | |   _| |_ _               |     |  | | | | -_| | | |  |  |  | . | . |",
//"|____/|__,|_  |  |_____|_|              |__|__|  |_|___|___|_____|  |_____|___|___|",
//"          |___|                                                                    "
//	};
//
//	const std::string DAY_1_V2[STANDARD_ASCII_SIZE] = {
//
//"    ____                 ___                 ___       _   __                    __      __   ",
//"   / __ \____ ___  __   <  /                /   |     / | / /__ _      __       / /___  / /_  ",
//"  / / / / __ `/ / / /   / (_)              / /| |    /  |/ / _ \ | /| / /  __  / / __ \/ __ \ ",
//" / /_/ / /_/ / /_/ /   / /                / ___ |   / /|  /  __/ |/ |/ /  / /_/ / /_/ / /_/ / ",
//"/_____/\__,_/\__, /   /_(_)              /_/  |_|  /_/ |_/\___/|__/|__/   \____/\____/_.___/  ",
//"            /____/                                                                            "
//		};
//};
//
//TextArt txtArt;

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
extern const unsigned short TXT_SPD_FAST; // vitesse d'affichage
extern const unsigned short TXT_SPD_ER; // vitesse d'effacement


Colors Get_Current_Color();// Si on veut affiché quoi que ce soit, on utilise ceci pour vérifier si on a besoin, oui ou non de changer la couleur de l'output de la console
void Change_Color(int c);		// Permet de changer la couleur des prochains output de textes dans la console

int Find_Ctr_X(int size = 0);			// Trouve la crd en x qui permettrait d'output un char au centre
int Find_Ctr_String_X(std::string txt);	// ce que j'aurais du faire depuis le début lol. Retourne la valeur en X d'une string centré dans la console
int Half_String(std::string txt);		// Le nombre de charactère qui compose la moitié d'une string, utile pour les affichages




Coord Up_Txt_1(std::string txt);	// Pour afficher du texte en Haut sur la première ligne
Coord Up_Txt_2(std::string txt);	// Pour afficher du texte en Haut sur la 2e ligne
Coord Up_Txt_3(std::string txt);	// Pour afficher du texte en Haut sur la 3e ligne

Coord Heart_Txt_Crd_Right(std::string txt, int line = 0);	// Affiche du texte à la droite du coeur
Coord Heart_Txt_Crd_Left(std::string txt, int line = 0);	// Affiche du texte à la gauche du coeur

Coord Boss_Txt_Crd (std::string txt = TXT_CONST.SPACE_STRING, int line = 0);	// Affiche du texte à l'emplacement du personnage du boss
int Boss_Txt_X ();	// Affiche du texte à l'emplacement du personnage du boss
int Boss_Txt_Y (int line = 0);	// Affiche du texte à l'emplacement du personnage du boss
void Erase_All_Boss_Txt();

Coord Jerry_Txt_Crd(std::string txt, int line = 0);	// Affiche du texte à l'emplacement du personnage de Jimmy
int Jerry_Txt_X();
int Jerry_Txt_Y(int line = 0);
void Erase_All_Jerry_Txt();

void Erase_Right_Text();