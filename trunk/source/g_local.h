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
// g_local.h -- local definitions for game module

#if !defined(__G_LOCAL_H__) || !defined(INCLUDE_GUARDS)
#define __G_LOCAL_H__

#include "cc_options.h"
#include "../shared/shared.h"

#if 0
#include "Newton.h"
#endif

// define GAME_INCLUDE so that game.h does not define the
// short, server-visible gclient_t and edict_t structures,
// because we define the full size ones in this file
#define GAME_INCLUDE
#include "game.h"

// Paril, CleanCode Quake2
#include "cc_shared.h"

// the "gameversion" client command will print this plus compile date
#define GAMEVERSION	"baseq2"

//==================================================================

// view pitching times
#define DAMAGE_TIME		5
#define FALL_TIME		3

#define FRAMETIME		1

// memory tags to allow dynamic memory to be cleaned up
#define TAG_GAME	765		// clear when unloading the dll
#define TAG_LEVEL	766		// clear when loading a new level
#define TAG_CLEAN_GAME	TAG_GAME		// "Clean" memory
#define TAG_CLEAN_LEVEL	TAG_LEVEL		// "Clean" memory

//gib types
typedef int EGibType;
enum
{
	GIB_ORGANIC,
	GIB_METALLIC
};

// power armor types
typedef int EPowerArmorType;
enum
{
	POWER_ARMOR_NONE,
	POWER_ARMOR_SCREEN,
	POWER_ARMOR_SHIELD
};

// handedness values
typedef int EHandedness;
enum
{
	RIGHT_HANDED,
	LEFT_HANDED,
	CENTER_HANDED
};

typedef int ECrossLevelTriggerFlags;
enum
{
	SFL_CROSS_TRIGGER_1		= BIT(0),
	SFL_CROSS_TRIGGER_2		= BIT(1),
	SFL_CROSS_TRIGGER_3		= BIT(2),
	SFL_CROSS_TRIGGER_4		= BIT(3),
	SFL_CROSS_TRIGGER_5		= BIT(4),
	SFL_CROSS_TRIGGER_6		= BIT(5),
	SFL_CROSS_TRIGGER_7		= BIT(6),
	SFL_CROSS_TRIGGER_8		= BIT(7),
	SFL_CROSS_TRIGGER_MASK	= 255
};

// noise types for PlayerNoise
typedef int ENoiseTye;
enum
{
	PNOISE_SELF,
	PNOISE_WEAPON,
	PNOISE_IMPACT
};

//
// this structure is left intact through an entire game
// it should be initialized at dll load time, and read/written to
// the server.ssv file for savegames
//
typedef int EGameMode;
enum //EGameMode
{
	GAME_SINGLEPLAYER		=	BIT(0),
	GAME_DEATHMATCH			=	BIT(1),
	GAME_COOPERATIVE		=	BIT(2),

#ifdef CLEANCTF_ENABLED
	GAME_CTF				=	BIT(3)
#endif
};

typedef struct
{
	char		helpmessage1[128];
	char		helpmessage2[128];
	byte		helpchanged;	// flash F1 icon if non 0, play sound
								// and increment only if 1, 2, or 3

	gclient_t	*clients;		// [maxclients]

	// can't store spawnpoint in level, because
	// it would get overwritten by the savegame restore
	char		spawnpoint[32];	// needed for coop respawns

	// store latched cvars here that we want to get at often
	byte		maxclients;
	byte		maxspectators;
	int			maxentities;
	bool		cheats;
	EGameMode	mode; // Game mode

	// cross level triggers
	int			serverflags;
	bool		autosaved;
} game_locals_t;


//
// this structure is cleared as each map is entered
// it is read/written to the level.sav file for savegames
//
typedef struct
{
	FrameNumber_t	framenum;

	char		level_name[MAX_QPATH];	// the descriptive name (Outer Base, etc)
	char		mapname[MAX_QPATH];		// the server name (base1, etc)
	char		nextmap[MAX_QPATH];		// go here when fraglimit is hit
	char		forcemap[MAX_QPATH];	// go here

	// intermission state
	FrameNumber_t		intermissiontime;		// time the intermission was started
	char		*changemap;
	int			exitintermission;
	vec3f		IntermissionOrigin;
	vec3f		IntermissionAngles;

	CPlayerEntity		*sight_client;	// changed once each frame for coop games

#ifndef MONSTERS_USE_PATHFINDING
	CBaseEntity	*sight_entity;
	int			sight_entity_framenum;
	CBaseEntity	*sound_entity;
	int			sound_entity_framenum;
	CBaseEntity	*sound2_entity;
	int			sound2_entity_framenum;
#else
	class		CPathNode	*NoiseNode;
	float		SoundEntityFramenum;
	CPlayerEntity		*SoundEntity;
#endif

	int			total_secrets;
	int			found_secrets;

	int			total_goals;
	int			found_goals;

	int			total_monsters;
	int			killed_monsters;

	CBaseEntity	*CurrentEntity;	// entity running from G_RunFrame
	int			body_que;			// dead bodies

	int			power_cubes;		// ugly necessity for coop
	uint32		inhibit;
	uint32		EntityNumber;
} level_locals_t;


// spawn_temp_t is only used to hold entity field values that
// can be set from the editor, but aren't actualy present
// in edict_t during gameplay
typedef struct
{
	// world vars
	char		*sky;
	float		skyrotate;
	vec3_t		skyaxis;
	char		*nextmap;

	int			lip;
	int			distance;
	int			height;
	char		*noise;
	float		pausetime;
	char		*item;
	char		*gravity;
} spawn_temp_t;

typedef int EFuncState;
enum
{
	STATE_TOP,
	STATE_BOTTOM,
	STATE_UP,
	STATE_DOWN
};

extern	game_locals_t	game;
extern	level_locals_t	level;
extern	gameExport_t	globals;
extern	spawn_temp_t	st;

// means of death
typedef uint32	EMeansOfDeath;
enum // EMeansOfDeath
{
	MOD_UNKNOWN,
	MOD_BLASTER,
	MOD_SHOTGUN,
	MOD_SSHOTGUN,
	MOD_MACHINEGUN,
	MOD_CHAINGUN,
	MOD_GRENADE,
	MOD_G_SPLASH,
	MOD_ROCKET,
	MOD_R_SPLASH,
	MOD_HYPERBLASTER,
	MOD_RAILGUN,
	MOD_BFG_LASER,
	MOD_BFG_BLAST,
	MOD_BFG_EFFECT,
	MOD_HANDGRENADE,
	MOD_HG_SPLASH,
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_HELD_GRENADE,
	MOD_EXPLOSIVE,
	MOD_BARREL,
	MOD_BOMB,
	MOD_EXIT,
	MOD_SPLASH,
	MOD_TARGET_LASER,
	MOD_TRIGGER_HURT,
	MOD_HIT,
	MOD_TARGET_BLASTER,
#ifdef CLEANCTF_ENABLED
	MOD_GRAPPLE,
#endif

	MOD_FRIENDLY_FIRE		=	512
};

extern	EMeansOfDeath	meansOfDeath;

extern	edict_t			*g_edicts;

#define FOFS(x) (int)&(((edict_t *)0)->x)
#define STOFS(x) (int)&(((spawn_temp_t *)0)->x)
#define LLOFS(x) (int)&(((level_locals_t *)0)->x)
#define CLOFS(x) (int)&(((CClient *)0)->x)

#define irandom(x)	((int)(frand()*(x)))
#define icrandom(x)	((int)(crand()*(x)))
#define random()	(frand())
#define crandom()	(crand())

#define world	(&g_edicts[0])

// Spawnflags
// 6 bits reserved for editor flags
// 8 bits used as power cube id bits for coop games

// item spawnflags
typedef int EItemSpawnflags;
enum
{
	ITEM_TRIGGER_SPAWN			= BIT(0),
	ITEM_NO_TOUCH				= BIT(1),


	DROPPED_ITEM				= BIT(16),
	DROPPED_PLAYER_ITEM			= BIT(17),
	ITEM_TARGETS_USED			= BIT(18)
};

// edict->spawnflags
// these are set with checkboxes on each entity in the map editor
typedef int EEdictSpawnflags;
enum
{
	SPAWNFLAG_NOT_EASY			= BIT(8),
	SPAWNFLAG_NOT_MEDIUM		= BIT(9),
	SPAWNFLAG_NOT_HARD			= BIT(10),
	SPAWNFLAG_NOT_DEATHMATCH	= BIT(11),
	SPAWNFLAG_NOT_COOP			= BIT(12)
};


//
// fields are needed for spawning from the entity string
// and saving / loading games
//
enum
{
	FFL_SPAWNTEMP = 1,
	FFL_NOSPAWN
};

typedef enum {
	F_INT, 
	F_FLOAT,
	F_LSTRING,			// string on disk, pointer in memory, TAG_LEVEL
	F_GSTRING,			// string on disk, pointer in memory, TAG_GAME
	F_VECTOR,
	F_ANGLEHACK,
	F_EDICT,			// index on disk, pointer in memory
	F_ITEM,				// index on disk, pointer in memory
	F_NEWITEM,			// index on disk, pointer in memory
	F_CLIENT,			// index on disk, pointer in memory
	F_FUNCTION,
	F_MMOVE,
	F_IGNORE
} fieldtype_t;

typedef struct
{
	char	*name;
	int		ofs;
	fieldtype_t	type;
	int		flags;
} field_t;


extern	field_t fields[];

//
// g_cmds.c
//
void Cmd_Help_f (CPlayerEntity *ent);
void Cmd_Score_f (CPlayerEntity *ent);

//
// g_utils.c
//
void	G_ProjectSource (const vec3f &point, const vec3f &distance, const vec3f &forward, const vec3f &right, vec3f &result);

void	G_InitEdict (edict_t *e);
edict_t	*G_Spawn (void);
void	G_FreeEdict (edict_t *e);

// Changed to int, rarely used as a float..
CBaseEntity *FindRadius (CBaseEntity *From, vec3f &org, int Radius, uint32 EntityFlags);

template <class ReturnType, uint32 EntityFlags>
ReturnType *FindRadius (CBaseEntity *From, vec3f &org, int Radius)
{
	return dynamic_cast<ReturnType*>(FindRadius (From, org, Radius, EntityFlags));
}

template <uint32 EntityFlags>
inline CBaseEntity *FindRadius (CBaseEntity *From, vec3f &org, int Radius)
{
	return FindRadius (From, org, Radius, EntityFlags);
}

//
// g_combat.c
//
void T_RadiusDamage (CBaseEntity *inflictor, CBaseEntity *attacker, float damage, CBaseEntity *ignore, float radius, EMeansOfDeath mod);

// damage flags
enum
{
	DAMAGE_RADIUS				= BIT(0), // Indirect damage
	DAMAGE_NO_ARMOR				= BIT(1), // Goes through armor
	DAMAGE_ENERGY				= BIT(2), // Energy-based (blaster)
	DAMAGE_NO_KNOCKBACK			= BIT(3), // Don't add knockback
	DAMAGE_BULLET				= BIT(4), // Bullet damage (used for ricochets)
	DAMAGE_NO_PROTECTION		= BIT(5)  // Always damages
};

#define DEFAULT_BULLET_HSPREAD	300
#define DEFAULT_BULLET_VSPREAD	500
#define DEFAULT_SHOTGUN_HSPREAD	1000
#define DEFAULT_SHOTGUN_VSPREAD	500
#define DEFAULT_DEATHMATCH_SHOTGUN_COUNT	12
#define DEFAULT_SHOTGUN_COUNT	12
#define DEFAULT_SSHOTGUN_COUNT	20

//
// g_misc.c
//
void ThrowHead (edict_t *self, MediaIndex gibIndex, int damage, int type);
void BecomeExplosion1(edict_t *self);

//
// g_ai.c
//
void AI_SetSightClient (void);

//
// g_client.c
//
void BeginIntermission (class CTargetChangeLevel *targ);

//
// g_chase.c
//
void UpdateChaseCam(CPlayerEntity *ent);
void ChaseNext(CPlayerEntity *ent);
void ChasePrev(CPlayerEntity *ent);
void GetChaseTarget(CPlayerEntity *ent);

//============================================================================

// client_t->anim_priority
enum
{
	ANIM_BASIC,
	ANIM_WAVE,
	ANIM_JUMP,
	ANIM_PAIN,
	ANIM_ATTACK,
	ANIM_DEATH,
	ANIM_REVERSE
};

// this structure is cleared on each PutClientInServer(),
// except for 'client->pers'
struct gclient_s
{
	// known to server
	playerState_t	playerState;				// communicated by server to clients
	int				ping;
};

class CKeyValuePair
{
public:
	char	*Key;
	char	*Value;

	CKeyValuePair (char *Key, char *Value) :
	Key((Key) ? Mem_PoolStrDup(Key, com_gamePool, 0) : NULL),
	Value((Key) ? Mem_PoolStrDup(Value, com_gamePool, 0) : NULL)
	{
	};

	~CKeyValuePair ()
	{
		if (Key)
			QDelete Key;
		if (Value)
			QDelete Value;
	};
};

struct edict_s
{
	entityStateOld_t	state;
	struct gclient_s	*client;	// NULL if not a player
									// the server expects the first part
									// of gclient_s to be a player_state_t
									// but the rest of it is opaque
	bool				inUse;
	int					linkCount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t				area;				// linked to a division node or leaf
	
	int					numClusters;		// if -1, use headnode instead
	int					clusterNums[MAX_ENT_CLUSTERS];
	int					headNode;			// unused if numClusters != -1
	int					areaNum, areaNum2;

	//================================

	int					svFlags;			// SVF_NOCLIENT, SVF_DEADMONSTER, SVF_MONSTER, etc
	vec3_t				mins, maxs;
	vec3_t				absMin, absMax, size;
	solid_t				solid;
	int					clipMask;
	struct edict_s		*owner;


	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!

	//================================
	std::list<CKeyValuePair*>	*ParseData;

	char				*model;
	FrameNumber_t		freetime;			// sv.time when the object was freed
	
	//
	// only used locally in game, not by server
	//
	char		*classname;

	FrameNumber_t		timestamp;

	float		angle;			// set in qe3, -1 = up, -2 = down
	char		*target;
	char		*targetname;
	char		*killtarget;
	char		*team;
	char		*pathtarget;
	char		*deathtarget;
	char		*combattarget;

	float		speed, accel, decel;

	float		gravity;		// per entity gravity multiplier (1.0 is normal)
								// use for lowgrav artifact, flares

	edict_t		*goalentity;
	edict_t		*movetarget;

	FrameNumber_t		pain_debounce_time;
	FrameNumber_t		damage_debounce_time;

	int			show_hostile;

	FrameNumber_t		powerarmor_time;

	char		*map;			// target_changelevel

	int			viewheight;		// height above origin where eyesight is determined
	int			dmg;
	int			radius_dmg;
	float		dmg_radius;
	int			sounds;			//make this a spawntemp var?
	int			count;

	MediaIndex			noise_index;
	MediaIndex			noise_index2;
	float		volume;
	float		attenuation;

	// timing variables
	float		wait;
	float		delay;			// before firing targets
	float		random;

	FrameNumber_t		teleport_time;

	int			watertype;
	int			waterlevel;
	int			light_level;
	int			style;			// also used as areaportal number

	// Paril
	CBaseItem		*item;
	CBaseEntity		*Entity;
#if 0
	const NewtonBody	*newtonBody;
#endif
};

extern	CCvar	*maxentities;
extern	CCvar	*deathmatch;
extern	CCvar	*coop;
extern	CCvar	*dmflags;
extern	CCvar	*skill;
extern	CCvar	*fraglimit;
extern	CCvar	*timelimit;
extern	CCvar	*password;
extern	CCvar	*spectator_password;
extern	CCvar	*needpass;
extern	CCvar	*g_select_empty;
extern	CCvar	*dedicated;

extern	CCvar	*filterban;

extern	CCvar	*sv_gravity;

extern	CCvar	*gun_x, *gun_y, *gun_z;
extern	CCvar	*sv_rollspeed;
extern	CCvar	*sv_rollangle;

extern	CCvar	*run_pitch;
extern	CCvar	*run_roll;
extern	CCvar	*bob_up;
extern	CCvar	*bob_pitch;
extern	CCvar	*bob_roll;

extern	CCvar	*developer;

extern	CCvar	*sv_cheats;
extern	CCvar	*maxclients;
extern	CCvar	*maxspectators;

extern	CCvar	*flood_msgs;
extern	CCvar	*flood_persecond;
extern	CCvar	*flood_waitdelay;

extern	CCvar	*sv_maplist;
extern	CCvar	*map_debug;
extern	CCvar	*cc_techflags;

#ifdef CLEANCTF_ENABLED
extern	CCvar	*capturelimit;
extern	CCvar	*instantweap;
#endif

#ifdef CLEANCTF_ENABLED
#include "cc_ctf.h"
#endif

extern CBaseEntity *World;

#else
FILE_WARNING
#endif