#include "blast_ammo.h"

#include "../events/msg_dispatcher.h"
#include "../lvls/lvl_script.h"
#include "../UI/console_output/render_list.h"
#include "../UI/map.h"
#include "blast_ammo_animator.h"


static int x = 5;	// case � droite de box limit right
static int y = 2;	// case en dessous de box limit up
static std::string eraseNum = "    ";	// pour erase un nombre



/// shoot ou add ne modifie pas le ratio de la bar length
// alors si barlength d�passe son max?
// redraw la bar en vert?
// fait juste changer le counter en cyan
// draw une deuxi�me bar par dessus comme dans les jeux de fighter

bool BlastAmmo::Shoot()
{
	if (Is_Active())
	{
		if (!Ammo_Available())
			return false;
		else
		{
			ammo--;

			//if (!Ammo_Available())
			//	MsgQueue::Register(DISABLE_BLAST);	// D�sactive tout simplement le blast du joueur

			// Signale d'update l'interface
			Dr_Or_Er_Ammo_Count();

			


			return true;
		}
	}
	else
		return true;	// on peut tirer sans restrictions si ammo n'est pas actif
	
}


void BlastAmmo::Set_Ammo(int nbShots) // Setter un nombre d'ammo active automatiquement le limitateur
{	
	ammo = nbShots;

	if (active == false)
	{
		active = true;	// devient automatiquement actif
		MsgQueue::Register(ENABLE_BLAST);	// Cons�quamment, le joueur peut tirer!

		// Le ratio et l'ui est activ� uniquement quand on utilise la m�thode set
		DrawBlastAmmo::Show_Ammo_UI();	// L'interface doit �tre modifi�



	}
}

void BlastAmmo::Set_Ammo_For_Checkpoint()	// Set la limite selon le nombre assign� au checkpoint d'un niveau
{
	if (gCurrentLevel == 1)
		Set_Ammo(LVL1_BLAST_AMMO[gCurrentCheckPoints[gCurrentLevel - 1]]);
	else
		if (gCurrentLevel == 2)
			Set_Ammo(LVL2_BLAST_AMMO[gCurrentCheckPoints[gCurrentLevel - 1]]);

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

	ConsoleRender::Add_String(eraseNum, { map.Get_Box_Limit(RIGHT) + 2 + x,map.Get_Box_Limit(UP) + y + 2 });	// Erase le nombre pr�c�dant

	if (ammo == 0)
		clr = LIGHT_RED;
	else 
		clr = WHITE;

	if(ammo < 9)
		ConsoleRender::Add_String(std::to_string(ammo), { map.Get_Box_Limit(RIGHT) + 4 + x,map.Get_Box_Limit(UP) + y + 2 }, clr,0,erase);
	else
		if (ammo < 99)
			ConsoleRender::Add_String( std::to_string(ammo),{ map.Get_Box_Limit(RIGHT) + 3 + x,map.Get_Box_Limit(UP) + y + 2 }, clr,0, erase);
		else
			ConsoleRender::Add_String(std::to_string(ammo), { map.Get_Box_Limit(RIGHT) + 2 + x,map.Get_Box_Limit(UP) + y + 2 }, clr,0, erase);
}
