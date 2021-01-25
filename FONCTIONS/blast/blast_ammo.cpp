#include "blast_ammo.h"

#include "../events/msg_dispatcher.h"
#include "../lvls/lvl_script.h"
#include "../UI/console_output/render_list.h"
#include "../UI/map.h"
#include "blast_ammo_animator.h"
#include "../player/player.h"
#include "../events/global_events/feedback/ev_ammo_depleted.h"
#include "../events/global_events/feedback/ev_drain_health.h"


static int x = 8;	// case à droite de box limit right
static int y = 2;	// case en dessous de box limit up
static std::string eraseNum = "    ";	// pour erase un nombre


/// shoot ou add ne modifie pas le ratioBarPerAmmo de la bar length
// alors si barlength dépasse son max?
// redraw la bar en vert?
// fait juste changer le counter en cyan
// draw une deuxième bar par dessus comme dans les jeux de fighter

void BlastAmmo::Deactivate() {
	active = false;
	DrawBlastAmmo::Dr_Or_Er_Bar(DrawBlastAmmo::MAX_BAR_SIZE, WHITE,true);
	DrawBlastAmmo::Er_Ammo_Count();
	Cancel_Ev_Ammo_Depleted();	// efface ammo depleted si c'est le cas

}

void BlastAmmo::Activate() {
	active = true;
	//DrawBlastAmmo::Show_Ammo_UI();	// L'interface doit être modifié
	DrawBlastAmmo::Ev_Dr_Bar_From_Scratch();
	DrawBlastAmmo::Dr_Ammo_Count(this->ammo);
}

bool BlastAmmo::Drain_Health_For_Shot()
{
	if (P1.Get_HP() > 1)
	{
		P1.Player_Lose_HP();
		Add_Ev_Drain_Health();
		return true;
	}
	else
	{
		Ev_Hp_Drain_Msg();
		return false;
	}
	// ev drain health
}

bool BlastAmmo::Shoot()
{
	if (Is_Active())
	{
		if (!Ammo_Available())
			return Drain_Health_For_Shot();

		if (--ammo == 0)
			Ev_Ammo_Depleted();	 // Empty!
		else
			DrawBlastAmmo::Dr_Ammo_Remove();// Signale d'update l'interface
				 
		DrawBlastAmmo::Dr_Bar_Remove();	 // Réduit pt la longueur de la bar
		return true;
	}
	else
		return true;	// on peut tirer sans restrictions si ammo n'est pas actif
	
}

void BlastAmmo::Add_Ammo(int amm)
{
	if (active == false)
		active = true;	// devient automatiquement actif
	
	ammo += amm;
	//DrawBlastAmmo::Show_Ammo_UI();	// L'interface doit être modifié, mais différement, tu fera une animation plus tard
}

void BlastAmmo::Set_Ammo(int nbShots) // Setter un nombre d'ammo active automatiquement le limitateur
{	
	ammo = nbShots;

	if (active == false)
	{
		active = true;	// devient automatiquement actif
		MsgQueue::Register(ENABLE_BLAST);	// Conséquamment, le joueur peut tirer!

		// Le ratioBarPerAmmo et l'ui est activé uniquement quand on utilise la méthode set
		DrawBlastAmmo::Show_Ammo_UI();	// L'interface doit être modifié

		if(!nbShots)
			Ev_Ammo_Depleted();	 // Pas de ammo
	}
}



// UI UI UI UI UI UI UI 
//***********************
void BlastAmmo::Dr_Or_Er_Ammo(bool erase)
{
	ConsoleRender::Add_String("- SHOTS -", { map.Get_Box_Limit(RIGHT) + x,map.Get_Box_Limit(UP) + y }, BRIGHT_WHITE, TXT_SPD_DR);
	Dr_Or_Er_Ammo_Count(erase);
}

void BlastAmmo::Dr_Or_Er_Ammo_Count(bool erase)
{
	Colors clr;
	
	if (ammo == 0)
		clr = LIGHT_RED;
	else 
		clr = WHITE;

	ConsoleRender::Add_String(eraseNum, { map.Get_Box_Limit(RIGHT) + x,map.Get_Box_Limit(UP) + -1 });	// Erase le nombre précédant
	ConsoleRender::Add_String(std::to_string(ammo), { map.Get_Box_Limit(RIGHT) + x ,map.Get_Box_Limit(UP) - 1 }, clr,0,erase);

}
