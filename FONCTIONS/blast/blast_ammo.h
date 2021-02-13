#pragma once
#include "../math/math_stuff.h"

/*
	Blast ammo restreint le nombre de shots que le joueur peut faire. Une limite sera fixé pour chacun des puzzles d'un niveau
*/

class BlastAmmo
{
	bool active = false;		// Si inactif, le joueur peut tirer à l'infinie	
	int ammo;			
	int emergencyAmmo;

	// UI
	void Dr_Or_Er_Ammo(bool erase = false);
	void Dr_Or_Er_Ammo_Count(bool erase = false);

public:
	// FONCTIONS PRINCIPALES 
	bool Is_Active() { return active; }	
	void Deactivate();	
	void Activate(bool redraw = 1);
	bool Ammo_Available() { return ammo; }	
	bool Shoot();	
	int Get_Nb_Ammo() { return ammo; }
	int Get_Nb_Emergency_Ammo() { return emergencyAmmo; }
	void Add_Ammo(int amm = 1);
	bool Use_Emergency_ammo();		// Si le joueur ne possède plus d'ammo, il peut tirer encore 2 fois 

	// SET
	void Set_Ammo(int nbShots); 
	void Set_Nb_Emergency_Ammo(int nbShots);

};
