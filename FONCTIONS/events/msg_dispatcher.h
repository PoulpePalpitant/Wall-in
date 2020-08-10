#pragma once

// La liste de tout les messages D'EVENT
/*
	Pour les events du jeu, j'ai décidé de limiter la complexité au maximum afin de pouvoir finir le plus rapidement possible. Il y aurait beaucoup de manière d'intégrer un système de gestion de message et j'ai du mal à trouver rapidement une
	BONNE manière de faire à mon niveau de compréhension. Je crois pas que ce projet est le bon pour tester ça, surtout considérant les besoins limités en matière d'event. Pour le futur, voici desw pistes, en plus des recherches que
	ta mis dans tes favoris su chrome.	/////fuckit, ima try something actually\\\\\

*/






// FUCK LES OBSERVATEURS. 


// Tu peux combiner l,obs avec l'event

// quand il est actif, l'empêche de checker pour s'activer :)

enum MsgType
{
	LITERALLY_NOTHING	// Null
	
	/* Game stuff*/
	, WAITING_TIME
	, PAUSE_GAME
	, UNPAUSE_GAME

	/*Level Stuff*/
	, PLS_INTIALIZE_LVL
	, STAGE_ADVANCE			// Passe au prochain stage dans le niveau
	, LVL_INITIALIZED
	, FINAL_PUSH
	, LVL_ENDED
	, VICTORY
	, DEFEAT

	/* UI stuff */
	, SHOW_HEALTH
	, HIDE_HEALTH
	, SHOW_MOD_QUEUE
	, HIDE_NEXT_QUEUE

	/* grid stuff */
	, GRIDS_RESIZED

	/* Walls and Links stuff*/
	, LINK_ACTIVATED
	, LINK_DEACTIVATED
	, WALL_ACTIVATED
	, WALL_DEACTIVATED

	/* Items */
	, ITEM_PICKUP
	, ITEM_DESTROYED
	, ITEM_SPAWNED
	, SPAWN_SPECIAL_ITEM

	/* Player Stuff*/
	, SPAWN_PLAYER
	, PLAYER_SPAWNED
	, LOCK_PLAYER		// Player ne peut plus rien faire, its cutscene time!
	, FREE_PLAYER		// CUTSCENE TERMINÉ, player peux bouger
	, IS_A_DOUCHE
	, FIRST_HIT		
	, BUMPED_BORDER		// Essayer de bouger en dehors du grid
	, TOUCHED_ENNEMY
	, P1_LOST_HP
	, PLAYER_DEAD

	/* Ennemy Stuff*/
	, ENNEMY_KILLED
	, ENNEMY_SPWN
	, JERRY_DIED
	, SPECIAL_SPAWN
	, STOP_BOT_SPAWNS	// n'update plus les spawn
	, STOP_BOT_MOVE		// n'update plus les mouvements
	, STOP_BOTS			// n'update plus les deux plus haut
	, START_BOT_SPAWNS	// update les spawn
	, START_BOT_MOVE	// update les mouvements
	, START_BOTS		// update les deux plus haut

	/* Blast Stuff*/
	, BLAST_REACHED_BORDER
	, WALL_TRANSFER
	, BLAST_HIT_ITEM
	, BULLETS_DEPLETED
	, ACTIVATE_BLAST	// Empêche le joueur de tirer
	, DEACTIVATE_BLAST	// Empêche le joueur de tirer

	/* Window stuff*/
	, CHANGE_WINSIZE	// Nécessiter de changer la window

	/* Clavier*/
	, PRESSED_ENTER		/* Le joueur à pesé sur enter, pour faire un choix */
	, SELECTED_SOMETHING
	, PRESSED_KEY
	, BLOCK_ALL_INPUTS
	, UNBLOCK_ALL_INPUTS
};


// CONST
const int MSG_QUEUE_SIZE = 1000;	// Maximum de message par cycle. yup, taht many

// GLOBAL
extern MsgType gCurrentMsg;		// Prend un msg qui sera interprété par les event Listeners

class MsgQueue			// Initialisation à un ring buffer
{
	static MsgType queue[MSG_QUEUE_SIZE];	// La liste de tout les messages enregistré pendant une frame
	static int head, tail;				// début, fin, itérateur d'indice du array
	static int total;

	static void Unregister();
public:
	static void Register(MsgType msg);	// Ajoute le message à la liste des message à traiter pour ce cycle
	static void Dispatch_Messages();
};

void Dispatch_To_Lvl();	// Par ici qu'on va updater tout les events du niveau
void Dispatch_To_Global();	// Update tout les autres qui sont pas dans des modules indépendants
