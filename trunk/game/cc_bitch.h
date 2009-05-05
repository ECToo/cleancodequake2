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
// cc_bitch.h
// Iron Maiden
//


class CMaiden : public CMonster
{
public:
	int	SoundMissilePrelaunch;
	int	SoundMissileLaunch;
	int	SoundMeleeSwing;
	int	SoundMeleeHit;
	int	SoundMissileReload;
	int	SoundDeath1;
	int	SoundDeath2;
	int	SoundFallDown;
	int	SoundIdle1;
	int	SoundIdle2;
	int	SoundPain1;
	int	SoundPain2;
	int	SoundPain3;
	int	SoundSight;
	int	SoundSearch;

	CMaiden ();

	void Allocate (edict_t *ent);

	void Attack ();
	void Dodge (edict_t *attacker, float eta);
	void Idle ();
	void Run ();
	void Sight ();
	void Stand ();
	void Walk ();
	void Melee ();

	void DuckDown ();
	void DuckHold ();
	void DuckUp ();

	void Moan ();
	void Reload ();
	void PreAttack ();
	void Rocket ();
	void ReRocket ();
	void Slash ();
	void DoSlash ();
	void ReSlash ();
	void Attack1 ();

	void Dead ();
	void Die (edict_t *inflictor, edict_t *attacker, int damage, vec3_t point);
	void Pain (edict_t *other, float kick, int damage);

	void Spawn ();
};

extern CMaiden Monster_Bitch;