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
// cc_railgun.cpp
// Railgun
//

#include "cc_local.h"
#include "cc_weaponmain.h"
#include "m_player.h"

CRailgun::CRailgun() :
CWeapon(9, 0, "models/weapons/v_rail/tris.md2", 0, 3, 4, 18,
		19, 56, 57, 61, "weapons/rg_hum.wav")
{
}

bool CRailgun::CanFire (CPlayerEntity *Player)
{
	switch (Player->Client.PlayerState.GetGunFrame())
	{
	case 4:
		return true;
	}
	return false;
}

bool CRailgun::CanStopFidgetting (CPlayerEntity *Player)
{
	switch (Player->Client.PlayerState.GetGunFrame())
	{
	case 56:
		return true;
	}
	return false;
}

void CRailgun::Fire (CPlayerEntity *Player)
{
	vec3f		start, forward, right, offset(0, 7,  Player->ViewHeight-8);
	const sint32	damage = (Game.GameMode & GAME_DEATHMATCH) ? // normal damage is too extreme in dm
				CalcQuadVal(100)
				:
				CalcQuadVal(150),
				kick = (Game.GameMode & GAME_DEATHMATCH) ?
				CalcQuadVal(200) 
				:
				CalcQuadVal(250);

	Player->Client.ViewAngle.ToVectors (&forward, &right, NULL);

	Player->Client.KickOrigin = forward * -3;
	Player->Client.KickAngles.X = -3;

	Player->P_ProjectSource (offset, forward, right, start);
	CRailGunShot::Fire (Player, start, forward, damage, kick);

	// send muzzle flash
	Muzzle (Player, MZ_RAILGUN);
	FireAnimation (Player);
	AttackSound (Player);

	Player->Client.PlayerState.GetGunFrame()++;
	Player->PlayerNoiseAt (start, PNOISE_WEAPON);
	DepleteAmmo(Player, 1);
}

#if XATRIX_FEATURES
#include "cc_xatrix_phalanx.h"

void CRailgun::Use (CWeaponItem *Wanted, CPlayerEntity *Player)
{
	if (!Player->Client.Persistent.Inventory.Has(Wanted))
	{
		// Do we have an ion ripper?
		if (Player->Client.Persistent.Inventory.Has(CPhalanx::Weapon.Item))
			CPhalanx::Weapon.Use (Wanted, Player); // Use that.
		else
			Player->PrintToClient (PRINT_HIGH, "Out of item: %s\n", Wanted->Name);
		return;
	}

	// see if we're already using it
	if (Player->Client.Persistent.Weapon == this)
	{
		// Do we have an ion ripper?
		if (Player->Client.Persistent.Inventory.Has(CPhalanx::Weapon.Item))
			CPhalanx::Weapon.Use (Wanted, Player); // Use that.
		return;
	}

	if (Wanted->Ammo && !CvarList[CV_SELECT_EMPTY].Integer() && !(Wanted->Flags & ITEMFLAG_AMMO))
	{
		if (!Player->Client.Persistent.Inventory.Has(Wanted->Ammo->GetIndex()))
		{
			Player->PrintToClient (PRINT_HIGH, "No %s for %s.\n", Wanted->Ammo->Name, Wanted->Name);
			return;
		}

		if (Player->Client.Persistent.Inventory.Has(Wanted->Ammo->GetIndex()) < Wanted->Amount)
		{
			Player->PrintToClient (PRINT_HIGH, "Not enough %s for %s.\n", Wanted->Ammo->Name, Wanted->Name);
			return;
		}
	}

	// change to this weapon when down
	Player->Client.NewWeapon = this;
}
#endif

WEAPON_DEFS (CRailgun);

LINK_ITEM_TO_CLASS (weapon_railgun, CItemEntity);

void CRailgun::CreateItem (CItemList *List)
{
	NItems::Railgun = QNew (com_itemPool, 0) CWeaponItem
		("weapon_railgun", "models/weapons/g_rail/tris.md2", EF_ROTATE, "misc/w_pkup.wav", "w_railgun", "Railgun",
		ITEMFLAG_DROPPABLE|ITEMFLAG_WEAPON|ITEMFLAG_GRABBABLE|ITEMFLAG_STAY_COOP|ITEMFLAG_USABLE, "",
		&Weapon, NItems::Slugs, 1, "#w_railgun.md2");
};

