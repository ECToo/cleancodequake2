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
// cc_weaponmain.cpp
// Main system/class for the weapons
//

#include "cc_local.h"
#include "m_player.h"

CWeapon::CWeapon(char *model, int ActivationStart, int ActivationEnd, int FireStart, int FireEnd,
				 int IdleStart, int IdleEnd, int DeactStart, int DeactEnd, char *WeaponSound) :
ActivationStart(ActivationStart),
ActivationEnd(ActivationEnd),
FireStart(FireStart),
FireEnd(FireEnd),
IdleStart(IdleStart),
IdleEnd(IdleEnd),
DeactStart(DeactStart),
DeactEnd(DeactEnd),
WeaponSound(WeaponSound)
{
	WeaponModelString = model;

	ActivationNumFrames = (ActivationEnd - ActivationStart);
	FireNumFrames = (FireEnd - FireStart);
	IdleNumFrames = (IdleEnd - IdleStart);
	DeactNumFrames = (DeactEnd - DeactStart);
};

void CWeapon::InitWeapon (CPlayerEntity *Player)
{
	Player->Client.PlayerState.SetGunFrame (ActivationStart);
	Player->Client.PlayerState.SetGunIndex (WeaponModelIndex);
	Player->Client.weaponstate = WS_ACTIVATING;
}

void CWeapon::WeaponGeneric (CPlayerEntity *Player)
{
	// Idea from Brazen source
	int newFrame = -1, newState = -1;

	switch (Player->Client.weaponstate)
	{
	case WS_ACTIVATING:
		if (Player->Client.PlayerState.GetGunFrame() == ActivationEnd)
		{
			newFrame = IdleStart;
			newState = WS_IDLE;
		}
		break;
	case WS_IDLE:
		if (Player->Client.NewWeapon && Player->Client.NewWeapon != this)
		{
			// We want to go away!
			newState = WS_DEACTIVATING;
			newFrame = DeactStart;
		}
		else if ((Player->Client.buttons|Player->Client.latched_buttons) & BUTTON_ATTACK)
		{
			Player->Client.latched_buttons &= ~BUTTON_ATTACK;

			// This here is ugly, but necessary so that machinegun/chaingun/hyperblaster
			// get the right acceptance on first-frame-firing
			Player->Client.buttons |= BUTTON_ATTACK;

			// We want to attack!
			// First call, check AttemptToFire
			if (AttemptToFire(Player))
			{
				// Got here, we can fire!
				Player->Client.PlayerState.SetGunFrame(FireStart);
				Player->Client.weaponstate = WS_FIRING;

				// We need to check against us right away for first-frame firing
				WeaponGeneric(Player);
				return;
			}
			else
			{
				OutOfAmmo(Player);
				NoAmmoWeaponChange (Player);
			}
		}

		// Either we are still idle or a failed fire.
		if (newState == -1)
		{
			if (Player->Client.PlayerState.GetGunFrame() == IdleEnd)
				newFrame = IdleStart;
			else
			{
				if (CanStopFidgetting(Player) && (rand()&15))
					newFrame = Player->Client.PlayerState.GetGunFrame();
			}
		}
		break;
	case WS_FIRING:
		// Check if this is a firing frame.
		if (CanFire(Player))
		{
			Fire(Player);

			// Now, this call above CAN change the underlying frame and state.
			// We need this block to make sure we are still doing what we are supposed to.
			newState = Player->Client.weaponstate;
			newFrame = Player->Client.PlayerState.GetGunFrame();
		}

		// Only do this if we haven't been explicitely set a newFrame
		// because we might want to keep firing beyond this point
		if (newFrame == -1 && Player->Client.PlayerState.GetGunFrame() > FireEnd)
		{
			newFrame = IdleStart+1;
			newState = WS_IDLE;
		}
		break;
	case WS_DEACTIVATING:
		if (Player->Client.PlayerState.GetGunFrame() == DeactEnd)
		{
			// Change weapon
			ChangeWeapon (Player);
			return;
		}
		break;
	}

	if (newFrame != -1)
		Player->Client.PlayerState.SetGunFrame(newFrame);
	if (newState != -1)
		Player->Client.weaponstate = newState;

	if (newFrame == -1 && newState == -1)
		Player->Client.PlayerState.SetGunFrame (Player->Client.PlayerState.GetGunFrame() + 1);
}

void CWeapon::ChangeWeapon (CPlayerEntity *Player)
{
	Player->Client.pers.LastWeapon = Player->Client.pers.Weapon;
	Player->Client.pers.Weapon = Player->Client.NewWeapon;
	Player->Client.NewWeapon = NULL;
	Player->Client.machinegun_shots = 0;

	// set visible model
	if (Player->Client.pers.Weapon && Player->State.GetModelIndex() == 255)
		Player->State.SetSkinNum ((Player->gameEntity - g_edicts - 1) | ((Player->Client.pers.Weapon->vwepIndex & 0xff) << 8));

	if (!Player->Client.pers.Weapon)
	{	// dead
		Player->Client.PlayerState.SetGunIndex(0);
		if (!Player->Client.grenade_thrown && !Player->Client.grenade_blew_up && Player->Client.grenade_time >= level.time) // We had a grenade cocked
		{
			WeaponGrenades.FireGrenade(Player, false);
			Player->Client.grenade_time = 0;
		}
		return;
	}

	Player->Client.pers.Weapon->InitWeapon(Player);

	Player->Client.anim_priority = ANIM_PAIN;
	if (Player->Client.PlayerState.GetPMove()->pmFlags & PMF_DUCKED)
	{
		Player->State.SetFrame (FRAME_crpain1);
		Player->Client.anim_end = FRAME_crpain4;
	}
	else
	{
		Player->State.SetFrame (FRAME_pain301);
		Player->Client.anim_end = FRAME_pain304;
	}
}

void CWeapon::DepleteAmmo (CPlayerEntity *Player, int Amount = 1)
{
	if (this->WeaponItem)
	{
		CAmmo *Ammo = this->WeaponItem->Ammo;

		if (Ammo)
			Player->Client.pers.Inventory.Remove (Ammo, Amount);
	}
	else if (this->Item && (this->Item->Flags & ITEMFLAG_AMMO))
		Player->Client.pers.Inventory.Remove (this->Item, Amount);
}

bool CWeapon::AttemptToFire (CPlayerEntity *Player)
{
	int numAmmo = 0;
	CAmmo *Ammo;
	int quantity = 0;

	if (this->Item && (this->Item->Flags & ITEMFLAG_AMMO))
	{
		numAmmo = Player->Client.pers.Inventory.Has(this->Item);
		Ammo = dynamic_cast<CAmmo*>(this->Item);
		quantity = Ammo->Amount;
	}
	// Revision: Always going to be true here.
	else
	{
		if (this->WeaponItem->Ammo)
		{
			Ammo = this->WeaponItem->Ammo;
			quantity = this->WeaponItem->Quantity;
			if (Ammo)
				numAmmo = Player->Client.pers.Inventory.Has(Ammo);
		}
		else
			return true;
	}

	if (numAmmo < quantity)
		return false;
	else
		return true;
}

void CWeapon::OutOfAmmo (CPlayerEntity *Player)
{
	// Doesn't affect pain anymore!
	if (level.time >= Player->gameEntity->damage_debounce_time)
	{
		PlaySoundFrom(Player->gameEntity, CHAN_AUTO, SoundIndex("weapons/noammo.wav"));
		Player->gameEntity->damage_debounce_time = level.time + 1;
	}
}

// Routines
inline void P_ProjectSource (CPlayerEntity *Player, vec3_t distance, vec3_t forward, vec3_t right, vec3_t result)
{
	vec3_t	_distance, point;

	Player->State.GetOrigin(point);
	Vec3Copy (distance, _distance);
	if (Player->Client.pers.hand == LEFT_HANDED)
		_distance[1] *= -1;
	else if (Player->Client.pers.hand == CENTER_HANDED)
		_distance[1] = 0;
	G_ProjectSource (point, _distance, forward, right, result);
}

/*
===============
PlayerNoise
Revised for CleanCode.
===============
*/
void PlayerNoise(CPlayerEntity *Player, vec3_t where, int type)
{
#ifndef MONSTERS_USE_PATHFINDING
	edict_t		*noise;
#endif

	if (type == PNOISE_WEAPON)
	{
		if (Player->Client.silencer_shots)
		{
			Player->Client.silencer_shots--;
			return;
		}
	}

	if (game.mode & GAME_DEATHMATCH)
		return;

	//if (who->flags & FL_NOTARGET)
	//	return;

#ifndef MONSTERS_USE_PATHFINDING
	if (!who->mynoise)
	{
		noise = G_Spawn();
		noise->classname = "player_noise";
		Vec3Set (noise->mins, -8, -8, -8);
		Vec3Set (noise->maxs, 8, 8, 8);
		noise->owner = who;
		noise->svFlags = SVF_NOCLIENT;
		who->mynoise = noise;

		noise = G_Spawn();
		noise->classname = "player_noise";
		Vec3Set (noise->mins, -8, -8, -8);
		Vec3Set (noise->maxs, 8, 8, 8);
		noise->owner = who;
		noise->svFlags = SVF_NOCLIENT;
		who->mynoise2 = noise;
	}

	if (type == PNOISE_SELF || type == PNOISE_WEAPON)
	{
		noise = who->mynoise;
		level.sound_entity = noise;
		level.sound_entity_framenum = level.framenum;
	}
	else // type == PNOISE_IMPACT
	{
		noise = who->mynoise2;
		level.sound2_entity = noise;
		level.sound2_entity_framenum = level.framenum;
	}

	Vec3Copy (where, noise->state.origin);
	Vec3Subtract (where, noise->maxs, noise->absMin);
	Vec3Add (where, noise->maxs, noise->absMax);
	noise->teleport_time = level.time;
	gi.linkentity (noise);
#else
	level.NoiseNode = GetClosestNodeTo(where);
	level.SoundEntityFramenum = level.framenum;
	level.SoundEntity = Player;
#endif
}

void CWeapon::Muzzle (CPlayerEntity *Player, int muzzleNum)
{
	if (isSilenced)
		muzzleNum |= MZ_SILENCED;
	vec3_t origin;
	Player->State.GetOrigin (origin);
	CTempEnt::MuzzleFlash(origin, Player->gameEntity-g_edicts, muzzleNum);
}

/*
=================
Think_Weapon

Called by ClientBeginServerFrame
=================
*/
void CWeapon::Think (CPlayerEntity *Player)
{
#ifdef CLEANCTF_ENABLED
	if ((game.mode & GAME_CTF) && !Player->Client.resp.ctf_team)
		return;
#endif

	// if just died, put the weapon away
	if (Player->gameEntity->health < 1)
	{
		Player->Client.NewWeapon = NULL;
		ChangeWeapon (Player);
		return;
	}

	// call active weapon think routine
	isQuad = (Player->Client.quad_framenum > level.framenum);
	isSilenced = (Player->Client.silencer_shots) ? true : false;
	WeaponGeneric (Player);
#ifdef CLEANCTF_ENABLED
	if (this != &WeaponGrapple && Player->CTFApplyHaste())
		WeaponGeneric(Player);
#endif
}

void CWeapon::AttackSound(CPlayerEntity *Player)
{
#ifdef CLEANCTF_ENABLED
//ZOID
	if (!Player->CTFApplyStrengthSound())
//ZOID
#endif
	if (isQuad)
		PlaySoundFrom(Player->gameEntity, CHAN_ITEM, SoundIndex("items/damage3.wav"));
#ifdef CLEANCTF_ENABLED
//ZOID
	Player->CTFApplyHasteSound();
//ZOID
#endif
}

// YUCK
// Better way?
void CWeapon::NoAmmoWeaponChange (CPlayerEntity *Player)
{
	// Dead?
	if (!Player->Client.pers.Weapon || Player->gameEntity->health <= 0 || Player->gameEntity->deadflag)
		return;

	// Collect info on our current state
	bool HasShotgun = (Player->Client.pers.Inventory.Has(FindItem("Shotgun")) != 0);
	bool HasSuperShotgun = (Player->Client.pers.Inventory.Has(FindItem("Super Shotgun")) != 0);
	bool HasMachinegun = (Player->Client.pers.Inventory.Has(FindItem("Machinegun")) != 0);
	bool HasChaingun = (Player->Client.pers.Inventory.Has(FindItem("Chaingun")) != 0);
	bool HasGrenadeLauncher = (Player->Client.pers.Inventory.Has(FindItem("Grenade Launcher")) != 0);
	bool HasRocketLauncher = (Player->Client.pers.Inventory.Has(FindItem("Rocket Launcher")) != 0);
	bool HasHyperblaster = (Player->Client.pers.Inventory.Has(FindItem("Hyperblaster")) != 0);
	bool HasRailgun = (Player->Client.pers.Inventory.Has(FindItem("Railgun")) != 0);
	bool HasBFG = (Player->Client.pers.Inventory.Has(FindItem("BFG10k")) != 0);

	bool HasShells = (Player->Client.pers.Inventory.Has(FindItem("Shells")) != 0);
	bool HasShells_ForSuperShotty = (Player->Client.pers.Inventory.Has(FindItem("Shells")) > 5);
	bool HasBullets = (Player->Client.pers.Inventory.Has(FindItem("Bullets")) != 0);
	bool HasBullets_ForChaingun = (Player->Client.pers.Inventory.Has(FindItem("Bullets")) >= 50);
	bool HasGrenades = (Player->Client.pers.Inventory.Has(FindItem("Grenades")) != 0);
	bool HasRockets = (Player->Client.pers.Inventory.Has (FindItem("Rockets")) != 0);
	bool HasCells = (Player->Client.pers.Inventory.Has (FindItem("Cells")) != 0);
	bool HasCells_ForBFG = (Player->Client.pers.Inventory.Has (FindItem("Cells")) >= 50);
	bool HasSlugs = (Player->Client.pers.Inventory.Has(FindItem("Slugs")) != 0);

	bool AlmostDead = (Player->gameEntity->health <= 20);

	CWeaponItem	*Chosen_Weapon = NULL;
	CAmmo		*Chosen_Ammo = NULL;

	// Try not to choose explosive weapons
	if (AlmostDead)
	{
		if (HasCells && HasHyperblaster)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Hyperblaster"));
		else if (HasSlugs && HasRailgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Railgun"));
		else if (HasBullets_ForChaingun && HasChaingun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Chaingun"));
		else if (HasBullets_ForChaingun && HasMachinegun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Machinegun"));
		else if (HasShells_ForSuperShotty && HasSuperShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Super Shotgun"));
		else if (HasShells && HasSuperShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Super Shotgun"));
		else if (HasShells_ForSuperShotty && HasShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Shotgun"));
		else if (HasShells && HasShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Shotgun"));
	}

	// Still nothing
	if (!Chosen_Weapon || !Chosen_Ammo)
	{
		if (HasCells_ForBFG && HasBFG)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("BFG10k"));
		else if (HasCells && HasHyperblaster)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Hyperblaster"));
		else if (HasSlugs && HasRailgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Railgun"));
		else if (HasRockets && HasRocketLauncher)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Rocket Launcher"));
		else if (HasGrenades && HasGrenadeLauncher)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Grenade Launcher"));
		else if (HasBullets_ForChaingun && HasChaingun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Chaingun"));
		else if (HasBullets && HasMachinegun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Machinegun"));
		else if (HasBullets && HasChaingun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Chaingun"));
		else if (HasShells_ForSuperShotty && HasSuperShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Super Shotgun"));
		else if (HasShells && HasSuperShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Super Shotgun"));
		else if (HasShells_ForSuperShotty && HasShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Shotgun"));
		else if (HasShells && HasShotgun)
			Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Shotgun"));
		else if (HasGrenades)
			Chosen_Ammo = dynamic_cast<CAmmo*>(FindItem("Grenades"));
	}

	if (!Chosen_Weapon && !Chosen_Ammo)
		Chosen_Weapon = dynamic_cast<CWeaponItem*>(FindItem("Blaster"));

	bool HasCurrentWeapon = true;
	// Do a quick check to see if we still even have the weapon we're holding.
	if (Player->Client.pers.Weapon->WeaponItem && !Player->Client.pers.Inventory.Has(Player->Client.pers.Weapon->WeaponItem))
		HasCurrentWeapon = false;

	Player->Client.NewWeapon = (Chosen_Weapon == NULL) ? Chosen_Ammo->Weapon : Chosen_Weapon->Weapon;
	if (!HasCurrentWeapon)
		Player->Client.pers.Weapon->ChangeWeapon(Player);
}

void CWeapon::FireAnimation (CPlayerEntity *Player)
{
	// start the animation
	Player->Client.anim_priority = ANIM_ATTACK;
	if (Player->Client.PlayerState.GetPMove()->pmFlags & PMF_DUCKED)
	{
		Player->State.SetFrame (FRAME_crattak1-1);
		Player->Client.anim_end = FRAME_crattak9;
	}
	else
	{
		Player->State.SetFrame (FRAME_attack1-1);
		Player->Client.anim_end = FRAME_attack8;
	}
}