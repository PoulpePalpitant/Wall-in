//
//#include "ev_dr_ammo_UI.h"
//
//#include "../../../blast/blast_ammo_animator.h"
//#include "../../../UI/map.h"
//#include "../../../blast/blast.h"
//#include "../../../UI/console_output/render_list.h"
//#include "../../events.h"
//#include "../../../UI/console_output/draw_queue.h"
//
//namespace DrawBlastAmmo {
//
//	static Event ev_DrAmmoAdd(Ev_Dr_Ammo_Add);
//	static Event ev_DrAmmoRemove(Ev_Dr_Ammo_Remove);
//
//	DrawerQueue Q_ev_AddAmmo(10, 9);
//	DrawerQueue Q_ev_RemoveAmmo(10, 9);
//
//	void Ev_Dr_Ammo_Add()		// Quand il y a un ajout d'ammo
//	{
//		static unsigned char line = 179;
//		static unsigned char tear = 250;
//		static Coord crd;
//		static int x;
//
//		if (!ev_DrAmmoAdd.Is_Active())
//		{
//			ev_DrAmmoAdd.Activate();
//			ev_DrAmmoAdd.Start(0);	// On ne tick pas ce timer
//		}
//		else
//		{
//			for (int i = 0; i < Q_ev_AddAmmo.Get_Total(); i++)
//			{
//				while (Q_ev_AddAmmo.queue[i].timer.Tick())
//				{
//
//					crd = Q_ev_AddAmmo.queue[i].XY;
//					x = crd.x;				// ne changera pas
//
//					switch (Q_ev_AddAmmo.queue[i].currStep)
//					{
//					case 1:
//						ConsoleRender::Add_Char(crd, line);
//						Q_ev_AddAmmo.Step(i, 100000);
//						break;
//					case 2:
//						ConsoleRender::Add_Char({ x,crd.y - 1 }, line);	//																 
//						ConsoleRender::Add_Char({ x,crd.y + 1 }, line);	//																 
//						Q_ev_AddAmmo.Step(i, 80000);
//						break;
//
//					case 3:
//						ConsoleRender::Add_Char(crd, tear);			// Modifie le milieu								    			 
//						Q_ev_AddAmmo.Step(i, 40000);
//						break;
//
//					case 4:
//						ConsoleRender::Add_Char({ x,crd.y - 1 }, TXT_CONST.SPACE);		// efface										
//						ConsoleRender::Add_Char({ x,crd.y + 1 }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ x,crd.y - 2 }, line);	// draw										
//						ConsoleRender::Add_Char({ x,crd.y + 2 }, line);
//						ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// Modifie le milieu
//						Q_ev_AddAmmo.Step(i, 25000);
//						break;
//
//					case 5:
//						ConsoleRender::Add_Char({ x,crd.y - 2 }, TXT_CONST.SPACE);	// erase																							
//						ConsoleRender::Add_Char({ x,crd.y + 2 }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ x,crd.y - 3 }, line, GRAY); // draw
//						ConsoleRender::Add_Char({ x,crd.y + 3 }, line, GRAY);
//						Q_ev_AddAmmo.Step(i, 15000);
//						break;
//
//					case 6:
//						ConsoleRender::Add_Char({ x,crd.y - 3 }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ x,crd.y + 3 }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ x,crd.y - 4 }, tear, GRAY);
//						ConsoleRender::Add_Char({ x,crd.y + 4 }, tear, GRAY);
//						Q_ev_AddAmmo.Step(i, 10000);
//						break;
//
//					case 7:
//						ConsoleRender::Add_Char({ x,crd.y - 4 }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ x,crd.y + 4 }, TXT_CONST.SPACE);
//						Q_ev_AddAmmo.Step(i);
//						Q_ev_AddAmmo.Remove(i);
//						break;
//					}
//				}
//			}
//
//			if (!Q_ev_AddAmmo.Get_Total())
//				ev_DrAmmoAdd.Cancel();
//
//		}
//	}
//
//	void Ev_Dr_Ammo_Remove()	// Quand un ammo est utilisé
//	{
//		static Coord left;
//		static Coord right;
//		static Coord start;
//		static unsigned char botLine = 196;
//		static unsigned char tear = 250;
//		static unsigned char end = '.';
//
//
//		if (!ev_DrAmmoRemove.Is_Active())
//		{
//			ev_DrAmmoRemove.Activate();
//			ev_DrAmmoRemove.Start(0);	// On ne tick pas ce timer
//		}
//		else
//		{
//			for (int i = 0; i < Q_ev_RemoveAmmo.Get_Total(); i++)
//			{
//				while (Q_ev_RemoveAmmo.queue[i].timer.Tick())
//				{
//					start = right = left = Q_ev_RemoveAmmo.queue[i].XY;
//
//					switch (Q_ev_RemoveAmmo.queue[i].currStep)
//					{
//					case 1:
//						ConsoleRender::Add_Char(start, botLine);		//	_
//						Q_ev_RemoveAmmo.Step(i, 100000);
//						break;
//					case 2:
//						left.x -= 2;		ConsoleRender::Add_Char(left, botLine);
//						right.x += 2;		ConsoleRender::Add_Char(right, botLine);	// _ _ _
//						Q_ev_RemoveAmmo.Step(i, 60000);
//						break;
//
//					case 3:
//						ConsoleRender::Add_Char(start, tear);			// Modifie le milieu
//						left.x -= 3;		ConsoleRender::Add_Char(left, botLine);
//						right.x += 3;		ConsoleRender::Add_Char(right, botLine);		//	__ . __						    			 
//						Q_ev_RemoveAmmo.Step(i, 50000);
//						break;
//
//					case 4:
//						ConsoleRender::Add_Char({ start.x - 3, start.y }, TXT_CONST.SPACE);		//  ___  .  ___ 
//						ConsoleRender::Add_Char({ start.x + 3, start.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ start.x - 2, start.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ start.x + 2, start.y }, TXT_CONST.SPACE);
//						left.x -= 4;		ConsoleRender::Add_Char(left, botLine, WHITE);
//						right.x += 4;		ConsoleRender::Add_Char(right, botLine, WHITE);
//						left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);
//						right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
//						left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);
//						right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
//						Q_ev_RemoveAmmo.Step(i, 40000);
//						break;
//
//					case 5:
//						ConsoleRender::Add_Char(start, TXT_CONST.SPACE);
//						left.x -= 6;
//						right.x += 6;
//						ConsoleRender::Add_Char({ left.x + 1,left.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ right.x - 1, right.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ left.x + 2,left.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ right.x - 2, right.y }, TXT_CONST.SPACE);
//						left.x--;		ConsoleRender::Add_Char(left, botLine, GRAY);
//						right.x++;		ConsoleRender::Add_Char(right, botLine, GRAY);
//						Q_ev_RemoveAmmo.Step(i, 15000);
//						break;
//
//					case 6:
//						left.x -= 6;right.x += 6; 	// .             .
//						ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char(right, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ left.x + 3,left.y }, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char({ right.x - 3, right.y }, TXT_CONST.SPACE);
//						left.x--;	right.x++;
//						ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char(right, TXT_CONST.SPACE);
//						left.x--;		right.x++;
//						ConsoleRender::Add_Char(left, tear, GRAY);
//						ConsoleRender::Add_Char(right, tear, GRAY);
//						Q_ev_RemoveAmmo.Step(i, 10000);
//						break;
//
//					case 7:
//						left.x -= 8;right.x += 8;
//						ConsoleRender::Add_Char(left, TXT_CONST.SPACE);
//						ConsoleRender::Add_Char(right, TXT_CONST.SPACE);
//
//						Q_ev_RemoveAmmo.Step(i);
//						Q_ev_RemoveAmmo.Remove(i);
//						break;
//					}
//				}
//			}
//
//			if (!Q_ev_RemoveAmmo.Get_Total())
//				ev_DrAmmoRemove.Cancel();
//		}
//	}
//
//	void Add_Ev_Dr_Ammo_Add()	// Ajoute un élément dans la drawerqueue de cet event
//	{
//		Q_ev_AddAmmo.Add(Get_Ori());
//		Ev_Dr_Ammo_Add();	// trigger l'event si il n'était pas déjà actif
//	}
//	void Add_Ev_Dr_Ammo_Remove()	// Ajoute un élément dans la drawerqueue de cet event
//	{
//		Q_ev_RemoveAmmo.Add(Get_Ori());	// Add élément dans la queue
//		Ev_Dr_Ammo_Remove();	// trigger l'event si il n'était pas déjà actif
//	}
//
//
//}