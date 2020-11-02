#pragma once

enum Duality
{
	GOOD, BAD
};



// Les modifiers sont une propriété du blast et des links. Le modifier par défaut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h

/*
	INTÉRACTIONS AVEC LES MODIFIERS

	Chaque blast qui impact un link du même type va créer 1 mur de la force même force du type. Le link free au bout possèdera le même modifier

	- BUFFER : BLAST
	Créer un super link. Tout les walls connectés au super link deviennent un super wall. Les supers walls sont capable d'arrêter 2 bots!

	- REGULAR : LINK
	Tout les tirs régulier ou de types BUFFER sur ce link vont générer un super wall. 

	- BLOCKER : BLAST
	Le blocker détruit tout les childs connectés au link qu'il rencontre. Il transforme le link rencontré en BLOCKER, sans créer de wall. 

	- REGULAR : LINK
	Le blocker Link est impassable et absorbe tout les AUTRES types de blast.

	- CORRUPTED : BLAST
	Une fois le blast terminé, il créer, ou convertit 1 Link en link CORRUPTED. Il peut convertir les deux autres types de modifiers?
	Tout les nouveaux walls qui seront attaché à ce Link n'auront aucun effet sur les bots, et les bots qui les traversent ne les détruiront pas

	- CORRUPTED : LINK
	Le link corrompue transforme tout les blasts REGULAR et BUFFER qui le percutent en corrompus. 

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, FORCEFIELD,  COLOR_A, COLOR_B, BLIND_COLOR
};

// Le joueur aurait une queue de modifiers qui sont appliqués au prochain blast qu'il tir
// Les intercations d'un modifiers du blast et celui d'un link créer des intéractions uniques




// BOTS QUI CONVERTI TES MURS EN CORRUPTED!