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

#include "g_local.h"

typedef struct
{
	char	*name;
	void	(*spawn)(edict_t *ent);
} spawn_t;


/*void SP_item_health (edict_t *self);
void SP_item_health_small (edict_t *self);
void SP_item_health_large (edict_t *self);
void SP_item_health_mega (edict_t *self);*/

void SP_info_player_start (edict_t *ent);
void SP_info_player_deathmatch (edict_t *ent);
void SP_info_player_coop (edict_t *ent);
void SP_info_player_intermission (edict_t *ent);

void SP_func_plat (edict_t *ent);
void SP_func_rotating (edict_t *ent);
void SP_func_button (edict_t *ent);
void SP_func_door (edict_t *ent);
void SP_func_door_secret (edict_t *ent);
void SP_func_door_rotating (edict_t *ent);
void SP_func_water (edict_t *ent);
void SP_func_train (edict_t *ent);
void SP_func_conveyor (edict_t *self);
void SP_func_wall (edict_t *self);
void SP_func_object (edict_t *self);
void SP_func_explosive (edict_t *self);
void SP_func_timer (edict_t *self);
void SP_func_areaportal (edict_t *ent);
void SP_func_clock (edict_t *ent);
void SP_func_killbox (edict_t *ent);

void SP_trigger_always (edict_t *ent);
void SP_trigger_once (edict_t *ent);
void SP_trigger_multiple (edict_t *ent);
void SP_trigger_relay (edict_t *ent);
void SP_trigger_push (edict_t *ent);
void SP_trigger_hurt (edict_t *ent);
void SP_trigger_key (edict_t *ent);
void SP_trigger_counter (edict_t *ent);
void SP_trigger_elevator (edict_t *ent);
void SP_trigger_gravity (edict_t *ent);
void SP_trigger_teleport (edict_t *ent);
void SP_trigger_monsterjump (edict_t *ent);

void SP_target_temp_entity (edict_t *ent);
void SP_target_speaker (edict_t *ent);
void SP_target_explosion (edict_t *ent);
void SP_target_changelevel (edict_t *ent);
void SP_target_secret (edict_t *ent);
void SP_target_goal (edict_t *ent);
void SP_target_splash (edict_t *ent);
void SP_target_spawner (edict_t *ent);
void SP_target_blaster (edict_t *ent);
void SP_target_crosslevel_trigger (edict_t *ent);
void SP_target_crosslevel_target (edict_t *ent);
void SP_target_laser (edict_t *self);
void SP_target_help (edict_t *self);
void SP_target_actor (edict_t *self);
void SP_target_location (edict_t *self);
void SP_target_position (edict_t *self);
void SP_target_lightramp (edict_t *self);
void SP_target_earthquake (edict_t *ent);
void SP_target_character (edict_t *ent);
void SP_target_string (edict_t *ent);

void SP_worldspawn (edict_t *ent);
void SP_viewthing (edict_t *ent);

void SP_light (edict_t *self);
void SP_light_mine1 (edict_t *ent);
void SP_light_mine2 (edict_t *ent);
void SP_info_null (edict_t *self);
void SP_info_notnull (edict_t *self);
void SP_path_corner (edict_t *self);
void SP_point_combat (edict_t *self);

void SP_misc_banner (edict_t *self);
void SP_misc_satellite_dish (edict_t *self);
void SP_misc_actor (edict_t *self);
void SP_misc_gib_arm (edict_t *self);
void SP_misc_gib_leg (edict_t *self);
void SP_misc_gib_head (edict_t *self);
void SP_misc_insane (edict_t *self);
void SP_misc_deadsoldier (edict_t *self);
void SP_misc_viper (edict_t *self);
void SP_misc_viper_bomb (edict_t *self);
void SP_misc_bigviper (edict_t *self);
void SP_misc_strogg_ship (edict_t *self);
void SP_misc_teleporter (edict_t *self);
void SP_misc_teleporter_dest (edict_t *self);
void SP_misc_blackhole (edict_t *self);
void SP_misc_eastertank (edict_t *self);
void SP_misc_easterchick (edict_t *self);
void SP_misc_easterchick2 (edict_t *self);
void SP_misc_model (edict_t *self);

void SP_turret_breach (edict_t *self);
void SP_turret_base (edict_t *self);
//void SP_turret_driver (edict_t *self);

spawn_t	spawns[] = {
	/*{"item_health", SP_item_health},
	{"item_health_small", SP_item_health_small},
	{"item_health_large", SP_item_health_large},
	{"item_health_mega", SP_item_health_mega},*/

	{"info_player_start", SP_info_player_start},
	{"info_player_deathmatch", SP_info_player_deathmatch},
	{"info_player_coop", SP_info_player_coop},
	{"info_player_intermission", SP_info_player_intermission},
#ifdef CLEANCTF_ENABLED
//ZOID
	{"info_player_team1", SP_info_player_team1},
	{"info_player_team2", SP_info_player_team2},
//ZOID
#endif

	{"func_plat", SP_func_plat},
	{"func_button", SP_func_button},
	{"func_door", SP_func_door},
	{"func_door_secret", SP_func_door_secret},
	{"func_door_rotating", SP_func_door_rotating},
	{"func_rotating", SP_func_rotating},
	{"func_train", SP_func_train},
	{"func_water", SP_func_water},
	{"func_conveyor", SP_func_conveyor},
	{"func_areaportal", SP_func_areaportal},
	{"func_clock", SP_func_clock},
	{"func_wall", SP_func_wall},
	{"func_object", SP_func_object},
	{"func_timer", SP_func_timer},
	{"func_explosive", SP_func_explosive},
	{"func_killbox", SP_func_killbox},

	{"trigger_always", SP_trigger_always},
	{"trigger_once", SP_trigger_once},
	{"trigger_multiple", SP_trigger_multiple},
	{"trigger_relay", SP_trigger_relay},
	{"trigger_push", SP_trigger_push},
	{"trigger_hurt", SP_trigger_hurt},
	{"trigger_key", SP_trigger_key},
	{"trigger_counter", SP_trigger_counter},
	{"trigger_elevator", SP_trigger_elevator},
	{"trigger_gravity", SP_trigger_gravity},
	{"trigger_monsterjump", SP_trigger_monsterjump},
#ifdef CLEANCTF_ENABLED
//ZOID
	{"trigger_teleport", SP_trigger_teleport},
	{"info_teleport_destination", SP_info_teleport_destination},
//ZOID
#endif

	{"target_temp_entity", SP_target_temp_entity},
	{"target_speaker", SP_target_speaker},
	{"target_explosion", SP_target_explosion},
	{"target_changelevel", SP_target_changelevel},
	{"target_secret", SP_target_secret},
	{"target_goal", SP_target_goal},
	{"target_splash", SP_target_splash},
	{"target_spawner", SP_target_spawner},
	{"target_blaster", SP_target_blaster},
	{"target_crosslevel_trigger", SP_target_crosslevel_trigger},
	{"target_crosslevel_target", SP_target_crosslevel_target},
	{"target_laser", SP_target_laser},
	{"target_help", SP_target_help},
	//{"target_actor", SP_target_actor},
	{"target_lightramp", SP_target_lightramp},
	{"target_location", SP_target_location},
	{"target_position", SP_target_position},
	{"target_earthquake", SP_target_earthquake},
	{"target_character", SP_target_character},
	{"target_string", SP_target_string},

	{"worldspawn", SP_worldspawn},
	{"viewthing", SP_viewthing},

	{"light", SP_light},
	{"light_mine1", SP_light_mine1},
	{"light_mine2", SP_light_mine2},
	{"info_null", SP_info_null},
	{"func_group", SP_info_null},
	{"info_notnull", SP_info_notnull},
	{"path_corner", SP_path_corner},
	{"point_combat", SP_point_combat},

	//{"misc_explobox", SP_misc_explobox},
	{"misc_banner", SP_misc_banner},
	{"misc_satellite_dish", SP_misc_satellite_dish},
	//{"misc_actor", SP_misc_actor},
	{"misc_gib_arm", SP_misc_gib_arm},
	{"misc_gib_leg", SP_misc_gib_leg},
	{"misc_gib_head", SP_misc_gib_head},
	//{"misc_insane", SP_misc_insane},
	{"misc_deadsoldier", SP_misc_deadsoldier},
	{"misc_viper", SP_misc_viper},
	{"misc_viper_bomb", SP_misc_viper_bomb},
	{"misc_bigviper", SP_misc_bigviper},
	{"misc_strogg_ship", SP_misc_strogg_ship},
	{"misc_teleporter", SP_misc_teleporter},
	{"misc_teleporter_dest", SP_misc_teleporter_dest},
	{"misc_blackhole", SP_misc_blackhole},
	{"misc_eastertank", SP_misc_eastertank},
	{"misc_easterchick", SP_misc_easterchick},
	{"misc_easterchick2", SP_misc_easterchick2},
	{"misc_model", SP_misc_model},
#ifdef CLEANCTF_ENABLED
//ZOID
	{"misc_ctf_banner", SP_misc_ctf_banner},
	{"misc_ctf_small_banner", SP_misc_ctf_small_banner},
//ZOID
#endif

/*	{"monster_berserk", SP_monster_berserk},
	{"monster_gladiator", SP_monster_gladiator},
	{"monster_gunner", SP_monster_gunner},
	{"monster_infantry", SP_monster_infantry},
	{"monster_soldier_light", SP_monster_soldier_light},
	{"monster_soldier", SP_monster_soldier},
	{"monster_soldier_ss", SP_monster_soldier_ss},
	{"monster_tank", SP_monster_tank},
	{"monster_tank_commander", SP_monster_tank},
	{"monster_medic", SP_monster_medic},
	{"monster_flipper", SP_monster_flipper},
	{"monster_chick", SP_monster_chick},
	{"monster_parasite", SP_monster_parasite},
	{"monster_flyer", SP_monster_flyer},
	{"monster_brain", SP_monster_brain},
	{"monster_floater", SP_monster_floater},
	{"monster_hover", SP_monster_hover},
	{"monster_mutant", SP_monster_mutant},
	{"monster_supertank", SP_monster_supertank},
	{"monster_boss2", SP_monster_boss2},
	{"monster_boss3_stand", SP_monster_boss3_stand},
	{"monster_jorg", SP_monster_jorg},
	{"monster_makron", SP_monster_makron},

	{"monster_commander_body", SP_monster_commander_body},*/

	{"turret_breach", SP_turret_breach},
	{"turret_base", SP_turret_base},
	//{"turret_driver", SP_turret_driver},

	{NULL, NULL}
};

/*
===============
ED_CallSpawn

Finds the spawn function for the entity and calls it
===============
*/
void ED_CallSpawn (edict_t *ent)
{
	spawn_t	*s;
	if (!ent->classname)
	{
		//gi.dprintf ("ED_CallSpawn: NULL classname\n");
		MapPrint (MAPPRINT_ERROR, ent, ent->state.origin, "NULL classname!\n");
		return;
	}

	// check item spawn functions
	if (ItemExists(ent))
		return;

	if ((ent->Monster = FindMonster(ent->classname)) != NULL)
	{
		ent->Monster->Allocate(ent);
		ent->Monster->Init (ent);
		return;
	}
	else
		ent->Monster = NULL;

	// Check CleanCode stuff
	CBaseEntity *MapEntity = ResolveMapEntity(ent);
	if (MapEntity != NULL)
		return;

	// check normal spawn functions
	for (s=spawns ; s->name ; s++)
	{
		if (!strcmp(s->name, ent->classname))
		{	// found it
			s->spawn (ent);
			return;
		}
	}
	//gi.dprintf ("%s doesn't have a spawn function\n", ent->classname);
	MapPrint (MAPPRINT_ERROR, ent, ent->state.origin, "Invalid entity (no spawn function)\n");
}

/*
=============
ED_NewString
=============
*/
char *ED_NewString (char *string)
{
	size_t l = strlen(string) + 1;
	char *newb = QNew (com_levelPool, 0) char[l];
	char *new_p = newb;

	for (size_t i=0 ; i< l ; i++)
	{
		if (string[i] == '\\' && i < l-1)
		{
			i++;
			if (string[i] == 'n')
				*new_p++ = '\n';
			else
				*new_p++ = '\\';
		}
		else
			*new_p++ = string[i];
	}
	
	return newb;
}


/*
===============
ED_ParseField

Takes a key/value pair and sets the binary values
in an edict
===============
*/
static void ED_ParseField (char *key, char *value, edict_t *ent)
{
	field_t	*f;
	byte	*b;
	float	v;
	vec3_t	vec;

	for (f=fields ; f->name ; f++)
	{
		if (!(f->flags & FFL_NOSPAWN) && !Q_stricmp(f->name, key))
		{	// found it
			if (f->flags & FFL_SPAWNTEMP)
				b = (byte *)&st;
			else
				b = (byte *)ent;

			switch (f->type)
			{
			case F_LSTRING:
				*(char **)(b+f->ofs) = ED_NewString (value);
				break;
			case F_VECTOR:
				sscanf_s (value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
				((float *)(b+f->ofs))[0] = vec[0];
				((float *)(b+f->ofs))[1] = vec[1];
				((float *)(b+f->ofs))[2] = vec[2];
				break;
			case F_INT:
				*(int *)(b+f->ofs) = atoi(value);
				break;
			case F_FLOAT:
				*(float *)(b+f->ofs) = atof(value);
				break;
			case F_ANGLEHACK:
				v = atof(value);
				((float *)(b+f->ofs))[0] = 0;
				((float *)(b+f->ofs))[1] = v;
				((float *)(b+f->ofs))[2] = 0;
				break;
			case F_IGNORE:
				break;
			}
			return;
		}
	}
	//gi.dprintf ("%s is not a field\n", key);
	MapPrint (MAPPRINT_ERROR, ent, ent->state.origin, "\"%s\" is not a field\n", key);
}

/*
====================
ED_ParseEdict

Parses an edict out of the given string, returning the new position
ed should be a properly initialized empty edict.
====================
*/
static char *ED_ParseEdict (char *data, edict_t *ent)
{
	bool	init;
	char	keyName[256];
	char	*token;

	init = false;
	memset (&st, 0, sizeof(st));

	// Go through all the dictionary pairs
	for ( ; ; ) {
		// Parse key
		token = Com_Parse (&data);
		if (token[0] == '}')
			break;
		if (!data)
			gi.error ("ED_ParseEntity: EOF without closing brace");

		Q_strncpyz (keyName, token, sizeof(keyName));
		
		// Parse value	
		token = Com_Parse (&data);
		if (!data)
			gi.error ("ED_ParseEntity: EOF without closing brace");
		if (token[0] == '}')
			gi.error ("ED_ParseEntity: closing brace without data");

		init = true;	

		// Keynames with a leading underscore are used for utility comments,
		// and are immediately discarded by quake
		if (keyName[0] == '_')
			continue;

		ED_ParseField (keyName, token, ent);
	}

	if (!init)
		memset (ent, 0, sizeof(*ent));

	return data;
}


/*
================
G_FindTeams

Chain together all entities with a matching team field.

All but the first will have the FL_TEAMSLAVE flag set.
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams (void)
{
	edict_t	*e, *e2, *chain;
	int		i, j;
	int		c, c2;

	c = 0;
	c2 = 0;
	for (i=1, e=g_edicts+i ; i < globals.numEdicts ; i++,e++)
	{
		if (!e->inUse)
			continue;
		if (!e->team)
			continue;
		if (e->flags & FL_TEAMSLAVE)
			continue;
		chain = e;
		e->teammaster = e;
		c++;
		c2++;
		for (j=i+1, e2=e+1 ; j < globals.numEdicts ; j++,e2++)
		{
			if (!e2->inUse)
				continue;
			if (!e2->team)
				continue;
			if (e2->flags & FL_TEAMSLAVE)
				continue;
			if (!strcmp(e->team, e2->team))
			{
				c2++;
				chain->teamchain = e2;
				e2->teammaster = e;
				chain = e2;
				e2->flags |= FL_TEAMSLAVE;
			}
		}
	}

	DebugPrintf ("%i teams with %i entities\n", c, c2);
}


/*
==============
SpawnEntities

Creates a server's entity / program execution context by
parsing textual entity definitions out of an ent file.
==============
*/
extern int entityNumber;
#include "cc_exceptionhandler.h"

void InitEntities ()
{
	// Set up the world
	edict_t *theWorld = &g_edicts[0];
	if (!theWorld->Entity)
		theWorld->Entity = QNew (com_levelPool, 0) CWorldEntity(0);

	// Set up the client entities
	for (int i = 1; i <= game.maxclients; i++)
	{
		edict_t *ent = &g_edicts[i];

		if (!ent->Entity)
			ent->Entity = QNew (com_gamePool, 0) CPlayerEntity(i);
	}
}

extern CPlayerEntity **SavedClients;

char *gEntString;
void SpawnEntities (char *mapname, char *entities, char *spawnpoint)
{
#ifdef CC_USE_EXCEPTION_HANDLER
__try
{
#endif
	edict_t		*ent;
	int			inhibit;
	char		*token;
	int			i;
	int		skill_level;
	uint32 startTime = Sys_Milliseconds();

	entityNumber = 0;
	InitMapCounter();

	skill_level = skill->Integer();
	if (skill_level < 0)
		skill_level = 0;
	if (skill_level > 3)
		skill_level = 3;
	if (skill->Integer() != skill_level)
		skill->Set(Q_VarArgs("%i", skill_level), true);

	CPlayerEntity::SaveClientData ();

	Mem_FreePool (com_levelPool);
	gEntString = Mem_PoolStrDup(entities, com_levelPool, 0);

	entities = CC_ParseSpawnEntities (mapname, entities);

#ifdef MONSTERS_USE_PATHFINDING
	InitNodes ();
#endif

	memset (&level, 0, sizeof(level));
	memset (g_edicts, 0, game.maxentities * sizeof(g_edicts[0]));

	Q_strncpyz (level.mapname, mapname, sizeof(level.mapname)-1);
	Q_strncpyz (game.spawnpoint, spawnpoint, sizeof(game.spawnpoint)-1);

	// set client fields on player ents
	for (i=0 ; i<game.maxclients ; i++)
	{
		// Reset the entity states
		g_edicts[i+1].Entity = SavedClients[i];
		g_edicts[i+1].client = game.clients + i;
	}

	QDelete[] SavedClients;

	InitEntities ();

	ent = NULL;
	inhibit = 0;

	// Parse ents
	for ( ; ; ) {
		// Parse the opening brace
		token = Com_Parse (&entities);
		if (!entities)
			break;
		if (token[0] != '{')
			gi.error ("ED_LoadFromFile: found %s when expecting {", token);

		if (!ent)
			ent = g_edicts;
		else
			ent = G_Spawn ();
		entities = ED_ParseEdict (entities, ent);

		// Yet another map hack
		if (!Q_stricmp(level.mapname, "command") && !Q_stricmp(ent->classname, "trigger_once") && !Q_stricmp(ent->model, "*27"))
			ent->spawnflags &= ~SPAWNFLAG_NOT_HARD;

		entityNumber++;
		// Remove things (except the world) from different skill levels or deathmatch
		if (ent != g_edicts)
		{
			if (game.mode & GAME_DEATHMATCH)
			{
				if ( ent->spawnflags & SPAWNFLAG_NOT_DEATHMATCH )
				{
					G_FreeEdict (ent);	
					inhibit++;
					continue;
				}
			}
			else
			{
				if ( /* ((game.mode == GAME_COOPERATIVE) && (ent->spawnflags & SPAWNFLAG_NOT_COOP)) || */
					((skill->Integer() == 0) && (ent->spawnflags & SPAWNFLAG_NOT_EASY)) ||
					((skill->Integer() == 1) && (ent->spawnflags & SPAWNFLAG_NOT_MEDIUM)) ||
					(((skill->Integer() == 2) || (skill->Integer() == 3)) && (ent->spawnflags & SPAWNFLAG_NOT_HARD))
					)
					{
						G_FreeEdict (ent);	
						inhibit++;
						continue;
					}
			}

			ent->spawnflags &= ~(SPAWNFLAG_NOT_EASY|SPAWNFLAG_NOT_MEDIUM|SPAWNFLAG_NOT_HARD|SPAWNFLAG_NOT_COOP|SPAWNFLAG_NOT_DEATHMATCH);
		}

		ED_CallSpawn (ent);
	}

	DebugPrintf ("%i entities removed\n", inhibit);

#ifdef DEBUG
	i = 1;
	ent = EDICT_NUM(i);
	while (i < globals.numEdicts) {
		if (ent->inUse != 0 || ent->inUse != 1)
			Com_DevPrintf ("Invalid entity %d\n", i);
		i++, ent++;
	}
#endif

	G_FindTeams ();

	PlayerTrail_Init ();

#ifdef MONSTERS_USE_PATHFINDING
	LoadNodes();
	LoadPathTable ();
#endif

#ifdef CLEANCTF_ENABLED
//ZOID
	CTFSpawn();
//ZOID
#endif

	DebugPrintf ("Finished server initialization in %d ms\n", Sys_Milliseconds() - startTime);
#ifdef CC_USE_EXCEPTION_HANDLER
	}
	__except (EGLExceptionHandler(GetExceptionCode(), GetExceptionInformation()))
	{
		return;
	}
#endif
}


//===================================================================

/*QUAKED worldspawn (0 0 0) ?

Only used for the world.
"sky"	environment map name
"skyaxis"	vector axis for rotating sky
"skyrotate"	speed of rotation in degrees/second
"sounds"	music cd track number
"gravity"	800 is default gravity
"message"	text to print at user logon
*/
void CreateDMStatusbar ();
void CreateSPStatusbar ();
void SetItemNames ();
void SP_worldspawn (edict_t *ent)
{
	ClearList(); // Do this before ANYTHING
	// Seed the random number generator
	srand (time(NULL));

	ent->Entity->gameEntity->movetype = MOVETYPE_PUSH;
	ent->Entity->SetSolid (SOLID_BSP);
	ent->Entity->SetInUse (true);			// since the world doesn't use G_Spawn()
	ent->Entity->State.SetModelIndex (1);		// world model is always index 1

	// reserve some spots for dead player bodies for coop / deathmatch
	BodyQueue_Init ();

	if (st.nextmap)
		Q_strncpyz (level.nextmap, st.nextmap, sizeof(level.nextmap));

	// make some data visible to the server
	if (ent->message && ent->message[0])
	{
		gi.configstring (CS_NAME, ent->message);
		Q_strncpyz (level.level_name, ent->message, sizeof(level.level_name));
	}
	else
		Q_strncpyz (level.level_name, level.mapname, sizeof(level.level_name));

	if (st.sky && st.sky[0])
		gi.configstring (CS_SKY, st.sky);
	else
		gi.configstring (CS_SKY, "unit1_");

	gi.configstring (CS_SKYROTATE, Q_VarArgs ("%f", st.skyrotate) );

	gi.configstring (CS_SKYAXIS, Q_VarArgs ("%f %f %f",
		st.skyaxis[0], st.skyaxis[1], st.skyaxis[2]) );

	gi.configstring (CS_CDTRACK, Q_VarArgs ("%i", ent->sounds) );

	gi.configstring (CS_MAXCLIENTS, maxclients->String() );

	// status bar program
	if (game.mode & GAME_DEATHMATCH)
	{
#ifdef CLEANCTF_ENABLED
//ZOID
		if (game.mode & GAME_CTF)
		{
			CreateCTFStatusbar();

			//precaches
			ImageIndex("i_ctf1");
			ImageIndex("i_ctf2");
			ImageIndex("i_ctf1d");
			ImageIndex("i_ctf2d");
			ImageIndex("i_ctf1t");
			ImageIndex("i_ctf2t");
			ImageIndex("i_ctfj");
		}
		else
//ZOID
#endif
		CreateDMStatusbar();
	}
	else
		CreateSPStatusbar();

	//---------------
	SetItemNames();

	CCvar *gravity = QNew (com_levelPool, 0) CCvar ("gravity", "800", 0);
	if (!st.gravity)
		gravity->Set("800");
	else
		gravity->Set(st.gravity);

	SoundIndex ("player/lava1.wav");
	SoundIndex ("player/lava2.wav");

	SoundIndex ("misc/pc_up.wav");
	SoundIndex ("misc/talk1.wav");

	SoundIndex ("misc/udeath.wav");

	SoundIndex ("items/respawn1.wav");

	DoWeaponVweps ();
	//-------------------

	SoundIndex ("player/gasp1.wav");		// gasping for air
	SoundIndex ("player/gasp2.wav");		// head breaking surface, not gasping
	SoundIndex ("player/watr_in.wav");	// feet hitting water
	SoundIndex ("player/watr_out.wav");	// feet leaving water
	SoundIndex ("player/watr_un.wav");	// head going underwater
	SoundIndex ("player/u_breath1.wav");
	SoundIndex ("player/u_breath2.wav");
	SoundIndex ("world/land.wav");		// landing thud
	SoundIndex ("misc/h2ohit1.wav");		// landing splash
	SoundIndex ("weapons/noammo.wav");
	SoundIndex ("infantry/inflies1.wav");

	InitGameMedia ();

//
// Setup light animation tables. 'a' is total darkness, 'z' is doublebright.
//

	// 0 normal
	gi.configstring(CS_LIGHTS+0, "m");
	
	// 1 FLICKER (first variety)
	gi.configstring(CS_LIGHTS+1, "mmnmmommommnonmmonqnmmo");
	
	// 2 SLOW STRONG PULSE
	gi.configstring(CS_LIGHTS+2, "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba");
	
	// 3 CANDLE (first variety)
	gi.configstring(CS_LIGHTS+3, "mmmmmaaaaammmmmaaaaaabcdefgabcdefg");
	
	// 4 FAST STROBE
	gi.configstring(CS_LIGHTS+4, "mamamamamama");
	
	// 5 GENTLE PULSE 1
	gi.configstring(CS_LIGHTS+5,"jklmnopqrstuvwxyzyxwvutsrqponmlkj");
	
	// 6 FLICKER (second variety)
	gi.configstring(CS_LIGHTS+6, "nmonqnmomnmomomno");
	
	// 7 CANDLE (second variety)
	gi.configstring(CS_LIGHTS+7, "mmmaaaabcdefgmmmmaaaammmaamm");
	
	// 8 CANDLE (third variety)
	gi.configstring(CS_LIGHTS+8, "mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa");
	
	// 9 SLOW STROBE (fourth variety)
	gi.configstring(CS_LIGHTS+9, "aaaaaaaazzzzzzzz");
	
	// 10 FLUORESCENT FLICKER
	gi.configstring(CS_LIGHTS+10, "mmamammmmammamamaaamammma");

	// 11 SLOW PULSE NOT FADE TO BLACK
	gi.configstring(CS_LIGHTS+11, "abcdefghijklmnopqrrqponmlkjihgfedcba");
	
	// styles 32-62 are assigned by the light program for switchable lights

	// 63 testing
	gi.configstring(CS_LIGHTS+63, "a");

	dmFlags.UpdateFlags(dmflags->Integer());
}

