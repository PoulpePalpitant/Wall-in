#pragma once

#include <iostream>

#include "../UI/txtstyle.h"
#include "../UI/direction.h"
#include "../math/math_stuff.h"






// SPAWN WARNING SERA UNE ANIMATION "D�CLANCHER PAR UN SPAWN" ET NON UN OBJET � L'INT�RIEUR DE BOT







/* 
	M�me si cette class repr�sente plus un �l�ment d'l'UI, je la place ici parce qu'elle est intimement li� au bots.
	� chaque fois qu'un bot va spawner, un warning visuel sera affich�e � l'endroit de son spawn. 
	Ce warning sera sous la forme d'une fl�che clignotante qui change de couleur pour signifi� l'arriv� imminente du bot.
*/

// SIDENOTE: si un bot est diff�rent, �a serait hot d'avoir un warning diff�rent


const char BOT_WRNG_DESIGN[4]{ 'V','>','^','<' };
const static int SPWN_DLAY = 10;		// Le nombre de bot move cycle avant que le bot va commencer � avancer

class SpawnWarning {
private:
	C_D nbWarnCycles;			// Le nombre de cycle de mouvment que le warning de bot bot sera actif
	char warnSym;				// Le symbole qui warn le player que le bot s'en vient!!
	Colors warnColor;			// Sa couleur. Celle-ci va varier selon que le nbWarnCycles se rapproche de 0

	//Cptr Chk_Spwn_Warning_Cycles();	// Update le nombre de warning: Pars de 10, diminue jusqu'� z�ro
	void Upd_Spwn_Warning_Color();	// Update la couleur. Passe du jaune au rouge
	void UI_Dis_Warning();			// Affiche le symbole du warning, et l'efface aussi. C'est en quelque sorte l'animation du spawn warning ici.
public:
	C_D Chk_If_Spawn_Warning()
	{
		if (nbWarnCycles)	// Si le nombre de de warning cycles est plus grand que z�ro
		{
			Upd_Spwn_Warning_Color();
			UI_Dis_Warning();			// On affiche/efface, le spawn warning
			return	nbWarnCycles--;
		}
		else
			return 0;	// Il , n'y aura pas de spawn warning � afficher
	}

	// Constructor
	SpawnWarning(Direction botDir, C_D warnCycles) {
		this->warnSym = BOT_WRNG_DESIGN[botDir];
		this->nbWarnCycles = warnCycles;
		warnColor = Colors::LIGHT_YELLOW;
	}
	SpawnWarning(Direction botDir) {
		this->warnSym = BOT_WRNG_DESIGN[botDir];
		this->nbWarnCycles = SPWN_DLAY;
		warnColor = Colors::LIGHT_YELLOW;
	}
};


