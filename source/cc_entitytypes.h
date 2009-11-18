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
// cc_entitytypes.h
// Different base entity classes
//

#if !defined(__CC_ENTITYTYPES_H__) || !defined(INCLUDE_GUARDS)
#define __CC_ENTITYTYPES_H__

// "Hurtable" entity
class CHurtableEntity : public virtual CBaseEntity
{
public:
	sint32			Health;
	sint32			MaxHealth;
	sint32			GibHealth;
	bool		DeadFlag;
	bool		CanTakeDamage;

	ENTITYFIELD_VIRTUAL_DEFS
	ENTITYFIELDS_SAVABLE_VIRTUAL(CHurtableEntity)

	CHurtableEntity ();
	CHurtableEntity (sint32 index);

	virtual void Pain (CBaseEntity *other, float kick, sint32 damage) {};
	virtual void Die (CBaseEntity *inflictor, CBaseEntity *attacker, sint32 damage, vec3f &point) {};

	virtual bool CanDamage (CBaseEntity *inflictor);
	virtual bool CheckTeamDamage (CBaseEntity *attacker);
	virtual sint32 CheckPowerArmor (vec3f &point, vec3f &normal, sint32 damage, sint32 dflags);
	virtual void Killed (CBaseEntity *inflictor, CBaseEntity *attacker, sint32 damage, vec3f &point);

	// An "extension" of sorts to TakeDamage
	// which handles the effects when we are hurt
	virtual void DamageEffect (vec3f &dir, vec3f &point, vec3f &normal, sint32 &damage, sint32 &dflags);

	// Takes damage.
	// For this, "this" is target. Use this if the
	// entity can be casted to CHurtableEntity or is CHurtableEntity
	// without question.
	virtual void TakeDamage (	CBaseEntity *inflictor, CBaseEntity *attacker,
							vec3f dir, vec3f point, vec3f normal, sint32 damage,
							sint32 knockback, sint32 dflags, EMeansOfDeath mod);
	
	// This is a convenient static version.
	// This will cast targ to CHurtableEntity
	// and make the necessary damage adjustments if possible.
	// If "targ" can't take damage, nothing will happen.
	static void TakeDamage (	CBaseEntity *targ, CBaseEntity *inflictor,
							CBaseEntity *attacker, vec3f dir, vec3f point,
							vec3f normal, sint32 damage, sint32 knockback,
							sint32 dflags, EMeansOfDeath mod);
};

class CBlockableEntity : public virtual CBaseEntity
{
public:
	CBlockableEntity ();
	CBlockableEntity (sint32 Index);

	virtual void Blocked (CBaseEntity *other) = 0;
};

class CUsableEntity : public virtual CBaseEntity
{
public:
	char				*Message;
	char				*Target;
	char				*KillTarget;
	char				*PathTarget;
	CBaseEntity			*Activator;
	FrameNumber_t		Delay;
	MediaIndex			NoiseIndex;
	bool				Usable;

	ENTITYFIELD_VIRTUAL_DEFS
	ENTITYFIELDS_SAVABLE_VIRTUAL(CUsableEntity)

	CUsableEntity ();
	CUsableEntity (sint32 Index);

	virtual void Use (CBaseEntity *other, CBaseEntity *activator) {};
	virtual void UseTargets (CBaseEntity *activator, char *Message);
};

// Thinkable entity
// Simple think function
class CThinkableEntity : public virtual CBaseEntity
{
public:
	FrameNumber_t		NextThink;

	CThinkableEntity ();
	CThinkableEntity (sint32 index);

	ENTITYFIELDS_SAVABLE(CThinkableEntity)

	void			RunThink ();
	virtual void	Think () = 0;
	virtual void	PreThink () {};
};

// Touchable entity
class CTouchableEntity : public virtual CBaseEntity
{
public:
	bool Touchable; // Setting to false is equivilent to putting touch = NULL in original Q2

	ENTITYFIELDS_SAVABLE(CTouchableEntity)

	CTouchableEntity ();
	CTouchableEntity (sint32 index);

	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);
};

CC_ENUM (uint8, EPhysicsType)
{
	PHYSICS_NONE,

	PHYSICS_NOCLIP,
	PHYSICS_PUSH,
	PHYSICS_STOP,
	PHYSICS_WALK,
	PHYSICS_STEP,
	PHYSICS_FLY,
	PHYSICS_TOSS,
	PHYSICS_FLYMISSILE,
	PHYSICS_BOUNCE
};
// Contains common code that projectiles will use
class CPhysicsEntity : public virtual CBaseEntity
{
public:
	float				GravityMultiplier;	// per entity gravity multiplier (1.0 is normal)
											// use for lowgrav artifact, flares
	EPhysicsType		PhysicsType;
	vec3f				AngularVelocity;
	vec3f				Velocity;
	float				Mass;
	struct WaterInfo_t
	{
		EBrushContents		Type;
		EWaterLevel			Level;
	} WaterInfo;

	bool				PhysicsDisabled;
	CPhysicsEntity ();
	CPhysicsEntity (sint32 index);

	class CTrace	PushEntity (vec3f &push);
	inline void		AddGravity ();
	void			Impact (CTrace *trace);
};

// "Bouncy" projectile
class CBounceProjectile : public virtual CPhysicsEntity
{
public:
	float			backOff;

	CBounceProjectile ();
	CBounceProjectile (sint32 index);

	bool			Run ();
};

// Same as bouncy, except doesn't bounce
class CTossProjectile : public virtual CBounceProjectile
{
public:
	CTossProjectile();
	CTossProjectile (sint32 index);
};

// Doesn't add gravity
class CFlyMissileProjectile : public virtual CPhysicsEntity
{
public:
	CFlyMissileProjectile ();
	CFlyMissileProjectile (sint32 index);

	bool			Run ();
};

// Gravity, special edge handling
class CStepPhysics : public virtual CPhysicsEntity
{
public:
	CStepPhysics ();
	CStepPhysics (sint32 index);

	virtual void	CheckGround ();

	sint32				FlyMove (float time, sint32 mask);
	void			AddRotationalFriction ();
	bool			Run ();
};

class CPushPhysics : public virtual CPhysicsEntity
{
public:
	CPushPhysics ();
	CPushPhysics (sint32 Index);

	bool			Run ();
};

class CStopPhysics : public virtual CPushPhysics
{
public:
	CStopPhysics ();
	CStopPhysics (sint32 Index);

	bool			Run ();
};

#else
FILE_WARNING
#endif