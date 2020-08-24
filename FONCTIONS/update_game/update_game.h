#pragma once

extern bool gPauseUpdates;

void Update_Game_NOT_60FPS();
void Update_Game();			// Update tout ce qui se passe dans le jeu
void Update_Player_Action();// Traite les inputs du joueur
