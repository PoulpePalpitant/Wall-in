
#include "../UI/console_output/render_list.h"
#include "spawnwarning.h"
#include "bot.h"


const int SPWN_DLAY = 38;		// LEGACY = 14    Le nombre de bot move cycle avant que le bot va commencer à avancer


C_D SpawnWarning::Show_Spawn_Warning()
{
	if (nbWarnCycles)	// Si le nombre de de warning cycles est plus grand que zéro
	{
		Upd_Spwn_Warning_Color();
		return	nbWarnCycles--;
	}
	else
		return 0;	// Il , n'y aura pas de spawn warning à afficher
}

//  Change la couleur du warning pour stresser le joueur
void SpawnWarning::Upd_Spwn_Warning_Color() {

	if (nbWarnCycles == 6)
		warnColor = Colors::LIGHT_YELLOW;	// 6 cycle left
	else
		if (nbWarnCycles == 3)
			warnColor = Colors::LIGHT_RED;	// 3 cycle left
}

void SpawnWarning::Init_Spawn_Warning(Direction botDir, C_D warnCycles)					// Initialise le warning. 
{
	this->warnSym = BOT_WRNG_DESIGN[botDir];
	this->nbWarnCycles = warnCycles;
	warnColor = Colors::WHITE;
}

