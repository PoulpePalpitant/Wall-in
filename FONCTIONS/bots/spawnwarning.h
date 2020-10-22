#pragma once

#include <iostream>

#include "../UI/txtstyle.h"
#include "../UI/direction.h"
#include "../math/math_stuff.h"






// SPAWN WARNING SERA UNE ANIMATION "D�CLANCHER PAR UN SPAWN" ET NON UN OBJET � L'INT�RIEUR DE BOT


// Sera diff�rent selon le type de bot




/* 
	M�me si cette class repr�sente plus un �l�ment d'l'UI, je la place ici parce qu'elle est intimement li� au bots.
	� chaque fois qu'un bot va spawner, un warning visuel sera affich�e � l'endroit de son spawn. 
	Ce warning sera sous la forme d'une fl�che clignotante qui change de couleur pour signifi� l'arriv� imminente du bot.
*/

// SIDENOTE: si un bot est diff�rent, �a serait hot d'avoir un warning diff�rent


const char BOT_WRNG_DESIGN[4]{ '^','<','v','>' };
const static int SPWN_DLAY = 14;		// Le nombre de bot move cycle avant que le bot va commencer � avancer

class SpawnWarning {
private:
	friend class Bot;
	C_D nbWarnCycles;			// Le nombre de cycle de mouvment que le warning de bot bot sera actif
	char warnSym;				// Le symbole qui warn le player que le bot s'en vient!!
	Colors warnColor;			// Sa couleur. Celle-ci va varier selon que le nbWarnCycles se rapproche de 0

	//Cptr Chk_Spwn_Warning_Cycles();	// Update le nombre de warning: Pars de 10, diminue jusqu'� z�ro
public:
	void Init_Spawn_Warning(Direction botDir, C_D warnCycles = SPWN_DLAY);						// to figure out
	void Upd_Spwn_Warning_Color();	// Update la couleur. Passe du jaune au rouge
	C_D Show_Spawn_Warning();
};


