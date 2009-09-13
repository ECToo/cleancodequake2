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
// cc_infantry.cpp
// Infantry Monster
//

#include "cc_local.h"
#include "m_infantry.h"
#include "cc_infantry.h"

CInfantry::CInfantry ()
{
	Scale = MODEL_SCALE;
}

CFrame InfantryFramesStand [] =
{
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0)
};
CAnim InfantryMoveStand (FRAME_stand50, FRAME_stand71, InfantryFramesStand);

void CInfantry::Stand ()
{
	CurrentMove = &InfantryMoveStand;
}

CFrame InfantryFramesFidget [] =
{
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 3),
	CFrame (&CMonster::AI_Stand, 6),
	CFrame (&CMonster::AI_Stand, 3),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -2),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, -1),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, -3),
	CFrame (&CMonster::AI_Stand, -2),
	CFrame (&CMonster::AI_Stand, -3),
	CFrame (&CMonster::AI_Stand, -3),
	CFrame (&CMonster::AI_Stand, -2)
};
CAnim InfantryMoveFidget (FRAME_stand01, FRAME_stand49, InfantryFramesFidget, &CMonster::Stand);

void CInfantry::Idle ()
{
	CurrentMove = &InfantryMoveFidget;
	Entity->PlaySound (CHAN_VOICE, SoundIdle, 1, ATTN_IDLE, 0);
}

CFrame InfantryFramesWalk [] =
{
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 6),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 5)
};
CAnim InfantryMoveWalk (FRAME_walk03, FRAME_walk14, InfantryFramesWalk);

void CInfantry::Walk ()
{
	CurrentMove = &InfantryMoveWalk;
}

CFrame InfantryFramesRun [] =
{
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 20),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 7),
	CFrame (&CMonster::AI_Run, 30),
	CFrame (&CMonster::AI_Run, 35),
	CFrame (&CMonster::AI_Run, 2),
	CFrame (&CMonster::AI_Run, 6)
};
CAnim InfantryMoveRun (FRAME_run01, FRAME_run08, InfantryFramesRun);

void CInfantry::Run ()
{
	// FIXME: handle this elsewhere
	if (AIFlags & AI_STAND_GROUND)
		CurrentMove = &InfantryMoveStand;
	else
		CurrentMove = &InfantryMoveRun;
}

CFrame InfantryFramesPain1 [] =
{
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 6),
	CFrame (&CMonster::AI_Move, 2)
};
CAnim InfantryMovePain1 (FRAME_pain101, FRAME_pain110, InfantryFramesPain1, ConvertDerivedFunction(&CInfantry::Run));

CFrame InfantryFramesPain2 [] =
{
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 5),
	CFrame (&CMonster::AI_Move, 2)
};
CAnim InfantryMovePain2 (FRAME_pain201, FRAME_pain210, InfantryFramesPain2, ConvertDerivedFunction(&CInfantry::Run));

void CInfantry::Pain (CBaseEntity *other, float kick, int damage)
{
	if (Entity->gameEntity->health < (Entity->gameEntity->max_health / 2))
		Entity->State.SetSkinNum(1);

#ifdef MONSTER_USE_ROGUE_AI
	DoneDodge();
#endif

	if (level.framenum < Entity->gameEntity->pain_debounce_time)
		return;

	Entity->gameEntity->pain_debounce_time = level.framenum + 30;
	
	if (skill->Integer() == 3)
		return;		// no pain anims in nightmare

	CurrentMove = (!irandom(2)) ? &InfantryMovePain1 : &InfantryMovePain2;
	Entity->PlaySound (CHAN_VOICE, (!irandom(2)) ? SoundPain1 : SoundPain2);

#ifdef MONSTER_USE_ROGUE_AI
	// PMM - clear duck flag
	if (AIFlags & AI_DUCKED)
		UnDuck();
#endif
}

static const vec3f	DeathAimAngles[] =
{
	vec3f(0.0, 5.0, 0.0),
	vec3f(10.0, 15.0, 0.0),
	vec3f(20.0, 25.0, 0.0),
	vec3f(25.0, 35.0, 0.0),
	vec3f(30.0, 40.0, 0.0),
	vec3f(30.0, 45.0, 0.0),
	vec3f(25.0, 50.0, 0.0),
	vec3f(20.0, 40.0, 0.0),
	vec3f(15.0, 35.0, 0.0),
	vec3f(40.0, 35.0, 0.0),
	vec3f(70.0, 35.0, 0.0),
	vec3f(90.0, 35.0, 0.0)
};

void CInfantry::MachineGun ()
{
	vec3f	start, forward, right;
	int		flash_number;

	if (Entity->State.GetFrame() == FRAME_attak111)
	{
		flash_number = MZ2_INFANTRY_MACHINEGUN_1;
		Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
		G_ProjectSource (Entity->State.GetOrigin(), dumb_and_hacky_monster_MuzzFlashOffset[flash_number], forward, right, start);

		if (Entity->gameEntity->enemy)
		{
			vec3f target = Entity->gameEntity->enemy->state.origin;
			target = target.MultiplyAngles (-0.2f, Entity->gameEntity->enemy->velocity);
			target.Z += Entity->gameEntity->enemy->viewheight;

			forward = target - start;
			forward.NormalizeFast ();
		}
		else
			Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
	}
	else
	{
		flash_number = MZ2_INFANTRY_MACHINEGUN_2 + (Entity->State.GetFrame() - FRAME_death211);

		Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
		G_ProjectSource (Entity->State.GetOrigin(), dumb_and_hacky_monster_MuzzFlashOffset[flash_number], forward, right, start);

		(Entity->State.GetAngles() - DeathAimAngles[flash_number-MZ2_INFANTRY_MACHINEGUN_2]).ToVectors (&forward, NULL, NULL);
	}

	MonsterFireBullet (start, forward, 3, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}

void CInfantry::Sight ()
{
	Entity->PlaySound (CHAN_BODY, SoundSight);
}

void CInfantry::Dead ()
{
	Entity->SetMins (vec3f(-16, -16, -24));
	Entity->SetMaxs (vec3f(16, 16, -8));
	Entity->PhysicsType = PHYSICS_TOSS;
	Entity->SetSvFlags (Entity->GetSvFlags() | SVF_DEADMONSTER);
	Entity->Link ();

	// FIXME: BAD
	CheckFlies ();
}

CFrame InfantryFramesDeath1 [] =
{
	CFrame (&CMonster::AI_Move, -4),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -4),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 9),
	CFrame (&CMonster::AI_Move, 9),
	CFrame (&CMonster::AI_Move, 5),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -3)
};
CAnim InfantryMoveDeath1 (FRAME_death101, FRAME_death120, InfantryFramesDeath1, ConvertDerivedFunction(&CInfantry::Dead));

// Off with his head
CFrame InfantryFramesDeath2 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 5),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -2,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -2,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -3,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -1,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -2,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, 0,   ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, 2,   ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, 2,   ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, 3,   ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -10, ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -7,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -8,  ConvertDerivedFunction(&CInfantry::MachineGun)),
	CFrame (&CMonster::AI_Move, -6),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim InfantryMoveDeath2 (FRAME_death201, FRAME_death225, InfantryFramesDeath2, ConvertDerivedFunction(&CInfantry::Dead));

CFrame InfantryFramesDeath3 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -6),
	CFrame (&CMonster::AI_Move, -11),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -11),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim InfantryMoveDeath3 (FRAME_death301, FRAME_death309, InfantryFramesDeath3, ConvertDerivedFunction(&CInfantry::Dead));


void CInfantry::Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3f &point)
{
// check for gib
	if (Entity->gameEntity->health <= Entity->gameEntity->gib_health)
	{
		Entity->PlaySound (CHAN_VOICE, SoundIndex ("misc/udeath.wav"));
		for (int n= 0; n < 2; n++)
			CGibEntity::Spawn (Entity, gMedia.Gib_Bone[0], damage, GIB_ORGANIC);
		for (int n= 0; n < 4; n++)
			CGibEntity::Spawn (Entity, gMedia.Gib_SmallMeat, damage, GIB_ORGANIC);
		Entity->ThrowHead (gMedia.Gib_Head[1], damage, GIB_ORGANIC);
		Entity->DeadFlag = true;
		return;
	}

	if (Entity->DeadFlag == true)
		return;

// regular death
	Entity->DeadFlag = true;
	Entity->CanTakeDamage = true;

	CAnim *Animation;
	int pSound;
	switch (irandom(3))
	{
	case 0:
	default:
		Animation = &InfantryMoveDeath1;
		pSound = SoundDie2;
		break;
	case 1:
		Animation = &InfantryMoveDeath2;
		pSound = SoundDie1;
		break;
	case 2:
		Animation = &InfantryMoveDeath3;
		pSound = SoundDie2;
		break;
	}
	CurrentMove = Animation;
	Entity->PlaySound (CHAN_VOICE, pSound);
}

#ifndef MONSTER_USE_ROGUE_AI
void CInfantry::Duck_Down ()
{
	if (AIFlags & AI_DUCKED)
		return;
	AIFlags |= AI_DUCKED;
	vec3f maxs = Entity->GetMaxs();
	maxs.Z -= 32;
	Entity->SetMaxs (maxs);
	Entity->CanTakeDamage = true;
	PauseTime = level.framenum + 10;
	Entity->Link ();
}

void CInfantry::Duck_Hold ()
{
	if (level.framenum >= PauseTime)
		AIFlags &= ~AI_HOLD_FRAME;
	else
		AIFlags |= AI_HOLD_FRAME;
}

void CInfantry::Duck_Up ()
{
	AIFlags &= ~AI_DUCKED;
	vec3f maxs = Entity->GetMaxs();
	maxs.Z += 32;
	Entity->SetMaxs (maxs);
	Entity->CanTakeDamage = true;
	Entity->Link ();
}
#endif

CFrame InfantryFramesDuck [] =
{
#ifndef MONSTER_USE_ROGUE_AI
	CFrame (&CMonster::AI_Move, -2, ConvertDerivedFunction(&CInfantry::Duck_Down)),
	CFrame (&CMonster::AI_Move, -5, ConvertDerivedFunction(&CInfantry::Duck_Hold)),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 4, ConvertDerivedFunction(&CInfantry::Duck_Up)),
	CFrame (&CMonster::AI_Move, 0)
#else
	CFrame (&CMonster::AI_Move, -2, &CMonster::DuckDown),
	CFrame (&CMonster::AI_Move, -5, &CMonster::DuckHold),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 4, &CMonster::UnDuck),
	CFrame (&CMonster::AI_Move, 0)
#endif
};
CAnim InfantryMoveDuck (FRAME_duck01, FRAME_duck05, InfantryFramesDuck, ConvertDerivedFunction(&CInfantry::Run));

#ifndef MONSTER_USE_ROGUE_AI
void CInfantry::Dodge (CBaseEntity *attacker, float eta)
{
	if (random() > 0.25)
		return;

	if (!Entity->gameEntity->enemy)
		Entity->gameEntity->enemy = attacker->gameEntity;

	CurrentMove = &InfantryMoveDuck;
}
#endif

void CInfantry::CockGun ()
{
	Entity->PlaySound (CHAN_WEAPON, SoundWeaponCock);
}

void CInfantry::Fire ()
{
	MachineGun ();

	if (level.framenum >= PauseTime)
		AIFlags &= ~AI_HOLD_FRAME;
	else
		AIFlags |= AI_HOLD_FRAME;
}

#ifndef INFANTRY_DOES_REVERSE_GUN_ATTACK
CFrame InfantryFramesAttack1 [] =
{
	CFrame (&CMonster::AI_Charge, 4),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CInfantry::CockGun)),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 2),
	CFrame (&CMonster::AI_Charge, -2),
	CFrame (&CMonster::AI_Charge, -3),
	CFrame (&CMonster::AI_Charge, 1, ConvertDerivedFunction(&CInfantry::Fire)),
	CFrame (&CMonster::AI_Charge, 5),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -2),
	CFrame (&CMonster::AI_Charge, -3)
};
CAnim InfantryMoveAttack1 (FRAME_attak101, FRAME_attak115, InfantryFramesAttack1, ConvertDerivedFunction(&CInfantry::Run));
#else
CFrame InfantryFramesAttack1 [] =
{
	//CFrame (&CMonster::AI_Charge, -3),
	//CFrame (&CMonster::AI_Charge, -2),
	//CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 5),
	CFrame (&CMonster::AI_Charge, 1, ConvertDerivedFunction(&CInfantry::Fire)),
	CFrame (&CMonster::AI_Charge, -3),
	CFrame (&CMonster::AI_Charge, -2),
	CFrame (&CMonster::AI_Charge, 2),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, -1, ConvertDerivedFunction(&CInfantry::CockGun)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 4)
};
CAnim InfantryMoveAttack1 (FRAME_attak112, FRAME_attak101, InfantryFramesAttack1, ConvertDerivedFunction(&CInfantry::Run));
#endif


void CInfantry::Swing ()
{
	Entity->PlaySound (CHAN_WEAPON, SoundPunchSwing);
}

void CInfantry::Smack ()
{
	static vec3f	aim (MELEE_DISTANCE, 0, 0);
	if (CMeleeWeapon::Fire (Entity, aim, (5 + (irandom(5))), 50))
		Entity->PlaySound (CHAN_WEAPON, SoundPunchHit);
}

CFrame InfantryFramesAttack2 [] =
{
	CFrame (&CMonster::AI_Charge, 3),
	CFrame (&CMonster::AI_Charge, 6),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CInfantry::Swing)),
	CFrame (&CMonster::AI_Charge, 8),
	CFrame (&CMonster::AI_Charge, 5),
	CFrame (&CMonster::AI_Charge, 8, ConvertDerivedFunction(&CInfantry::Smack)),
	CFrame (&CMonster::AI_Charge, 6),
	CFrame (&CMonster::AI_Charge, 3),
};
CAnim InfantryMoveAttack2 (FRAME_attak201, FRAME_attak208, InfantryFramesAttack2, ConvertDerivedFunction(&CInfantry::Run));

void CInfantry::Attack ()
{
	PauseTime = level.framenum + ((randomMT() & 15) + 11);
	CurrentMove = &InfantryMoveAttack1;
}

void CInfantry::Melee ()
{
	CurrentMove = &InfantryMoveAttack2;
}

#ifdef MONSTER_USE_ROGUE_AI
void CInfantry::Duck (float eta)
{
	if ((CurrentMove == &InfantryMoveAttack1) ||
		(CurrentMove == &InfantryMoveAttack2))
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->Integer())
		{
			AIFlags &= ~AI_DUCKED;
			return;
		}
	}

	if (skill->Integer() == 0)
		// PMM - stupid dodge
		DuckWaitTime = level.framenum + ((eta + 1) * 10);
	else
		DuckWaitTime = level.framenum + ((eta + (0.1 * (3 - skill->Integer()))) * 10);

	// has to be done immediately otherwise he can get stuck
	DuckDown();

	NextFrame = FRAME_duck01;
	CurrentMove = &InfantryMoveDuck;
}

void CInfantry::SideStep ()
{
	if ((CurrentMove == &InfantryMoveAttack1) ||
		(CurrentMove == &InfantryMoveAttack2))
	{
		// if we're shooting, and not on easy, don't dodge
		if (skill->Integer())
		{
			AIFlags &= ~AI_DODGING;
			return;
		}
	}

	if (CurrentMove != &InfantryMoveRun)
		CurrentMove = &InfantryMoveRun;
}
#endif

void CInfantry::Spawn ()
{
	Entity->SetSolid (SOLID_BBOX);
	Entity->State.SetModelIndex ( ModelIndex("models/monsters/infantry/tris.md2"));
	Entity->SetMins (vec3f(-16, -16, -24));
	Entity->SetMaxs (vec3f(16, 16, 32));

	SoundPain1 = SoundIndex ("infantry/infpain1.wav");
	SoundPain2 = SoundIndex ("infantry/infpain2.wav");
	SoundDie1 = SoundIndex ("infantry/infdeth1.wav");
	SoundDie2 = SoundIndex ("infantry/infdeth2.wav");

	SoundGunshot = SoundIndex ("infantry/infatck1.wav");
	SoundWeaponCock = SoundIndex ("infantry/infatck3.wav");
	SoundPunchSwing = SoundIndex ("infantry/infatck2.wav");
	SoundPunchHit = SoundIndex ("infantry/melee2.wav");
	
	SoundSight = SoundIndex ("infantry/infsght1.wav");
	SoundSearch = SoundIndex ("infantry/infsrch1.wav");
	SoundIdle = SoundIndex ("infantry/infidle1.wav");

	Entity->gameEntity->health = 100;
	Entity->gameEntity->gib_health = -40;
	Entity->gameEntity->mass = 200;

	MonsterFlags = (MF_HAS_MELEE | MF_HAS_ATTACK | MF_HAS_IDLE | MF_HAS_SIGHT
#ifdef MONSTER_USE_ROGUE_AI
		| MF_HAS_SIDESTEP | MF_HAS_DUCK | MF_HAS_UNDUCK | MF_HAS_DODGE
#endif
		);

	Entity->Link ();

	CurrentMove = &InfantryMoveStand;
	WalkMonsterStart ();
}

LINK_MONSTER_CLASSNAME_TO_CLASS ("monster_infantry", CInfantry);