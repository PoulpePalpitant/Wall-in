#pragma once

#include "../grid/grid.h"
#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"

/*
	Le blast �a va �tre la fa�on pour le joueur de d�truire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur � partir de sa position de d�part. Ce projectile va avanc� jusqu'� ce qu'il 
	atteigne un obstacle. Quand le projectile s'arr�te, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est d�truit

*/

extern const Distance DFLT_BLAST_LENGTH_HOR;		// La longueur par d�faut du blast 
extern const Distance DFLT_BLAST_LENGTH_VER;		// La hauteur par d�faut du blast

enum class BlastType{REGULAR};	// Les propri�t�s sp�ciales du blast

// Quand le joueur appuie sur une touche de tir, il faut Setup les proprit�s du blast qu'il va tirer. Ces propri�t�s seront entreposer dans cette class
// SIDENOTE: Une seule structure de blast sera cr��(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement chang�

class Blast
{

	protected:
		friend class MoveBlast;	// L'animation du blast 

	BlastType type;	// Le type de blast

	//UI
	unsigned char sym;				// Le symbole du blast sera unique et r�p�t�(juste une longue ligne)
	Colors color;			// La couleur du blast sera unique, ou changera d�pandamment de ton animation.
	Distance maxSize;		// Donne la longueur max du blast en nombre de case dans la console
	Distance nbSteps;		// Le nombre de d�placement que le blast � fait dans la console (1 case = un d�placement)
	//time_t (temps entre chaque move)

	int grdLimit;					// L'endroit ou le blast va s'arr�ter dans son �pop� lin�aire
	Distance btwLinks;				// LA distance qui s�pare chaque �l�ment du grid de links. Sert de r�f�rence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de d�placement � faire avant que le blast se retrouve sur la m�me position qu'un �l�ment LINK.

	GridIndexIncrementor grdPos;		// HITBOX: V�rifie la pr�sence de colision avec les link que le blast traverse en avan�ant dans le grid
	CoordIncrementor frontXY;			// UI: Sert � uniquement � afficher chaque symbole de l'animation (dans une direction). Sert aussi � trimer la longueur du blast dans l'animation
	CoordIncrementor tailXY;			// UI: Sert  � trimer la longueur du blast dans l'animation

	// SETUP DU BLAST
	void Setup_Blast_UI(BlastType& type, Direction& blastDir);					// Assigne l'apparence du blast
	void Setup_Grid_Limit(Direction &direction);								// Calcul la limite ou le blast va devoir s'arr�ter
	void Setup_Position_Incrementors(Direction &direction, GrdCoord &startPos);	// Sa position 
	void Setup_Dist_Btw_Links(Direction& blastDir);								// Setup la distance qui va s�parer chaque �l�ment du Link Grid que le blast va parcourir

	// MISE EN ACTION DU BLAST
	bool Has_Reached_Limit();		// V�rifie si le blast � atteint la fin de son p�riple
	bool Blast_Is_On_LinkGrid();	// V�rifie si la "t�te" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }					// Reset le temps que �a va prendre pour rencontrer un autre Link

public:
	void Setup_Blast(BlastType& type, GrdCoord &startPos, Direction &blastDir);	// Setup tout les param�tre du blast pour le tir
	int Blast_Shot();	// le tir du blast...
};

// Les objets blasts :D

extern Blast blastP1;
extern Blast blastP2;