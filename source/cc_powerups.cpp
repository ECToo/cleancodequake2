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
// cc_powerups.cpp
// Powerups
//

#include "cc_local.h"

CBasePowerUp::CBasePowerUp(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBaseItem(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache),
PowerupFlags(PowerupFlags)
{
};

// Powerups!
bool CBasePowerUp::Pickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (PowerupFlags & POWERFLAG_STORE)
	{
		if (other->Client.pers.Inventory.Has(this) > 0 &&
			(!(PowerupFlags & POWERFLAG_STACK) ||
			(PowerupFlags & (POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP) && (game.mode == GAME_COOPERATIVE)) ||
			(game.mode == GAME_COOPERATIVE) && (Flags & ITEMFLAG_STAY_COOP)))
			return false;

		other->Client.pers.Inventory += this;
	}

	DoPickup (ent, other);
	return true;
}

void CBasePowerUp::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
}

void CBasePowerUp::Use (CPlayerEntity *ent)
{
}

void CBasePowerUp::Drop (CPlayerEntity *ent)
{
	if (PowerupFlags & POWERFLAG_STORE)
	{	
		DropItem (ent);
		ent->Client.pers.Inventory -= this;
	}
}

CMegaHealth::CMegaHealth(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CBackPack::CBackPack(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CQuadDamage::CQuadDamage(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CInvulnerability::CInvulnerability(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CSilencer::CSilencer(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CRebreather::CRebreather(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CEnvironmentSuit::CEnvironmentSuit(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CBandolier::CBandolier(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CAdrenaline::CAdrenaline(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CAncientHead::CAncientHead(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

CPowerShield::CPowerShield(char *Classname, char *WorldModel, int EffectFlags,
			   char *PickupSound, char *Icon, char *Name, EItemFlags Flags,
			   char *Precache, EPowerupFlags PowerupFlags) :
CBasePowerUp(Classname, WorldModel, EffectFlags, PickupSound, Icon, Name, Flags, Precache, PowerupFlags)
{
};

class CMegaHealthEntity : public CItemEntity
{
public:
	bool			MegaHealthThinking;
	CPlayerEntity	*Player;

	CMegaHealthEntity () :
	  CBaseEntity(),
	  CItemEntity(),
	  Player(NULL)
	  {
		  MegaHealthThinking = false;
	  };

	CMegaHealthEntity (int Index) :
	  CBaseEntity (Index),
	  CItemEntity(Index),
	  Player(NULL)
	  {
		  MegaHealthThinking = false;
	  };

	void Think ()
	{
		if (MegaHealthThinking)
		{
			if (Player->Health > Player->MaxHealth
		
			&& ((
#ifdef CLEANCTF_ENABLED
			!(game.mode & GAME_CTF) && 
#endif
			!dmFlags.dfDmTechs) || !Player->HasRegeneration())
				)
			{
				NextThink = level.framenum + 10;
				Player->Health -= 1;
				return;
			}

			if (!(SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
				gameEntity->item->SetRespawn (this, 200);
			else
				Free ();
			MegaHealthThinking = false;
		}
		else
			CItemEntity::Think ();
	};

	void Spawn (CBaseItem *item)
	{
		if ((game.mode & GAME_DEATHMATCH) && (dmFlags.dfNoHealth || dmFlags.dfNoItems))
		{
			Free ();
			return;
		}

		gameEntity->item = item;
		NextThink = level.framenum + 2;    // items start after other solids
		ThinkState = ITS_DROPTOFLOOR;
		NoPhysics = true;

		State.SetEffects(item->EffectFlags);
		State.SetRenderEffects(RF_GLOW);
	};
};


// Seperate powerup classes
void CMegaHealth::DoPickup (CItemEntity *ent, CPlayerEntity *other)
{
	CMegaHealthEntity *MegaHealth = dynamic_cast<CMegaHealthEntity*>(ent);

	if ((!dmFlags.dfDmTechs
#ifdef CLEANCTF_ENABLED
		&& !(game.mode & GAME_CTF)
#endif
		)|| ((
#ifdef CLEANCTF_ENABLED
		(game.mode & GAME_CTF) || 
#endif
		dmFlags.dfDmTechs) && !other->HasRegeneration()))
	{
		MegaHealth->MegaHealthThinking = true;
		MegaHealth->NextThink = level.framenum + 50;
		MegaHealth->Player = other;
		MegaHealth->Flags |= FL_RESPAWN;
		MegaHealth->SetSvFlags (MegaHealth->GetSvFlags() | SVF_NOCLIENT);
		MegaHealth->SetSolid (SOLID_NOT);

		other->Health += 100;
#ifdef CLEANCTF_ENABLED
	}
	else if (!(MegaHealth->SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
		MegaHealth->gameEntity->item->SetRespawn (ent, 300);
#endif
}

void CBackPack::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	// Increase their max ammo, if applicable
	for (int i = 0; i < AMMOTAG_MAX; i++)
	{
		if (other->Client.pers.maxAmmoValues[i] < maxBackpackAmmoValues[i])
			other->Client.pers.maxAmmoValues[i] = maxBackpackAmmoValues[i];
	}

	// Give them some more ammo
	NItems::Bullets->AddAmmo (other, NItems::Bullets->Quantity);
	NItems::Shells->AddAmmo (other, NItems::Shells->Quantity);
	NItems::Grenades->AddAmmo (other, NItems::Grenades->Quantity);
	NItems::Cells->AddAmmo (other, NItems::Cells->Quantity);
	NItems::Slugs->AddAmmo (other, NItems::Slugs->Quantity);
	NItems::Rockets->AddAmmo (other, NItems::Rockets->Quantity);

	if (!(ent->SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
		SetRespawn (ent, 1800);
}

static int	quad_drop_timeout_hack;

void CQuadDamage::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode & GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 600);
		if (ent->SpawnFlags & DROPPED_PLAYER_ITEM)
			quad_drop_timeout_hack = (ent->NextThink - level.framenum);

		if (dmFlags.dfInstantItems)
			Use (other);
	}
}

void CQuadDamage::Use (CPlayerEntity *ent)
{
	int timeOut = 300;

	if (quad_drop_timeout_hack)
	{
		timeOut = quad_drop_timeout_hack;
		quad_drop_timeout_hack = 0;
	}

	if (ent->Client.quad_framenum > level.framenum)
		ent->Client.quad_framenum += timeOut;
	else
		ent->Client.quad_framenum = level.framenum + timeOut;

	ent->Client.pers.Inventory -= this;

	ent->PlaySound (CHAN_ITEM, SoundIndex("items/damage.wav"));
}

void CInvulnerability::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode == GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 300);
		if (dmFlags.dfInstantItems || (ent->SpawnFlags & DROPPED_PLAYER_ITEM))
			Use (other);
	}
}

void CInvulnerability::Use (CPlayerEntity *ent)
{
	ent->Client.pers.Inventory -= this;

	if (ent->Client.invincible_framenum > level.framenum)
		ent->Client.invincible_framenum += 300;
	else
		ent->Client.invincible_framenum = level.framenum + 300;

	ent->PlaySound (CHAN_ITEM, SoundIndex("items/protect.wav"));
}

void CSilencer::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode & GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 300);
		if (dmFlags.dfInstantItems || (ent->SpawnFlags & DROPPED_PLAYER_ITEM))
			Use (other);
	}
}

void CSilencer::Use (CPlayerEntity *ent)
{
	ent->Client.pers.Inventory -= this;
	ent->Client.silencer_shots += 30;
}

void CRebreather::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode & GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 600);
		if (dmFlags.dfInstantItems || (ent->SpawnFlags & DROPPED_PLAYER_ITEM))
			Use (other);
	}
}

void CRebreather::Use (CPlayerEntity *ent)
{
	ent->Client.pers.Inventory -= this;

	if (ent->Client.breather_framenum > level.framenum)
		ent->Client.breather_framenum += 300;
	else
		ent->Client.breather_framenum = level.framenum + 300;
}

void CEnvironmentSuit::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode & GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 600);
		if (dmFlags.dfInstantItems || (ent->SpawnFlags & DROPPED_PLAYER_ITEM))
			Use (other);
	}
}

void CEnvironmentSuit::Use (CPlayerEntity *ent)
{
	ent->Client.pers.Inventory -= this;

	if (ent->Client.enviro_framenum > level.framenum)
		ent->Client.enviro_framenum += 300;
	else
		ent->Client.enviro_framenum = level.framenum + 300;
}

void CBandolier::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	// Increase their max ammo, if applicable
	for (int i = 0; i < AMMOTAG_MAX; i++)
	{
		if (other->Client.pers.maxAmmoValues[i] < maxBandolierAmmoValues[i])
			other->Client.pers.maxAmmoValues[i] = maxBandolierAmmoValues[i];
	}

	// Give them some more ammo
	NItems::Bullets->AddAmmo (other, NItems::Bullets->Quantity);
	NItems::Shells->AddAmmo (other, NItems::Shells->Quantity);

	if (!(ent->SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
		SetRespawn (ent, 600);
}

void CAdrenaline::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (!(game.mode & GAME_DEATHMATCH))
		other->MaxHealth += 1;

	if (other->Health < other->MaxHealth)
		other->Health = other->MaxHealth;

	if (!(ent->SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
		SetRespawn (ent, 600);
}

void CAncientHead::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	other->MaxHealth += 2;

	if (!(ent->SpawnFlags & DROPPED_ITEM) && (game.mode & GAME_DEATHMATCH))
		SetRespawn (ent, 600);
}

void CPowerShield::DoPickup (class CItemEntity *ent, CPlayerEntity *other)
{
	if (game.mode & GAME_DEATHMATCH)
	{
		if (!(ent->SpawnFlags & DROPPED_ITEM) )
			SetRespawn (ent, 600);

		// auto-use for DM only if we didn't already have one
		if (!other->Client.pers.Inventory.Has(this))
			Use (other);
	}
}

void CPowerShield::Use (CPlayerEntity *ent)
{
	if (ent->Flags & FL_POWER_ARMOR)
	{
		ent->Flags &= ~FL_POWER_ARMOR;
		ent->PlaySound (CHAN_AUTO, SoundIndex("misc/power2.wav"));
	}
	else
	{
		if (!ent->Client.pers.Inventory.Has(NItems::Cells))
		{
			ent->PrintToClient (PRINT_HIGH, "No cells for %s.\n", Name);
			return;
		}
		ent->Flags |= FL_POWER_ARMOR;
		ent->PlaySound (CHAN_AUTO, SoundIndex("misc/power1.wav"));
	}
}

void CPowerShield::Drop (CPlayerEntity *ent)
{
	if ((ent->Flags & FL_POWER_ARMOR) && (ent->Client.pers.Inventory.Has(this) == 1))
		Use (ent);
	CBasePowerUp::Drop (ent);
}

class CPowerupEntity : public CItemEntity
{
public:
	CPowerupEntity() :
	  CBaseEntity(),
	  CItemEntity ()
	  {
	  };

	CPowerupEntity (int Index) :
	  CBaseEntity(Index),
	  CItemEntity (Index)
	  {
	  };

	void Spawn (CBaseItem *item)
	{
		if ((game.mode & GAME_DEATHMATCH) && dmFlags.dfNoItems)
		{
			Free ();
			return;
		}

		gameEntity->item = item;
		NextThink = level.framenum + 2;    // items start after other solids
		ThinkState = ITS_DROPTOFLOOR;
		NoPhysics = true;

		State.SetEffects(item->EffectFlags);
		State.SetRenderEffects(RF_GLOW);
	};
};

LINK_ITEM_TO_CLASS (item_health_mega, CMegaHealthEntity);
LINK_ITEM_TO_CLASS (item_pack, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_quad, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_invulnerability, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_silencer, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_breather, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_enviro, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_bandolier, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_adrenaline, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_ancient_head, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_power_shield, CPowerupEntity);
LINK_ITEM_TO_CLASS (item_power_screen, CPowerupEntity);

void AddPowerupsToList ()
{
	NItems::MegaHealth = QNew (com_gamePool, 0) CMegaHealth("item_health_mega", "models/items/mega_h/tris.md2", 0, "items/m_health.wav", "i_health", "MegaHealth", ITEMFLAG_HEALTH|ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE, "", 0);
	NItems::BackPack = QNew (com_gamePool, 0) CBackPack ("item_pack", "models/items/pack/tris.md2", EF_ROTATE, "items/pkup.wav", "i_pack", "Ammo Pack", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE, "", POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Quad = QNew (com_gamePool, 0) CQuadDamage ("item_quad", "models/items/quaddama/tris.md2", EF_ROTATE, "items/pkup.wav", "p_quad", "Quad Damage", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_DROPPABLE|ITEMFLAG_USABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Invul = QNew (com_gamePool, 0) CInvulnerability ("item_invulnerability", "models/items/invulner/tris.md2", EF_ROTATE, "items/pkup.wav", "p_invulnerability", "Invulnerability", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_DROPPABLE|ITEMFLAG_USABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Silencer = QNew (com_gamePool, 0) CSilencer ("item_silencer", "models/items/silencer/tris.md2", EF_ROTATE, "items/pkup.wav", "p_silencer", "Silencer", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_DROPPABLE|ITEMFLAG_USABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Rebreather = QNew (com_gamePool, 0) CRebreather ("item_breather", "models/items/breather/tris.md2", EF_ROTATE, "items/pkup.wav", "p_rebreather", "Rebreather", ITEMFLAG_POWERUP|ITEMFLAG_STAY_COOP|ITEMFLAG_GRABBABLE|ITEMFLAG_DROPPABLE|ITEMFLAG_USABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::EnvironmentSuit = QNew (com_gamePool, 0) CEnvironmentSuit ("item_enviro", "models/items/enviro/tris.md2", EF_ROTATE, "items/pkup.wav", "p_envirosuit", "Environment Suit", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_DROPPABLE|ITEMFLAG_USABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Bandolier = QNew (com_gamePool, 0) CBandolier ("item_bandolier", "models/items/band/tris.md2", EF_ROTATE, "items/pkup.wav", "p_bandolier", "Bandolier", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE, "", POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::Adrenaline = QNew (com_gamePool, 0) CAdrenaline ("item_adrenaline", "models/items/adrenal/tris.md2", EF_ROTATE, "items/pkup.wav", "p_adrenaline", "Adrenaline", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE, "", 0);
	NItems::AncientHead = QNew (com_gamePool, 0) CAncientHead ("item_ancient_head", "models/items/c_head/tris.md2", EF_ROTATE, "items/pkup.wav", "i_fixme", "Ancient Head", ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE, "", 0);
	NItems::PowerShield = QNew (com_gamePool, 0) CPowerShield ("item_power_shield", "models/items/armor/shield/tris.md2", EF_ROTATE, "misc/ar3_pkup.wav", "i_powershield", "Power Shield", ITEMFLAG_ARMOR|ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_USABLE|ITEMFLAG_DROPPABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);
	NItems::PowerScreen = QNew (com_gamePool, 0) CPowerShield ("item_power_screen", "models/items/armor/screen/tris.md2", EF_ROTATE, "misc/ar3_pkup.wav", "i_powerscreen", "Power Screen", ITEMFLAG_ARMOR|ITEMFLAG_POWERUP|ITEMFLAG_GRABBABLE|ITEMFLAG_USABLE|ITEMFLAG_DROPPABLE, "", POWERFLAG_STORE|POWERFLAG_STACK|POWERFLAG_BUTNOTINCOOP);

	ItemList->AddItemToList (NItems::MegaHealth);
	ItemList->AddItemToList (NItems::BackPack);
	ItemList->AddItemToList (NItems::Quad);
	ItemList->AddItemToList (NItems::Invul);
	ItemList->AddItemToList (NItems::Silencer);
	ItemList->AddItemToList (NItems::Rebreather);
	ItemList->AddItemToList (NItems::EnvironmentSuit);
	ItemList->AddItemToList (NItems::Bandolier);
	ItemList->AddItemToList (NItems::Adrenaline);
	ItemList->AddItemToList (NItems::AncientHead);
	ItemList->AddItemToList (NItems::PowerShield);
	ItemList->AddItemToList (NItems::PowerScreen);
}