

#include "../bots/botlist.h"
#include "bots_to_spawn.h"
#include "find_next_spawn_crd.h"
#include "valid_spwn_intervals.h"
#include "../grid/spawngrid.h"

#include "spawn_bot.h"

// Ça c'était pour les spawn block je crois
// Création des pointeurs pour la liste d'indice de coord de spawns invalide
static BotSpawner* deb = NULL, * fin = NULL, * it = NULL;		//	Pointe vers le début et la fin de la liste de Coord
static int cptr = 0;												// Le nombre spawns Coord Indice qu'on a vérifié comme étant invalide
static int cptrInv = 0;												// Le nombre de spawn invalidé (ceux qui sont réservé pour un bot uniquement durant ce cycle)
static bool ValidCoord;



static void Spawn_Da_Bot_On_Da_Coord(SpwCrd crd)
{
	// type = Poptypelist() ;p
	botList.Add_Bot(bots_to_spawn::type, crd, gCustomBot.is);	// Tous le même TYPE, ils ont
	// SpawnWarning Stuff???

}


static SpwCrd spawn = {};

void Spawn_Bot()
{
	for (int &i = bots_to_spawn::gNumSpawnTOT; i > 0; i--)
	{
		spawn = Find_Spwn_Coord();			//retourne le spawn
		
		if (spawn.spwNum == -1)			// Le spawn à échoué
			continue;

		Spawn_Da_Bot_On_Da_Coord(spawn);
	}

	ValidSpwnIntervals::Reset_For_Next_Cycle();	// Doit ré-initialiser les listes à chaque cycle de spawn
}


