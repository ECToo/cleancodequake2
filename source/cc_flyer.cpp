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
// cc_flyer.cpp
// Flyer Monster
//

#include "cc_local.h"
#include "m_flyer.h"
#include "cc_flyer.h"

CFlyer::CFlyer ()
{
	Scale = MODEL_SCALE;
}

void CFlyer::Sight ()
{
	Entity->PlaySound (CHAN_VOICE, SoundSight);
}

void CFlyer::Idle ()
{
	Entity->PlaySound (CHAN_VOICE, SoundIdle, 1, ATTN_IDLE, 0);
}

void CFlyer::PopBlades ()
{
	Entity->PlaySound (CHAN_VOICE, SoundSproing);
}

CFrame FlyerFramesStand [] =
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
CAnim FlyerMoveStand (FRAME_stand01, FRAME_stand45, FlyerFramesStand);

CFrame FlyerFramesWalk [] =
{
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5)
};
CAnim FlyerMoveWalk (FRAME_stand01, FRAME_stand45, FlyerFramesWalk);

CFrame FlyerFramesRun [] =
{
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 10)
};
CAnim FlyerMoveRun (FRAME_stand01, FRAME_stand45, FlyerFramesRun);

void CFlyer::Run ()
{
	if (AIFlags & AI_STAND_GROUND)
		CurrentMove = &FlyerMoveStand;
	else
		CurrentMove = &FlyerMoveRun;
}

void CFlyer::Walk ()
{
	CurrentMove = &FlyerMoveWalk;
}

void CFlyer::Stand ()
{
	CurrentMove = &FlyerMoveStand;
}

/*mframe_t flyer_frames_start [] =
{
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	flyer_nextmove
};
mmove_t flyer_move_start = {FRAME_start01, FRAME_start06, flyer_frames_start, NULL};

mframe_t flyer_frames_stop [] =
{
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	NULL,
		ai_move, 0,	flyer_nextmove
};
mmove_t flyer_move_stop = {FRAME_stop01, FRAME_stop07, flyer_frames_stop, NULL};

void flyer_stop (edict_t *self)
{
		self->monsterinfo.currentmove = &flyer_move_stop;
}

void flyer_start (edict_t *self)
{
		self->monsterinfo.currentmove = &flyer_move_start;
}*/

CFrame FlyerFramesPain3 [] =
{	
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim FlyerMovePain3 (FRAME_pain301, FRAME_pain304, FlyerFramesPain3, ConvertDerivedFunction(&CFlyer::Run));

CFrame FlyerFramesPain2 [] =
{
	CFrame (&CMonster::AI_Move, 0) ,
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim FlyerMovePain2 (FRAME_pain201, FRAME_pain204, FlyerFramesPain2, ConvertDerivedFunction(&CFlyer::Run));

CFrame FlyerFramesPain1 [] =
{
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
CAnim FlyerMovePain1 (FRAME_pain101, FRAME_pain109, FlyerFramesPain1, ConvertDerivedFunction(&CFlyer::Run));

/*mframe_t flyer_frames_defense [] = 
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,		// Hold this frame
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_defense = {FRAME_defens01, FRAME_defens06, flyer_frames_defense, NULL};

mframe_t flyer_frames_bankright [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_bankright = {FRAME_bankr01, FRAME_bankr07, flyer_frames_bankright, NULL};

mframe_t flyer_frames_bankleft [] =
{
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL,
		ai_move, 0, NULL
};
mmove_t flyer_move_bankleft = {FRAME_bankl01, FRAME_bankl07, flyer_frames_bankleft, NULL};*/	

void CFlyer::Fire (int FlashNumber)
{
	vec3f	start, forward, right, end, dir;
	int effect;

	if (!Entity->gameEntity->enemy)
		return;

	if ((Entity->State.GetFrame() == FRAME_attak204) || (Entity->State.GetFrame() == FRAME_attak207) || (Entity->State.GetFrame() == FRAME_attak210))
		effect = EF_HYPERBLASTER;
	else
		effect = 0;

	Entity->State.GetAngles().ToVectors (&forward, &right, NULL);
	G_ProjectSource (Entity->State.GetOrigin(), dumb_and_hacky_monster_MuzzFlashOffset[FlashNumber], forward, right, start);
	
	end = Entity->gameEntity->enemy->state.origin;
	end.Z += Entity->gameEntity->enemy->viewheight;
	dir = end - start;

	MonsterFireBlaster (start, dir, 1, 1000, FlashNumber, effect);
}

void CFlyer::FireLeft ()
{
	Fire (MZ2_FLYER_BLASTER_1);
}

void CFlyer::FireRight ()
{
	Fire (MZ2_FLYER_BLASTER_2);
}

CFrame FlyerFramesAttack2 [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireLeft)),			// left gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireRight)),		// right gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireLeft)),			// left gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireRight)),		// right gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireLeft)),			// left gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireRight)),		// right gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireLeft)),			// left gun
	CFrame (&CMonster::AI_Charge, -10, ConvertDerivedFunction(&CFlyer::FireRight)),		// right gun
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim FlyerMoveAttack2 (FRAME_attak201, FRAME_attak217, FlyerFramesAttack2, ConvertDerivedFunction(&CFlyer::Run));

void CFlyer::SlashLeft ()
{
	vec3_t	aim = {MELEE_DISTANCE, Entity->GetMins().X, 0};
	CMeleeWeapon::Fire (Entity, aim, 5, 0);
	Entity->PlaySound (CHAN_WEAPON, SoundSlash);
}

void CFlyer::SlashRight ()
{
	vec3_t	aim = {MELEE_DISTANCE, Entity->GetMaxs().X, 0};
	CMeleeWeapon::Fire (Entity, aim, 5, 0);
	Entity->PlaySound (CHAN_WEAPON, SoundSlash);
}

CFrame FlyerFramesStartMelee [] =
{
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CFlyer::PopBlades)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim FlyerMoveStartMelee (FRAME_attak101, FRAME_attak106, FlyerFramesStartMelee, ConvertDerivedFunction(&CFlyer::LoopMelee));

CFrame FlyerFramesEndMelee [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim FlyerMoveEndMelee (FRAME_attak119, FRAME_attak121, FlyerFramesEndMelee, ConvertDerivedFunction(&CFlyer::Run));


CFrame FlyerFramesLoopMelee [] =
{
	CFrame (&CMonster::AI_Charge, 0),		// Loop Start
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CFlyer::SlashLeft)),		// Left Wing Strike
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CFlyer::SlashRight)),	// Right Wing Strike
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)		// Loop Ends
};
CAnim FlyerMoveLoopMelee (FRAME_attak107, FRAME_attak118, FlyerFramesLoopMelee, ConvertDerivedFunction(&CFlyer::CheckMelee));

void CFlyer::LoopMelee ()
{
/*	if (random() <= 0.5)	
		self->monsterinfo.currentmove = &flyer_move_attack1;
	else */
	CurrentMove = &FlyerMoveLoopMelee;
}

void CFlyer::Attack ()
{
/*	if (random() <= 0.5)	
		self->monsterinfo.currentmove = &flyer_move_attack1;
	else */
	CurrentMove = &FlyerMoveAttack2;
}

void CFlyer::Melee ()
{
	CurrentMove = &FlyerMoveStartMelee;
}

void CFlyer::CheckMelee ()
{
	if (range (Entity->gameEntity, Entity->gameEntity->enemy) == RANGE_MELEE)
		CurrentMove = (random() <= 0.8) ? &FlyerMoveLoopMelee : &FlyerMoveEndMelee;
	else
		CurrentMove = &FlyerMoveEndMelee;
}

void CFlyer::Pain (CBaseEntity *other, float kick, int damage)
{
	if (Entity->gameEntity->health < (Entity->gameEntity->max_health / 2))
		Entity->State.SetSkinNum(1);

	if (level.framenum < Entity->gameEntity->pain_debounce_time)
		return;

	Entity->gameEntity->pain_debounce_time = level.framenum + 30;
	if (skill->Integer() == 3)
		return;		// no pain anims in nightmare

	switch (rand() % 3)
	{
	case 0:
		Entity->PlaySound (CHAN_VOICE, SoundPain1);
		CurrentMove = &FlyerMovePain1;
		break;
	case 1:
		Entity->PlaySound (CHAN_VOICE, SoundPain2);
		CurrentMove = &FlyerMovePain2;
		break;
	default:
		Entity->PlaySound (CHAN_VOICE, SoundPain1);
		CurrentMove = &FlyerMovePain3;
		break;
	}
}

void CFlyer::Die(CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point)
{
	Entity->PlaySound (CHAN_VOICE, SoundDie);
	Entity->BecomeExplosion(false);
}

#ifdef FLYER_KNOWS_HOW_TO_DODGE
CFrame FlyerFramesRollLeft [] =
{
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15)
};
CAnim FlyerMoveRollLeft (FRAME_rollf01, FRAME_rollf09, FlyerFramesRollLeft, ConvertDerivedFunction(&CFlyer::ChooseAfterDodge));

CFrame FlyerFramesRollRight [] =
{
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15),
	CFrame (ConvertDerivedAIMove(&CFlyer::AI_Roll), 15)
};
CAnim FlyerMoveRollRight (FRAME_rollr01, FRAME_rollr09, FlyerFramesRollRight, ConvertDerivedFunction(&CFlyer::ChooseAfterDodge));

void CFlyer::AI_Roll(float Dist)
{
	vec3_t	v;

	Entity->State.GetOrigin(v);
	Vec3Subtract (Entity->gameEntity->enemy->state.origin, v, v);
	IdealYaw = VecToYaw(v);
	ChangeYaw ();

	float Yaw = (Entity->State.GetAngles().Y - 90);
	if (CurrentMove == &FlyerMoveRollRight)
		Yaw = (Entity->State.GetAngles().Y + 90);

	if (Dist)
		WalkMove (Yaw, Dist);
}

void CFlyer::ChooseAfterDodge ()
{
	CurrentMove = (random() < 0.5) ? &FlyerMoveRun : &FlyerMoveAttack2;
}

#ifndef MONSTER_USE_ROGUE_AI
void CFlyer::Dodge (CBaseEntity *attacker, float eta)
#else
void CFlyer::Duck (float eta)
#endif
{
	if (random() > (0.35f + ((skill->Float()+1) / 10)) )
		return;
	
	// Don't dodge if we're attacking or dodging already
	if ((CurrentMove == &FlyerMoveRollLeft || CurrentMove == &FlyerMoveRollRight) || (CurrentMove == &FlyerMoveAttack2 && (random() < 0.5)))
		return;

	CTrace trace;
	vec3_t right, end;
	vec3_t angles;
	Entity->State.GetAngles(angles);

	Angles_Vectors (angles, NULL, right, NULL);
	bool WantsLeft = (random() < 0.5);

	// Approximate travel distance.
	// First, check if we can roll right.
	bool CanRollRight = false;
	bool CanRollLeft = false;

	Entity->State.GetOrigin(end);
	Vec3MA (end, -(15 * 5), right, end);
	trace = CTrace (Entity->State.GetOrigin(), Entity->GetMins(), Entity->GetMaxs(), vec3f(end), Entity->gameEntity, CONTENTS_MASK_MONSTERSOLID);

	if (trace.fraction == 1.0)
		CanRollRight = true;

	// Now check the left
	Entity->State.GetOrigin(end);
	Vec3MA (end, (15 * 5), right, end);
	trace = CTrace(Entity->State.GetOrigin(), Entity->GetMins(), Entity->GetMaxs(), vec3f(end), Entity->gameEntity, CONTENTS_MASK_MONSTERSOLID);

	if (trace.fraction == 1.0)
		CanRollLeft = true;

	// Can we roll the way we wanted?
	if (WantsLeft && !CanRollLeft && CanRollRight)
		WantsLeft = false;
	else if (!WantsLeft && CanRollLeft && !CanRollRight)
		WantsLeft = true;

	CurrentMove = (WantsLeft) ? &FlyerMoveRollLeft : &FlyerMoveRollRight;
}
#endif

#ifdef MONSTER_USE_ROGUE_AI
void CFlyer::SideStep ()
{
	if (AIFlags & AI_STAND_GROUND)
		CurrentMove = &FlyerMoveStand;
	else
		CurrentMove = &FlyerMoveRun;
}
#endif

void CFlyer::Spawn ()
{
	// fix a map bug in jail5.bsp
	if (!Q_stricmp(level.mapname, "jail5") && (Entity->State.GetOrigin().Z == -104))
	{
		Entity->gameEntity->targetname = Entity->gameEntity->target;
		Entity->gameEntity->target = NULL;
	}

	SoundSight = SoundIndex ("flyer/flysght1.wav");
	SoundIdle = SoundIndex ("flyer/flysrch1.wav");
	SoundPain1 = SoundIndex ("flyer/flypain1.wav");
	SoundPain2 = SoundIndex ("flyer/flypain2.wav");
	SoundSlash = SoundIndex ("flyer/flyatck2.wav");
	SoundSproing = SoundIndex ("flyer/flyatck1.wav");
	SoundDie = SoundIndex ("flyer/flydeth1.wav");

	SoundIndex ("flyer/flyatck3.wav");

	Entity->State.SetModelIndex (ModelIndex ("models/monsters/flyer/tris.md2"));
	Entity->SetMins (vec3f(-16, -16, -24));
	Entity->SetMaxs (vec3f(16, 16, 16));
	Entity->SetSolid (SOLID_BBOX);

	Entity->State.SetSound (SoundIndex ("flyer/flyidle1.wav"));

	Entity->gameEntity->health = 50;
	Entity->gameEntity->mass = 50;

	MonsterFlags |= (MF_HAS_IDLE | MF_HAS_SIGHT | MF_HAS_MELEE | MF_HAS_ATTACK
#ifdef MONSTER_USE_ROGUE_AI
	| MF_HAS_DUCK | MF_HAS_UNDUCK | MF_HAS_DODGE | MF_HAS_SIDESTEP
#endif
		);
	Entity->Link ();

	CurrentMove = &FlyerMoveStand;
	FlyMonsterStart ();
}

LINK_MONSTER_CLASSNAME_TO_CLASS ("monster_flyer", CFlyer);