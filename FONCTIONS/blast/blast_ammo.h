#pragma once
#include "../math/math_stuff.h"

/*
	Blast ammo restreint le nombre de shots que le joueur peut faire. Une limite sera fixé pour chacun des puzzles d'un niveau
*/

class BlastAmmo
{
	bool active = false;		// Si inactif, le joueur peut tirer à l'infinie	
	int ammo;			// Le nombre de shot restant que le joueur peut faire

	// UI
	void Dr_Or_Er_Ammo(bool erase = false);
	void Dr_Or_Er_Ammo_Count(bool erase = false);

public:
	// FONCTIONS PRINCIPALES 
	bool Is_Active() { return active; }	// is it?
	void Deactivate() { active = false; }	// nah
	bool Ammo_Available() { return ammo; }	// Can we shoot?
	bool Shoot();	// Spend un "shot"
	int Get_Nb_Ammo() { return ammo; }	// that amount

	// SET
	void Set_Ammo(int nbShots); 
	void Set_Ammo_For_Checkpoint();	// Set la limite selon le nombre assigné au checkpoint d'un niveau
};
