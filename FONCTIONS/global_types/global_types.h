#pragma once



/*
	 Les modifiers sont une propri�t� du blast et des links. Le modifier par d�faut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h
	 *******************************************************************************************************************************************************************************

	INT�RACTIONS AVEC LES MODIFIERS

	TL:DR
	BUFFER double la r�sistance des murs face au bot
	BLOCKER d�truit tout, sauf les autres blockers. Il n'est compatible qu'avec lui-m�me
	FORCEFIELD les wall ENERGIZED ou WEAK passent au travers. Tout les autres, non.
	WEAK ne stop pas les bots. Si ce fait travers� par un bot, ou si traverse un force field, se transforme en REGULAR
	ENERGIZED peut pass� � travers les forcefield � l'infinie. Se d�place super rapidement.

	-----------

	BUFFER BLAST -> REGULAR LINK
	Cr�er un super link. Tout les walls ENFANT connect�s au super link deviennent un super wall. Les supers walls sont capable d'arr�ter 2 bots!

	REGULAR BLAST -> BUFFER LINK
	Tout les tirs r�gulier vont g�n�rer un super wall.  ou de types BUFFER sur ce link 

	BUFFER/REGULAR BLAST -> BLOCKER LINK
	D�truit le blast. Aucun mur ne sera cr��
	
	BLOCKER BLAST -> REGULAR/BUFFER LINK 
	Le blocker d�truit tout les childs connect�s au link qu'il rencontre. Il transforme le link rencontr� en BLOCKER, sans cr�er de wall. 

	BLOCKER BLAST -> BLOCKER LINK
	Cr�er un mur ordinaire, en convertissant auss le link free en blocker 

	BUFFER/BLOCKER BLAST -> BUFFER/BLOCKER LINK
	Si deux modifier identiques se rencontrent, �a cr�er un mur, avec l'addition de cr�er un link free convertit au MODIFIER du blast

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, FORCEFIELD,  ENERGIZER, COLOR_B, BLIND_COLOR
};

// CORRUPUTER, COLOR_B ET BLIND_COLOR SONT INUTILIS�S