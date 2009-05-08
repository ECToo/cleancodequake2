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
// cc_tank.cpp
// Tank
//

#include "cc_local.h"
#include "m_tank.h"

CTank Monster_Tank;
CTankCommander Monster_Tank_Commander;

CTank::CTank ()
{
	Classname = "monster_tank";
	Scale = MODEL_SCALE;
}

CTankCommander::CTankCommander ()
{
	Classname = "monster_tank_commander";
	Scale = MODEL_SCALE;
}

void CTank::Allocate (edict_t *ent)
{
	ent->Monster = new CTank(Monster_Tank);
}

void CTankCommander::Allocate (edict_t *ent)
{
	ent->Monster = new CTankCommander(Monster_Tank_Commander);
}

//
// misc
//

void CTank::Sight ()
{
	Sound (Entity, CHAN_VOICE, SoundSight);
}

void CTank::Footstep ()
{
	Sound (Entity, CHAN_BODY, SoundStep);
}

void CTank::Thud ()
{
	Sound (Entity, CHAN_BODY, SoundThud);
}

void CTank::Windup ()
{
	Sound (Entity, CHAN_WEAPON, SoundWindup);
}

void CTank::Idle ()
{
	Sound (Entity, CHAN_VOICE, SoundIdle, 1, ATTN_IDLE, 0);
}

//
// stand
//

CFrame TankFramesStand []=
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
CAnim	TankMoveStand (FRAME_stand01, FRAME_stand30, TankFramesStand);
	
void CTank::Stand ()
{
	CurrentMove = &TankMoveStand;
}

//
// walk
//

CFrame TankFramesWalk [] =
{
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 3),
	CFrame (&CMonster::AI_Walk, 2),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 4, ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Walk, 3),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 4),
	CFrame (&CMonster::AI_Walk, 5),
	CFrame (&CMonster::AI_Walk, 7),
	CFrame (&CMonster::AI_Walk, 7),
	CFrame (&CMonster::AI_Walk, 6),
	CFrame (&CMonster::AI_Walk, 6, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMoveWalk (FRAME_walk05, FRAME_walk20, TankFramesWalk);

void CTank::Walk ()
{
	CurrentMove = &TankMoveWalk;
}

//
// run
//

CFrame TankFramesStartRun [] =
{
	CFrame (&CMonster::AI_Run,  0),
	CFrame (&CMonster::AI_Run,  6),
	CFrame (&CMonster::AI_Run,  6),
	CFrame (&CMonster::AI_Run, 11, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMoveStartRun (FRAME_walk01, FRAME_walk04, TankFramesStartRun, ConvertDerivedFunction(&CTank::Run));

CFrame TankFramesRun [] =
{
	CFrame (&CMonster::AI_Run, 4),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 3),
	CFrame (&CMonster::AI_Run, 2),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 4),
	CFrame (&CMonster::AI_Run, 4, ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Run, 3),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 4),
	CFrame (&CMonster::AI_Run, 5),
	CFrame (&CMonster::AI_Run, 7),
	CFrame (&CMonster::AI_Run, 7),
	CFrame (&CMonster::AI_Run, 6),
	CFrame (&CMonster::AI_Run, 6, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMoveRun (FRAME_walk05, FRAME_walk20, TankFramesRun);

CFrame TankFramesStopRun [] =
{
	CFrame (&CMonster::AI_Run,  3),
	CFrame (&CMonster::AI_Run,  3),
	CFrame (&CMonster::AI_Run,  2),
	CFrame (&CMonster::AI_Run,  2),
	CFrame (&CMonster::AI_Run,  4, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMoveStopRun (FRAME_walk21, FRAME_walk25, TankFramesStopRun, ConvertDerivedFunction(&CTank::Walk));

void CTank::Run ()
{
	if (Entity->enemy && Entity->enemy->client)
		AIFlags |= AI_BRUTAL;
	else
		AIFlags &= ~AI_BRUTAL;

	if (AIFlags & AI_STAND_GROUND)
	{
		CurrentMove = &TankMoveStand;
		return;
	}

	if (CurrentMove == &TankMoveWalk ||
		CurrentMove == &TankMoveStartRun)
	{
		CurrentMove = &TankMoveRun;
	}
	else
	{
		CurrentMove = &TankMoveStartRun;
	}
}

//
// pain
//

CFrame TankFramesPain1 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim TankMovePain1 (FRAME_pain101, FRAME_pain104, TankFramesPain1, ConvertDerivedFunction(&CTank::Run));

CFrame TankFramesPain2 [] =
{
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim TankMovePain2 (FRAME_pain201, FRAME_pain205, TankFramesPain2, ConvertDerivedFunction(&CTank::Run));

CFrame TankFramesPain3 [] =
{
	CFrame (&CMonster::AI_Move, -7),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMovePain3 (FRAME_pain301, FRAME_pain316, TankFramesPain3, ConvertDerivedFunction(&CTank::Run));

void CTank::Pain (edict_t *other, float kick, int damage)
{
	if (Entity->health < (Entity->max_health / 2))
		Entity->s.skinNum |= 1;

	if (damage <= 10)
		return;

	if (level.time < Entity->pain_debounce_time)
			return;

	if (damage <= 30 && random() > 0.2)
		return;
	
	// If hard or nightmare, don't go into pain while attacking
	if ( skill->Integer() >= 2)
	{
		if ( (Entity->s.frame >= FRAME_attak301) && (Entity->s.frame <= FRAME_attak330) )
			return;
		if ( (Entity->s.frame >= FRAME_attak101) && (Entity->s.frame <= FRAME_attak116) )
			return;
	}

	Entity->pain_debounce_time = level.time + 3;
	Sound (Entity, CHAN_VOICE, SoundPain);

	if (skill->Integer() == 3)
		return;		// no pain anims in nightmare

	CurrentMove = ((damage <= 60) ? ((damage <= 30) ? &TankMovePain1 : &TankMovePain2) : &TankMovePain3);
};


//
// attacks
//

void CTank::Blaster ()
{
	vec3_t	forward, right;
	vec3_t	start;
	vec3_t	end;
	vec3_t	dir;
	int		flash_number;

	switch (Entity->s.frame)
	{
	case FRAME_attak110:
		flash_number = MZ2_TANK_BLASTER_1;
		break;
	case FRAME_attak113:
		flash_number = MZ2_TANK_BLASTER_2;
		break;
	default:
		flash_number = MZ2_TANK_BLASTER_3;
		break;
	}

	Angles_Vectors (Entity->s.angles, forward, right, NULL);
	G_ProjectSource (Entity->s.origin, dumb_and_hacky_monster_MuzzFlashOffset[flash_number], forward, right, start);

	Vec3Copy (Entity->enemy->s.origin, end);
	end[2] += Entity->enemy->viewheight;
	Vec3Subtract (end, start, dir);

	MonsterFireBlaster (start, dir, 30, 800, flash_number, EF_BLASTER);
}	

void CTank::Strike ()
{
	Sound (Entity, CHAN_WEAPON, SoundStrike);
}	

void CTank::Rocket ()
{
	vec3_t	forward, right;
	vec3_t	start;
	vec3_t	dir;
	vec3_t	vec;
	int		flash_number;

	switch (Entity->s.frame)
	{
	case FRAME_attak324:
		flash_number = MZ2_TANK_ROCKET_1;
		break;
	case FRAME_attak327:
		flash_number = MZ2_TANK_ROCKET_2;
		break;
	default:
		flash_number = MZ2_TANK_ROCKET_3;
		break;
	}

	Angles_Vectors (Entity->s.angles, forward, right, NULL);
	G_ProjectSource (Entity->s.origin, dumb_and_hacky_monster_MuzzFlashOffset[flash_number], forward, right, start);

	Vec3Copy (Entity->enemy->s.origin, vec);
	vec[2] += Entity->enemy->viewheight;
	Vec3Subtract (vec, start, dir);
	VectorNormalizef (dir, dir);

	MonsterFireRocket (start, dir, 50, 550, flash_number);
}	

void CTank::MachineGun ()
{
	vec3_t	dir;
	vec3_t	vec;
	vec3_t	start;
	vec3_t	forward, right;
	int		flash_number = MZ2_TANK_MACHINEGUN_1 + (Entity->s.frame - FRAME_attak406);

	Angles_Vectors (Entity->s.angles, forward, right, NULL);
	G_ProjectSource (Entity->s.origin, dumb_and_hacky_monster_MuzzFlashOffset[flash_number], forward, right, start);

	if (Entity->enemy)
	{
		Vec3Copy (Entity->enemy->s.origin, vec);
		vec[2] += Entity->enemy->viewheight;
		Vec3Subtract (vec, start, vec);
		VecToAngles (vec, vec);
		dir[0] = vec[0];
	}
	else
		dir[0] = 0;

	if (Entity->s.frame <= FRAME_attak415)
		dir[1] = Entity->s.angles[1] - 8 * (Entity->s.frame - FRAME_attak411);
	else
		dir[1] = Entity->s.angles[1] + 8 * (Entity->s.frame - FRAME_attak419);
	dir[2] = 0;

	Angles_Vectors (dir, forward, NULL, NULL);

	MonsterFireBullet (start, forward, 20, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
}	


CFrame TankFramesAttackBlast [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -2),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,	ConvertDerivedFunction(&CTank::Blaster)),		// 10
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,	ConvertDerivedFunction(&CTank::Blaster)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,	ConvertDerivedFunction(&CTank::Blaster)) // 16
};
CAnim TankMoveAttackBlast (FRAME_attak101, FRAME_attak116, TankFramesAttackBlast, ConvertDerivedFunction(&CTank::ReAttackBlaster));

CFrame TankFramesReAttackBlast [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,	ConvertDerivedFunction(&CTank::Blaster)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,	ConvertDerivedFunction(&CTank::Blaster))			// 16
};
CAnim TankMoveReAttackBlast (FRAME_attak111, FRAME_attak116, TankFramesReAttackBlast, ConvertDerivedFunction(&CTank::ReAttackBlaster));

CFrame TankFramesAttackPostBlast [] =	
{
	CFrame (&CMonster::AI_Move, 0),				// 17
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, -2,	ConvertDerivedFunction(&CTank::Footstep))		// 22
};
CAnim TankMoveAttackPostBlast (FRAME_attak117, FRAME_attak122, TankFramesAttackPostBlast, ConvertDerivedFunction(&CTank::Run));

void CTank::ReAttackBlaster ()
{
	if (skill->Integer() >= 2 && visible (Entity, Entity->enemy) && Entity->enemy->health > 0 && random() <= 0.6)
	{
		CurrentMove = &TankMoveReAttackBlast;
		return;
	}
	CurrentMove = &TankMoveAttackPostBlast;
}

void CTank::PostStrike ()
{
	Entity->enemy = NULL;
	Run ();
}

CFrame TankFramesAttackStrike [] =
{
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 6),
	CFrame (&CMonster::AI_Move, 7),
	CFrame (&CMonster::AI_Move, 9, ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 2, ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, 0, ConvertDerivedFunction(&CTank::Windup)),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0, ConvertDerivedFunction(&CTank::Strike)),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -1),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -10),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, -2, ConvertDerivedFunction(&CTank::Footstep))
};
CAnim TankMoveAttackStrike (FRAME_attak201, FRAME_attak238, TankFramesAttackStrike, ConvertDerivedFunction(&CTank::PostStrike));

CFrame TankFramesAttackPreRocket [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),			// 10

	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 1),
	CFrame (&CMonster::AI_Charge, 2),
	CFrame (&CMonster::AI_Charge, 7),
	CFrame (&CMonster::AI_Charge, 7),
	CFrame (&CMonster::AI_Charge, 7,  ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),			// 20

	CFrame (&CMonster::AI_Charge, -3)
};
CAnim TankMoveAttackPreRocket (FRAME_attak301, FRAME_attak321, TankFramesAttackPreRocket, ConvertDerivedFunction(&CTank::DoAttackRocket));

CFrame TankFramesAttackFireRocket [] =
{
	CFrame (&CMonster::AI_Charge, -3),			// Loop Start	22 
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,  ConvertDerivedFunction(&CTank::Rocket)),		// 24
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0,  ConvertDerivedFunction(&CTank::Rocket)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, -1, ConvertDerivedFunction(&CTank::Rocket))		// 30	Loop End
};
CAnim TankMoveAttackFireRocket (FRAME_attak322, FRAME_attak330, TankFramesAttackFireRocket, ConvertDerivedFunction(&CTank::ReFireRocket));

CFrame TankFramesAttackPostRocket [] =
{	
	CFrame (&CMonster::AI_Charge, 0),			// 31
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 2),
	CFrame (&CMonster::AI_Charge, 3),
	CFrame (&CMonster::AI_Charge, 4),
	CFrame (&CMonster::AI_Charge, 2),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),			// 40

	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, -9),
	CFrame (&CMonster::AI_Charge, -8),
	CFrame (&CMonster::AI_Charge, -7),
	CFrame (&CMonster::AI_Charge, -1),
	CFrame (&CMonster::AI_Charge, -1, ConvertDerivedFunction(&CTank::Footstep)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),			// 50

	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim TankMoveAttackPostRocket (FRAME_attak331, FRAME_attak353, TankFramesAttackPostRocket, ConvertDerivedFunction(&CTank::Run));

CFrame TankFramesAttackChain [] =
{
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (NULL,      0, ConvertDerivedFunction(&CTank::MachineGun)),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0),
	CFrame (&CMonster::AI_Charge, 0)
};
CAnim TankMoveAttackChain (FRAME_attak401, FRAME_attak429, TankFramesAttackChain, ConvertDerivedFunction(&CTank::Run));

void CTank::ReFireRocket ()
{
	// Only on hard or nightmare
	if ( skill->Integer() >= 2 && Entity->enemy->health > 0 && visible(Entity, Entity->enemy) && random() <= 0.4)
	{
		CurrentMove = &TankMoveAttackFireRocket;
		return;
	}
	CurrentMove = &TankMoveAttackPostRocket;
}

void CTank::DoAttackRocket ()
{
	CurrentMove = &TankMoveAttackFireRocket;
}

void CTank::Attack ()
{
	vec3_t	vec;
	float	range;
	float	r;

	if (Entity->enemy->health < 0)
	{
		CurrentMove = &TankMoveAttackStrike;
		AIFlags &= ~AI_BRUTAL;
		return;
	}

	Vec3Subtract (Entity->enemy->s.origin, Entity->s.origin, vec);
	range = Vec3Length (vec);

	r = random();

	if (range <= 125)
	{
		if (r < 0.4)
			CurrentMove = &TankMoveAttackChain;
		else 
			CurrentMove = &TankMoveAttackBlast;
	}
	else if (range <= 250)
	{
		if (r < 0.5)
			CurrentMove = &TankMoveAttackChain;
		else
			CurrentMove = &TankMoveAttackBlast;
	}
	else
	{
		if (r < 0.33)
			CurrentMove = &TankMoveAttackChain;
		else if (r < 0.66)
		{
			CurrentMove = &TankMoveAttackPreRocket;
			Entity->pain_debounce_time = level.time + 5.0;	// no pain for a while
		}
		else
			CurrentMove = &TankMoveAttackBlast;
	}
}


//
// death
//

void CTank::Dead ()
{
	Vec3Set (Entity->mins, -16, -16, -16);
	Vec3Set (Entity->maxs, 16, 16, -0);
	Entity->movetype = MOVETYPE_TOSS;
	Entity->svFlags |= SVF_DEADMONSTER;
	NextThink = 0;
	gi.linkentity (Entity);
}

CFrame TankFramesDeath1 [] =
{
	CFrame (&CMonster::AI_Move, -7),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 3),
	CFrame (&CMonster::AI_Move, 6),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 1),
	CFrame (&CMonster::AI_Move, 2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -2),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -3),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, -4),
	CFrame (&CMonster::AI_Move, -6),
	CFrame (&CMonster::AI_Move, -4),
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, -7),
	CFrame (&CMonster::AI_Move, -15, ConvertDerivedFunction(&CTank::Thud)),
	CFrame (&CMonster::AI_Move, -5),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0),
	CFrame (&CMonster::AI_Move, 0)
};
CAnim TankMoveDeath (FRAME_death101, FRAME_death132, TankFramesDeath1, ConvertDerivedFunction(&CTank::Dead));

void CTank::Die (edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

// check for gib
	if (Entity->health <= Entity->gib_health)
	{
		Sound (Entity, CHAN_VOICE, SoundIndex ("misc/udeath.wav"));
		for (n= 0; n < 1 /*4*/; n++)
			ThrowGib (Entity, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (Entity, "models/objects/gibs/sm_metal/tris.md2", damage, GIB_METALLIC);
		ThrowGib (Entity, "models/objects/gibs/chest/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (Entity, "models/objects/gibs/gear/tris.md2", damage, GIB_METALLIC);
		Entity->deadflag = DEAD_DEAD;
		return;
	}

	if (Entity->deadflag == DEAD_DEAD)
		return;

// regular death
	Sound (Entity, CHAN_VOICE, SoundDie);
	Entity->deadflag = DEAD_DEAD;
	Entity->takedamage = DAMAGE_YES;

	CurrentMove = &TankMoveDeath;
}


//
// monster_tank
//

void CTank::Spawn ()
{
	Entity->s.modelIndex = ModelIndex ("models/monsters/tank/tris.md2");
	Vec3Set (Entity->mins, -32, -32, -16);
	Vec3Set (Entity->maxs, 32, 32, 72);
	Entity->movetype = MOVETYPE_STEP;
	Entity->solid = SOLID_BBOX;

	SoundPain = SoundIndex ("tank/tnkpain2.wav");
	SoundThud = SoundIndex ("tank/tnkdeth2.wav");
	SoundIdle = SoundIndex ("tank/tnkidle1.wav");
	SoundDie = SoundIndex ("tank/death.wav");
	SoundStep = SoundIndex ("tank/step.wav");
	SoundWindup = SoundIndex ("tank/tnkatck4.wav");
	SoundStrike = SoundIndex ("tank/tnkatck5.wav");
	SoundSight = SoundIndex ("tank/sight1.wav");

	SoundIndex ("tank/tnkatck1.wav");
	SoundIndex ("tank/tnkatk2a.wav");
	SoundIndex ("tank/tnkatk2b.wav");
	SoundIndex ("tank/tnkatk2c.wav");
	SoundIndex ("tank/tnkatk2d.wav");
	SoundIndex ("tank/tnkatk2e.wav");
	SoundIndex ("tank/tnkatck3.wav");

	Entity->health = 750;
	Entity->gib_health = -200;
	Entity->mass = 500;

	MonsterFlags |= (MF_HAS_ATTACK | MF_HAS_SIGHT | MF_HAS_IDLE);

	gi.linkentity (Entity);
	WalkMonsterStart();
}

void CTankCommander::Spawn ()
{
	CTank::Spawn ();
	Entity->health = 1000;
	Entity->gib_health = -225;
	Entity->s.skinNum = 2;
}