#pragma once

#include <string>
#include "coord.h"


const int NUM_COOL_CHARS = 23;
const int NUM_RECT_CHARS = 7;
const int COOL_CHARS[NUM_COOL_CHARS] = { 170,193,196,197,194,191,192,195,213,217,218,201,204,200,203,206,205,202,187,186,240,238,242 };
const int RECT_CHARS[NUM_RECT_CHARS] = { 176,178,177,220,219,223,254 };

// Some Goal text

const std::string GOAL_STOP = "- STOP THEM ALL -";

// Constantes de symboles souvent utulis�s
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
const int DOH_FONT_SIZE= 16;


// Des couleurs
enum Colors
{
	BLACK = 0, GRAY = 8,
	BLUE = 1, LIGHT_BLUE = 9,
	GREEN = 2, LIGHT_GREEN = 10,
	AQUA = 3, LIGHT_AQUA = 11,							
	RED = 4, LIGHT_RED = 12,
	PURPLE = 5, LIGHT_PURPLE = 13,
	YELLOW = 6, LIGHT_YELLOW = 14,
	WHITE = 7, BRIGHT_WHITE = 15,
	TEST = 155,
	BG_WH_LIGHT_GREEN = 250,	
	BG_WH_LIGHT_RED = 252,		
	BG_WH_LIGHT_PURPLE = 253,	
};

extern Colors gCurrentColor;	// La couleur actuelle d'output dans la console. 
extern Colors gBossClr;
extern Colors gJerClr;

extern const int TXT_SPD_DR;
extern const int TXT_SPD_FAST; 
extern const int TXT_SPD_ER;


Colors Get_Current_Color();// Si on veut affich� quoi que ce soit, on utilise ceci pour v�rifier si on a besoin, oui ou non de changer la couleur de l'output de la console
void Change_Color(int c);		// Permet de changer la couleur des prochains output de textes dans la console

int Find_Ctr_X(int size = 0);			// Trouve la crd en x qui permettrait d'output un char au centre
int Find_Ctr_String_X(std::string txt);	// ce que j'aurais du faire depuis le d�but lol. Retourne la valeur en X d'une string centr� dans la console
int Half_String(std::string txt);		// Le nombre de charact�re qui compose la moiti� d'une string, utile pour les affichages
int Find_Ctr_Grid(std::string txt);		// Affiche au centre du grid			


Coord Up_Txt_1(std::string txt);	// Pour afficher du texte en Haut sur la premi�re ligne
Coord Up_Txt_2(std::string txt);	// Pour afficher du texte en Haut sur la 2e ligne
Coord Up_Txt_3(std::string txt);	// Pour afficher du texte en Haut sur la 3e ligne

Coord Heart_Txt_Crd_Right(std::string txt, int line = 0);	// Affiche du texte � la droite du coeur
Coord Heart_Txt_Crd_Left(std::string txt, int line = 0);	// Affiche du texte � la gauche du coeur

Coord Boss_Txt_Crd (std::string txt = TXT_CONST.SPACE_STRING, int line = 0);	// Affiche du texte � l'emplacement du personnage du boss
int Boss_Txt_X ();	// Affiche du texte � l'emplacement du personnage du boss
int Boss_Txt_Y (int line = 0);	// Affiche du texte � l'emplacement du personnage du boss
void Erase_All_Boss_Txt(bool slow = false);

Coord Jerry_Txt_Crd(std::string txt, int line = 0);	// Affiche du texte � l'emplacement du personnage de Jimmy
int Jerry_Txt_X();
int Jerry_Txt_Y(int line = 0);
void Erase_All_Jerry_Txt();

void Erase_Right_Text();

void Dr_Or_Er_Title(const std::string* title, Coord start, int layers = STANDARD_ASCII_SIZE, Colors clr = WHITE, bool erase = false);	// Affiche 1 title qui � cet forme:
//"----___________ --_____ ---__--",		espace vide: vont �tre draw	
//"---/ ____/  _/ |-/ /   |--/ /--",		tiret	: ne sera pas draw
//"--/ /_---/ //  |/ / /| |-/ /---",		AScii art generator sur google g�n�re le art, tu remplis les trous avec des tirets, � LA MAIN! 
//"-/ __/-_/ // /|  / ___ |/ /___-",		Faut avoir le nombre exact de char pour chaque lignes
//"/_/---/___/_/-|_/_/---|_/_____/|",		si ta deux char comme �a en jaune	\\	= 1 char
//"--------------------------------"		Why am i doing this to myself? DAMN YOU CONSOLE! 

// Affiche un title � la con, mais juste 1 ligne de celle-ci, et selon une vitesse, et cr�er 1 string � chaque fois pour effacer les tirets de merde, et semble vraiment slow
void Dr_Or_Er_Title_Line(const std::string* title, Coord start, int line, Colors clr = WHITE, int speed = 0, bool erase = false);