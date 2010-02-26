/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
/*
This source file is contained as part of CleanCode Quake2, a project maintained
by Paril, to 'clean up' and make Quake2 an easier source base to read and work with.

You may use any part of this code to help create your own bases and own mods off
this code if you wish. It is under the same license as Quake 2 source (as above),
therefore you are free to have to fun with it. All I ask is you email me so I can
list the mod on my page for CleanCode Quake2 to help get the word around. Thanks.
*/

//
// cc_ctfmenu.cpp
// Self-explanatory
//

#include "cc_local.h"
#include "cc_menu.h"

#if CLEANCTF_ENABLED

class CCTFCreditsMenu : public CMenu
{
public:
	CCTFCreditsMenu			(CPlayerEntity *Player) :
	CMenu(Player)
	{
		Cursor = 2;
	};

	class CCloseLabel : public CMenu_Label
	{
	public:
		CCloseLabel(CCTFCreditsMenu *Menu, sint32 x, sint32 y) :
		CMenu_Label(Menu, x, y)
		{
		};

		bool Select (CPlayerEntity *Player)
		{
			Player->Client.Respawn.MenuState.CloseMenu();
			CTFOpenJoinMenu (Player);

			// Has to be false so we can tell it to switch manually
			return false;
		};
	};


	bool				Open ()
	{
		sint32 x = 0, y = -76; // Top

		CMenu_Label *TopGreen = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
		TopGreen->Enabled = false;
		TopGreen->Align = LA_CENTER;
		TopGreen->Flags = LF_GREEN;
		TopGreen->LabelString = "Quake II\nCleanCode Capture the Flag\n\nProgramming\n\nOriginal Idea\n\nArt\n\n\n\nSounds\n\nTesting";

		y += 32;

		CMenu_Label *BottomWhite = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
		BottomWhite->Enabled = false;
		BottomWhite->Align = LA_CENTER;
		BottomWhite->LabelString = "Paril\n\nDavid 'Zoid' Kirsch\n\nAdrian Carmack\nPaul Steed\nBrian Cozzens\n\nTom Klok\n\nxRDVx";

		x = -93;
		y += (8 * 12);

		CCloseLabel *Back = QNew (TAG_LEVEL) CCloseLabel (this, x, y);
		Back->Enabled = true;
		Back->LabelString = "Back";

		return true;
	};

	void				Close ()
	{
	};

	void				Draw (bool reliable)
	{
		CStatusBar Bar;

		DrawItems(&Bar);
		Bar.SendMsg(Player, reliable);
	};
};

void CTFOpenCreditsMenu(CPlayerEntity *Player)
{
	if (Player->Client.Respawn.MenuState.InMenu)
		return;

	Player->Client.Respawn.MenuState.CurrentMenu = QNew (TAG_LEVEL) CCTFCreditsMenu(Player);
	Player->Client.Respawn.MenuState.OpenMenu ();

	Player->Client.Respawn.MenuState.CurrentMenu->Draw (true);
}

class CCTFMainMenu : public CMenu
{
public:
	CCTFMainMenu			(CPlayerEntity *Player) :
	CMenu(Player)
	{
		Cursor = 3;
	};

	class CJoinGameLabel : public CMenu_Label
	{
	public:
		sint32 team;

		CJoinGameLabel(CCTFMainMenu *Menu, sint32 x, sint32 y, sint32 team) :
		CMenu_Label(Menu, x, y),
		team(team)
		{
		};

		bool Select (CPlayerEntity *Player)
		{
			Player->GetSvFlags() &= ~SVF_NOCLIENT;
			Player->Client.Respawn.CTF.Team = team;
			Player->Client.Respawn.CTF.State = 0;
			Player->CTFAssignSkin(Player->Client.Persistent.UserInfo);

			// assign a ghost if we are in match mode
			if (ctfgame.match == MATCH_GAME)
			{
				if (Player->Client.Respawn.CTF.Ghost)
					ctfgame.Ghosts.erase (Player->Client.Respawn.CTF.Ghost->Code);
				Player->Client.Respawn.CTF.Ghost = NULL;
				Player->CTFAssignGhost();
			}

			Player->PutInServer ();
			// add a teleportation effect
			Player->State.GetEvent() = EV_PLAYER_TELEPORT;
			// hold in place briefly
			Player->Client.PlayerState.GetPMove()->pmFlags = PMF_TIME_TELEPORT;
			Player->Client.PlayerState.GetPMove()->pmTime = 14;
			BroadcastPrintf(PRINT_HIGH, "%s joined the %s team.\n",
				Player->Client.Persistent.Name.c_str(), CTFTeamName(team));

			if (ctfgame.match == MATCH_SETUP)
			{
				Player->PrintToClient	(PRINT_CENTER, 
									"***********************\n"
									"Type \"ready\" in console\n"
									"to ready up.\n"
									"***********************");
			}
			return true;
		};
	};

	class CObserverLabel : public CMenu_Label
	{
	public:
		CObserverLabel(CCTFMainMenu *Menu, sint32 x, sint32 y) :
		CMenu_Label(Menu, x, y)
		{
		};

		bool Select (CPlayerEntity *Player)
		{
			if (Player->Client.Chase.Target)
			{
				Player->Client.Chase.Target = NULL;
				return true;
			}

			for (sint32 i = 1; i <= Game.MaxClients; i++)
			{
				CPlayerEntity *e = entity_cast<CPlayerEntity>((Game.Entities + i)->Entity);
				if (e->GetInUse() && e->GetSolid() != SOLID_NOT)
				{
					Player->Client.Chase.Target = e;
					Player->Client.LayoutFlags |= LF_UPDATECHASE;
					return true;
				}
			}

			Player->PrintToClient(PRINT_CENTER, "No one to chase\n");
			return true;
		};
	};

	class CCreditsLabel : public CMenu_Label
	{
	public:
		CCreditsLabel(CCTFMainMenu *Menu, sint32 x, sint32 y) :
		CMenu_Label(Menu, x, y)
		{
		};

		bool Select (CPlayerEntity *Player)
		{
			Player->Client.Respawn.MenuState.CloseMenu();
			CTFOpenCreditsMenu (Player);

			// Has to be false so we can tell it to switch manually
			return false;
		};
	};

	bool				Open ()
	{
		sint32 num1 = 0, num2 = 0;
		for (sint32 i = 0; i < Game.MaxClients; i++)
		{
			CPlayerEntity *Player = entity_cast<CPlayerEntity>(Game.Entities[i+1].Entity);
			if (!Player->GetInUse())
				continue;
			if (Player->Client.Respawn.CTF.Team == CTF_TEAM1)
				num1++;
			else if (Player->Client.Respawn.CTF.Team == CTF_TEAM2)
				num2++;
		}

		sint32 x = 0, y = 0;

		CMenu_Image *Background = QNew (TAG_LEVEL) CMenu_Image (this, x, y);
		Background->ImageString = "inventory";
		Background->Width = 256;
		Background->Height = 192;
		Background->Enabled = false;

		y = -76; // Top
		CMenu_Label *TopName = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
		TopName->Enabled = false;
		TopName->Align = LA_CENTER;
		TopName->Flags = LF_GREEN;
		TopName->LabelString = "Quake II\nCleanCode Capture the Flag";

		y += (8 * 2);
		CMenu_Label *LevelName = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
		LevelName->Enabled = false;
		LevelName->Align = LA_CENTER;
		LevelName->Flags = LF_GREEN;
		LevelName->LabelString = Level.FullLevelName;

		y += 8;
		CMenu_Label *MatchProgress;
		switch (ctfgame.match)
		{
		case MATCH_NONE :
			break;

		case MATCH_SETUP :
			MatchProgress = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
			MatchProgress->Enabled = false;
			MatchProgress->Align = LA_CENTER;
			MatchProgress->Flags = LF_GREEN;
			MatchProgress->LabelString = "MATCH SETUP IN PROGRESS";
			break;

		case MATCH_PREGAME :
			MatchProgress = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
			MatchProgress->Enabled = false;
			MatchProgress->Align = LA_CENTER;
			MatchProgress->Flags = LF_GREEN;
			MatchProgress->LabelString = "MATCH STARTING";
			break;

		case MATCH_GAME :
			MatchProgress = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
			MatchProgress->Enabled = false;
			MatchProgress->Align = LA_CENTER;
			MatchProgress->Flags = LF_GREEN;
			MatchProgress->LabelString = "MATCH IN PROGRESS";
			break;
		}

		y += 8 * 3;
		x = -98;

		if (ctfgame.match >= MATCH_PREGAME && CvarList[CV_MATCH_LOCK].Integer())
		{
			CMenu_Label *LockedMsg = QNew (TAG_LEVEL) CMenu_Label(this, x, y);
			LockedMsg->Enabled = false;
			LockedMsg->Align = LA_LEFT;
			LockedMsg->LabelString = "MATCH IS LOCKED\n(entry is not permitted)";
		}
		else if (CvarList[CV_CTF_FORCEJOIN].String() && *CvarList[CV_CTF_FORCEJOIN].String())
		{
			if (Q_stricmp(CvarList[CV_CTF_FORCEJOIN].String(), "red") == 0)
			{
				// Only add red
				CJoinGameLabel *JoinRed = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y, CTF_TEAM1);
				JoinRed->Enabled = true;
				JoinRed->Align = LA_LEFT;
				FormatString (JoinRed->LabelString, "Join %s Team    (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Red MATCH" : "Red", num1);
			}
			else if (Q_stricmp(CvarList[CV_CTF_FORCEJOIN].String(), "blue") == 0)
			{
				// Only add blue
				CJoinGameLabel *JoinBlue = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y + 8, CTF_TEAM2);
				JoinBlue->Enabled = true;
				JoinBlue->Align = LA_LEFT;
				FormatString (JoinBlue->LabelString, "Join %s Team    (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Blue MATCH" : "Blue", num2);
			}
			else
			{
				CJoinGameLabel *JoinRed = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y, CTF_TEAM1);
				JoinRed->Enabled = true;
				JoinRed->Align = LA_LEFT;
				FormatString (JoinRed->LabelString, "Join %s Team     (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Red MATCH" : "Red", num1);

				CJoinGameLabel *JoinBlue = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y + 8, CTF_TEAM2);
				JoinBlue->Enabled = true;
				JoinBlue->Align = LA_LEFT;
				FormatString (JoinBlue->LabelString, "Join %s Team   (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Blue MATCH" : "Blue", num2);
			}
		}
		else
		{
			CJoinGameLabel *JoinRed = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y, CTF_TEAM1);
			JoinRed->Enabled = true;
			JoinRed->Align = LA_LEFT;
			FormatString (JoinRed->LabelString, "Join %s Team    (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Red MATCH" : "Red", num1);

			CJoinGameLabel *JoinBlue = QNew (TAG_LEVEL) CJoinGameLabel(this, x, y + 8, CTF_TEAM2);
			JoinBlue->Enabled = true;
			JoinBlue->Align = LA_LEFT;
			FormatString (JoinBlue->LabelString, "Join %s Team   (%d players)", (ctfgame.match >= MATCH_PREGAME) ? "Blue MATCH" : "Blue", num2);
		}

		y += 24;
		CObserverLabel *ChaseCam = QNew (TAG_LEVEL) CObserverLabel(this, x, y);
		ChaseCam->Enabled = true;
		ChaseCam->Align = LA_LEFT;
		ChaseCam->LabelString = ((Player->Client.Chase.Target) ? "Leave Chase Camera" : "Chase Camera");

		y += 8;
		CCreditsLabel *Credits = QNew (TAG_LEVEL) CCreditsLabel(this, x, y);
		Credits->Enabled = true;
		Credits->Align = LA_LEFT;
		Credits->LabelString = "Credits";

		return true;
	};

	void				Close ()
	{
	};

	void				Draw (bool reliable)
	{
		CStatusBar Bar;

		DrawItems(&Bar);
		Bar.SendMsg(Player, reliable);
	};
};

void CTFOpenJoinMenu(CPlayerEntity *Player)
{
	if (Player->Client.Respawn.MenuState.InMenu)
		return;

	Player->Client.Respawn.MenuState.CurrentMenu = QNew (TAG_LEVEL) CCTFMainMenu(Player);
	Player->Client.Respawn.MenuState.OpenMenu ();

	Player->Client.Respawn.MenuState.CurrentMenu->Draw (true);
}
#endif
