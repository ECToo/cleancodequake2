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
// cc_ctfitementities.cpp
// CTF Item Entities
//

#include "cc_local.h"

CFlagEntity::CFlagEntity () :
CBaseEntity(),
CItemEntity()
{
};

CFlagEntity::CFlagEntity (int Index) :
CBaseEntity(Index),
CItemEntity(Index)
{
};

void CFlagEntity::Think ()
{
	switch (ThinkState)
	{
	case FTS_FLAGSETUP:
		{
			SetMins (vec3f(-15, -15, -15));
			SetMaxs (vec3f(15, 15, 15));

			if (gameEntity->model)
				State.SetModelIndex (ModelIndex(gameEntity->model));
			else
				State.SetModelIndex (ModelIndex(gameEntity->item->WorldModel));
			SetSolid (SOLID_TRIGGER);
			NoTouch = false;
			NoPhysics = false;

			vec3f dest = State.GetOrigin() + vec3f(0, 0, -128);
			CTrace tr (State.GetOrigin(), GetMins(), GetMaxs(), dest, gameEntity, CONTENTS_MASK_SOLID);
			if (tr.startSolid)
			{
				vec3f origin = State.GetOrigin();
				DebugPrintf ("CTFFlagSetup: %s startSolid at (%f %f %f)\n", gameEntity->classname, origin.X, origin.Y, origin.Z);
				Free ();
				return;
			}

			State.SetOrigin (tr.EndPos);

			Link ();

			NextThink = level.framenum + FRAMETIME;
			ThinkState = FTS_FLAGTHINK;
		}
		break;
	case FTS_FLAGTHINK:
		if (GetSolid() != SOLID_NOT)
			State.SetFrame (173 + (((State.GetFrame() - 173) + 1) % 16));
		NextThink = level.framenum + FRAMETIME;
		break;
	default:
		CItemEntity::Think ();
	};
};

bool CFlagEntity::Run ()
{
	return CItemEntity::Run ();
};

void CFlagEntity::Spawn (CBaseItem *Item)
{
//ZOID
//Don't spawn the flags unless enabled
	if (!(game.mode & GAME_CTF))
	{
		Free ();
		return;
	}

	gameEntity->item = Item;

	NextThink = level.framenum + 2;    // items start after other solids
	ThinkState = FTS_FLAGSETUP;
	NoPhysics = true;

	State.SetEffects(Item->EffectFlags);
	State.SetRenderEffects(RF_GLOW);
};

CRedFlagEntity::CRedFlagEntity () :
CBaseEntity(),
CFlagEntity()
{
};

CRedFlagEntity::CRedFlagEntity (int Index) :
CBaseEntity(Index),
CFlagEntity(Index)
{
};

bool CRedFlagEntity::Run ()
{
	return CFlagEntity::Run ();
};

void CRedFlagEntity::BecomeExplosion (bool grenade)
{
	CTFResetFlag(CTF_TEAM1); // this will free self!
	BroadcastPrintf(PRINT_HIGH, "The %s flag has returned!\n",
		CTFTeamName(CTF_TEAM1));
};


CBlueFlagEntity::CBlueFlagEntity () :
CBaseEntity(),
CFlagEntity()
{
};

CBlueFlagEntity::CBlueFlagEntity (int Index) :
CBaseEntity(Index),
CFlagEntity(Index)
{
};

bool CBlueFlagEntity::Run ()
{
	return CFlagEntity::Run ();
};

void CBlueFlagEntity::BecomeExplosion (bool grenade)
{
	CTFResetFlag(CTF_TEAM2); // this will free self!
	BroadcastPrintf(PRINT_HIGH, "The %s flag has returned!\n",
		CTFTeamName(CTF_TEAM2));
};

class CDroppedFlagEntity : public CFlagEntity
{
public:
	bool Red;

	CDroppedFlagEntity() :
	CFlagEntity()
	{
	};
	CDroppedFlagEntity(int Index) :
	CFlagEntity(Index)
	{
	};

	void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf)
	{
		if (((other->gameEntity == gameEntity->owner) && (NextThink - level.framenum > CTF_AUTO_FLAG_RETURN_TIMEOUT-20)))
			return;

		CItemEntity::Touch (other, plane, surf);
	};

	void Think ()
	{
		if (Red)
		{
			CTFResetFlag (CTF_TEAM1);
			BroadcastPrintf(PRINT_HIGH, "The %s flag has returned!\n",
				CTFTeamName(CTF_TEAM1));
		}
		else
		{
			CTFResetFlag (CTF_TEAM2);
			BroadcastPrintf(PRINT_HIGH, "The %s flag has returned!\n",
				CTFTeamName(CTF_TEAM2));
		}
	};

	void Spawn ()
	{
		Red = false;
	};
};

CItemEntity *CFlag::DropItem (CBaseEntity *ent)
{
	CDroppedFlagEntity	*dropped = QNew (com_levelPool, 0) CDroppedFlagEntity();
	vec3f	forward, right;

	dropped->gameEntity->classname = Classname;
	dropped->gameEntity->item = this;
	dropped->gameEntity->spawnflags = DROPPED_ITEM;
	dropped->State.SetEffects (EffectFlags);
	dropped->State.SetRenderEffects (RF_GLOW);
	dropped->SetMins (vec3f(-15));
	dropped->SetMaxs (vec3f(15));
	dropped->State.SetModelIndex (ModelIndex(WorldModel));
	dropped->SetSolid (SOLID_TRIGGER);
	dropped->gameEntity->owner = ent->gameEntity;

	if (ent->EntityFlags & ENT_PLAYER)
	{
		CPlayerEntity *Player = dynamic_cast<CPlayerEntity*>(ent);
		CTrace	trace;

		Player->Client.ViewAngle.ToVectors (&forward, &right, NULL);
		vec3f offset (24, 0, -16);

		vec3f result;
		G_ProjectSource (ent->State.GetOrigin(), offset, forward, right, result);

		trace = CTrace (ent->State.GetOrigin(), dropped->GetMins(), dropped->GetMaxs(),
			result, ent->gameEntity, CONTENTS_SOLID);
		dropped->State.SetOrigin (trace.endPos);
	}
	else
	{
		ent->State.GetAngles().ToVectors(&forward, &right, NULL);
		dropped->State.SetOrigin (ent->State.GetOrigin());
	}

	forward.Scale(100);
	dropped->gameEntity->velocity[0] = forward.X;
	dropped->gameEntity->velocity[1] = forward.Y;
	dropped->gameEntity->velocity[2] = 300;

	dropped->NextThink = level.framenum + CTF_AUTO_FLAG_RETURN_TIMEOUT;
	dropped->Link ();

	return dropped;
};

LINK_ITEM_TO_CLASS (item_flag_team1, CRedFlagEntity);
LINK_ITEM_TO_CLASS (item_flag_team2, CBlueFlagEntity);