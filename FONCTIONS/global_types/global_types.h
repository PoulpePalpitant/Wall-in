#pragma once

enum Duality
{
	GOOD, BAD
};



// Les modifiers sont une propriété du blast et des links. Le modifier par défaut s'appel REGULAR. Pour activer un nouveau modifier il faut prendre un item modifier, voir items.h

/*
	INTÉRACTIONS AVEC LES MODIFIERS

	- BUFFER : BLAST
	Créer un super link. Tout les walls connectés au super link deviennent un super wall. Les supers walls sont capable d'arrêter 2 bots!

	- BUFFER : LINK
	Tout les tirs régulier ou de types BUFFER sur ce link vont générer un super wall. Un blast BUFFER  sur un link BUFFER va créer un autre wall

	- TELEPORTER : BLAST
	Créer un blast qui permet la téléportation. Quand le blast se termine, le joueur est téléporté au tip? 

	- TELEPORTER: LINK
	Si le joueur le transfère, il sera tp à l'endroit final, si le tp existe encore(pas atteint un blocker)

	- BLOCKER : BLAST
	Le blocker détruit tout les childs connectés au link qu'il rencontre. Il transforme le link rencontré en BLOCKER, sans créer de wall. Si son parent meurt, le BLOCKER sera détruit.
	(Reste à tester) Si le blocker s'arrête sur une bordure, il laisse un 'X' permanant sur la map

	- BLOCKER : LINK
	Le blocker Link est impassable et absorbe tout les autres types de blast. Néanmoins, si un blast de type BLOCKER l'atteint, ça pourrait créer un autre wall, avec un blocker au bout
	SINON, TIRER UN BLOCKER AVEC UN BLOCKER POURRAIT ANNIHILER LA CHAÎNE AU COMPLET, PARENT INCLUT

	- CORRUPTED : BLAST
	Une fois le blast terminé, il créer, ou convertit 1 Link en link CORRUPTED. Si le blast convertit, il n créer pas de wall. Il peut convertir les deux autres types de modifiers
	Tout les nouveaux walls qui seront attaché à ce Link n'auront aucun effet sur les bots, et les bots qui les traversent ne les détruiront pas

	- CORRUPTED : LINK
	Le link corrompue transforme tout les blasts qui le percutent en corrompus. Un BLOCKER blast ignore cet effet et peut efficacement blocker la propagation de la corruption
	un blast CORRUPTED sur un link CORRUPTED créer un wall avec un free link CORRUPTED

	Intéractions weird, mais possibles:
	Avoir un BLOCK link tout  seul sur la bordure et le transformer en CORRUPTED résulterais un link CORRUPTED sans wall, coller sur la bordure. 

*/

enum Modifier
{
	REGULAR, BUFFER, BLOCKER,  CORRUPTER, COLOR_A, COLOR_B, BLIND_COLOR
};

// Le joueur aurait une queue de modifiers qui sont appliqués au prochain blast qu'il tir
// Les intercations d'un modifiers du blast et celui d'un link créer des intéractions uniques




// BOTS QUI CONVERTI TES MURS EN CORRUPTED!