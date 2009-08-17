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
// cc_ban.h
// Simple ban system
//
#if !defined(__CC_BAN_H__) || !defined(INCLUDE_GUARDS)
#define __CC_BAN_H__


#include <vector>
#include <string>

typedef int EBanTypeFlags;
enum// EBanTypeFlags
{
	BAN_SQUELCH		=	1, // Banned from talking
	BAN_SPECTATOR	=	2, // Banned from moving to spectator mode
	BAN_ENTER		=	4, // Banned from entering the game
};

typedef struct IPAddress_s
{
	byte adr[4];
} IPAddress;

typedef struct BanIndex_s
{
	bool			IP;
	union
	{
		IPAddress	*IPAddress;
		char		*Name;
	};

	EBanTypeFlags	Flags;
} BanIndex;

class CBanList
{
	std::vector<BanIndex*>	BanList;

public:

	void LoadFromFile ();
	void SaveList ();

	void AddToList (IPAddress Adr, EBanTypeFlags Flags);
	void RemoveFromList (IPAddress Adr);
	void AddToList (char *Name, EBanTypeFlags Flags);
	void RemoveFromList (char *Name);

	void ChangeBan (IPAddress Adr, EBanTypeFlags Flags);
	void ChangeBan (char *Name, EBanTypeFlags Flags);

	// Call these with ent->client->pers.IP if after spawning
	bool IsSquelched (IPAddress IP);
	bool IsBannedFromSpectator (IPAddress IP);
	bool IsBanned (IPAddress IP);

	bool IsSquelched (char *Name);
	bool IsBannedFromSpectator (char *Name);
	bool IsBanned (char *Name);
};

extern CBanList	Bans;

IPAddress IPStringToArrays (const char *IP);
IPAddress IPStringToArrays (char *IP);

#else
FILE_WARNING
#endif