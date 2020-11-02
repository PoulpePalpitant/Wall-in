#pragma once

enum Duality
{
	GOOD, BAD
};



// Les modifiers sont une propri�t� du blast et des links. Le modifier par d�faut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h

/*
	INT�RACTIONS AVEC LES MODIFIERS

	Chaque blast qui impact un link du m�me type va cr�er 1 mur de la force m�me force du type. Le link free au bout poss�dera le m�me modifier

	- BUFFER : BLAST
	Cr�er un super link. Tout les walls connect�s au super link deviennent un super wall. Les supers walls sont capable d'arr�ter 2 bots!

	- REGULAR : LINK
	Tout les tirs r�gulier ou de types BUFFER sur ce link vont g�n�rer un super wall. 

	- BLOCKER : BLAST
	Le blocker d�truit tout les childs connect�s au link qu'il rencontre. Il transforme le link rencontr� en BLOCKER, sans cr�er de wall. 

	- REGULAR : LINK
	Le blocker Link est impassable et absorbe tout les AUTRES types de blast.

	- CORRUPTED : BLAST
	Une fois le blast termin�, il cr�er, ou convertit 1 Link en link CORRUPTED. Il peut convertir les deux autres types de modifiers?
	Tout les nouveaux walls qui seront attach� � ce Link n'auront aucun effet sur les bots, et les bots qui les traversent ne les d�truiront pas

	- CORRUPTED : LINK
	Le link corrompue transforme tout les blasts REGULAR et BUFFER qui le percutent en corrompus. 

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, FORCEFIELD,  COLOR_A, COLOR_B, BLIND_COLOR
};

// Le joueur aurait une queue de modifiers qui sont appliqu�s au prochain blast qu'il tir
// Les intercations d'un modifiers du blast et celui d'un link cr�er des int�ractions uniques




// BOTS QUI CONVERTI TES MURS EN CORRUPTED!