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
// cc_rogue_misc_entities.cpp
// 
//

#include "cc_local.h"

class CMiscNukeCore : public IMapEntity, public IUsableEntity
{
public:
	CMiscNukeCore () :
	  IMapEntity (),
	  IUsableEntity ()
	  {
	  };

	CMiscNukeCore (sint32 Index) :
	  IBaseEntity (Index),
	  IMapEntity (Index),
	  IUsableEntity (Index)
	  {
	  };

	void SaveFields (CFile &File)
	{
		IMapEntity::SaveFields (File);
		IUsableEntity::SaveFields (File);
	}

	void LoadFields (CFile &File)
	{
		IMapEntity::LoadFields (File);
		IUsableEntity::LoadFields (File);
	}

	IMPLEMENT_SAVE_HEADER(CMiscNukeCore);

	void Use (IBaseEntity *Other, IBaseEntity *Activator)
	{
		GetSvFlags() ^= SVF_NOCLIENT;
	}

	void Spawn ()
	{
		State.GetModelIndex() = ModelIndex("models/objects/core/tris.md2");
		Usable = true;
		Link ();
	}
};

LINK_CLASSNAME_TO_CLASS ("misc_nuke_core", CMiscNukeCore);

#include "cc_brushmodels.h"
#include "cc_tent.h"

/*QUAKED func_door_secret2 (0 .5 .8) ? open_once 1st_left 1st_down no_shoot always_shoot slide_right slide_forward
Basic secret door. Slides back, then to the left. Angle determines direction.

FLAGS:
open_once = not implemented yet
1st_left = 1st move is left/right of arrow
1st_down = 1st move is forwards/backwards
no_shoot = not implemented yet
always_shoot = even if targeted, keep shootable
reverse_left = the sideways move will be to right of arrow
reverse_back = the to/from move will be forward

VALUES:
wait = # of seconds before coming back (5 default)
dmg  = damage to inflict when blocked (2 default)
*/

CC_ENUM (uint8, EDoorSecretSpawnflags)
{
	SEC_OPEN_ONCE				= BIT(0),
	SEC_1ST_LEFT				= BIT(1),
	SEC_1ST_DOWN				= BIT(2),
	SEC_NO_SHOOT				= BIT(3),
	SEC_YES_SHOOT				= BIT(4),
	SEC_MOVE_RIGHT				= BIT(5),
	SEC_MOVE_FORWARD			= BIT(6)
};

class CDoorSecret2 : public CDoor
{
public:
	enum
	{
		DOORSECRETTHINK_6 = BRUSHTHINK_CUSTOM_START,
		DOORSECRETTHINK_4,
		DOORSECRETTHINK_2
	};

	enum
	{
		DOORSECRETENDFUNC_DONE,
		DOORSECRETENDFUNC_5,
		DOORSECRETENDFUNC_3,
		DOORSECRETENDFUNC_1
	};

	CDoorSecret2 () :
	  IBaseEntity(),
	  CDoor ()
	  {
		  BrushType |= BRUSH_SECRETDOOR;
	  };

	CDoorSecret2 (sint32 Index) :
	  IBaseEntity(Index),
	  CDoor(Index)
	  {
		  BrushType |= BRUSH_SECRETDOOR;
	  };

	IMPLEMENT_SAVE_HEADER(CDoorSecret2)

	void Touch (IBaseEntity *Other, plane_t *plane, cmBspSurface_t *surf)
	{
		if (!(Other->EntityFlags & ENT_PLAYER))
			return;

		if (Level.Frame < TouchDebounce)
			return;

		TouchDebounce = Level.Frame + 20;

		(entity_cast<CPlayerEntity>(Other))->PrintToClient (PRINT_CENTER, "%s", Message.c_str());
	}
	void Blocked (IBaseEntity *Other)
	{
		if (!(Flags & FL_TEAMSLAVE) && (Other->EntityFlags & ENT_HURTABLE) && entity_cast<IHurtableEntity>(Other)->CanTakeDamage)
			entity_cast<IHurtableEntity>(Other)->TakeDamage (this, this, vec3fOrigin, Other->State.GetOrigin(), vec3fOrigin, Damage, 0, 0, MOD_CRUSH);
	}
	void Use (IBaseEntity *Other, IBaseEntity *Activator)
	{
		if (Flags & FL_TEAMSLAVE)
			return;

		// trigger all paired doors
		for (IBaseEntity *ent = this; ent; ent = ent->Team.Chain)
		{
			if (ent->EntityFlags & ENT_BRUSHMODEL)
				entity_cast<IBrushModel>(ent)->MoveCalc (StartOrigin, DOORSECRETENDFUNC_1);
		}
	}
	void Die (IBaseEntity *Inflictor, IBaseEntity *Attacker, sint32 Damage, vec3f &point)
	{
		Health = MaxHealth;
		CanTakeDamage = true;

		if (Flags & FL_TEAMSLAVE && Team.Master && (Team.Master->EntityFlags & ENT_HURTABLE) && (entity_cast<IHurtableEntity>(Team.Master)->CanTakeDamage))
			entity_cast<IHurtableEntity>(Team.Master)->Die (Inflictor, Attacker, Damage, point);
		else
			Use (Inflictor, Attacker);
	}

	void DoEndFunc ()
	{
		switch (EndFunc)
		{
			case DOORSECRETENDFUNC_DONE:
				if (!(TargetName) || (SpawnFlags & SEC_YES_SHOOT))
				{
					Health = 1;
					CanTakeDamage = true;
				}
				break;
			case DOORSECRETENDFUNC_5:
				NextThink = Level.Frame + 10;
				ThinkType = DOORSECRETTHINK_6;
				break;
			case DOORSECRETENDFUNC_3:
				if (!(SpawnFlags & SEC_OPEN_ONCE))
				{
					NextThink = Level.Frame + Wait;
					ThinkType = DOORSECRETTHINK_4;
				}
				break;
			case DOORSECRETENDFUNC_1:
				NextThink = Level.Frame + 10;
				ThinkType = DOORSECRETTHINK_2;
				break;
		};
	};
	void Think ()
	{
		switch (ThinkType)
		{
		case DOORSECRETTHINK_6:
			MoveCalc (MoveOrigin, DOORSECRETENDFUNC_DONE);
			break;
		case DOORSECRETTHINK_4:
			MoveCalc (StartOrigin, DOORSECRETENDFUNC_5);
			break;
		case DOORSECRETTHINK_2:
			MoveCalc (EndOrigin, DOORSECRETENDFUNC_3);
			break;
		default:
			IBrushModel::Think ();
		}
	};

	void Spawn ()
	{
		SoundStart = SoundIndex  ("doors/dr1_strt.wav");
		SoundMiddle = SoundIndex  ("doors/dr1_mid.wav");
		SoundEnd = SoundIndex  ("doors/dr1_end.wav");

		PhysicsType = PHYSICS_PUSH;
		GetSolid() = SOLID_BSP;
		SetBrushModel ();

		if (!(TargetName) || (SpawnFlags & SEC_YES_SHOOT))
		{
			Health = 1;
			MaxHealth = Health;
			CanTakeDamage = true;
		}

		Touchable = false;

		if (!Damage)
			Damage = 2;

		if (!Wait)
			Wait = 50;

		Accel =
		Decel =
		Speed = 50;

		// calculate positions
		vec3f forward, right, up;
		State.GetAngles().ToVectors (&forward, &right, &up);
		MoveOrigin = State.GetOrigin();
		MoveAngles = State.GetAngles();

		G_SetMovedir (State.GetAngles(), MoveDir);
		PhysicsType = PHYSICS_PUSH;
		GetSolid() = SOLID_BSP;
		SetBrushModel ();

		float lrSize = 0, fbSize = 0;
		if(MoveAngles.Y == 0 || MoveAngles.Y == 180)
		{
			lrSize = GetSize().Y;
			fbSize = GetSize().X;
		}		
		else if(MoveAngles.Y == 90 || MoveAngles.Y == 270)
		{
			lrSize = GetSize().X;
			fbSize = GetSize().Y;
		}		
		else
			MapPrint (MAPPRINT_WARNING, this, State.GetOrigin(), "Secret door not at 0, 90, 180, 270!\n");

		if (SpawnFlags & SEC_MOVE_FORWARD)
			forward *= fbSize;
		else
			forward *= (fbSize * -1);

		if (SpawnFlags & SEC_MOVE_RIGHT)
			right *= lrSize;
		else
			right *= (lrSize * -1);

		if (SpawnFlags & SEC_1ST_DOWN)
		{
			StartOrigin = State.GetOrigin() + forward;
			EndOrigin = StartOrigin + right;
		}
		else
		{
			StartOrigin = State.GetOrigin() + right;
			EndOrigin = StartOrigin + forward;
		}

		Link ();
	};
};

LINK_CLASSNAME_TO_CLASS ("func_door_secret2", CDoorSecret2);

CC_ENUM (uint8, EForceWallSpawnflags)
{
	FWALL_START_ON		=		BIT(0),
};

/*QUAKED func_force_wall (1 0 1) ? start_on
A vertical particle force wall. Turns on and solid when triggered.
If someone is in the force wall when it turns on, they're telefragged.

start_on - forcewall begins activated. triggering will turn it off.
style - color of particles to use.
	208: green, 240: red, 241: blue, 224: orange
*/
class CFuncForceWall : public IMapEntity, public IUsableEntity, public IBrushModel
{
public:
	vec3f		Start, End, SendOrigin;
	uint8		Style;
	bool		Telefrag;

	CFuncForceWall () :
	  IMapEntity (),
	  IUsableEntity (),
	  IBrushModel ()
	  {
	  };

	CFuncForceWall (sint32 Index) :
	  IBaseEntity (Index),
	  IMapEntity (Index),
	  IUsableEntity (Index),
	  IBrushModel (Index)
	  {
	  };

	ENTITYFIELD_DEFS
	ENTITYFIELDS_SAVABLE(CFuncForceWall)

	bool Run ()
	{
		return false;
	};

	void Use (IBaseEntity *Other, IBaseEntity *Activator)
	{
		if (!Telefrag)
		{
			Telefrag = 1;
			NextThink = 0;
			GetSolid() = SOLID_NOT;
			Link ();
		}
		else
		{
			Telefrag = false;
			NextThink = Level.Frame + FRAMETIME;
			GetSolid() = SOLID_BSP;
			KillBox();		// Is this appropriate?
			Link ();
		}
	};
	
	void Think ()
	{
		if (!Telefrag)
			CForceWall(Start, End, Style).Send();

		NextThink = Level.Frame + FRAMETIME;
	};

	void Spawn ()
	{
		SetBrushModel ();

		SendOrigin = (GetAbsMax() + GetAbsMin()) / 2;
		Start.Z = End.Z = GetAbsMax().Z;

		if (GetSize().X > GetSize().Y)
		{
			Start.X = GetAbsMin().X;
			End.X = GetAbsMax().X;
			Start.Y = End.Y = SendOrigin.Y;
		}
		else
		{
			Start.X = End.X = SendOrigin.X;
			Start.Y = GetAbsMin().Y;
			End.Y = GetAbsMax().Y;
		}
	
		if (!Style)
			Style = 208;

		PhysicsType = PHYSICS_NONE;
		Telefrag = true;

		if (SpawnFlags & FWALL_START_ON)
		{
			GetSolid() = SOLID_BSP;
			NextThink = Level.Frame + FRAMETIME;
		}
		else
			GetSolid() = SOLID_NOT;

		Usable = true;
		GetSvFlags() = SVF_NOCLIENT;
	
		Link ();
	};
};

ENTITYFIELDS_BEGIN(CFuncForceWall)
{
	CEntityField ("style",		EntityMemberOffset(CFuncForceWall,Style),			FT_BYTE | FT_SAVABLE),
		
	CEntityField ("Start",		EntityMemberOffset(CFuncForceWall,Start),			FT_VECTOR | FT_NOSPAWN | FT_SAVABLE),
	CEntityField ("End",		EntityMemberOffset(CFuncForceWall,End),				FT_VECTOR | FT_NOSPAWN | FT_SAVABLE),
	CEntityField ("SendOrigin",	EntityMemberOffset(CFuncForceWall,SendOrigin),		FT_VECTOR | FT_NOSPAWN | FT_SAVABLE),
	CEntityField ("Telefrag",	EntityMemberOffset(CFuncForceWall,Telefrag),		FT_BOOL | FT_NOSPAWN | FT_SAVABLE),
};
ENTITYFIELDS_END(CFuncForceWall)

bool			CFuncForceWall::ParseField (const char *Key, const char *Value)
{
	if (CheckFields<CFuncForceWall> (this, Key, Value))
		return true;

	// Couldn't find it here
	return (IMapEntity::ParseField(Key, Value) || IUsableEntity::ParseField(Key, Value) || IBrushModel::ParseField(Key, Value));
};

void			CFuncForceWall::SaveFields (CFile &File)
{
	SaveEntityFields <CFuncForceWall> (this, File);
	IMapEntity::SaveFields (File);
	IUsableEntity::SaveFields (File);
	IBrushModel::SaveFields (File);
}

void			CFuncForceWall::LoadFields (CFile &File)
{
	LoadEntityFields <CFuncForceWall> (this, File);
	IMapEntity::LoadFields (File);
	IUsableEntity::LoadFields (File);
	IBrushModel::LoadFields (File);
}

LINK_CLASSNAME_TO_CLASS ("func_force_wall", CFuncForceWall);

/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for lightning.
*/
class CInfoTeleportDestination : public IMapEntity
{
public:
	CInfoTeleportDestination (sint32 Index) :
	  IBaseEntity (Index),
	  IMapEntity (Index)
	  {
	  };

	IMPLEMENT_SAVE_HEADER(CInfoTeleportDestination)

	void Spawn ()
	{
	};
};

LINK_CLASSNAME_TO_CLASS ("info_teleport_destination", CInfoTeleportDestination);