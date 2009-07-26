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
// cc_boss2.cpp
// Biggun Protector
//

#include "cc_local.h"
#include "cc_boss2.h"
#include "m_boss2.h"

CBoss2::CBoss2 ()
{
	Scale = MODEL_SCALE;
};

void CBoss2::Search ()
{
	if (random() < 0.5)
		Entity->PlaySound (CHAN_VOICE, SoundSearch1, 1, ATTN_NONE, 0);
}

void CBoss2::FireRocket ()
{
	vec3f	forward, right;
	vec3f	start;

	Entity->State.GetAngles().ToVectors (&forward, &right, NULL);

//1
	vec3f origin = Entity->State.GetOrigin();

	G_ProjectSource (origin, dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_ROCKET_1], forward, right, start);
	vec3f vec = vec3f(Entity->gameEntity->enemy->state.origin);
	vec.Z += Entity->gameEntity->viewheight;
	vec3f dir = vec - start;
	dir.Normalize();
	MonsterFireRocket (start, dir, 50, 500, MZ2_BOSS2_ROCKET_1);

//2
	G_ProjectSource (origin, dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_ROCKET_2], forward, right, start);
	vec = vec3f(Entity->gameEntity->enemy->state.origin);
	vec.Z += Entity->gameEntity->viewheight;
	dir = vec - start;
	dir.Normalize();
	MonsterFireRocket (start, dir, 50, 500, MZ2_BOSS2_ROCKET_2);

//3
	G_ProjectSource (origin, dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_ROCKET_3], forward, right, start);
	vec = vec3f(Entity->gameEntity->enemy->state.origin);
	vec.Z += Entity->gameEntity->viewheight;
	dir = vec - start;
	dir.Normalize();
	MonsterFireRocket (start, dir, 50, 500, MZ2_BOSS2_ROCKET_3);

//4
	G_ProjectSource (origin, dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_ROCKET_4], forward, right, start);
	vec = vec3f(Entity->gameEntity->enemy->state.origin);
	vec.Z += Entity->gameEntity->viewheight;
	dir = vec - start;
	dir.Normalize();
	MonsterFireRocket (start, dir, 50, 500, MZ2_BOSS2_ROCKET_4);
}	

void CBoss2::FireBulletRight ()
{
	vec3f	forward, right, target;
	vec3f	start;

	Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
	G_ProjectSource (Entity->State.GetOrigin(), dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_MACHINEGUN_R1], forward, right, start);

	vec3_t tempTarget;
	Vec3MA (Entity->gameEntity->enemy->state.origin, -0.2f, Entity->gameEntity->enemy->velocity, tempTarget);
	target = vec3f(tempTarget);
	target.Z += Entity->gameEntity->enemy->viewheight;
	forward = target - start;
	forward.Normalize();

	MonsterFireBullet (start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, MZ2_BOSS2_MACHINEGUN_R1);
}	

void CBoss2::FireBulletLeft ()
{
	vec3f	forward, right, target;
	vec3f	start;

	Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
	G_ProjectSource (Entity->State.GetOrigin(), dumb_and_hacky_monster_MuzzFlashOffset[MZ2_BOSS2_MACHINEGUN_R1], forward, right, start);

	vec3_t tempTarget;
	Vec3MA (Entity->gameEntity->enemy->state.origin, -0.2f, Entity->gameEntity->enemy->velocity, tempTarget);
	target = vec3f(tempTarget);
	target.Z += Entity->gameEntity->enemy->viewheight;
	forward = target - start;
	forward.Normalize();

	MonsterFireBullet (start, forward, 6, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, MZ2_BOSS2_MACHINEGUN_L1);
}	

void CBoss2::MachineGun ()
{
	FireBulletLeft();
	FireBulletRight();
}	


CFrame Boss2FramesStand [] =
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
	CFrame (&CMonster::AI_Stand, 0)
};
CAnim Boss2MoveStand (FRAME_stand30, FRAME_stand50, Boss2FramesStand);

CFrame Boss2FramesFidget [] =
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
CAnim Boss2MoveFidget (FRAME_stand1, FRAME_stand30, Boss2FramesFidget);

CFrame Boss2FramesWalk [] =
{
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 8)
};
CAnim Boss2MoveWalk (FRAME_walk1, FRAME_walk20, Boss2FramesWalk);

CFrame Boss2FramesRun [] =
{
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8),
	CFrame (&CMonster::AI_Run, 8)
};
CAnim Boss2MoveRun (FRAME_walk1, FRAME_walk20, Boss2FramesRun);

CFrame Boss2FramesAttackPreMg [] =
{
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1, ConvertDerivedFunction(&CBoss2::AttackMg))
};
CAnim Boss2MoveAttackPreMg (FRAME_attack1, FRAME_attack9, Boss2FramesAttackPreMg);

// Loop this
CFrame Boss2FramesAttackMg [] =
{
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::MachineGun)),
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::MachineGun)),
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::MachineGun)),
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::MachineGun)),
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::MachineGun)),
	CFrame (&CMonster::AI_Charge, 1,	ConvertDerivedFunction(&CBoss2::ReAttackMg))
};
CAnim Boss2MoveAttackMg (FRAME_attack10, FRAME_attack15, Boss2FramesAttackMg);

CFrame Boss2FramesAttackPostMg [] =
{
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1)
};
CAnim Boss2MoveAttackPostMg (FRAME_attack16, FRAME_attack19, Boss2FramesAttackPostMg, &CMonster::Run);

CFrame Boss2FramesAttackRocket [] =
{
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Move, -20,	ConvertDerivedFunction(&CBoss2::FireRocket)),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 1)
};
CAnim Boss2MoveAttackRocket (FRAME_attack20, FRAME_attack40, Boss2FramesAttackRocket, &CMonster::Run);

CFrame Boss2FramesPainHeavy [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim Boss2MovePainHeavy (FRAME_pain2, FRAME_pain19, Boss2FramesPainHeavy, &CMonster::Run);

CFrame Boss2FramesPainLight [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim Boss2MovePainLight (FRAME_pain20, FRAME_pain23, Boss2FramesPainLight, &CMonster::Run);

CFrame Boss2FramesDeath [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0,	ConvertDerivedFunction(&CBoss2::Explode))
};
CAnim Boss2MoveDeath (FRAME_death2, FRAME_death50, Boss2FramesDeath, ConvertDerivedFunction(&CBoss2::Dead));

void CBoss2::Explode ()
{
	vec3_t	org;
	int		n;

	Think = ConvertDerivedFunction(&CBoss2::Explode);
	Entity->State.GetOrigin(org);
	org[2] += 24 + (rand()&15);
	switch (Entity->gameEntity->count++)
	{
	case 0:
		org[0] -= 24;
		org[1] -= 24;
		break;
	case 1:
		org[0] += 24;
		org[1] += 24;
		break;
	case 2:
		org[0] += 24;
		org[1] -= 24;
		break;
	case 3:
		org[0] -= 24;
		org[1] += 24;
		break;
	case 4:
		org[0] -= 48;
		org[1] -= 48;
		break;
	case 5:
		org[0] += 48;
		org[1] += 48;
		break;
	case 6:
		org[0] -= 48;
		org[1] += 48;
		break;
	case 7:
		org[0] += 48;
		org[1] -= 48;
		break;
	case 8:
		Entity->State.SetSound (0);
		for (n= 0; n < 4; n++)
			CGibEntity::Spawn (Entity, gMedia.Gib_SmallMeat, 500, GIB_ORGANIC);
		for (n= 0; n < 8; n++)
			CGibEntity::Spawn (Entity, gMedia.Gib_SmallMetal, 500, GIB_METALLIC);
		CGibEntity::Spawn (Entity, gMedia.Gib_Chest, 500, GIB_ORGANIC);
		Entity->ThrowHead (gMedia.Gib_Gear, 500, GIB_METALLIC);
		Entity->gameEntity->deadflag = DEAD_DEAD;
		return;
	}

	CTempEnt_Explosions::RocketExplosion (org, Entity->gameEntity);

	Entity->NextThink = level.framenum + FRAMETIME;
}


void CBoss2::Stand ()
{
	CurrentMove = &Boss2MoveStand;
}

void CBoss2::Run ()
{
	if (AIFlags & AI_STAND_GROUND)
		CurrentMove = &Boss2MoveStand;
	else
		CurrentMove = &Boss2MoveRun;
}

void CBoss2::Walk ()
{
	CurrentMove = &Boss2MoveWalk;
}

void CBoss2::Attack ()
{
	CurrentMove = ((vec3f(Entity->gameEntity->enemy->state.origin) - Entity->State.GetOrigin()).Length() <= 125) ?
		&Boss2MoveAttackPreMg : ((random() <= 0.6) ? &Boss2MoveAttackPreMg : &Boss2MoveAttackRocket);
}

void CBoss2::AttackMg ()
{
	CurrentMove = &Boss2MoveAttackMg;
}

void CBoss2::ReAttackMg ()
{
	CurrentMove = (infront(Entity->gameEntity, Entity->gameEntity->enemy)) ?
		((random() <= 0.7) ? &Boss2MoveAttackMg : &Boss2MoveAttackPostMg) : &Boss2MoveAttackPostMg;
}

void CBoss2::Pain (CBaseEntity *other, float kick, int damage)
{
	if (Entity->gameEntity->health < (Entity->gameEntity->max_health / 2))
		Entity->State.SetSkinNum(1);

	if (level.framenum < Entity->gameEntity->pain_debounce_time)
		return;

	Entity->gameEntity->pain_debounce_time = level.framenum + 30;

// American wanted these at no attenuation
	Entity->PlaySound (CHAN_VOICE, (damage < 10) ? SoundPain3 : ((damage < 30) ? SoundPain1 : SoundPain2), 1, ATTN_NONE, 0);
	CurrentMove = (damage < 30) ? &Boss2MovePainLight : &Boss2MovePainHeavy;
}

void CBoss2::Dead ()
{
	Entity->SetMins (vec3f(-56, -56, 0));
	Entity->SetMaxs (vec3f(56, 56, 80));
	Entity->TossPhysics = true;
	Entity->PhysicsType = PHYSICS_TOSS;
	Entity->SetSvFlags (Entity->GetSvFlags() | SVF_DEADMONSTER);
	Entity->NextThink = 0;
	Entity->Link ();
}

void CBoss2::Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point)
{
	Entity->PlaySound (CHAN_VOICE, SoundDeath, 1, ATTN_NONE, 0);
	Entity->gameEntity->deadflag = DEAD_DEAD;
	Entity->gameEntity->takedamage = false;
	Entity->gameEntity->count = 0;
	CurrentMove = &Boss2MoveDeath;
}

bool CBoss2::CheckAttack ()
{
	vec3f	spot1, spot2;
	vec3f	temp;
	float	chance;
	CTrace	tr;
	bool	enemy_infront;
	int		enemy_range;
	float	enemy_yaw;

	if (Entity->gameEntity->enemy->health > 0)
	{
	// see if any entities are in the way of the shot
		spot1 = Entity->State.GetOrigin();
		spot1.Z += Entity->gameEntity->viewheight;
		spot2 = vec3f (Entity->gameEntity->enemy->state.origin);
		spot2.Z += Entity->gameEntity->enemy->viewheight;

		tr = CTrace (spot1, spot2, Entity->gameEntity, CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_SLIME|CONTENTS_LAVA);

		// do we have a clear shot?
		if (tr.ent != Entity->gameEntity->enemy)
			return false;
	}
	
	enemy_infront = infront(Entity->gameEntity, Entity->gameEntity->enemy);
	enemy_range = range(Entity->gameEntity, Entity->gameEntity->enemy);
	temp = vec3f (Entity->gameEntity->enemy->state.origin) - Entity->State.GetOrigin();
	enemy_yaw = temp.ToYaw();

	IdealYaw = enemy_yaw;

	// melee attack
	if (enemy_range == RANGE_MELEE)
	{
		AttackState = AS_MISSILE;
		return true;
	}
	
// missile attack
	if (level.framenum < AttackFinished)
		return false;
		
	if (enemy_range == RANGE_FAR)
		return false;

	if (AIFlags & AI_STAND_GROUND)
		chance = 0.4f;
	else if (enemy_range == RANGE_MELEE)
		chance = 0.8f;
	else if (enemy_range == RANGE_NEAR)
		chance = 0.8f;
	else if (enemy_range == RANGE_MID)
		chance = 0.8f;
	else
		return false;

	if (random () < chance)
	{
		AttackState = AS_MISSILE;
		AttackFinished = level.framenum + (2*random())*10;
		return true;
	}

	AttackState = (random() < 0.3) ? AS_SLIDING : AS_STRAIGHT;
	return false;
}

/*QUAKED monster_boss2 (1 .5 0) (-56 -56 0) (56 56 80) Ambush Trigger_Spawn Sight
*/
void CBoss2::Spawn ()
{
	SoundPain1 = SoundIndex ("bosshovr/bhvpain1.wav");
	SoundPain2 = SoundIndex ("bosshovr/bhvpain2.wav");
	SoundPain3 = SoundIndex ("bosshovr/bhvpain3.wav");
	SoundDeath = SoundIndex ("bosshovr/bhvdeth1.wav");
	SoundSearch1 = SoundIndex ("bosshovr/bhvunqv1.wav");

	Entity->State.SetSound(SoundIndex ("bosshovr/bhvengn1.wav"));

	Entity->SetSolid(SOLID_BBOX);
	Entity->State.SetModelIndex(ModelIndex ("models/monsters/boss2/tris.md2"));
	Entity->SetMins (vec3f(-56, -56, 0));
	Entity->SetMaxs (vec3f(56, 56, 80));

	Entity->gameEntity->health = 2000;
	Entity->gameEntity->gib_health = -200;
	Entity->gameEntity->mass = 1000;

	Entity->gameEntity->flags |= FL_IMMUNE_LASER;
	
	MonsterFlags |= (MF_HAS_ATTACK | MF_HAS_SEARCH);
	Entity->Link ();

	CurrentMove = &Boss2MoveStand;

	FlyMonsterStart ();
}

LINK_MONSTER_CLASSNAME_TO_CLASS ("monster_boss2", CBoss2);