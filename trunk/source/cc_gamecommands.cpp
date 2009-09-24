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
// cc_gamecommands.cpp
// ClientCommand & related functions
//

#include "cc_local.h"
#include "m_player.h"
#include "cc_ban.h"

/*
==================
Cmd_God_f

Sets client to godmode

argv(0) god
==================
*/
void Cmd_God_f (CPlayerEntity *ent)
{
	ent->Flags ^= FL_GODMODE;
	ent->PrintToClient (PRINT_HIGH, "God mode %s\n", (!(ent->Flags & FL_GODMODE)) ? "off" : "on");
}


/*
==================
Cmd_Notarget_f

Sets client to notarget

argv(0) notarget
==================
*/
void Cmd_Notarget_f (CPlayerEntity *ent)
{
	ent->Flags ^= FL_NOTARGET;
	ent->PrintToClient (PRINT_HIGH, "Notarget %s\n", (!(ent->Flags & FL_NOTARGET)) ? "off" : "on");
}


/*
==================
Cmd_Noclip_f

argv(0) noclip
==================
*/
void Cmd_Noclip_f (CPlayerEntity *ent)
{
	ent->NoClip = !ent->NoClip;
	ent->PrintToClient (PRINT_HIGH, "Noclip %s\n", ent->NoClip ? "on" : "off");
}

/*
=================
Cmd_Kill_f
=================
*/
void Cmd_Kill_f (CPlayerEntity *ent)
{
//ZOID
	if (ent->gameEntity->solid == SOLID_NOT)
		return;
//ZOID

	if((level.framenum - ent->Client.respawn_time) < 50)
		return;

	ent->Flags &= ~FL_GODMODE;
	ent->Health = 0;
	meansOfDeath = MOD_SUICIDE;
	ent->Die (ent, ent, 100000, vec3fOrigin);
}

/*
=================
Cmd_PutAway_f
=================
*/
void Cmd_PutAway_f (CPlayerEntity *ent)
{
	ent->Client.showscores = false;
	ent->Client.showhelp = false;
	ent->Client.showinventory = false;

	if (ent->Client.resp.MenuState.InMenu)
		ent->Client.resp.MenuState.CloseMenu ();

	ent->Client.update_chase = true;
}


int PlayerSort (void const *a, void const *b)
{
	int		anum, bnum;

	anum = *(int *)a;
	bnum = *(int *)b;

	anum = game.clients[anum].playerState.stats[STAT_FRAGS];
	bnum = game.clients[bnum].playerState.stats[STAT_FRAGS];

	if (anum < bnum)
		return -1;
	if (anum > bnum)
		return 1;
	return 0;
}

class CPlayerListCountCallback : public CForEachPlayerCallback
{
public:
	int		*index;
	int		*count;

	CPlayerListCountCallback (int *index, int *count) :
	index(index),
	count(count)
	{
	};

	void Callback (CPlayerEntity *Player)
	{
		index[(*count)++] = Index;
	}
};

/*
=================
Cmd_Players_f
=================
*/
void Cmd_Players_f (CPlayerEntity *ent)
{
	int		count = 0;
	char	small[MAX_INFO_KEY];
	char	large[MAX_INFO_STRING];
	int		*index = QNew (com_genericPool, 0) int[game.maxclients];

	CPlayerListCountCallback (index, &count).Query ();

	// sort by frags
	qsort (index, count, sizeof(index[0]), PlayerSort);

	// print information
	large[0] = 0;

	for (int i = 0 ; i < count ; i++)
	{
		CPlayerEntity *Player = dynamic_cast<CPlayerEntity*>(g_edicts[i+1].Entity);
		Q_snprintfz (small, sizeof(small), "%3i %s\n",
			Player->Client.PlayerState.GetStat(STAT_FRAGS),
			Player->Client.pers.netname);
		if (strlen (small) + strlen(large) > sizeof(large) - 100 )
		{	// can't print all of them in one packet
			Q_strcatz (large, "...\n", MAX_INFO_STRING);
			break;
		}
		Q_strcatz (large, small, MAX_INFO_STRING);
	}

	ent->PrintToClient (PRINT_HIGH, "%s\n%i players\n", large, count);

	delete[] index;
}

/*
=================
Cmd_Wave_f
=================
*/
void Cmd_Wave_f (CPlayerEntity *ent)
{
	// can't wave when ducked
	if (ent->Client.PlayerState.GetPMove()->pmFlags & PMF_DUCKED)
		return;

	if (ent->Client.anim_priority > ANIM_WAVE)
		return;

	ent->Client.anim_priority = ANIM_WAVE;

	switch (ArgGeti(1))
	{
	case 0:
		ent->PrintToClient (PRINT_HIGH, "flipoff\n");
		ent->State.SetFrame (FRAME_flip01-1);
		ent->Client.anim_end = FRAME_flip12;
		break;
	case 1:
		ent->PrintToClient (PRINT_HIGH, "salute\n");
		ent->State.SetFrame (FRAME_salute01-1);
		ent->Client.anim_end = FRAME_salute11;
		break;
	case 2:
		ent->PrintToClient (PRINT_HIGH, "taunt\n");
		ent->State.SetFrame (FRAME_taunt01-1);
		ent->Client.anim_end = FRAME_taunt17;
		break;
	case 3:
		ent->PrintToClient (PRINT_HIGH, "wave\n");
		ent->State.SetFrame (FRAME_wave01-1);
		ent->Client.anim_end = FRAME_wave11;
		break;
	case 4:
	default:
		ent->PrintToClient (PRINT_HIGH, "point\n");
		ent->State.SetFrame (FRAME_point01-1);
		ent->Client.anim_end = FRAME_point12;
		break;
	}
}

/*
==================
Cmd_Say_f
==================
*/
#define MAX_TALK_STRING 100

bool CheckFlood(CPlayerEntity *ent)
{
	if (flood_msgs->Integer())
	{
		if (level.framenum < ent->Client.flood_locktill)
		{
			ent->PrintToClient (PRINT_HIGH, "You can't talk for %d more seconds\n",
				(int)((ent->Client.flood_locktill - level.framenum)/10));
			return true;
		}
		int i = ent->Client.flood_whenhead - flood_msgs->Integer() + 1;
		if (i < 0)
			i = (sizeof(ent->Client.flood_when)/sizeof(ent->Client.flood_when[0])) + i;
		if (ent->Client.flood_when[i] && 
			((level.framenum - ent->Client.flood_when[i])/10) < flood_persecond->Integer())
		{
			ent->Client.flood_locktill = level.framenum + (flood_waitdelay->Float() * 10);
			ent->PrintToClient (PRINT_CHAT, "Flood protection:  You can't talk for %d seconds.\n",
				flood_waitdelay->Integer());
			return true;
		}
		ent->Client.flood_whenhead = (ent->Client.flood_whenhead + 1) %
			(sizeof(ent->Client.flood_when)/sizeof(ent->Client.flood_when[0]));
		ent->Client.flood_when[ent->Client.flood_whenhead] = level.framenum;
	}
	return false;
}

class CSayPlayerCallback : public CForEachPlayerCallback
{
public:
	char	*Text;

	CSayPlayerCallback (char *Text) :
	Text(Text)
	{
	};

	void Callback (CPlayerEntity *Player)
	{
		Player->PrintToClient (PRINT_CHAT, "%s", Text);
	}
};

void Cmd_Say_f (CPlayerEntity *ent, bool team, bool arg0)
{
	char	*p;
	char	text[MAX_TALK_STRING];

	if (ArgCount () < 2 && !arg0)
		return;

	if (Bans.IsSquelched(ent->Client.pers.IP) || Bans.IsSquelched(ent->Client.pers.netname))
	{
		ent->PrintToClient (PRINT_HIGH, "You are squelched and may not talk.\n");
		return;
	}

	if (!(dmFlags.dfSkinTeams || dmFlags.dfModelTeams))
		team = false;

	if (team)
		Q_snprintfz (text, sizeof(text), "(%s): ", ent->Client.pers.netname);
	else
		Q_snprintfz (text, sizeof(text), "%s: ", ent->Client.pers.netname);

	if (arg0)
	{
		Q_strcatz (text, ArgGets(0), sizeof(text));
		Q_strcatz (text, " ", sizeof(text));
		Q_strcatz (text, ArgGetConcatenatedString(), sizeof(text));
	}
	else
	{
		p = ArgGetConcatenatedString();

		if (*p == '"')
		{
			p++;
			p[strlen(p)-1] = 0;
		}
		Q_strcatz(text, p, sizeof(text));
	}

	// don't let text be too long for malicious reasons
	if (strlen(text) >= sizeof(text)-1)
	{
		text[sizeof(text)-1] = 0;
		text[sizeof(text)-2] = '\n';
	}
	else
		Q_strcatz(text, "\n", sizeof(text));

	if (CheckFlood(ent))
		return;

	if (dedicated->Integer())
		Com_Printf(PRINT_CHAT, "%s", text);

	CSayPlayerCallback (text).Query ();
}

class CPlayerListCallback : public CForEachPlayerCallback
{
public:
	char			*Text;
	size_t			SizeOf;
	CPlayerEntity	*Ent;
	bool			Spectator;

	CPlayerListCallback (char *Text, size_t SizeOf, CPlayerEntity *Ent) :
	Text(Text),
	SizeOf(SizeOf),
	Ent(Ent)
	{
	};

	bool DoCallback (CPlayerEntity *Player)
	{
		char st[80];

		if (!Spectator)
			Q_snprintfz(st, sizeof(st), " - %02d:%02d %4d %3d %s%s\n",
				(level.framenum - Player->Client.resp.enterframe) / 600,
				((level.framenum - Player->Client.resp.enterframe) % 600)/10,
				Player->Client.GetPing(),
				Player->Client.resp.score,
				Player->Client.pers.netname,
				Player->Client.resp.spectator ? " (spectator)" : "");
		else
			Q_snprintfz(st, sizeof(st), " - %s%s\n",
				Player->Client.pers.netname,
				Player->Client.resp.spectator ? " (spectator)" : "");

		if (strlen(Text) + strlen(st) > SizeOf - 50)
		{
			Q_snprintfz (Text+strlen(Text), SizeOf, "And more...\n");
			Ent->PrintToClient (PRINT_HIGH, "%s", Text);
			return true;
		}

		Q_strcatz(Text, st, SizeOf);
		return false;
	}

	bool DoQuery (bool Spectator)
	{
		this->Spectator = Spectator;
		for (byte i = 1; i <= game.maxclients; i++)
		{
			CPlayerEntity *Player = dynamic_cast<CPlayerEntity*>(g_edicts[i].Entity);

			if (Spectator && (!Player->IsInUse() || Player->Client.pers.state != SVCS_SPAWNED))
				continue;
			else if (!Spectator && (Player->Client.pers.state == SVCS_SPAWNED))
				continue;

			Index = i;
			if (DoCallback (Player))
				return true;
		}
		return false;
	}

	void Query (bool)
	{
	}

	void Callback (CPlayerEntity *)
	{
	}
};

void Cmd_PlayerList_f(CPlayerEntity *ent)
{
	char text[MAX_COMPRINT/4];

	// connect time, ping, score, name
	*text = 0;

	Q_snprintfz (text, sizeof(text), "Spawned:\n");
	CPlayerListCallback(text, sizeof(text), ent).DoQuery (false);
	/*for (i = 0; i < game.maxclients; i++)
	{
		CPlayerEntity *e2 = dynamic_cast<CPlayerEntity*>(g_edicts[i+1].Entity);
		if (!e2->IsInUse())
			continue;
		if (e2->Client.pers.state != SVCS_SPAWNED)
			continue;

		Q_snprintfz(st, sizeof(st), " - %02d:%02d %4d %3d %s%s\n",
			(level.framenum - e2->Client.resp.enterframe) / 600,
			((level.framenum - e2->Client.resp.enterframe) % 600)/10,
			e2->Client.GetPing(),
			e2->Client.resp.score,
			e2->Client.pers.netname,
			e2->Client.resp.spectator ? " (spectator)" : "");
		if (strlen(text) + strlen(st) > sizeof(text) - 50) {
			Q_snprintfz (text+strlen(text), sizeof(text), "And more...\n");
			ent->PrintToClient (PRINT_HIGH, "%s", text);
			return;
		}
		Q_strcatz(text, st, sizeof(text));
	}*/

	Q_strcatz (text, "Connecting:\n", sizeof(text));
	/*for (i = 0; i < game.maxclients; i++)
	{
		CPlayerEntity *e2 = dynamic_cast<CPlayerEntity*>(g_edicts[i+1].Entity);
		if (e2->Client.pers.state == SVCS_SPAWNED)
			continue;

		Q_snprintfz(st, sizeof(st), " - %s%s\n",
			e2->Client.pers.netname,
			e2->Client.resp.spectator ? " (spectator)" : "");
		if (strlen(text) + strlen(st) > sizeof(text) - 50) {
			Q_snprintfz (text+strlen(text), sizeof(text), "And more...\n");
			ent->PrintToClient (PRINT_HIGH, "%s", text);
			return;
		}
		Q_strcatz(text, st, sizeof(text));
	}*/
	if (!CPlayerListCallback(text, sizeof(text), ent).DoQuery (true))
		ent->PrintToClient (PRINT_HIGH, "%s", text);
}

void GCmd_Say_f (CPlayerEntity *ent)
{
	Cmd_Say_f (ent, false, false);
}

void GCmd_SayTeam_f (CPlayerEntity *ent)
{
	Cmd_Say_f (ent, true, false);
}

void Cmd_Test_f (CPlayerEntity *ent)
{
	/*char *sound = ArgGets(1);

	if (!sound || !sound[0])
		return;

	gi.configstring (CS_SOUNDS+70, sound);
	PlaySoundFrom (ent->gameEntity, CHAN_AUTO, 70, 1, ATTN_NONE);*/
	//vec3f or = ent->State.GetOrigin();
	//BroadcastPrintf (PRINT_CENTER, "(%s)\nis at (%.0f %.0f %.0f)", ent->Client.pers.netname, or.X, or.Y, or.Z);
	//CGibEntity::Spawn (ent, gMedia.Gib_SmallMeat, ArgGeti(1), GIB_ORGANIC);
/*
	DebugPrintf (		"random       crandom          frand           crand\n"
						"------       -------          ------         ------\n");
	for (int i = 0; i < 12; i++)
	{
		DebugPrintf(	"%5.2f        %6.2f            %5.2f          %5.2f\n",
			random(), crandom(), frand(), crand());
	}

	uint32 randomtime, crandomtime, frandtime, crandtime;
	
	randomtime = Sys_Milliseconds ();
	for (uint32 i = 0; i < 8000000; i++)
		random ();
	randomtime = Sys_Milliseconds () - randomtime;
		
	crandomtime = Sys_Milliseconds ();
	for (uint32 i = 0; i < 8000000; i++)
		crandom ();
	crandomtime = Sys_Milliseconds () - crandomtime;

	frandtime = Sys_Milliseconds ();
	for (uint32 i = 0; i < 8000000; i++)
		frand ();
	frandtime = Sys_Milliseconds () - frandtime;
		
	crandtime = Sys_Milliseconds ();
	for (uint32 i = 0; i < 8000000; i++)
		crand ();
	crandtime = Sys_Milliseconds () - crandtime;

	DebugPrintf(	"%5u        %6u            %5u          %5u\n",
		randomtime, crandomtime, frandtime, crandtime);
		*/
	//DebugPrintf ("%i %i %i\n", (int)ent->State.GetOrigin().X, (int)ent->State.GetOrigin().Y, (int)ent->State.GetOrigin().Z);

	uint32 time1 = Sys_Milliseconds ();
	for (uint32 i = 0; i < 80000; i++)
		gMedia.FlySound();
	time1 = Sys_Milliseconds() - time1;

	uint32 time2 = Sys_Milliseconds ();
	for (uint32 i = 0; i < 80000; i++)
		SoundIndex ("misc/windfly.wav");
	time2 = Sys_Milliseconds() - time2;

	DebugPrintf ("%ums vs %ums\n", time1, time2);
}

void GCTFSay_Team (CPlayerEntity *ent);
void Cmd_MenuLeft_t (CPlayerEntity *ent);
void Cmd_MenuRight_t (CPlayerEntity *ent);

void Cmd_Register ()
{
	// These commands are generic, and can be executed any time
	// during play, even during intermission and by spectators.
	Cmd_AddCommand ("players",				Cmd_Players_f,			CMD_SPECTATOR);
	Cmd_AddCommand ("say",					GCmd_Say_f,				CMD_SPECTATOR);
	Cmd_AddCommand ("score",				Cmd_Score_f,			CMD_SPECTATOR);
	Cmd_AddCommand ("help",					Cmd_Help_f,				CMD_SPECTATOR);
	Cmd_AddCommand ("putaway",				Cmd_PutAway_f,			CMD_SPECTATOR);
	Cmd_AddCommand ("playerlist",			
#ifdef CLEANCTF_ENABLED
		CTFPlayerList,		
#else
		Cmd_PlayerList_f,		
#endif
		CMD_SPECTATOR);

	// These commands are also generic, but can only be executed
	// by in-game players during the game
	Cmd_AddCommand ("kill",					Cmd_Kill_f);
	Cmd_AddCommand ("wave",					Cmd_Wave_f);

	Cmd_AddCommand ("use",					Cmd_Use_f);
	Cmd_AddCommand ("uselist",				Cmd_UseList_f); // Paril
	Cmd_AddCommand ("drop",					Cmd_Drop_f);
	Cmd_AddCommand ("inven",				Cmd_Inven_f);
	Cmd_AddCommand ("invuse",				Cmd_InvUse_f);
	Cmd_AddCommand ("invdrop",				Cmd_InvDrop_f);
	Cmd_AddCommand ("weapprev",				Cmd_WeapPrev_f);
	Cmd_AddCommand ("weapnext",				Cmd_WeapNext_f);
	Cmd_AddCommand ("weaplast",				Cmd_WeapLast_f);
	Cmd_AddCommand ("invnext",				Cmd_SelectNextItem_f);
	Cmd_AddCommand ("invprev",				Cmd_SelectPrevItem_f);
	Cmd_AddCommand ("invnextw",				Cmd_SelectNextWeapon_f);
	Cmd_AddCommand ("invprevw",				Cmd_SelectPrevWeapon_f);
	Cmd_AddCommand ("invnextp",				Cmd_SelectNextPowerup_f);
	Cmd_AddCommand ("invprevp",				Cmd_SelectPrevPowerup_f);
	Cmd_AddCommand ("test",					Cmd_Test_f);

	// And last but certainly not least...
	Cmd_AddCommand ("god",					Cmd_God_f,				CMD_CHEAT);
	Cmd_AddCommand ("notarget",				Cmd_Notarget_f,			CMD_CHEAT);
	Cmd_AddCommand ("noclip",				Cmd_Noclip_f,			CMD_CHEAT);
	Cmd_AddCommand ("give",					Cmd_Give_f,				CMD_CHEAT);
	Cmd_AddCommand ("spawn",				Cmd_Give,				CMD_CHEAT);
	
	// CleanMenu commands
	Cmd_AddCommand ("menu_left",			Cmd_MenuLeft_t,			CMD_SPECTATOR);
	Cmd_AddCommand ("menu_right",			Cmd_MenuRight_t,		CMD_SPECTATOR);

#ifdef CLEANCTF_ENABLED
	Cmd_AddCommand ("say_team",				GCTFSay_Team,			CMD_SPECTATOR);
	Cmd_AddCommand ("team",					CTFTeam_f);
	Cmd_AddCommand ("id",					CTFID_f);
	Cmd_AddCommand ("yes",					CTFVoteYes);
	Cmd_AddCommand ("no",					CTFVoteNo);
	Cmd_AddCommand ("ready",				CTFReady);
	Cmd_AddCommand ("notready",				CTFNotReady);
	Cmd_AddCommand ("ghost",				CTFGhost);
	Cmd_AddCommand ("admin",				CTFAdmin);
	Cmd_AddCommand ("stats",				CTFStats);
	Cmd_AddCommand ("warp",					CTFWarp);
	Cmd_AddCommand ("boot",					CTFBoot);
	Cmd_AddCommand ("observer",				CTFObserver);
#endif
}

/*
=================
ClientCommand
=================
*/
#include "cc_exceptionhandler.h"
void ClientCommand (edict_t *ent)
{
#ifdef CC_USE_EXCEPTION_HANDLER
__try
{
#endif
	if (!ent->client)
		return;		// not fully in game yet

	InitArg ();
	Cmd_RunCommand (ArgGets(0), dynamic_cast<CPlayerEntity*>(ent->Entity));
	EndArg ();
#ifdef CC_USE_EXCEPTION_HANDLER
}
__except (EGLExceptionHandler(GetExceptionCode(), GetExceptionInformation()))
{
	EndArg ();
	return;
}
#endif
}