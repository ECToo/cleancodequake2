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
// cc_brushmodels.h
// 
//

#if !defined(__CC_BRUSHMODELS_H__) || !defined(INCLUDE_GUARDS)
#define __CC_BRUSHMODELS_H__

enum
{
	BRUSHTHINK_NONE,

	BRUSHTHINK_MOVEBEGIN,
	BRUSHTHINK_MOVEFINAL,
	BRUSHTHINK_MOVEDONE,

	BRUSHTHINK_MOVEACCEL,

	BRUSHTHINK_AMOVEBEGIN,
	BRUSHTHINK_AMOVEFINAL,
	BRUSHTHINK_AMOVEDONE,

	BRUSHTHINK_CUSTOM_START,
};

// Contains code common to brush models
class CBrushModel : public virtual CBaseEntity, public CThinkableEntity, public CPushPhysics, public CStopPhysics
{
public:
	int32		TouchDebounce;

	// fixed data
	vec3_t		StartOrigin;
	vec3_t		StartAngles;
	vec3_t		EndOrigin;
	vec3_t		EndAngles;

	MediaIndex	SoundStart;
	MediaIndex	SoundMiddle;
	MediaIndex	SoundEnd;

	float		Accel;
	float		Speed;
	float		Decel;
	float		Distance;

	float		Wait;

	// state data
	int			MoveState;
	vec3_t		Dir;
	float		CurrentSpeed;
	float		MoveSpeed;
	float		NextSpeed;
	float		RemainingDistance;
	float		DecelDistance;
	uint32		EndFunc;
	virtual void	DoEndFunc () {};

	uint32		ThinkType;

	CBrushModel ();
	CBrushModel (int Index);

	// Origin/velocity
	void MoveDone ();
	void MoveFinal ();
	void MoveBegin ();
	void MoveCalc (vec3_t dest, uint32 EndFunc);

	// Angle/avelocity
	void AngleMoveDone ();
	void AngleMoveFinal ();
	void AngleMoveBegin ();
	void AngleMoveCalc (uint32 EndFunc);

	// Accel
	inline float AccelerationDistance (const float target, const float rate)
	{
		return (target * ((target / rate) + 1) / 2);
	}

	void CalcAcceleratedMove();
	void Accelerate ();
	void ThinkAccelMove ();

	virtual void Think ();
	bool Run ();
};

class CPlatForm : public CMapEntity, public CBrushModel, public CBlockableEntity, public CUsableEntity
{
public:
	enum
	{
		PLATTHINK_GO_DOWN = BRUSHTHINK_CUSTOM_START
	};
	CPlatForm();
	CPlatForm(int Index);

	bool Run ();
	void Blocked (CBaseEntity *other);
	void Use (CBaseEntity *other, CBaseEntity *activator);
	void HitTop ();
	void HitBottom ();

	enum
	{
		PLATENDFUNC_HITBOTTOM,
		PLATENDFUNC_HITTOP
	};

	void DoEndFunc ();
	void GoDown ();
	void GoUp ();
	void Think ();

	class CPlatFormInsideTrigger : public CTouchableEntity
	{
	public:
		CPlatFormInsideTrigger::CPlatFormInsideTrigger ();
		CPlatFormInsideTrigger::CPlatFormInsideTrigger (int Index);
		void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);
	};

	void SpawnInsideTrigger ();
	void Spawn ();
};

// Base door class
class CDoor : public CMapEntity, public CBrushModel, public CHurtableEntity, public CBlockableEntity, public CTouchableEntity, public CUsableEntity
{
public:
	enum
	{
		DOORTHINK_SPAWNDOORTRIGGER = BRUSHTHINK_CUSTOM_START,
		DOORTHINK_CALCMOVESPEED,

		DOORTHINK_GODOWN,
	};
	CDoor();
	CDoor(int Index);

	void UseAreaPortals (bool isOpen);
	bool Run ();

	enum
	{
		DOORENDFUNC_HITBOTTOM,
		DOORENDFUNC_HITTOP
	};

	virtual void HitTop ();
	virtual void HitBottom ();
	virtual void GoDown ();
	virtual void GoUp (CBaseEntity *activator);
	virtual void DoEndFunc ();
	virtual void Think ();

	class CDoorTrigger : public CTouchableEntity
	{
	public:
		int32		TouchDebounce;

		CDoorTrigger::CDoorTrigger ();
		CDoorTrigger::CDoorTrigger (int Index);

		void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);
	};

	virtual void Blocked (CBaseEntity *other);
	virtual void Use (CBaseEntity *other, CBaseEntity *activator);
	virtual void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point);
	virtual void Pain (CBaseEntity *other, float kick, int damage);
	virtual void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);

	// Thinks
	void SpawnDoorTrigger ();
	void CalcMoveSpeed ();

	virtual void Spawn ();
};

class CRotatingDoor : public CDoor
{
public:
	CRotatingDoor ();
	CRotatingDoor (int Index);

	void GoDown();
	void GoUp (CBaseEntity *activator);

	void Spawn ();
};

class CMovableWater : public CDoor
{
public:
	CMovableWater ();
	CMovableWater (int Index);

	void Spawn ();
};

class CDoorSecret : public CDoor
{
public:
	enum
	{
		DOORSECRETTHINK_6 = BRUSHTHINK_CUSTOM_START,
		DOORSECRETTHINK_4,
		DOORSECRETTHINK_2
	};

	enum
	{
		DOORSECRETENDFUNC_DONE,
		DOORSECRETENDFUNC_5,
		DOORSECRETENDFUNC_3,
		DOORSECRETENDFUNC_1
	};

	CDoorSecret ();
	CDoorSecret (int Index);

	void Blocked (CBaseEntity *other);
	void Use (CBaseEntity *other, CBaseEntity *activator);
	void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point);

	void DoEndFunc ();
	void Think ();

	void Spawn ();
};

class CButton : public CMapEntity, public CBrushModel, public CHurtableEntity, public CTouchableEntity, public CUsableEntity
{
public:
	enum
	{
		BUTTONTHINK_RETURN = BRUSHTHINK_CUSTOM_START,
	};
	CButton();
	CButton(int Index);

	bool Run ();

	enum
	{
		BUTTONENDFUNC_WAIT,
		BUTTONENDFUNC_DONE
	};

	virtual void DoEndFunc ();
	virtual void Think ();
	virtual void Fire ();

	virtual void Use (CBaseEntity *other, CBaseEntity *activator);
	virtual void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point);
	virtual void Pain (CBaseEntity *other, float kick, int damage);
	virtual void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);

	virtual void Spawn ();
};

class CTrainBase : public CMapEntity, public CBrushModel, public CBlockableEntity, public CUsableEntity
{
public:
	enum
	{
		TRAINTHINK_FIND = BRUSHTHINK_CUSTOM_START,
		TRAINTHINK_NEXT,
	};
	CTrainBase();
	CTrainBase(int Index);

	virtual bool Run ();

	enum
	{
		TRAINENDFUNC_WAIT,
	};

	void TrainWait ();
	void Next ();
	void Resume ();
	void Find ();

	virtual void DoEndFunc ();
	virtual void Think ();

	virtual void Blocked (CBaseEntity *other);
	virtual void Use (CBaseEntity *other, CBaseEntity *activator);

	virtual void Spawn ();
};

class CTrain : public CTrainBase
{
public:
	CTrain ();
	CTrain (int Index);

	void Spawn ();
};

class CTriggerElevator : public CMapEntity, public CThinkableEntity, public CUsableEntity
{
public:
	CTrain			*MoveTarget;
	bool			Usable;

	CTriggerElevator ();
	CTriggerElevator (int Index);

	void Think ();
	void Use (CBaseEntity *other, CBaseEntity *activator);

	void Spawn ();
};

class CWorldEntity : public CBrushModel
{
public:
	CWorldEntity ();
	CWorldEntity (int Index);

	bool Run ();
	void Spawn ();
};

class CRotatingBrush : public CMapEntity, public CBrushModel, public CUsableEntity, public CBlockableEntity, public CTouchableEntity
{
public:
	bool Blockable;

	CRotatingBrush ();
	CRotatingBrush (int Index);

	void Use (CBaseEntity *other, CBaseEntity *activator);
	void Blocked (CBaseEntity *other);
	void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);

	bool Run ();
	void Spawn ();
};

class CConveyor : public CMapEntity, public CBrushModel, public CUsableEntity
{
public:
	CConveyor ();
	CConveyor (int Index);

	void Use (CBaseEntity *other, CBaseEntity *activator);

	bool Run ();
	void Spawn ();
};

class CAreaPortal : public CMapEntity, public CUsableEntity
{
public:
	CAreaPortal ();
	CAreaPortal (int Index);

	void Use (CBaseEntity *other, CBaseEntity *activator);

	bool Run ();
	void Spawn ();
};

class CFuncWall : public CMapEntity, public CBrushModel, public CUsableEntity
{
public:
	bool Usable;

	CFuncWall ();
	CFuncWall (int Index);

	void Use (CBaseEntity *other, CBaseEntity *activator);

	bool Run ();
	void Spawn ();
};

class CFuncObject : public CMapEntity, public CBrushModel, public CTossProjectile, public CTouchableEntity, public CUsableEntity
{
public:
	bool Usable;

	CFuncObject ();
	CFuncObject (int Index);

	void Think ();
	void Use (CBaseEntity *other, CBaseEntity *activator);
	void Touch (CBaseEntity *other, plane_t *plane, cmBspSurface_t *surf);

	bool Run ();
	void Spawn ();
};

class CFuncExplosive : public CMapEntity, public CBrushModel, public CUsableEntity, public CHurtableEntity
{
public:
	enum EFuncExplosiveUseType
	{
		FUNCEXPLOSIVE_USE_NONE,
		FUNCEXPLOSIVE_USE_SPAWN,
		FUNCEXPLOSIVE_USE_EXPLODE
	};

	EFuncExplosiveUseType	UseType;

	CFuncExplosive ();
	CFuncExplosive (int Index);

	void DoSpawn ();

	void Use (CBaseEntity *other, CBaseEntity *activator);
	void Pain (CBaseEntity *other, float kick, int damage);
	void Die (CBaseEntity *inflictor, CBaseEntity *attacker, int damage, vec3_t point);

	bool Run ();
	void Spawn ();
};

class CKillbox : public CMapEntity, public CUsableEntity
{
public:
	CKillbox ();
	CKillbox (int Index);

	void Use (CBaseEntity *other, CBaseEntity *activator);
	void Spawn ();
};

#else
FILE_WARNING
#endif