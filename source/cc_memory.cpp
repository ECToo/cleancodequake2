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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

//
// cc_memory.cpp
// 
//

#include "cc_local.h"

CC_DISABLE_DEPRECATION

const uint32 HEADER_MAGIC_CONSTANT = (('E'<<24)+('N'<<16)+('E'<<8)+'G');

struct SMemSentinel
{
	uint32				Magic;
	void				*Header;

	bool Check (void *CheckHeader)
	{
		return (Magic == HEADER_MAGIC_CONSTANT && Header == CheckHeader);
	};
};

struct SMemHeader
{
	SMemSentinel		SentinelHeader;
	void				*Address;
	sint32				TagNum;
	size_t				Size, RealSize;
	const char			*FileName, *Line;

	bool Check ()
	{
		return (SentinelHeader.Check(this) && ((SMemSentinel*)(((uint8*)this) + RealSize - sizeof(SMemSentinel)))->Check(this));
	};
};

static void *Mem_TagAlloc (size_t Size, const sint32 TagNum, const char *FileName, const char *Line)
{
	size_t RealSize = Size + sizeof(SMemHeader) + sizeof(SMemSentinel);
	SMemHeader *Mem = (SMemHeader*)((TagNum == TAG_GENERIC) ? malloc(RealSize) : gi.TagMalloc(RealSize, TagNum));
	SMemSentinel *Footer = (SMemSentinel*)(((uint8*)Mem) + RealSize - sizeof(SMemSentinel));

	Mem->SentinelHeader.Header = Footer->Header = Mem;
	Mem->TagNum = TagNum;
	Mem->Size = Size;
	Mem->FileName = FileName;
	Mem->Line = Line;
	Footer->Magic = Mem->SentinelHeader.Magic = HEADER_MAGIC_CONSTANT;
	Mem->RealSize = RealSize;
	Mem->Address = (((uint8*)Mem) + sizeof(SMemHeader));
	Mem_Zero (Mem->Address, Size);

	return Mem->Address;
}

static void Mem_TagFree (void *Pointer)
{
	SMemHeader *Header = (SMemHeader*)(((uint8*)Pointer) - sizeof(SMemHeader));

	if (!Header->Check())
		assert (0);

	if (Header->TagNum == TAG_GENERIC)
		free (Header);
	else
		gi.TagFree (Header);
}

void Mem_FreeTag (const sint32 TagNum)
{
	gi.FreeTags (TagNum);
}
CC_ENABLE_DEPRECATION

#ifdef WIN32
#pragma warning(disable : 4290)
#endif

void *operator new(size_t Size, const sint32 TagNum, const char *FileName, const char *Line)
{
	return Mem_TagAlloc(Size, TagNum, FileName, Line);
}

void *operator new[](size_t Size, const sint32 TagNum, const char *FileName, const char *Line)
{
	return Mem_TagAlloc(Size, TagNum, FileName, Line);
}

void operator delete(void *Pointer, const sint32 TagNum)
{
	if (Pointer == NULL)
	{
		CC_ASSERT_EXPR (0, "Attempted to free NULL");
		return;
	}

	Mem_TagFree (Pointer);
	TagNum;
}

void operator delete[](void *Pointer, const sint32 TagNum)
{
	if (Pointer == NULL)
	{
		CC_ASSERT_EXPR (0, "Attempted to free NULL");
		return;
	}

	Mem_TagFree (Pointer);
	TagNum;
}

void *operator new (size_t Size) throw (std::bad_alloc)
{
	return Mem_TagAlloc(Size, TAG_GENERIC, "null", "null");
}

void operator delete (void *Pointer) throw ()
{
	Mem_TagFree (Pointer);
}

/*
================
Mem_TagStrDup
================
*/
char *Mem_TagStrDup (const char *in, const sint32 tagNum)
{
	char	*out = QNew(tagNum) char[(size_t)(strlen (in) + 1)];
	Q_strncpyz (out, in, (size_t)(strlen (in) + 1));

	return out;
}
