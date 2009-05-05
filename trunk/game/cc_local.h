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
// cc_local.h
// Local header. Contains definitions local to CleanCode files and not necessarily used by the Quake2 base.
//

#include "g_local.h"

void WriteDirection (vec3_t val);
void WritePosition (vec3_t val);
void WriteString (char *val);
void WriteAngle (float val);
void WriteFloat (float val);
void WriteLong (long val);
void WriteShort (short val);
void WriteByte (byte val);
void WriteChar (char val);

enum ECastType : int
{
	// Cast type
	CAST_MULTI,
	CAST_UNI
};
enum ECastFlags : int
{
	CASTFLAG_PVS = 1,
	CASTFLAG_PHS = 2,
	CASTFLAG_RELIABLE = 4
};

void Cast (ECastFlags castFlags, edict_t *Ent);
void Cast (ECastFlags castFlags, vec3_t Origin);
void Cast (ECastType castType, ECastFlags castFlags, vec3_t Origin, edict_t *Ent);

uint32 Com_HashGeneric(const char *name, const int hashSize);

extern CItemList *ItemList;