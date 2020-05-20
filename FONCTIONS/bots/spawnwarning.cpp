
#include "spawnwarning.h"




//// Sert � updater on est au combienti�me cycle de warning du bot
//Cptr SpawnWarning::Chk_Spwn_Warning_Cycles()
//{
//	if (!nbWarnCycles)
//		return nbWarnCycles;		// le warning est d�j� a 0. �a veut dire que le bot est d�j� spawn�, plus besoin de warning
//	else
//		return nbWarnCycles--;		// D�cr�mente le cycle de warning
//}

//  Change la couleur du warning pour stresser le joueur
void SpawnWarning::Upd_Spwn_Warning_Color() {

	if (nbWarnCycles == 6)
		warnColor = Colors::LIGHT_YELLOW;	// 6 cycle left
	else
		if (nbWarnCycles == 3)
			warnColor = Colors::LIGHT_RED;	// 3 cycle left
}

// Affiche le warning que le bot s'en vient ( clignotement, alterne entre effacement et symbole : >, ' ', >, ' ' 
void SpawnWarning::UI_Dis_Warning() {
	if (nbWarnCycles % 2 == 0)
		std::cout << warnSym;
	else
		std::cout << TXT_CONST.SPACE;	// Efface le symbole du warning pr�c�dent
}