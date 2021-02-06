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
 "C'est ici que le projet � commenc� en fait, ce qui veut dire que la fa�on de faire pour animer ce truc n'a pas vraiment �volu�. J'ai essay� de limiter la fr�quence de d�tection de colision
 mais j'pense qu'au final �a l'a over-compliqu� les choses pour rien"

	Le blast �a va �tre la fa�on pour le joueur de d�truire les bots. Quand le joueur blast, il tir un projectile d'une certaine longueur � partir de sa position de d�part. Ce projectile va avanc� jusqu'� ce qu'il 
	atteigne un obstacle. Quand le projectile s'arr�te, il laisse un mur que les bots ne peuvent franchir. Si un bot fonce dedans, le mur est d�truit

*/
struct BlastType						
{
	WallType wallType;	// La force du wall qui sera cr��.
	Modifier mod;		// Le type de Link qui sera cr��	
};							

extern const BlastType DFLT_BLAST;					
extern const Distance DFLT_BLAST_LENGTH_HOR;		
extern const Distance DFLT_BLAST_LENGTH_VER;		
extern const time_t DFLT_BLAST_SPD_VER;				
extern const time_t DFLT_BLAST_SPD_HOR;

// SIDENOTE: Une seule structure de blast sera cr��(par joueurs). Pour chaque tir futur, les valeurs du blast seront tout simplement chang�

class Blast
{
	friend void Change_Blast();	

	protected:
		friend class UI_MoveBlast;	// L'animation du blast 
		friend class WallGrid;		// Acc�s pour enregistr� des nouveaux murs
		friend class AllGrids;
		friend class LinkGrid;		// Pour enregistr� des nouveaux Links


	bool active;			// Le blast est actif ou non. Quand il est actif il est en train de se d�placer
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
	
	// POSITION/D�PLACEMENT
	int grdLimit;					// L'endroit ou le blast va s'arr�ter dans son �pop� lin�aire
	Distance nbSteps;				// Le nombre de d�placement que le blast � fait dans la console (1 case = un d�placement)
	Distance btwLinks;				// LA distance qui s�pare chaque �l�ment du grid de links. Sert de r�f�rence pour la prochaine variable
	C_D movesTillNxtLink;			// Donne le nombre actuel de d�placement � faire avant que le blast se retrouve sur la m�me position qu'un �l�ment LINK.

	GridIndexIncrementor grdPos;	
	CoordIncrementor frontXY;		
	CoordIncrementor tailXY;		
	Direction dir;					
	SpeedTimer updateTimer;			

	// POST-BLAST	
	WallType wallType = WallType::REGULAR;	// Produit des int�ractions unique
	Modifier modifier;						

	// SETUP DU BLAST
	void Setup_Blast_UI();					
	void Setup_Grid_Limit();									
	void Setup_Position_Incrementors(GrdCoord &startPos);		
	void Setup_Dist_Btw_Links();								
	void Setup_Length();										
	void Setup_Speed(bool quick = false);						
	

	// CHANGEMENT DES PROPRI�T�S DE BASES
	void Modify_Max_LengthHor(Distance newLength) { maxlengthHor = newLength; }		
	void Modify_Max_LengthVer(Distance newLength) { maxlengthVer = newLength; }		
	void Modify_SpeedHor(unsigned int spd) { speedHor = spd; }		
	void Modify_SpeedVer(unsigned int spd) { speedVer = spd; }		

	// MISE EN ACTION DU BLAST
	bool Is_Next_Wall_Active();		// Check si le prochain wall que le blast va travers� est alive. Le blast devrait stopp� si c'est le cas
	bool Has_Reached_Limit();		// V�rifie si le blast � atteint la fin de son p�riple
	bool Blast_Is_On_LinkGrid();	// V�rifie si la "t�te" du projectile est sur une case du link Grid
	void Reset_Countdown_Till_Nxt_Link() { movesTillNxtLink = btwLinks; }		// Reset le temps que �a va prendre pour rencontrer un autre Link
	void Stop_Blast();	

	// POST-BLAST
	int Nb_Of_Links_To_Activate();
	int Nb_Of_Walls_Per_Blast();		// Calcul le nombre de walls � enregistrer apr�s un blast.
public:
	void  Set_WallType(WallType strgth) { wallType = strgth; }	// Set la wallType du blast(surviens g�n�ralement lors du transfert d'un wall. la strght sera la m�me que le wall)
	
	// GET UTILES
	const CoordIncrementor* const Get_Front_XY() { const CoordIncrementor* const copy = &frontXY; return copy; } // Retourne un pointeur constant vers l'adresse, pour pouvoir copier correctement l'axe, qui est en fait un pointeur vers une crd
	Direction Get_Dir() { return dir; }
	Distance Get_Distance_Travelled() { return nbSteps; }
	Modifier Get_Modifier() { return modifier; }
	BlastAmmo& Get_Ammo_Manager() { return ammo; }

	// FONCTIONS PRINCIPALES 

	bool Is_Player_Shooting_Border(Direction dir);			// Si le joueur est coll� sur une bordure, et tir dessus, le blast fail
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

