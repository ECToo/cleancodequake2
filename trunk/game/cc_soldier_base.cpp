#include "cc_local.h"
#include "m_soldier.h"

void CSoldierBase::Idle ()
{
	if (random() > 0.8)
		Sound (Entity, CHAN_VOICE, SoundIdle, 1, ATTN_IDLE, 0);
}

void CSoldierBase::CockGun ()
{
	Sound (Entity, CHAN_WEAPON, SoundCock);
}


// STAND

CFrame SoldierFramesStand1 [] =
{
	CFrame (&CMonster::AI_Stand, 0, ConvertDerivedFunction(&CSoldierBase::Idle)),
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
CAnim SoldierMoveStand1 (FRAME_stand101, FRAME_stand130, SoldierFramesStand1, ConvertDerivedFunction(&CSoldierBase::Stand));

CFrame SoldierFramesStand3 [] =
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
	CFrame (&CMonster::AI_Stand, 0, ConvertDerivedFunction(&CSoldierBase::CockGun)),
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
CAnim SoldierMoveStand3 (FRAME_stand301, FRAME_stand339, SoldierFramesStand3, ConvertDerivedFunction(&CSoldierBase::Stand));

void CSoldierBase::Stand ()
{
	if ((CurrentMove == &SoldierMoveStand3) || (random() < 0.8))
		CurrentMove = &SoldierMoveStand1;
	else
		CurrentMove = &SoldierMoveStand3;
}


//
// WALK
//

void CSoldierBase::Walk1_Random ()
{
	if (random() > 0.1)
		NextFrame = FRAME_walk101;
}

CFrame SoldierFramesWalk1 [] =
{
	CFrame (&CMonster::AI_Walk, 3),
	CFrame (&CMonster::AI_Walk, 6),
	CFrame (&CMonster::AI_Walk, 2),
	CFrame (&CMonster::AI_Walk, 2),
	CFrame (&CMonster::AI_Walk, 2),
	CFrame (&CMonster::AI_Walk, 1),
	CFrame (&CMonster::AI_Walk, 6),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 3),
	CFrame (&CMonster::AI_Walk, -1, ConvertDerivedFunction(&CSoldierBase::Walk1_Random)),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0),
	CFrame (&CMonster::AI_Walk, 0)
};
CAnim SoldierMoveWalk1 (FRAME_walk101, FRAME_walk133, SoldierFramesWalk1);

CFrame SoldierFramesWalk2 [] =
{
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 9),
	CFrame (&CMonster::AI_Walk, 8),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 1),
	CFrame (&CMonster::AI_Walk, 3),
	CFrame (&CMonster::AI_Walk, 7),
	CFrame (&CMonster::AI_Walk, 6),
	CFrame (&CMonster::AI_Walk, 7)
};
CAnim SoldierMoveWalk2 (FRAME_walk209, FRAME_walk218, SoldierFramesWalk2);

void CSoldierBase::Walk ()
{
	if (random() < 0.5)
		CurrentMove = &SoldierMoveWalk1;
	else
		CurrentMove = &SoldierMoveWalk2;
}


//
// RUN
//

CFrame SoldierFramesStartRun [] =
{
	CFrame (&CMonster::AI_Run, 7),
	CFrame (&CMonster::AI_Run, 5)
};
CAnim SoldierMoveStartRun (FRAME_run01, FRAME_run02, SoldierFramesStartRun, ConvertDerivedFunction(&CSoldierBase::Run));

CFrame SoldierFramesRun [] =
{
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 11),
	CFrame (&CMonster::AI_Run, 11),
	CFrame (&CMonster::AI_Run, 16),
	CFrame (&CMonster::AI_Run, 10),
	CFrame (&CMonster::AI_Run, 15)
};
CAnim SoldierMoveRun (FRAME_run03, FRAME_run08, SoldierFramesRun);

void CSoldierBase::Run ()
{
	if (AIFlags & AI_STAND_GROUND)
	{
		CurrentMove = &SoldierMoveStand1;
		return;
	}

	if (CurrentMove == &SoldierMoveWalk1 ||
		CurrentMove == &SoldierMoveWalk2 ||
		CurrentMove == &SoldierMoveStartRun)
		CurrentMove = &SoldierMoveRun;
	else
		CurrentMove = &SoldierMoveStartRun;
}


//
// PAIN
//

CFrame SoldierFramesPain1 [] =
{
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMovePain1 (FRAME_pain101, FRAME_pain105, SoldierFramesPain1, ConvertDerivedFunction(&CSoldierBase::Run));

CFrame SoldierFramesPain2 [] =
{
	CFrame (&CMonster::AI_Move, -13),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 2)
};
CAnim SoldierMovePain2 (FRAME_pain201, FRAME_pain207, SoldierFramesPain2, ConvertDerivedFunction(&CSoldierBase::Run));

CFrame SoldierFramesPain3 [] =
{
	CFrame (&CMonster::AI_Move, -8),
	CFrame (&CMonster::AI_Move, 10),
	CFrame (&CMonster::AI_Move, -4),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 2)
};
CAnim SoldierMovePain3 (FRAME_pain301, FRAME_pain318, SoldierFramesPain3, ConvertDerivedFunction(&CSoldierBase::Run));

CFrame SoldierFramesPain4 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -6),
	CFrame (&CMonster::AI_Move, 8),
	CFrame (&CMonster::AI_Move, 4),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 5),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMovePain4 (FRAME_pain401, FRAME_pain417, SoldierFramesPain4, ConvertDerivedFunction(&CSoldierBase::Run));


void CSoldierBase::Pain (edict_t *other, float kick, int damage)
{
	if (Entity->health < (Entity->max_health / 2))
			Entity->s.skinNum |= 1;

	if (level.time < Entity->pain_debounce_time)
	{
		if ((Entity->velocity[2] > 100) && ( (CurrentMove == &SoldierMovePain1) || (CurrentMove == &SoldierMovePain2) || (CurrentMove == &SoldierMovePain3)))
			CurrentMove = &SoldierMovePain4;
		return;
	}

	Entity->pain_debounce_time = level.time + 3;
	Sound (Entity, CHAN_VOICE, SoundPain);

	if (Entity->velocity[2] > 100)
	{
		CurrentMove = &SoldierMovePain4;
		return;
	}

	if (skill->Integer() == 3)
		return;		// no pain anims in nightmare

	float r = random();
	if (r < 0.33)
		CurrentMove = &SoldierMovePain1;
	else if (r < 0.66)
		CurrentMove = &SoldierMovePain2;
	else
		CurrentMove = &SoldierMovePain3;
}


//
// ATTACK
//

// ATTACK1 (blaster/shotgun)

void CSoldierBase::Fire1 ()
{
	FireGun (0);
}

void CSoldierBase::Attack1_Refire1 ()
{
	if (Entity->s.skinNum > 1)
		return;

	if (Entity->enemy->health <= 0)
		return;

	if ( ((skill->Integer() == 3) && (random() < 0.5)) || (range(Entity, Entity->enemy) == RANGE_MELEE) )
		NextFrame = FRAME_attak102;
	else
		NextFrame = FRAME_attak110;
}

void CSoldierBase::Attack1_Refire2 ()
{
	if (Entity->s.skinNum < 2)
		return;

	if (Entity->enemy->health <= 0)
		return;

	if ( ((skill->Integer() == 3) && (random() < 0.5)) || (range(Entity, Entity->enemy) == RANGE_MELEE) )
		NextFrame = FRAME_attak102;
}

CFrame SoldierFramesAttack1 [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Fire1)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Attack1_Refire1)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::CockGun)),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Attack1_Refire2)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim SoldierMoveAttack1 (FRAME_attak101, FRAME_attak112, SoldierFramesAttack1, ConvertDerivedFunction(&CSoldierBase::Run));

// ATTACK2 (blaster/shotgun)

void CSoldierBase::Fire2 ()
{
	FireGun (1);
}

void CSoldierBase::Attack2_Refire1 ()
{
	if (Entity->s.skinNum > 1)
		return;

	if (Entity->enemy->health <= 0)
		return;

	if ( ((skill->Integer() == 3) && (random() < 0.5)) || (range(Entity, Entity->enemy) == RANGE_MELEE) )
		NextFrame = FRAME_attak204;
	else
		NextFrame = FRAME_attak216;
}

void CSoldierBase::Attack2_Refire2 ()
{
	if (Entity->s.skinNum < 2)
		return;

	if (Entity->enemy->health <= 0)
		return;

	if ( ((skill->Integer() == 3) && (random() < 0.5)) || (range(Entity, Entity->enemy) == RANGE_MELEE) )
		NextFrame = FRAME_attak204;
}

CFrame SoldierFramesAttack2 [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Fire2)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Attack2_Refire1)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::CockGun)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Attack2_Refire2)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim SoldierMoveAttack2 (FRAME_attak201, FRAME_attak218, SoldierFramesAttack2, ConvertDerivedFunction(&CSoldierBase::Run));

// ATTACK3 (duck and shoot)

void CSoldierBase::Duck_Down ()
{
	if (AIFlags & AI_DUCKED)
		return;
	AIFlags |= AI_DUCKED;
	Entity->maxs[2] -= 32;
	Entity->takedamage = DAMAGE_YES;
	PauseTime = level.time + 1;
	gi.linkentity (Entity);
}

void CSoldierBase::Duck_Up ()
{
	Entity->monsterinfo.aiflags &= ~AI_DUCKED;
	Entity->maxs[2] += 32;
	Entity->takedamage = DAMAGE_AIM;
	gi.linkentity (Entity);
}

void CSoldierBase::Fire3 ()
{
	Duck_Down ();
	FireGun (2);
}

void CSoldierBase::Attack3_Refire ()
{
	if ((level.time + 0.4) < PauseTime)
		NextFrame = FRAME_attak303;
}

CFrame SoldierFramesAttack3 [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Fire3)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Attack3_Refire)),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Duck_Up)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim SoldierMoveAttack3 (FRAME_attak301, FRAME_attak309, SoldierFramesAttack3, ConvertDerivedFunction(&CSoldierBase::Run));

// ATTACK4 (machinegun)

void CSoldierBase::Fire4 ()
{
	FireGun (3);
//
//	if (self->enemy->health <= 0)
//		return;
//
//	if ( ((skill->Integer() == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
//		self->monsterinfo.nextframe = FRAME_attak402;
}

CFrame SoldierFramesAttack4 [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0, ConvertDerivedFunction(&CSoldierBase::Fire4)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim SoldierMoveAttack4 (FRAME_attak401, FRAME_attak406, SoldierFramesAttack4, ConvertDerivedFunction(&CSoldierBase::Run));

// ATTACK6 (run & shoot)

void CSoldierBase::Fire8 ()
{
	FireGun (7);
}

void CSoldierBase::Attack6_Refire ()
{
	if (Entity->enemy->health <= 0)
		return;

	if (range(Entity, Entity->enemy) < RANGE_MID)
		return;

	if (skill->Integer() == 3)
		NextFrame = FRAME_runs03;
}

CFrame SoldierFramesAttack6 [] =
{
	CFrame (&CMonster::AI_Charge, 10),
	CFrame (&CMonster::AI_Charge,  4),
	CFrame (&CMonster::AI_Charge, 12),
	CFrame (&CMonster::AI_Charge, 11, ConvertDerivedFunction(&CSoldierBase::Fire8)),
	CFrame (&CMonster::AI_Charge, 13),
	CFrame (&CMonster::AI_Charge, 18),
	CFrame (&CMonster::AI_Charge, 15),
	CFrame (&CMonster::AI_Charge, 14),
	CFrame (&CMonster::AI_Charge, 11),
	CFrame (&CMonster::AI_Charge,  8),
	CFrame (&CMonster::AI_Charge, 11),
	CFrame (&CMonster::AI_Charge, 12),
	CFrame (&CMonster::AI_Charge, 12),
	CFrame (&CMonster::AI_Charge, 17, ConvertDerivedFunction(&CSoldierBase::Attack6_Refire))
};
CAnim SoldierMoveAttack6 (FRAME_runs01, FRAME_runs14, SoldierFramesAttack6, ConvertDerivedFunction(&CSoldierBase::Run));

/*void soldier_attack()
{
	if (self->s.skinNum < 4)
	{
		if (random() < 0.5)
			self->monsterinfo.currentmove = &soldier_move_attack1;
		else
			self->monsterinfo.currentmove = &soldier_move_attack2;
	}
	else
		self->monsterinfo.currentmove = &soldier_move_attack4;
}*/


//
// SIGHT
//

void CSoldierBase::Sight ()
{
	Sound (Entity, CHAN_VOICE, (random() < 0.5) ? SoundSight1 : SoundSight2);

	if ((skill->Integer() > 0) && (range(Entity, Entity->enemy) >= RANGE_MID))
	{
		if (random() > 0.5)
			CurrentMove = &SoldierMoveAttack6;
	}
}

//
// DUCK
//

void CSoldierBase::Duck_Hold ()
{
	if (level.time >= PauseTime)
		AIFlags &= ~AI_HOLD_FRAME;
	else
		AIFlags |= AI_HOLD_FRAME;
}

CFrame SoldierFramesDuck [] =
{
	CFrame (&CMonster::AI_Move, 5, ConvertDerivedFunction(&CSoldierBase::Duck_Down)),
	CFrame (&CMonster::AI_Move, -1, ConvertDerivedFunction(&CSoldierBase::Duck_Hold)),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 0,  ConvertDerivedFunction(&CSoldierBase::Duck_Up)),
	CFrame (&CMonster::AI_Move, 5)
};
CAnim SoldierMoveDuck (FRAME_duck01, FRAME_duck05, SoldierFramesDuck, ConvertDerivedFunction(&CSoldierBase::Run));

void CSoldierBase::Dodge (edict_t *attacker, float eta)
{
	if (random() > 0.25)
		return;

	if (!Entity->enemy)
		Entity->enemy = attacker;

	PauseTime = level.time + eta + 0.3;

	switch (skill->Integer())
	{
	case 0:
	case 1:
		if (random() > 0.33)
			CurrentMove = &SoldierMoveDuck;
		else
			CurrentMove = &SoldierMoveAttack3;
		break;
	case 2:
	case 3:
	default:
		if (random() > 0.66)
			CurrentMove = &SoldierMoveDuck;
		else
			CurrentMove = &SoldierMoveAttack3;
		break;
	}
}


//
// DEATH
//

void CSoldierBase::Fire6 ()
{
	FireGun (5);
}

void CSoldierBase::Fire7 ()
{
	FireGun (6);
}

void CSoldierBase::Dead ()
{
	Vec3Set (Entity->mins, -16, -16, -24);
	Vec3Set (Entity->maxs, 16, 16, -8);
	Entity->movetype = MOVETYPE_TOSS;
	Entity->svFlags |= SVF_DEADMONSTER;
	Entity->nextthink = 0;
	gi.linkentity (Entity);
}

CFrame SoldierFramesDeath1 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -5),
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
	CFrame (&CMonster::AI_Move, 0, ConvertDerivedFunction(&CSoldierBase::Fire6)),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0, ConvertDerivedFunction(&CSoldierBase::Fire7)),
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
CAnim SoldierMoveDeath1 (FRAME_death101, FRAME_death136, SoldierFramesDeath1, ConvertDerivedFunction(&CSoldierBase::Dead));

CFrame SoldierFramesDeath2 [] =
{
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
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
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMoveDeath2 (FRAME_death201, FRAME_death235, SoldierFramesDeath2, ConvertDerivedFunction(&CSoldierBase::Dead));

CFrame SoldierFramesDeath3 [] =
{
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
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
};
CAnim SoldierMoveDeath3 (FRAME_death301, FRAME_death345, SoldierFramesDeath3, ConvertDerivedFunction(&CSoldierBase::Dead));

CFrame SoldierFramesDeath4 [] =
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
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),

	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMoveDeath4 (FRAME_death401, FRAME_death453, SoldierFramesDeath4, ConvertDerivedFunction(&CSoldierBase::Dead));

CFrame SoldierFramesDeath5 [] =
{
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -5),
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
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMoveDeath5 (FRAME_death501, FRAME_death524, SoldierFramesDeath5, ConvertDerivedFunction(&CSoldierBase::Dead));

CFrame SoldierFramesDeath6 [] =
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
	CFrame (&CMonster::AI_Move, 0)
};
CAnim SoldierMoveDeath6 (FRAME_death601, FRAME_death610, SoldierFramesDeath6, ConvertDerivedFunction(&CSoldierBase::Dead));

void CSoldierBase::Die (edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
// check for gib
	if (Entity->health <= Entity->gib_health)
	{
		Sound (Entity, CHAN_VOICE, SoundIndex ("misc/udeath.wav"));
		for (int n= 0; n < 3; n++)
			ThrowGib (Entity, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowGib (Entity, "models/objects/gibs/chest/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (Entity, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		Entity->deadflag = DEAD_DEAD;
		return;
	}

	if (Entity->deadflag == DEAD_DEAD)
		return;

// regular death
	Entity->deadflag = DEAD_DEAD;
	Entity->takedamage = DAMAGE_YES;
	Entity->s.skinNum |= 1;

	Sound (Entity, CHAN_VOICE, SoundDeath);

	if (fabs((Entity->s.origin[2] + Entity->viewheight) - point[2]) <= 4)
	{
		// head shot
		CurrentMove = &SoldierMoveDeath3;
		return;
	}

	switch (rand() % 5)
	{
	case 0:
		CurrentMove = &SoldierMoveDeath1;
		break;
	case 1:
		CurrentMove = &SoldierMoveDeath2;
		break;
	case 2:
		CurrentMove = &SoldierMoveDeath4;
		break;
	case 3:
		CurrentMove = &SoldierMoveDeath5;
		break;
	case 4:
		CurrentMove = &SoldierMoveDeath6;
		break;
	}
}

void CSoldierBase::Spawn ()
{
	Scale = MODEL_SCALE;

	Vec3Set (Entity->mins, -16, -16, -24);
	Vec3Set (Entity->maxs, 16, 16, 32);
	Entity->movetype = MOVETYPE_STEP;
	Entity->solid = SOLID_BBOX;

	Entity->s.modelIndex = ModelIndex ("models/monsters/soldier/tris.md2");

	SoundIdle =	SoundIndex ("soldier/solidle1.wav");
	SoundSight1 =	SoundIndex ("soldier/solsght1.wav");
	SoundSight2 =	SoundIndex ("soldier/solsrch1.wav");
	SoundCock =	SoundIndex ("infantry/infatck3.wav");

	Entity->mass = 100;
	MonsterFlags |= (MF_HAS_ATTACK | MF_HAS_SIGHT | MF_HAS_IDLE);

	SpawnSoldier ();

	gi.linkentity (Entity);

	Stand ();
	WalkMonsterStart ();
}