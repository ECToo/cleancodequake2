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
// cc_sbar.h
// Contains a class to create statusbars easily, without the need to directly edit a string.
// This can also be used for scoreboards (+ SendMsg)
//

#include "cc_local.h"

CStatusBar::CStatusBar()
{
	bar = QNew (com_levelPool, 0) char[MAX_COMPRINT/2];
	temp = QNew (com_levelPool, 0) char[MAX_COMPRINT/2];
}

CStatusBar::~CStatusBar()
{
	QDelete[] bar;
	QDelete[] temp;
}

size_t CStatusBar::Length ()
{
	return strlen(bar);
}

void CStatusBar::Send ()
{
	ConfigString (CS_STATUSBAR, bar);
}

void CStatusBar::SendMsg (CPlayerEntity *ent, bool reliable)
{
	WriteByte (SVC_LAYOUT);
	WriteString (bar);
	ent->CastTo ((reliable) ? CASTFLAG_RELIABLE : CASTFLAG_UNRELIABLE);
}

void CStatusBar::AddToBarBuffer (char *string)
{
	Q_snprintfz (bar, MAX_COMPRINT/2, "%s%s", bar, temp);
}

void CStatusBar::AddVirtualPoint_Y (int y)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "yv %i ", y);
	AddToBarBuffer (temp);
}

void CStatusBar::AddVirtualPoint_X (int x)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "xv %i ", x);
	AddToBarBuffer (temp);
}

void CStatusBar::AddPoint_X (int x, bool inverted = false)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "x%c %i ", inverted ? 'r' : 'l', x);
	AddToBarBuffer (temp);
}

void CStatusBar::AddPoint_Y (int y, bool inverted = false)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "y%c %i ", inverted ? 'b' : 't', y);
	AddToBarBuffer (temp);
}

void CStatusBar::AddString (char *string, bool highBit = false, bool center = false)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "%sstring%s \"%s\" ", center ? "c" : "", highBit ? "2" : "", string);
	AddToBarBuffer(temp);
}

void CStatusBar::AddStatString (int stat)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "stat_string %i ", stat);
	AddToBarBuffer (temp);
}

void CStatusBar::AddPic (char *pic)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "picn %s ", pic);
	AddToBarBuffer(temp);
}

void CStatusBar::AddPicStat (int stat)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "pic %i ", stat);
	AddToBarBuffer(temp);
}

void CStatusBar::AddNumStat (int stat, int width = 3)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "num %i %i ", width, stat);
	AddToBarBuffer(temp);
}

void CStatusBar::AddIf (int stat)
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "if %i ", stat);
	AddToBarBuffer(temp);
}

void CStatusBar::AddEndIf ()
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "endif ");
	AddToBarBuffer(temp);
}

void CStatusBar::AddAmmoNum ()
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "anum ");
	AddToBarBuffer(temp);
}

void CStatusBar::AddHealthNum ()
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "hnum ");
	AddToBarBuffer(temp);
}

void CStatusBar::AddArmorNum ()
{
	Q_snprintfz (temp, MAX_COMPRINT/2, "rnum ");
	AddToBarBuffer(temp);
}

void CStatusBar::AddClientBlock (int x, int y, int cNum, int score, int ping, int time)
{
	assert (!(cNum >= game.maxclients || cNum < 0));

	Q_snprintfz (temp, MAX_COMPRINT/2, "client %i %i %i %i %i %i ", x, y, cNum, score, ping, time);
	AddToBarBuffer(temp);
}

void CStatusBar::AddClientBlock (int x, int y, int cNum, int score, int ping)
{
	assert (!(cNum >= game.maxclients || cNum < 0));

	Q_snprintfz (temp, MAX_COMPRINT/2, "ctf %i %i %i %i %i %i ", x, y, cNum, score, ping);
	AddToBarBuffer(temp);
}

void CreateDMStatusbar ()
{
	CStatusBar DMBar;

	DMBar.AddPoint_Y (-24, true);

	DMBar.AddVirtualPoint_X (0);
	DMBar.AddHealthNum ();
	DMBar.AddVirtualPoint_X (50);
	DMBar.AddPicStat (STAT_HEALTH_ICON);

	DMBar.AddIf (STAT_AMMO_ICON);
	DMBar.AddVirtualPoint_X (100);
	DMBar.AddAmmoNum ();
	DMBar.AddVirtualPoint_X (150);
	DMBar.AddPicStat (STAT_AMMO_ICON);
	DMBar.AddEndIf ();

	DMBar.AddIf (STAT_ARMOR);
	DMBar.AddVirtualPoint_X (200);
	DMBar.AddArmorNum ();
	DMBar.AddVirtualPoint_X (250);
	DMBar.AddPicStat (STAT_ARMOR_ICON);
	DMBar.AddEndIf ();

	DMBar.AddIf (STAT_SELECTED_ICON);
	DMBar.AddVirtualPoint_X (296);
	DMBar.AddPicStat (STAT_SELECTED_ICON);
	DMBar.AddEndIf ();

	DMBar.AddPoint_Y (-50, true);

	DMBar.AddIf (STAT_PICKUP_ICON);
	DMBar.AddVirtualPoint_X (0);
	DMBar.AddPicStat (STAT_PICKUP_ICON);
	DMBar.AddVirtualPoint_X (26);
	DMBar.AddPoint_Y (-42, true);
	DMBar.AddStatString (STAT_PICKUP_STRING);
	DMBar.AddPoint_Y (-50, true);
	DMBar.AddEndIf ();

	DMBar.AddIf (STAT_TIMER_ICON);
	DMBar.AddVirtualPoint_X (246);
	DMBar.AddNumStat (STAT_TIMER, 2);
	DMBar.AddVirtualPoint_X (296);
	DMBar.AddPicStat (STAT_TIMER_ICON);
	DMBar.AddEndIf ();

	DMBar.AddIf (STAT_HELPICON);
	DMBar.AddVirtualPoint_X (148);
	DMBar.AddPicStat (STAT_HELPICON);
	DMBar.AddEndIf ();

	DMBar.AddPoint_X (-50, true);
	DMBar.AddPoint_Y (2);
	DMBar.AddNumStat (STAT_FRAGS);

	DMBar.AddPoint_Y (-129, true);

	DMBar.AddIf (STAT_TECH);
		DMBar.AddPoint_X (-26, true);
		DMBar.AddPicStat (STAT_TECH);
	DMBar.AddEndIf();

	DMBar.AddIf (STAT_CHASE);
	DMBar.AddVirtualPoint_X (0);
	DMBar.AddPoint_Y (-68, true);
	DMBar.AddString ("Chasing");
	DMBar.AddVirtualPoint_X (64);
	DMBar.AddStatString (STAT_CHASE);
	DMBar.AddEndIf ();

	DMBar.Send();
}

void CreateSPStatusbar ()
{
	CStatusBar SPBar;

	SPBar.AddPoint_Y (-24, true);

	SPBar.AddVirtualPoint_X (0);
	SPBar.AddHealthNum ();
	SPBar.AddVirtualPoint_X (50);
	SPBar.AddPicStat (STAT_HEALTH_ICON);

	SPBar.AddIf (STAT_AMMO_ICON);
	SPBar.AddVirtualPoint_X (100);
	SPBar.AddAmmoNum ();
	SPBar.AddVirtualPoint_X (150);
	SPBar.AddPicStat (STAT_AMMO_ICON);
	SPBar.AddEndIf ();

	SPBar.AddIf (STAT_ARMOR);
	SPBar.AddVirtualPoint_X (200);
	SPBar.AddArmorNum ();
	SPBar.AddVirtualPoint_X (250);
	SPBar.AddPicStat (STAT_ARMOR_ICON);
	SPBar.AddEndIf ();

	SPBar.AddIf (STAT_SELECTED_ICON);
	SPBar.AddVirtualPoint_X (296);
	SPBar.AddPicStat (STAT_SELECTED_ICON);
	SPBar.AddEndIf ();

	SPBar.AddPoint_Y (-50, true);

	SPBar.AddIf (STAT_PICKUP_ICON);
	SPBar.AddVirtualPoint_X (0);
	SPBar.AddPicStat (STAT_PICKUP_ICON);
	SPBar.AddVirtualPoint_X (26);
	SPBar.AddPoint_Y (-42, true);
	SPBar.AddStatString (STAT_PICKUP_STRING);
	SPBar.AddPoint_Y (-50, true);
	SPBar.AddEndIf ();

	SPBar.AddIf (STAT_TIMER_ICON);
	SPBar.AddVirtualPoint_X (246);
	SPBar.AddNumStat (STAT_TIMER, 2);
	SPBar.AddVirtualPoint_X (296);
	SPBar.AddPicStat (STAT_TIMER_ICON);
	SPBar.AddEndIf ();

	SPBar.AddIf (STAT_HELPICON);
	SPBar.AddVirtualPoint_X (148);
	SPBar.AddPicStat (STAT_HELPICON);
	SPBar.AddEndIf ();

	SPBar.Send();
}

/*
==================
HelpComputer

Draw help computer.
==================
*/
void HelpComputer (CPlayerEntity *ent)
{
	CStatusBar Scoreboard;
	static char	*sk = NULL;

	if (sk == NULL)
	{
		switch (skill->Integer())
		{
		case 0:
			sk = "easy";
			break;
		case 1:
			sk = "medium";
			break;
		case 2:
			sk = "hard";
			break;
		default:
			sk = "hard+";
			break;
		}
	}

	Scoreboard.AddVirtualPoint_X (32);
	Scoreboard.AddVirtualPoint_Y (8);
	Scoreboard.AddPic ("help");

	Scoreboard.AddVirtualPoint_X (202);
	Scoreboard.AddVirtualPoint_Y (12);
	Scoreboard.AddString (sk, true);

	Scoreboard.AddVirtualPoint_X (0);

	Scoreboard.AddVirtualPoint_Y (24);
	Scoreboard.AddString (level.level_name, true, true);

	Scoreboard.AddVirtualPoint_Y (54);
	Scoreboard.AddString (game.helpmessage1, true, true);

	Scoreboard.AddVirtualPoint_Y (110);
	Scoreboard.AddString (game.helpmessage2, true, true);

	Scoreboard.AddVirtualPoint_X (50);
	Scoreboard.AddVirtualPoint_Y (164);
	Scoreboard.AddString (" kills     goals    secrets", true);

	Scoreboard.AddVirtualPoint_Y (172);

	char tempBuffer[MAX_INFO_KEY];
	Q_snprintfz (tempBuffer, sizeof(tempBuffer), "%3i/%3i     %i/%i       %i/%i", level.killed_monsters, level.total_monsters, 
		level.found_goals, level.total_goals,
		level.found_secrets, level.total_secrets);

	Scoreboard.AddString (tempBuffer, true);

	Scoreboard.SendMsg (ent, true);
}
