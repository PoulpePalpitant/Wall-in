#include "blast_ammo.h"

#include "../events/msg_dispatcher.h"
#include "../lvls/lvl_script.h"
#include "../UI/console_output/render_list.h"
#include "../UI/map.h"
#include "blast_ammo_animator.h"
#include "../player/player.h"
#include "../events/global_events/feedback/ev_ammo_depleted.h"
#include "../events/global_events/feedback/ev_use_emergency_ammo.h"


static int x = 8;	
static int y = 2;	
static std::string eraseNum = "    ";	

void BlastAmmo::Deactivate() {
	active = false;
}

void BlastAmmo::Activate(bool redraw ) {
	active = true;

	if (redraw)
	{
		DrawBlastAmmo::Ev_Dr_Bar_From_Scratch();
		DrawBlastAmmo::Dr_Ammo_Count(this->ammo);
	}
}

bool BlastAmmo::Use_Emergency_ammo()
{
	if (this->emergencyAmmo)
	{
		this->emergencyAmmo--;
		DrawBlastAmmo::Dr_Emergency_Ammo(this->emergencyAmmo);
		Add_Ev_Use_Emergency_Ammo();

		if(!emergencyAmmo)
			Ev_Ammo_Depleted();

		return true;
	}
	else
	{
		Ev_No_Ammo_Msg();
		return false;
	}
}

bool BlastAmmo::Shoot()
{
	if (Is_Active())
	{
		if (!Ammo_Available())
		{
			if (Use_Emergency_ammo())
				return true;
			else
				return false;
		}

		if (--ammo >= 0)
			DrawBlastAmmo::Update_Ammo_Count(); // Signale d'update l'interface
				 
		DrawBlastAmmo::Dr_Bar_Remove();	 // Réduit pt la longueur de la bar
		return true;
	}
	else
		return true;	
	
}

void BlastAmmo::Add_Ammo(int amm)
{
	if (active == false)
		active = true;	
	
	ammo += amm;
	
	if (ammo == 1)
	{
		Cancel_Ev_Ammo_Depleted();
		Stop_Ev_Use_Emergency_Ammo();
	}

	DrawBlastAmmo::Dr_Ammo_Gain();
	DrawBlastAmmo::Update_Ammo_Count();
}

void BlastAmmo::Set_Ammo(int nbShots) // Setter un nombre d'ammo active automatiquement le limitateur
{	
	ammo = nbShots;
	Set_Nb_Emergency_Ammo(2);	// reset le nombre d'emergency ammo à chaque fois

	if (active == false)
	{
		active = true;	
		MsgQueue::Register(ENABLE_BLAST);	

		DrawBlastAmmo::Show_Ammo_UI();	
	}
}

void BlastAmmo::Set_Nb_Emergency_Ammo(int nbShots) {
	emergencyAmmo = nbShots;
	DrawBlastAmmo::Dr_Emergency_Ammo(nbShots);

	if (ammo == 0 && emergencyAmmo == 0)
		Ev_Ammo_Depleted();
}


// UI UI UI UI UI UI UI 
//***********************
void BlastAmmo::Dr_Or_Er_Ammo(bool erase)
{
	ConsoleRender::Add_String("- SHOTS -", { map.Get_Limit(RIGHT) + x,map.Get_Limit(UP) + y }, BRIGHT_WHITE, TXT_SPD_DR);
	Dr_Or_Er_Ammo_Count(erase);
}

void BlastAmmo::Dr_Or_Er_Ammo_Count(bool erase)
{
	Colors clr;
	
	if (ammo == 0)
		clr = LIGHT_RED;
	else 
		clr = WHITE;

	ConsoleRender::Add_String(eraseNum, { map.Get_Limit(RIGHT) + x,map.Get_Limit(UP) + -1 });	// Erase le nombre précédant
	ConsoleRender::Add_String(std::to_string(ammo), { map.Get_Limit(RIGHT) + x ,map.Get_Limit(UP) - 1 }, clr,0,erase);

}
