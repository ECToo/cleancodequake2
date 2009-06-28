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

// "Hurtable" entity
enum EDeadFlags
{
	DF_ALIVE,
	DF_DYING,
	DF_DEAD
};

class CHurtableEntity abstract : public virtual CBaseEntity
{
public:
	int			Health;
	int			MaxHealth;
	int			GibHealth;
	EDeadFlags	DeadFlag;
	bool		CanTakeDamage;
	CBaseEntity	*Enemy;

	CHurtableEntity ();
	CHurtableEntity (int index);

	virtual void Pain (CBaseEntity *other, float kick, int damage) = 0;
	virtual void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point) = 0;
};

// Thinkable entity
// Simple think function
class CThinkableEntity abstract : public virtual CBaseEntity
{
public:
	int32		NextThink;

	CThinkableEntity ();
	CThinkableEntity (int index);

	void			RunThink ();
	virtual void	Think () = 0;
};

// Touchable entity
class CTouchableEntity abstract : public virtual CBaseEntity
{
public:
	CTouchableEntity ();
	CTouchableEntity (int index);

	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);
};

// Contains common code that projectiles will use
class CPhysicsEntity abstract : public virtual CBaseEntity
{
public:
	CPhysicsEntity ();
	CPhysicsEntity (int index);

	virtual void	Think () {};
	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf) {};

	class CTrace	PushEntity (vec3_t push);
	inline void		AddGravity ();
	void			Impact (CTrace *trace);
};

// "Bouncy" projectile
class CBounceProjectile abstract : public CPhysicsEntity, public CTouchableEntity, public CThinkableEntity
{
protected:
	float			backOff;
public:
	CBounceProjectile ();
	CBounceProjectile (int index);

	virtual void	Think () {};
	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf) {};

	bool			Run ();
};

// Same as bouncy, except doesn't bounce
class CTossProjectile abstract : public CBounceProjectile
{
public:
	CTossProjectile();
	CTossProjectile (int index);

	virtual void	Think () {};
	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf) {};
};

// Doesn't add gravity
class CFlyMissileProjectile abstract : public CPhysicsEntity, public CTouchableEntity, public CThinkableEntity
{
public:
	CFlyMissileProjectile ();
	CFlyMissileProjectile (int index);

	virtual void	Think () {};
	virtual void	Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf) {};

	bool			Run ();
};