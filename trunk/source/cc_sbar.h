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
// This can also be used for like, scoreboards (+ SendMsg)
//

class CStatusBar
{
	char bar[MAX_COMPRINT/2];
	char temp[MAX_COMPRINT/2]; // A temp buffer used for adding stuffs to the bar buffer.

public:
	CStatusBar();
	void Send ();
	void SendMsg (edict_t *ent, bool reliable = true);

	void AddToBarBuffer (char *string);
	void AddVirtualPoint_Y (int y);
	void AddVirtualPoint_X (int x);
	void AddPoint_X (int x, bool inverted);
	void AddPoint_Y (int y, bool inverted);
	void AddString (char *string, bool highBi, bool center);
	void AddStatString (int stat);
	void AddPic (char *pic);
	void AddPicStat (int stat);
	void AddNumStat (int stat, int width);
	void AddIf (int stat);
	void AddEndIf ();
	void AddAmmoNum ();
	void AddHealthNum ();
	void AddArmorNum ();
	void AddClientBlock (int x, int y, int cNum, int score, int ping, int time);
	void AddClientBlock (int x, int y, int cNum, int score, int ping);

	size_t	Length ();
};

void HelpComputer (CPlayerEntity *ent);