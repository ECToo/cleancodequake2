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
// cc_berserk.cpp
// Berserker
//

#include "cc_local.h"
#include "cc_berserk.h"
#include "m_berserk.h"

CBerserker::CBerserker ()
{
	Scale = MODEL_SCALE;
}

void CBerserker::Sight ()
{
	Entity->PlaySound (CHAN_VOICE, SoundSight, 1, ATTN_NORM, 0);
}

void CBerserker::Search ()
{
	Entity->PlaySound (CHAN_VOICE, SoundSearch, 1, ATTN_NORM, 0);
}


CFrame BerserkFramesStand [] =
{
	CFrame (&CMonster::AI_Stand, 0, ConvertDerivedFunction(&CBerserker::Fidget)),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0),
	CFrame (&CMonster::AI_Stand, 0)
};
CAnim BerserkMoveStand (FRAME_stand1, FRAME_stand5, BerserkFramesStand);

void CBerserker::Stand ()
{
	CurrentMove = &BerserkMoveStand;
}

CFrame BerserkFramesStandFidget [] =
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
	CFrame (&CMonster::AI_Stand, 0)
};
CAnim BerserkMoveStandFidget (FRAME_standb1, FRAME_standb20, BerserkFramesStandFidget, &CMonster::Stand);

void CBerserker::Fidget ()
{
	if (AIFlags & AI_STAND_GROUND)
		return;
	if (random() > 0.15)
		return;

	CurrentMove = &BerserkMoveStandFidget;
	Entity->PlaySound (CHAN_WEAPON, SoundIdle, 1, ATTN_IDLE, 0);
}


CFrame BerserkFramesWalk [] =
{
	CFrame (&CMonster::AI_Walk, 9.1f),
	CFrame (&CMonster::AI_Walk, 6.3f),
	CFrame (&CMonster::AI_Walk, 4.9f),
	CFrame (&CMonster::AI_Walk, 6.7f),
	CFrame (&CMonster::AI_Walk, 6.0f),
	CFrame (&CMonster::AI_Walk, 8.2f),
	CFrame (&CMonster::AI_Walk, 7.2f),
	CFrame (&CMonster::AI_Walk, 6.1f),
	CFrame (&CMonster::AI_Walk, 4.9f),
	CFrame (&CMonster::AI_Walk, 4.7f),
	CFrame (&CMonster::AI_Walk, 4.7f),
	CFrame (&CMonster::AI_Walk, 4.8f)
};
CAnim BerserkMoveWalk (FRAME_walkc1, FRAME_walkc11, BerserkFramesWalk);

void CBerserker::Walk ()
{
	CurrentMove = &BerserkMoveWalk;
}

/*

  *****************************
  SKIPPED THIS FOR NOW!
  *****************************

   Running -> Arm raised in air

void()	berserk_runb1	=[	$r_att1 ,	berserk_runb2	] {ai_run(21);};
void()	berserk_runb2	=[	$r_att2 ,	berserk_runb3	] {ai_run(11);};
void()	berserk_runb3	=[	$r_att3 ,	berserk_runb4	] {ai_run(21);};
void()	berserk_runb4	=[	$r_att4 ,	berserk_runb5	] {ai_run(25);};
void()	berserk_runb5	=[	$r_att5 ,	berserk_runb6	] {ai_run(18);};
void()	berserk_runb6	=[	$r_att6 ,	berserk_runb7	] {ai_run(19);};
// running with arm in air : start loop
void()	berserk_runb7	=[	$r_att7 ,	berserk_runb8	] {ai_run(21);};
void()	berserk_runb8	=[	$r_att8 ,	berserk_runb9	] {ai_run(11);};
void()	berserk_runb9	=[	$r_att9 ,	berserk_runb10	] {ai_run(21);};
void()	berserk_runb10	=[	$r_att10 ,	berserk_runb11	] {ai_run(25);};
void()	berserk_runb11	=[	$r_att11 ,	berserk_runb12	] {ai_run(18);};
void()	berserk_runb12	=[	$r_att12 ,	berserk_runb7	] {ai_run(19);};
// running with arm in air : end loop
*/

CFrame BerserkFramesRun1 [] =
{
	CFrame (&CMonster::AI_Run, 21),
	CFrame (&CMonster::AI_Run, 11),
	CFrame (&CMonster::AI_Run, 21),
	CFrame (&CMonster::AI_Run, 25),
	CFrame (&CMonster::AI_Run, 18),
	CFrame (&CMonster::AI_Run, 19)
};
CAnim BerserkMoveRun1 (FRAME_run1, FRAME_run6, BerserkFramesRun1);

void CBerserker::Run ()
{
	CurrentMove = (AIFlags & AI_STAND_GROUND) ? &BerserkMoveStand : &BerserkMoveRun1;
}

void CBerserker::AttackSpike ()
{
	static	vec3f	aim (MELEE_DISTANCE, 0, -24);
	CMeleeWeapon::Fire (Entity, aim, (15 + (rand() % 6)), 400);		//	Faster attack -- upwards and backwards
}

void CBerserker::Swing ()
{
	Entity->PlaySound (CHAN_WEAPON, SoundPunch, 1, ATTN_NORM, 0);
}

CFrame BerserkFramesAttackSpike [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CBerserker::Swing)),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CBerserker::AttackSpike)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim BerserkMoveAttackSpike (FRAME_att_c1, FRAME_att_c8, BerserkFramesAttackSpike, &CMonster::Run);

void CBerserker::AttackClub ()
{
	vec3f	aim (MELEE_DISTANCE, Entity->GetMins().X, -4);
	CMeleeWeapon::Fire (Entity, aim, (5 + (rand() % 6)), 400);		// Slower attack
}

CFrame BerserkFramesAttackClub [] =
{	
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CBerserker::Swing)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CBerserker::AttackClub)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim BerserkMoveAttackClub (FRAME_att_c9, FRAME_att_c20, BerserkFramesAttackClub, &CMonster::Run);

#if 0
void berserk_strike (edict_t *self)
{
	//FIXME play impact sound
}


mframe_t berserk_frames_attack_strike [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0, berserk_swing,
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0, berserk_strike,
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 9.7f),
	CFrame (&CMonster::AI_Move, 13.6f, NULL
};
	
mmove_t berserk_move_attack_strike = {FRAME_att_c21, FRAME_att_c34, berserk_frames_attack_strike, berserk_run};
#endif


void CBerserker::Melee ()
{
	CurrentMove = ((rand() % 2) == 0) ? &BerserkMoveAttackSpike : &BerserkMoveAttackClub;
}


/*
void() 	berserk_atke1	=[	$r_attb1,	berserk_atke2	] {ai_run(9);};
void() 	berserk_atke2	=[	$r_attb2,	berserk_atke3	] {ai_run(6);};
void() 	berserk_atke3	=[	$r_attb3,	berserk_atke4	] {ai_run(18.4);};
void() 	berserk_atke4	=[	$r_attb4,	berserk_atke5	] {ai_run(25);};
void() 	berserk_atke5	=[	$r_attb5,	berserk_atke6	] {ai_run(14);};
void() 	berserk_atke6	=[	$r_attb6,	berserk_atke7	] {ai_run(20);};
void() 	berserk_atke7	=[	$r_attb7,	berserk_atke8	] {ai_run(8.5);};
void() 	berserk_atke8	=[	$r_attb8,	berserk_atke9	] {ai_run(3);};
void() 	berserk_atke9	=[	$r_attb9,	berserk_atke10	] {ai_run(17.5);};
void() 	berserk_atke10	=[	$r_attb10,	berserk_atke11	] {ai_run(17);};
void() 	berserk_atke11	=[	$r_attb11,	berserk_atke12	] {ai_run(9);};
void() 	berserk_atke12	=[	$r_attb12,	berserk_atke13	] {ai_run(25);};
void() 	berserk_atke13	=[	$r_attb13,	berserk_atke14	] {ai_run(3.7);};
void() 	berserk_atke14	=[	$r_attb14,	berserk_atke15	] {ai_run(2.6);};
void() 	berserk_atke15	=[	$r_attb15,	berserk_atke16	] {ai_run(19);};
void() 	berserk_atke16	=[	$r_attb16,	berserk_atke17	] {ai_run(25);};
void() 	berserk_atke17	=[	$r_attb17,	berserk_atke18	] {ai_run(19.6);};
void() 	berserk_atke18	=[	$r_attb18,	berserk_run1	] {ai_run(7.8);};
*/

CFrame BerserkFramesPain1 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim BerserkMovePain1 (FRAME_painc1, FRAME_painc4, BerserkFramesPain1, &CMonster::Run);

CFrame BerserkFramesPain2 [] =
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
	CFrame (&CMonster::AI_Move, 0)
};
CAnim BerserkMovePain2 (FRAME_painb1, FRAME_painb20, BerserkFramesPain2, &CMonster::Run);

void CBerserker::Pain (CBaseEntity *other, float kick, int damage)
{
	if (Entity->gameEntity->health < (Entity->gameEntity->max_health / 2))
		Entity->State.SetSkinNum(1);

	if (level.framenum < Entity->gameEntity->pain_debounce_time)
		return;

	Entity->gameEntity->pain_debounce_time = level.framenum + 30;
	Entity->PlaySound (CHAN_VOICE, SoundPain, 1, ATTN_NORM, 0);

	if (skill->Integer() == 3)
		return;		// no pain anims in nightmare

	CurrentMove = ((damage < 20) || (random() < 0.5)) ? &BerserkMovePain1 : &BerserkMovePain2;
}

void CBerserker::Dead ()
{
	Entity->SetMins (vec3f(-16, -16, -24));
	Entity->SetMaxs (vec3f(16, 16, -8));

	Entity->PhysicsType = PHYSICS_TOSS;
	Entity->SetSvFlags (Entity->GetSvFlags() | SVF_DEADMONSTER);
	Entity->Link ();

	Entity->NextThink = 0;
}

CFrame BerserkFramesDeath1 [] =
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
	CFrame (&CMonster::AI_Move, 0)
};
CAnim BerserkMoveDeath1 (FRAME_death1, FRAME_death13, BerserkFramesDeath1, ConvertDerivedFunction(&CBerserker::Dead));

CFrame BerserkFramesDeath2 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim BerserkMoveDeath2 (FRAME_deathc1, FRAME_deathc8, BerserkFramesDeath2, ConvertDerivedFunction(&CBerserker::Dead));

void CBerserker::Die(CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point)
{
	if (Entity->gameEntity->health <= Entity->gameEntity->gib_health)
	{
		Entity->PlaySound (CHAN_VOICE, SoundIndex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
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

	Entity->PlaySound (CHAN_VOICE, SoundDie, 1, ATTN_NORM, 0);
	Entity->DeadFlag = true;
	Entity->CanTakeDamage = true;

	CurrentMove = (damage >= 50) ? &BerserkMoveDeath1 : &BerserkMoveDeath2;
}

#ifdef MONSTER_USE_ROGUE_AI
void CBerserker::SideStep ()
{
	// don't check for attack; the eta should suffice for melee monsters
	if (CurrentMove != &BerserkMoveRun1)
		CurrentMove = &BerserkMoveRun1;
}
#endif

/*QUAKED monster_berserk (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void CBerserker::Spawn ()
{
	// pre-caches
	SoundPain  = SoundIndex ("berserk/berpain2.wav");
	SoundDie   = SoundIndex ("berserk/berdeth2.wav");
	SoundIdle  = SoundIndex ("berserk/beridle1.wav");
	SoundPunch = SoundIndex ("berserk/attack.wav");
	SoundSearch = SoundIndex ("berserk/bersrch1.wav");
	SoundSight = SoundIndex ("berserk/sight.wav");

	Entity->State.SetModelIndex (ModelIndex("models/monsters/berserk/tris.md2"));
	Entity->SetMins (vec3f(-16, -16, -24));
	Entity->SetMaxs (vec3f(16, 16, 32));
	Entity->SetSolid (SOLID_BBOX);

	Entity->gameEntity->health = 240;
	Entity->gameEntity->gib_health = -60;
	Entity->gameEntity->mass = 250;

	MonsterFlags = (MF_HAS_MELEE | MF_HAS_SEARCH | MF_HAS_SIGHT
#ifdef MONSTER_USE_ROGUE_AI
		| MF_HAS_SIDESTEP
#endif
		);

	CurrentMove = &BerserkMoveStand;

	Entity->Link ();
	WalkMonsterStart ();
}

LINK_MONSTER_CLASSNAME_TO_CLASS ("monster_berserk", CBerserker);