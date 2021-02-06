#pragma once

#include "../UI/txtstyle.h"
#include "../UI/direction.h"
#include "../math/math_stuff.h"



/* 
	� chaque fois qu'un bot va spawner, un warning visuel est affich�e � l'endroit de son spawn. 
*/

const char BOT_WRNG_DESIGN[4]{ '^','<','v','>' };
extern const int SPWN_DLAY;		//Le nombre de bot move cycle avant que le bot va commencer � avancer

class SpawnWarning {
private:
	friend class Bot;
	C_D nbWarnCycles;			
	char warnSym;				
	Colors warnColor;			

public:
	void Init_Spawn_Warning(Direction botDir, C_D warnCycles = SPWN_DLAY);						
	void Upd_Spwn_Warning_Color();	
	C_D Show_Spawn_Warning();
};


