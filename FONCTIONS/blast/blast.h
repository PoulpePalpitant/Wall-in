#pragma once

#include "../grid/grid.h"
#include "../grid/grd_incrementor.h"
#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"


/*
	Le blast ça va être la façon pour le joueur de détruire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur à partir de sa position de départ. Ce projectile va avancé jusqu'à ce qu'il 
	atteigne un obstacle. Quand le projectile s'arrête, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est détruit

*/

extern const Distance DFLT_BLAST_LENGTH_HOR;		// La longueur par défaut du blast 
extern const Distance DFLT_BLAST_LENGTH_VER;		// La hauteur par défaut du blast
extern const time_t DFLT_BLAST_SPD;					// Vitesse par défaut du blast 

enum class BlastType{REGULAR};	// Les propriétés spéciales du blast

// Quand le joueur appuie sur une touche de tir, il faut Setup les proprités du blast qu'il va tirer. Ces propriétés seront entreposer dans cette class
// SIDENOTE: Une seule structure de blast sera créé(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement changé

class Blast
{

	protected:
		friend class MoveBlast;	// L'animation du blast 
		friend class AllWallGrids;		// Accès pour enregistré des nouveaux murs
		friend class WallGrid;		// Accès pour enregistré des nouveaux murs

		friend class LinkGrid;		// Pour enregistré des nouveaux Links

	BlastType type;	// Le type de blast

	//UI
	unsigned char sym;				// Le symbole du blast sera unique et répété(juste une longue ligne)
	Colors color;			// La couleur du blast sera unique, ou changera dépandamment de ton animation.
	Distance length;		// Donne la longueur max du blast qui va être tiré en nombre de case dans la console
	Distance maxlengthHor = DFLT_BLAST_LENGTH_HOR;	// La longueur du blast selon l'axe des X. Peut être augmenté ou réduite durant la game
	Distance maxlengthVer = DFLT_BLAST_LENGTH_VER;	// La longueur du blast selon l'axe des Y. Peut être augmenté ou réduite durant la game 
	int speed;	/*milliseconds*/					// Vitesse du blast(ou délaie entre chaque affichage)
	/* maxspeed */

	int grdLimit;					// L'endroit ou le blast va s'arrêter dans son épopé linéaire
	Distance nbSteps;		// Le nombre de déplacement que le blast à fait dans la console (1 case = un déplacement)
	Distance btwLinks;				// LA distance qui sépare chaque élément du grid de links. Sert de référence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de déplacement à faire avant que le blast se retrouve sur la même position qu'un élément LINK.

	GridIndexIncrementor grdPos;		// HITBOX: Position dans le grid. Vérifie colision avec les link que le blast traverse en avançant dans le grid. 
	CoordIncrementor frontXY;			// UI: Sert à uniquement à afficher chaque symbole de l'animation (dans une direction). Sert aussi à trimer la longueur du blast dans l'animation
	CoordIncrementor tailXY;			// UI: Sert  à trimer la longueur du blast dans l'animation
	Direction dir;						// Ça direction dans la consoles

	// SETUP DU BLAST
	void Setup_Blast_UI();					// Assigne l'apparence du blast
	void Setup_Grid_Limit();								// Calcul la limite ou le blast va devoir s'arrêter
	void Setup_Position_Incrementors(GrdCoord &startPos);	// Sa position 
	void Setup_Dist_Btw_Links();								// Setup la distance qui va séparer chaque élément du Link Grid que le blast va parcourir
	void Setup_Length();					// Ajuste la longueur du blast qui sera tiré
	void Setup_Speed();											// La vitesse d'affichage du blast(temps de pause entre chaque)

	// MISE EN ACTION DU BLAST
	bool Has_Reached_Limit();		// Vérifie si le blast à atteint la fin de son périple
	bool Blast_Is_On_LinkGrid();	// Vérifie si la "tête" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }		// Reset le temps que ça va prendre pour rencontrer un autre Link
	void Setup_Blast(BlastType type, GrdCoord &startPos, Direction &blastDir);	// Setup tout les paramètre du blast pour le tir

public:
	Blast* Blast_Shot(BlastType type, GrdCoord& startPos, Direction& blastDir);	// le tir du blast...
};

// Les objets blasts :D

extern Blast blastP1;
extern Blast blastP2;