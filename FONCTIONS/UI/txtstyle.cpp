
#include "txtstyle.h"

#include "../console/sweet_cmd_console.h"
#include <Windows.h>


TextConstant TXT_CONST;	// Symboles constants et souvant utilisés pour l'affichage

extern Colors gCurrentColor = WHITE;	// La couleur actuelle d'output dans la console. 


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


// Trouve la crd en x qui permettrait d'output un char au centre
int Find_Ctr_X(int size)		
{
	return (gConWidth - size) / 2;
}