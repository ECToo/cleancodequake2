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
// cc_grenadelauncher.cpp
// Grenade Launcher
//

#include "cc_local.h"
#include "m_player.h"

CGrenadeLauncher WeaponGrenadeLauncher;

CGrenadeLauncher::CGrenadeLauncher() :
CWeapon("models/weapons/v_launch/tris.md2", 0, 5, 6, 16,
		17, 59, 60, 64)
{
}

bool CGrenadeLauncher::CanFire (CPlayerEntity *ent)
{
	switch (ent->Client.PlayerState.GetGunFrame())
	{
	case 6:
		return true;
	}
	return false;
}

bool CGrenadeLauncher::CanStopFidgetting (CPlayerEntity *ent)
{
	switch (ent->Client.PlayerState.GetGunFrame())
	{
	case 34:
	case 51:
	case 59:
		return true;
	}
	return false;
}

void CGrenadeLauncher::Fire (CPlayerEntity *ent)
{
	vec3f	offset (8, 8, ent->gameEntity->viewheight-8);
	vec3f	forward, right;
	vec3f	start;
	const int	damage = (isQuad) ? 480 : 120;
	const float	radius = 160;

	FireAnimation (ent);

	ent->Client.ViewAngle.ToVectors (&forward, &right, NULL);
	ent->P_ProjectSource (offset, forward, right, start);

	vec3f kickOrigin = forward;
	kickOrigin.Scale (-2);
	Vec3Copy (kickOrigin, ent->Client.kick_origin);
	ent->Client.kick_angles[0] = -1;

	CGrenade::Spawn (ent, start, forward, damage, 600, 2.5f, radius);

	Muzzle (ent, MZ_GRENADE);
	AttackSound (ent);

	ent->PlayerNoiseAt (start, PNOISE_WEAPON);

	if (!dmFlags.dfInfiniteAmmo)
		DepleteAmmo(ent, 1);

	ent->Client.PlayerState.SetGunFrame(ent->Client.PlayerState.GetGunFrame()+1);
}
