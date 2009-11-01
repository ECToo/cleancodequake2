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
// cc_brain.h
// 
//

#if !defined(__CC_BRAIN_H__) || !defined(INCLUDE_GUARDS)
#define __CC_BRAIN_H__

class CBrain : public CMonster
{
public:
	bool		Refire;

	MediaIndex	SoundChestOpen;
	MediaIndex	SoundTentaclesExtend;
	MediaIndex	SoundTentaclesRetract;
	MediaIndex	SoundDeath;
	MediaIndex	SoundIdle1;
	MediaIndex	SoundIdle2;
	MediaIndex	SoundIdle3;
	MediaIndex	SoundPain1;
	MediaIndex	SoundPain2;
	MediaIndex	SoundSight;
	MediaIndex	SoundSearch;
	MediaIndex	SoundMelee1;
	MediaIndex	SoundMelee2;
	MediaIndex	SoundMelee3;

	CBrain (uint32 ID);

	void Run ();
	void Search ();
	void Sight ();
	void Stand ();
	void Walk ();
	void Idle ();
	void Melee ();

	void SwingRight ();
	void SwingLeft ();
	void HitRight ();
	void HitLeft ();
	void ChestOpen ();
	void TentacleAttack ();
	void ChestClosed ();

#ifndef MONSTER_USE_ROGUE_AI
	void Duck_Down ();
	void Duck_Hold ();
	void Duck_Up ();

	void Dodge (CBaseEntity *attacker, float eta);
#else
	void Duck (float eta);
#endif

	void Dead ();
	void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3f &point);
	void Pain (CBaseEntity *other, float kick, int damage);

	void Spawn ();
};

#else
FILE_WARNING
#endif