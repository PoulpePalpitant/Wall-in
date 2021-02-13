#pragma once

#include <vector>
#include "../grid/grd_incrementor.h"
#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../math/math_stuff.h"
#include "../walls/walls.h"
#include "../link/link.h"
#include "../time/countdown_clock.h"
#include "../time/movement_timer.h"
#include "../global_types/global_types.h"
#include "blast_ammo.h"

/*
POST-MORTEM
 "C'est ici que le projet à commencé en fait, ce qui veut dire que la façon de faire pour animer ce truc n'a pas vraiment évolué. J'ai essayé de limiter la fréquence de détection de colision
 mais j'pense qu'au final ça l'a over-compliqué les choses pour rien"

	Le blast ça va être la façon pour le joueur de détruire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur à partir de sa position de départ. Ce projectile va avancé jusqu'à ce qu'il 
	atteigne un obstacle. Quand le projectile s'arrête, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est détruit

*/
struct BlastType						
{
	WallType wallType;	// La force du wall qui sera créé.
	Modifier mod;		// Le type de Link qui sera créé	
};							

extern const BlastType DFLT_BLAST;					
extern const Distance DFLT_BLAST_LENGTH_HOR;		
extern const Distance DFLT_BLAST_LENGTH_VER;		
extern const time_t DFLT_BLAST_SPD_VER;				
extern const time_t DFLT_BLAST_SPD_HOR;

// SIDENOTE: Une seule structure de blast sera créé(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement changé

class Blast
{
	friend void Change_Blast();	

	protected:
		friend class UI_MoveBlast;	// L'animation du blast 
		friend class WallGrid;		// Accès pour enregistré des nouveaux murs
		friend class AllGrids;
		friend class LinkGrid;		// Pour enregistré des nouveaux Links


	bool active;			// Le blast est actif ou non. Quand il est actif il est en train de se déplacer
	BlastAmmo ammo;			// Fixe une limit de blast que le joueur peut faire. Si vide, il ne peut tirer

	// STUPID FIX
	std::vector<GrdCoord> ffToRedraw;

	//UI
	unsigned char sym;		
	Colors color;			
	Distance length;		
	Distance maxlengthHor = DFLT_BLAST_LENGTH_HOR;	
	Distance maxlengthVer = DFLT_BLAST_LENGTH_VER;	
	int speed;	
	time_t speedVer = DFLT_BLAST_SPD_VER;		
	time_t speedHor = DFLT_BLAST_SPD_HOR;		
	
	// POSITION/DÉPLACEMENT
	int grdLimit;					// L'endroit ou le blast va s'arrêter dans son épopé linéaire
	Distance nbSteps;				// Le nombre de déplacement que le blast à fait dans la console (1 case = un déplacement)
	Distance btwLinks;				// LA distance qui sépare chaque élément du grid de links. Sert de référence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de déplacement à faire avant que le blast se retrouve sur la même position qu'un élément LINK.

	GridIndexIncrementor grdPos;	
	CoordIncrementor frontXY;		
	CoordIncrementor tailXY;		
	Direction dir;					
	SpeedTimer updateTimer;			

	// POST-BLAST	
	WallType wallType = WallType::REGULAR;	// Produit des intéractions unique
	Modifier modifier;						

	// SETUP DU BLAST
	void Setup_Blast_UI();					
	void Setup_Grid_Limit();									
	void Setup_Position_Incrementors(GrdCoord &startPos);		
	void Setup_Dist_Btw_Links();								
	void Setup_Length();										
	void Setup_Speed(bool quick = false);						
	

	// CHANGEMENT DES PROPRIÉTÉS DE BASES
	void Modify_Max_LengthHor(Distance newLength) { maxlengthHor = newLength; }		
	void Modify_Max_LengthVer(Distance newLength) { maxlengthVer = newLength; }		
	void Modify_SpeedHor(unsigned int spd) { speedHor = spd; }		
	void Modify_SpeedVer(unsigned int spd) { speedVer = spd; }		

	// MISE EN ACTION DU BLAST
	bool Is_Next_Wall_Active();		// Check si le prochain wall que le blast va traversé est alive. Le blast devrait stoppé si c'est le cas
	bool Has_Reached_Limit();		// Vérifie si le blast à atteint la fin de son périple
	bool Blast_Is_On_LinkGrid();	// Vérifie si la "tête" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }		// Reset le temps que ça va prendre pour rencontrer un autre Link
	void Stop_Blast();	

	// POST-BLAST
	int Nb_Of_Links_To_Activate();
	int Nb_Of_Walls_Per_Blast();		// Calcul le nombre de walls à enregistrer après un blast.
public:
	void  Set_WallType(WallType strgth) { wallType = strgth; }	// Set la wallType du blast(surviens généralement lors du transfert d'un wall. la strght sera la même que le wall)
	
	// GET UTILES
	const CoordIncrementor* const Get_Front_XY() { const CoordIncrementor* const copy = &frontXY; return copy; } // Retourne un pointeur constant vers l'adresse, pour pouvoir copier correctement l'axe, qui est en fait un pointeur vers une crd
	Direction Get_Dir() { return dir; }
	Distance Get_Distance_Travelled() { return nbSteps; }
	Modifier Get_Modifier() { return modifier; }
	BlastAmmo& Get_Ammo_Manager() { return ammo; }

	// FONCTIONS PRINCIPALES 

	bool Is_Player_Shooting_Border(Direction dir);			// Si le joueur est collé sur une bordure, et tir dessus, le blast fail
	bool Is_Active() { return active; }	
	void Setup_Blast( GrdCoord &startPos, Direction &blastDir, bool consume = true);
	void Setup_Modifier(Modifier mod);							
	void Change_To_Modifier_Color();							

	void UPD_Blast_Shot();	// le tir du blast...

	// Special: Clear le blast quand on le cancel
	void Cancel() { active = false; }
	void Clear_Blast();
};

// Les objets blasts :D

extern Blast blastP1;

