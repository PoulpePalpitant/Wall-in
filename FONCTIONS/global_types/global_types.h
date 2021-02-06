#pragma once



/*
	 Les modifiers sont une propriété du blast et des links. Le modifier par défaut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h
	 *******************************************************************************************************************************************************************************

	INTÉRACTIONS AVEC LES MODIFIERS

	TL:DR
	BUFFER double la résistance des murs face au bot
	BLOCKER détruit tout, sauf les autres blockers. Il n'est compatible qu'avec lui-même
	FORCEFIELD les wall ENERGIZED ou WEAK passent au travers. Tout les autres, non.
	WEAK ne stop pas les bots. Si ce fait traversé par un bot, ou si traverse un force field, se transforme en REGULAR
	ENERGIZED peut passé à travers les forcefield à l'infinie. Se déplace super rapidement.

	-----------

	BUFFER BLAST -> REGULAR LINK
	Créer un super link. Tout les walls ENFANT connectés au super link deviennent un super wall. Les supers walls sont capable d'arrêter 2 bots!

	REGULAR BLAST -> BUFFER LINK
	Tout les tirs régulier vont générer un super wall.  ou de types BUFFER sur ce link 

	BUFFER/REGULAR BLAST -> BLOCKER LINK
	Détruit le blast. Aucun mur ne sera créé
	
	BLOCKER BLAST -> REGULAR/BUFFER LINK 
	Le blocker détruit tout les childs connectés au link qu'il rencontre. Il transforme le link rencontré en BLOCKER, sans créer de wall. 

	BLOCKER BLAST -> BLOCKER LINK
	Créer un mur ordinaire, en convertissant auss le link free en blocker 

	BUFFER/BLOCKER BLAST -> BUFFER/BLOCKER LINK
	Si deux modifier identiques se rencontrent, ça créer un mur, avec l'addition de créer un link free convertit au MODIFIER du blast

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, FORCEFIELD,  ENERGIZER, COLOR_B, BLIND_COLOR
};

// CORRUPUTER, COLOR_B ET BLIND_COLOR SONT INUTILISÉS