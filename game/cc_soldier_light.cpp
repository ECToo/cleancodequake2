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
// cc_soldier_light.cpp
// Bew pew gew.
//

#include "cc_local.h"

CSoldierLight Monster_Soldier_Light;

CSoldierLight::CSoldierLight ()
{
	Classname = "monster_soldier_light";
}

void CSoldierLight::Allocate (edict_t *ent)
{
	ent->Monster = new CSoldierLight(Monster_Soldier_Light);
}

extern CAnim SoldierMoveAttack1;
extern CAnim SoldierMoveAttack2;
extern CAnim SoldierMoveAttack6;

void CSoldierLight::Attack ()
{
#ifdef MONSTER_USE_ROGUE_AI
	DoneDodge ();

	// PMM - blindfire!
	if (AttackState == AS_BLIND)
	{
		float r, chance;
		// setup shot probabilities
		if (BlindFireDelay < 1.0)
			chance = 1.0f;
		else if (BlindFireDelay < 7.5)
			chance = 0.4f;
		else
			chance = 0.1f;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		BlindFireDelay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (Vec3Compare (BlindFireTarget, vec3Origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
			return;

		// turn on manual steering to signal both manual steering and blindfire
		AIFlags |= AI_MANUAL_STEERING;
		CurrentMove = &SoldierMoveAttack1;
		AttackFinished = level.time + 1.5 + random();
		return;
	}
	// pmm

	float r = random();
	if ((!(AIFlags & (AI_BLOCKED|AI_STAND_GROUND))) &&
		(range(Entity, Entity->enemy) >= RANGE_NEAR) && 
		(r < (skill->Integer()*0.25)))
		CurrentMove = &SoldierMoveAttack6;
	else
#endif
	{
		if (random() < 0.5)
			CurrentMove = &SoldierMoveAttack1;
		else
			CurrentMove = &SoldierMoveAttack2;
	}
}

static int BlasterFlash [] = {MZ2_SOLDIER_BLASTER_1, MZ2_SOLDIER_BLASTER_2, MZ2_SOLDIER_BLASTER_3, MZ2_SOLDIER_BLASTER_4, MZ2_SOLDIER_BLASTER_5, MZ2_SOLDIER_BLASTER_6, MZ2_SOLDIER_BLASTER_7, MZ2_SOLDIER_BLASTER_8};
void CSoldierLight::FireGun (int FlashNumber)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flashIndex = BlasterFlash[FlashNumber];

	Angles_Vectors (Entity->state.angles, forward, right, NULL);
	G_ProjectSource (Entity->state.origin, dumb_and_hacky_monster_MuzzFlashOffset[flashIndex], forward, right, start);

	if (FlashNumber == 5 || FlashNumber == 6)
		Vec3Copy (forward, aim);
	else
	{
		Vec3Copy (Entity->enemy->state.origin, end);
		end[2] += Entity->enemy->viewheight;
		Vec3Subtract (end, start, aim);
		VecToAngles (aim, dir);
		Angles_Vectors (dir, forward, right, up);

		r = crandom()*1000;
		u = crandom()*500;
		Vec3MA (start, 8192, forward, end);
		Vec3MA (end, r, right, end);
		Vec3MA (end, u, up, end);

		Vec3Subtract (end, start, aim);
		VectorNormalizef (aim, aim);
	}

	MonsterFireBlaster (start, aim, 5, 600, flashIndex, EF_BLASTER);
}

void CSoldierLight::SpawnSoldier ()
{
	SoundPain = SoundIndex ("soldier/solpain2.wav");
	SoundDeath = SoundIndex ("soldier/soldeth2.wav");
	ModelIndex ("models/objects/laser/tris.md2");
	SoundIndex ("misc/lasfly.wav");
	SoundIndex ("soldier/solatck2.wav");

	Entity->state.skinNum = 0;
	Entity->health = 20;
	Entity->gib_health = -30;

#ifdef MONSTER_USE_ROGUE_AI
	BlindFire = true;
#endif
}