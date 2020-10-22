

#include "../bots/botlist.h"
#include "bots_to_spawn.h"
#include "find_next_spawn_crd.h"
#include "valid_spwn_intervals.h"
#include "../grid/spawngrid.h"
#include "../bots/botmeta.h"
#include "spawn_bot.h"
#include "../time/bot_move_cycle.h"
#include "../events/msg_dispatcher.h"

// �a c'�tait pour les spawn block je crois
// Cr�ation des pointeurs pour la liste d'indice de coord de spawns invalide
static BotSpawner* deb = NULL, * fin = NULL, * it = NULL;		//	Pointe vers le d�but et la fin de la liste de Coord
static int cptr = 0;												// Le nombre spawns Coord Indice qu'on a v�rifi� comme �tant invalide
static int cptrInv = 0;												// Le nombre de spawn invalid� (ceux qui sont r�serv� pour un bot uniquement durant ce cycle)
static bool ValidCoord;



static void Spawn_Da_Bot_On_Da_Coord(SpwCrd crd)
{
	// type = Poptypelist() ;p			// Tous le m�me TYPE, ils ont

	int botIndex = botList.Find_Available_Bot();	// trouve un bot accessible
	if (botIndex == -1)
		throw "There is too many bots, and it's getting buggy over here";
	else
		botList.bot[botIndex].Create_Bot(bots_to_spawn::type, crd, gCustomBot.is);	// spawn da bot!!
	// SpawnWarning Stuff???

}

static void Prevent_Overspawning()	// R�duit le nombre de spawn si on atteindrait le max
{
	if (gAllBotMeta.alive + bots_to_spawn::gNumSpawnTOT >= MAX_NUM_BOTS)				// Limite le nb de spawn au maximum allou�
	{
		int excess = gAllBotMeta.alive + bots_to_spawn::gNumSpawnTOT - MAX_NUM_BOTS;
		bots_to_spawn::gNumSpawnTOT -= excess;
	}
}
static SpwCrd spawn = {};

void Spawn_Bots()
{
	Prevent_Overspawning();	// On d�passe pas la limite de spawn permise

	bots_to_spawn::Set_Randomness();	// Set le taux de random pour ce spawn cycle

	for (int &i = bots_to_spawn::gNumSpawnTOT; i > 0; i--)
	{
		spawn = Find_Spwn_Coord();			//retourne le spawn
		
		if (spawn.spwNum == -1)			// Le spawn � �chou�
			continue;

		Spawn_Da_Bot_On_Da_Coord(spawn);
	}

	ValidSpwnIntervals::Reset_For_Next_Cycle();	// Doit r�-initialiser les listes � chaque cycle de spawn
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par d�faut pour le prochain spawn
}


void Spawn_A_Bot(Direction boxSide, int spwNum)	// Spawn un bot en dehors des cycles de spawn d'un niveau
{
	if (!gMoveBotsThisCycle)
		MsgQueue::Register(START_BOT_MOVE);	// Enable les bots pour qu'ils puissent bouger
	
	bots_to_spawn::Add_Spec(boxSide, spwNum /*= 3 */);	// Ajoute le bot en question
	//bots_to_spawn::Add_Spec(boxSide, --spwNum);	// for testy ;)
	//bots_to_spawn::Add_Spec(boxSide, --spwNum);	// for testy ;)
	//bots_to_spawn::Add_Spec(boxSide, --spwNum);	// for testy ;)
	Spawn_Bots();	// Ensuite on spawn le bot
}

