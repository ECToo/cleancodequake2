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
// cc_gameapi.h
// Contains overloads and other neat things
//

#if !defined(__CC_GAMEAPI_H__) || !defined(INCLUDE_GUARDS)
#define __CC_GAMEAPI_H__

void Cast (ECastFlags castFlags, edict_t *Ent);
void Cast (ECastFlags castFlags, vec3_t Origin);
void Cast (ECastType castType, ECastFlags castFlags, vec3_t Origin, edict_t *Ent);

// vec3f overloads
void Cast (ECastFlags castFlags, CBaseEntity *Ent);
void Cast (ECastFlags castFlags, vec3f *Origin);
void Cast (ECastType castType, ECastFlags castFlags, vec3f *Origin, CBaseEntity *Ent);

void SetModel (edict_t *ent, char *model);

int PointContents (vec3_t start);
int PointContents (vec3f &start);

int BoxEdicts (vec3_t mins, vec3_t maxs, edict_t **list, int maxCount, bool triggers);
int BoxEdicts (vec3f &mins, vec3f &maxs, edict_t **list, int maxCount, bool triggers);

void ConfigString (int configStringIndex, char *configStringValue, CPlayerEntity *Audience = NULL);
void GameError (char *fmt, ...);

_CC_DISABLE_DEPRECATION
// Hearable false = PVS, otherwise PHS
inline bool InArea (bool Hearable, vec3_t p1, vec3_t p2)
{
	if (Hearable)
		return (gi.inPHS (p1, p2) == 1);
	return (gi.inPVS (p1, p2) == 1);
}

inline bool InArea (bool Hearable, vec3f &p1, vec3f &p2)
{
	if (Hearable)
		return (gi.inPHS (p1, p2) == 1);
	return (gi.inPVS (p1, p2) == 1);
}

inline bool InHearableArea (vec3_t p1, vec3_t p2) { return InArea (true, p1, p2); }
inline bool InHearableArea (vec3f &p1, vec3f &p2) { return InArea (true, p1, p2); }
inline bool InVisibleArea (vec3_t p1, vec3_t p2) { return InArea (false, p1, p2); }
inline bool InVisibleArea (vec3f &p1, vec3f &p2) { return InArea (false, p1, p2); }

_CC_ENABLE_DEPRECATION

#else
FILE_WARNING
#endif