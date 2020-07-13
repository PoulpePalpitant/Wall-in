#pragma once

enum Duality
{
	GOOD, BAD
};



// Les modifiers sont une propri�t� du blast et des links. Le modifier par d�faut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h

/*
	INT�RACTIONS AVEC LES MODIFIERS

	- BUFFER : BLAST
	Cr�er un super link. Tout les walls connect�s au super link deviennent un super wall. Les supers walls sont capable d'arr�ter 2 bots!

	- BUFFER : LINK
	Tout les tirs r�gulier ou de types BUFFER sur ce link vont g�n�rer un super wall. Un blast BUFFER  sur un link BUFFER va cr�er un autre wall

	- TELEPORTER : BLAST
	Cr�er un blast qui permet la t�l�portation. Quand le blast se termine, le joueur est t�l�port� au tip? 

	- TELEPORTER: LINK
	Si le joueur le transf�re, il sera tp � l'endroit final, si le tp existe encore(pas atteint un blocker)

	- BLOCKER : BLAST
	Le blocker d�truit tout les childs connect�s au link qu'il rencontre. Il transforme le link rencontr� en BLOCKER, sans cr�er de wall. Si son parent meurt, le BLOCKER sera d�truit.
	(Reste � tester) Si le blocker s'arr�te sur une bordure, il laisse un 'X' permanant sur la map

	- BLOCKER : LINK
	Le blocker Link est impassable et absorbe tout les autres types de blast. N�anmoins, si un blast de type BLOCKER l'atteint, �a pourrait cr�er un autre wall, avec un blocker au bout
	SINON, TIRER UN BLOCKER AVEC UN BLOCKER POURRAIT ANNIHILER LA CHA�NE AU COMPLET, PARENT INCLUT

	- CORRUPTED : BLAST
	Une fois le blast termin�, il cr�er, ou convertit 1 Link en link CORRUPTED. Si le blast convertit, il n cr�er pas de wall. Il peut convertir les deux autres types de modifiers
	Tout les nouveaux walls qui seront attach� � ce Link n'auront aucun effet sur les bots, et les bots qui les traversent ne les d�truiront pas

	- CORRUPTED : LINK
	Le link corrompue transforme tout les blasts qui le percutent en corrompus. Un BLOCKER blast ignore cet effet et peut efficacement blocker la propagation de la corruption
	un blast CORRUPTED sur un link CORRUPTED cr�er un wall avec un free link CORRUPTED

	Int�ractions weird, mais possibles:
	Avoir un BLOCK link tout  seul sur la bordure et le transformer en CORRUPTED r�sulterais un link CORRUPTED sans wall, coller sur la bordure. 

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, COLOR_A, COLOR_B, BLIND_COLOR
};

// Le joueur aurait une queue de modifiers qui sont appliqu�s au prochain blast qu'il tir
// Les intercations d'un modifiers du blast et celui d'un link cr�er des int�ractions uniques




// BOTS QUI CONVERTI TES MURS EN CORRUPTED!