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
// cc_junk_entities.h
// Entities that share a "Junk" class
//

#if !defined(CC_GUARD_JUNK_ENTITIES_H) || !INCLUDE_GUARDS
#define CC_GUARD_JUNK_ENTITIES_H

class CJunkEntity : public virtual CBaseEntity
{
public:
	CJunkEntity ();
	CJunkEntity (sint32 Index);

	virtual void SaveFields (CFile &File)
	{
	}

	virtual void LoadFields (CFile &File)
	{
	}

	void Die (); // CALL THIS WHEN A JUNK IS FREED INSTEAD OF FREE()!
};

class CGibEntity : public CJunkEntity, public CTossProjectile, public CThinkableEntity
{
public:
	CGibEntity ();
	CGibEntity (sint32 Index);

	IMPLEMENT_SAVE_HEADER (CGibEntity)

	void SaveFields (CFile &File)
	{
		CThinkableEntity::SaveFields (File);
		CBounceProjectile::SaveFields (File);
	}

	void LoadFields (CFile &File)
	{
		CThinkableEntity::LoadFields (File);
		CBounceProjectile::LoadFields (File);
	}

	void Think ();

	bool Run ();
	static void Spawn (CBaseEntity *Owner, MediaIndex gibIndex, sint32 damage, sint32 type);
};

void Init_Junk();
void Shutdown_Junk ();

#else
FILE_WARNING
#endif