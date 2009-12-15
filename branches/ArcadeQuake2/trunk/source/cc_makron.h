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
// cc_makron.h
// 
//

#if !defined(__CC_MAKRON_H__) || !INCLUDE_GUARDS
#define __CC_MAKRON_H__

class CMakron : public CMonster
{
public:
	vec3f		SavedLoc;

	MediaIndex	SoundPain4;
	MediaIndex	SoundPain5;
	MediaIndex	SoundPain6;
	MediaIndex	SoundDeath;
	MediaIndex	SoundStepLeft;
	MediaIndex	SoundStepRight;
	MediaIndex	SoundAttackBfg;
	MediaIndex	SoundBrainSplorch;
	MediaIndex	SoundPreRailgun;
	MediaIndex	SoundPopUp;
	MediaIndex	SoundTaunt1;
	MediaIndex	SoundTaunt2;
	MediaIndex	SoundTaunt3;
	MediaIndex	SoundHit;

	MONSTER_SOUND_ENUM
	(
		SOUND_PAIN4,
		SOUND_PAIN5,
		SOUND_PAIN6,
		SOUND_DEATH,
		SOUND_STEPLEFT,
		SOUND_STEPRIGHT,
		SOUND_ATTACK_BFG,
		SOUND_BRAIN_SPLORCH,
		SOUND_PRE_RAILGUN,
		SOUND_POPUP,
		SOUND_TAUNT1,
		SOUND_TAUNT2,
		SOUND_TAUNT3,
		SOUND_HIT,

		SOUND_MAX
	);

	CMakron (uint32 ID);

	void SaveMonsterFields (CFile &File)
	{
		SAVE_MONSTER_SOUNDS
		File.Write<vec3f> (SavedLoc);
	}

	void LoadMonsterFields (CFile &File)
	{
		LOAD_MONSTER_SOUNDS
		SavedLoc = File.Read<vec3f> ();
	}

	void Run ();
	void Stand ();
	void Walk ();
	void Attack();
	bool CheckAttack ();
	void Sight ();

	void Taunt ();
	void StepLeft ();
	void StepRight ();
	void Hit ();
	void PopUp ();
	void BrainSplorch ();
	void PreRailgun ();
	void FireBFG ();
	void FireHyperblaster ();
	void FireRailgun ();
	void SavePosition ();

	void Dead ();
	void Die (CBaseEntity *inflictor, CBaseEntity *attacker, sint32 damage, vec3f &point);
	void Pain (CBaseEntity *other, float kick, sint32 damage);

	void Spawn ();
	static void Precache ();
	static void Toss (CBaseEntity *Spawner);
};

class CMakronJumpTimer : public virtual CBaseEntity, public CThinkableEntity
{
public:
	CMonsterEntity	*LinkedJorg;

	CMakronJumpTimer ();
	CMakronJumpTimer (sint32 Index);

	IMPLEMENT_SAVE_HEADER(CMakronJumpTimer)

	void SaveFields (CFile &File)
	{
		File.Write<sint32> ((LinkedJorg) ? LinkedJorg->State.GetNumber() : -1);

		CThinkableEntity::SaveFields (File);
	}

	void LoadFields (CFile &File)
	{
		sint32 Index = File.Read<sint32> ();

		if (Index != -1)
			LinkedJorg = entity_cast<CMonsterEntity>(g_edicts[Index].Entity);

		CThinkableEntity::LoadFields (File);
	}

	void Think ();
	static void Spawn (class CJorg *Jorg);
};

#else
FILE_WARNING
#endif