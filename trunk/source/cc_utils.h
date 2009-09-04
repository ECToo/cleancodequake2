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
// cc_utils.h
// g_utils, CleanCode style
//

#if !defined(__CC_UTILS_H__) || !defined(INCLUDE_GUARDS)
#define __CC_UTILS_H__

void	G_TouchTriggers (CBaseEntity *ent);
void G_SetMovedir (vec3f &angles, vec3f &movedir);
CBaseEntity *GetRandomTeamMember (CBaseEntity *Entity, CBaseEntity *Master);
CBaseEntity *CC_PickTarget (char *targetname);
void G_UseTargets (CBaseEntity *ent, CBaseEntity *activator);
bool KillBox (CBaseEntity *ent);
CBaseEntity *CC_Find (CBaseEntity *from, int fieldofs, char *match);

CBaseEntity *SelectFarthestDeathmatchSpawnPoint ();
CBaseEntity *SelectRandomDeathmatchSpawnPoint ();
float	PlayersRangeFromSpot (CBaseEntity *spot);

inline CBaseEntity *SelectDeathmatchSpawnPoint ()
{
	return (dmFlags.dfSpawnFarthest) ? SelectFarthestDeathmatchSpawnPoint () : SelectRandomDeathmatchSpawnPoint ();
}

class CForEachTeamChainCallback abstract
{
public:
	virtual void Callback (CBaseEntity *Entity) = 0;
};

void ForEachTeamChain (CBaseEntity *Master, CForEachTeamChainCallback *Callback);

#else
FILE_WARNING
#endif