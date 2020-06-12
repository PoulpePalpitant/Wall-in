

#include "../bots/botlist.h"
#include "bots_to_spawn.h"
#include "find_next_spawn_crd.h"
#include "valid_spwn_intervals.h"
#include "../grid/spawngrid.h"

#include "spawn_bot.h"

// �a c'�tait pour les spawn block je crois
// Cr�ation des pointeurs pour la liste d'indice de coord de spawns invalide
static BotSpawner* deb = NULL, * fin = NULL, * it = NULL;		//	Pointe vers le d�but et la fin de la liste de Coord
static int cptr = 0;												// Le nombre spawns Coord Indice qu'on a v�rifi� comme �tant invalide
static int cptrInv = 0;												// Le nombre de spawn invalid� (ceux qui sont r�serv� pour un bot uniquement durant ce cycle)
static bool ValidCoord;



static void Spawn_Da_Bot_On_Da_Coord(SpwCrd crd)
{
	// type = Poptypelist() ;p
	botList.Add_Bot(bots_to_spawn::type, crd, gCustomBot.is);	// Tous le m�me TYPE, ils ont
	// SpawnWarning Stuff???

}


static SpwCrd spawn = {};

void Spawn_Bot()
{
	for (int &i = bots_to_spawn::gNumSpawnTOT; i > 0; i--)
	{
		spawn = Find_Spwn_Coord();			//retourne le spawn
		
		if (spawn.spwNum == -1)			// Le spawn � �chou�
			continue;

		Spawn_Da_Bot_On_Da_Coord(spawn);
	}

	ValidSpwnIntervals::Reset_For_Next_Cycle();	// Doit r�-initialiser les listes � chaque cycle de spawn
}


