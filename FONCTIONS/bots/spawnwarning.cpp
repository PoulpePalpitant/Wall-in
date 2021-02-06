
#include "../UI/console_output/render_list.h"
#include "spawnwarning.h"
#include "bot.h"


const int SPWN_DLAY = 38;		

C_D SpawnWarning::Show_Spawn_Warning()
{
	if (nbWarnCycles)	
	{
		Upd_Spwn_Warning_Color();
		return	nbWarnCycles--;
	}
	else
		return 0;
}

//  Change la couleur du warning pour stresser le joueur
void SpawnWarning::Upd_Spwn_Warning_Color() {

	if (nbWarnCycles == 6)
		warnColor = Colors::LIGHT_YELLOW;	
	else
		if (nbWarnCycles == 3)
			warnColor = Colors::LIGHT_RED;	
}

void SpawnWarning::Init_Spawn_Warning(Direction botDir, C_D warnCycles)					
{
	this->warnSym = BOT_WRNG_DESIGN[botDir];
	this->nbWarnCycles = warnCycles;
	warnColor = Colors::WHITE;
}

