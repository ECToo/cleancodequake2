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
// cc_filesystem.cpp
// File system, for managing server files.
// From EGL
//

#include "cc_local.h"
#include "cc_filesystem.h"
#include <windows.h>

#define BASE_MODDIRNAME "baseq2"

#define FS_MAX_PAKS			1024
#define FS_MAX_HASHSIZE		1024
#define FS_MAX_FILEINDICES	1024

CCvar	*fs_basedir;
CCvar	*fs_cddir;
CCvar	*fs_game;
CCvar	*fs_gamedircvar;
CCvar	*fs_developer;

/*
=============================================================================

	FILESYSTEM FUNCTIONALITY

=============================================================================
*/

typedef struct fsLink_s {
	struct fsLink_s			*next;
	char					*from;
	int						fromLength;
	char					*to;
} fsLink_t;

typedef struct fsPath_s {
	char					pathName[MAX_OSPATH];
	char					gamePath[MAX_OSPATH];

	struct fsPath_s			*next;
} fsPath_t;

static char		fs_gameDir[MAX_OSPATH];

static fsLink_t	*fs_fileLinks;

static fsPath_t	*fs_searchPaths;
static fsPath_t	**fs_invSearchPaths;
static int		fs_numInvSearchPaths;
static fsPath_t	*fs_baseSearchPath;		// Without gamedirs

/*
=============================================================================

	FILE INDEXING

=============================================================================
*/

typedef struct fsHandleIndex_s {
	char					name[MAX_QPATH];

	bool					inUse;
	EFSOpenMode				openMode;

	// One of these is always NULL
	FILE					*regFile;
} fsHandleIndex_t;

static fsHandleIndex_t	fs_fileIndices[FS_MAX_FILEINDICES];

/*
=============================================================================

	HELPER FUNCTIONS

=============================================================================
*/

/*
================
__FileLen
================
*/
static int __FileLen(FILE *f)
{
	int pos = ftell(f);
	fseek(f, 0, SEEK_END);
	int end = ftell(f);
	fseek(f, pos, SEEK_SET);

	return end;
}

#include <direct.h>
#include <io.h>

/*
================
Sys_Mkdir
================
*/
void Sys_Mkdir (char *path)
{
	_mkdir (path);
}
/*
============
FS_CreatePath

Creates any directories needed to store the given filename
============
*/
void FS_CreatePath(char *path)
{
	for (char *ofs=path+1 ; *ofs ; ofs++)
	{
		if (*ofs == '/')
		{
			// Create the directory
			*ofs = 0;
			Sys_Mkdir (path);
			*ofs = '/';
		}
	}
}


/*
================
FS_CopyFile
================
*/
void FS_CopyFile(char *src, char *dst)
{
	if (fs_developer->Integer())
		Com_Printf(0, "FS_CopyFile (%s, %s)\n", src, dst);

	FILE *f1;
	fopen_s(&f1, src, "rb");
	if (!f1)
		return;
	FILE *f2;
	fopen_s(&f2, dst, "wb");
	if (!f2)
	{
		fclose(f1);
		return;
	}

	byte buffer[65536];
	for ( ; ; )
	{
		size_t l = fread(buffer, 1, sizeof(buffer), f1);
		if (!l)
			break;
		fwrite(buffer, 1, l, f2);
	}

	fclose(f1);
	fclose(f2);
}

/*
=============================================================================

	FILE HANDLING

=============================================================================
*/

/*
=================
FS_GetFreeHandle
=================
*/
static fileHandle_t FS_GetFreeHandle (fsHandleIndex_t **handle)
{
	fileHandle_t		i;
	fsHandleIndex_t		*hIndex;

	for (i=0, hIndex=fs_fileIndices ; i<FS_MAX_FILEINDICES ; hIndex++, i++) {
		if (hIndex->inUse)
			continue;

		hIndex->inUse = true;
		*handle = hIndex;
		return i+1;
	}

	Com_Error (ERR_FATAL, "FS_GetFreeHandle: no free handles!");
	return 0;
}


/*
=================
FS_GetHandle
=================
*/
static fsHandleIndex_t *FS_GetHandle (fileHandle_t fileNum)
{
	fsHandleIndex_t *hIndex;

	if (fileNum < 0 || fileNum > FS_MAX_FILEINDICES)
		Com_Error (ERR_FATAL, "FS_GetHandle: invalid file number");

	hIndex = &fs_fileIndices[fileNum-1];
	if (!hIndex->inUse)
		Com_Error (ERR_FATAL, "FS_GetHandle: invalid handle index");

	return hIndex;
}


/*
============
FS_FileLength

Returns the TOTAL file size, not the position.
Make sure to move the position back after moving to the beginning of the file for the size lookup.
============
*/
int FS_FileLength(fileHandle_t fileNum)
{
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	if (handle->regFile)
		return __FileLen(handle->regFile);

	// Shouldn't happen...
	assert (0);
	return -1;
}


/*
============
FS_Tell

Returns the current file position.
============
*/
int FS_Tell(fileHandle_t fileNum)
{
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	if (handle->regFile)
		return ftell(handle->regFile);

	// Shouldn't happen...
	assert (0);
	return 0;
}


/*
=================
FS_Read

Properly handles partial reads
=================
*/
size_t FS_Read(void *buffer, const size_t len, fileHandle_t fileNum)
{
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	if (handle->openMode != FS_MODE_READ_BINARY)
		Com_Error (ERR_FATAL, "FS_Read: %s: was not opened in read mode", handle->name);

	// Read in chunks for progress bar
	size_t remaining = len;
	byte *buf = (byte *)buffer;

	bool tried = false;
	if (handle->regFile)
	{
		// File
		while (remaining)
		{
			size_t read = fread(buf, 1, remaining, handle->regFile);
			switch(read)
			{
			case 0:
				// We might have been trying to read from a CD
				if (!tried)
					tried = true;
				else
				{
					if (fs_developer->Integer())
						Com_Printf(0, "FS_Read: 0 bytes read from \"%s\"", handle->name);
					return len - remaining;
				}
				break;

			case -1:
				Com_Error(ERR_FATAL, "FS_Read: -1 bytes read from \"%s\"", handle->name);
				break;
			}

			// Do some progress bar thing here
			remaining -= read;
			buf += read;
		}

		return len;
	}

	// Shouldn't happen...
	assert(0);
	return 0;
}


/*
=================
FS_Write
=================
*/
size_t FS_Write(void *buffer, const size_t size, fileHandle_t fileNum)
{
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	switch(handle->openMode)
	{
	case FS_MODE_WRITE_BINARY:
	case FS_MODE_APPEND_BINARY:
	case FS_MODE_WRITE_TEXT:
	case FS_MODE_APPEND_TEXT:
		break;
	default:
		Com_Error(ERR_FATAL, "FS_Write: %s: was no opened in append/write mode", handle->name);
		break;
	}
	if (size < 0)
		Com_Error(ERR_FATAL, "FS_Write: size < 0");

	// Write
	size_t remaining = size;
	byte *buf = (byte *)buffer;

	if (handle->regFile)
	{
		// File
		while (remaining)
		{
			size_t write = fwrite(buf, 1, remaining, handle->regFile);

			switch(write)
			{
			case 0:
				if (fs_developer->Integer())
					Com_Printf(PRNT_ERROR, "FS_Write: 0 bytes written to %s\n", handle->name);
				return size - remaining;

			case -1:
				Com_Error(ERR_FATAL, "FS_Write: -1 bytes written to %s", handle->name);
				break;
			}

			remaining -= write;
			buf += write;
		}

		return size;
	}

	// Shouldn't happen...
	assert (0);
	return 0;
}


/*
=================
FS_Seek
=================
*/
void FS_Seek(fileHandle_t fileNum, const long offset, const EFSSeekOrigin seekOrigin)
{
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	if (handle->regFile)
	{
		// Seek through a regular file
		switch(seekOrigin)
		{
		case FS_SEEK_SET:
			fseek(handle->regFile, offset, SEEK_SET);
			break;

		case FS_SEEK_CUR:
			fseek(handle->regFile, offset, SEEK_CUR);
			break;

		case FS_SEEK_END:
			fseek(handle->regFile, offset, SEEK_END);
			break;

		default:
			Com_Error(ERR_FATAL, "FS_Seek: bad origin (%i)", seekOrigin);
			break;
		}
	}
	assert (0);
}


/*
==============
FS_OpenFileAppend
==============
*/
static int FS_OpenFileAppend(fsHandleIndex_t *handle, bool binary)
{
	char path[MAX_OSPATH];
	Q_snprintfz(path, sizeof(path), "%s/%s", fs_gameDir, handle->name);

	// Create the path if it doesn't exist
	FS_CreatePath(path);

	// Open
	fopen_s(&handle->regFile, path, (binary) ? "ab" : "at");

	// Return length
	if (handle->regFile)
	{
		if (fs_developer->Integer())
			Com_Printf(0, "FS_OpenFileAppend: \"%s\"", path);
		return __FileLen(handle->regFile);
	}

	// Failed to open
	if (fs_developer->Integer())
		Com_Printf(0, "FS_OpenFileAppend: couldn't open \"%s\"", path);
	return -1;
}


/*
==============
FS_OpenFileWrite
==============
*/
static int FS_OpenFileWrite(fsHandleIndex_t *handle, bool binary)
{
	char path[MAX_OSPATH];
	Q_snprintfz(path, sizeof(path), "%s/%s", fs_gameDir, handle->name);

	// Create the path if it doesn't exist
	FS_CreatePath(path);

	// Open
	fopen_s(&handle->regFile, path, (binary) ? "wb" : "wt");

	// Return length
	if (handle->regFile)
	{
		if (fs_developer->Integer())
			Com_Printf(0, "FS_OpenFileWrite: \"%s\"", path);
		return 0;
	}

	// Failed to open
	if (fs_developer->Integer())
		Com_Printf(0, "FS_OpenFileWrite: couldn't open \"%s\"", path);
	return -1;
}

/*
================
Com_HashFileName

Normalizes path slashes, and stops before the extension.
hashSize MUST be a power of two!
================
*/
uint32 Com_HashFileName(const char *fileName, const int hashSize)
{
	uint32	hashValue = 0;
	for ( ; *fileName ; )
	{
		int ch = *(fileName++);
		if (ch == '\\')
			ch = '/';
		else if (ch == '.')
			break;

		hashValue = hashValue * 33 + Q_tolower(ch);
	}

	return (hashValue + (hashValue >> 5)) & (hashSize-1);
}


/*
===========
FS_OpenFileRead

Finds the file in the search path.
returns filesize and an open FILE *
Used for streaming data out of either a pak file or
a seperate file.
===========
*/
bool fs_fileFromPak = false;
static int FS_OpenFileRead(fsHandleIndex_t *handle)
{
	fs_fileFromPak = false;
	// Check for links first
	for (fsLink_t *link=fs_fileLinks ; link ; link=link->next)
	{
		if (!strncmp (handle->name, link->from, link->fromLength))
		{
			char netPath[MAX_OSPATH];
			Q_snprintfz(netPath, sizeof(netPath), "%s%s", link->to, handle->name+link->fromLength);

			// Open
			fopen_s(&handle->regFile, netPath, "rb");

			// Return length
			if (fs_developer->Integer())
				Com_Printf(0, "FS_OpenFileRead: link file: %s\n", netPath);
			if (handle->regFile)
				return __FileLen(handle->regFile);

			// Failed to load
			return -1;
		}
	}

	// Search through the path, one element at a time
	for (fsPath_t *searchPath=fs_searchPaths ; searchPath ; searchPath=searchPath->next)
	{
		// Check a file in the directory tree
		char netPath[MAX_OSPATH];
		Q_snprintfz(netPath, sizeof(netPath), "%s/%s", searchPath->pathName, handle->name);

		fopen_s(&handle->regFile, netPath, "rb");
		if (handle->regFile)
		{
			// Found it!
			if (fs_developer->Integer())
				Com_Printf(0, "FS_OpenFileRead: %s\n", netPath);
			return __FileLen(handle->regFile);
		}
	}

	if (fs_developer->Integer())
		Com_Printf(0, "FS_OpenFileRead: can't find %s\n", handle->name);

	return -1;
}


/*
===========
FS_OpenFile
===========
*/
int FS_OpenFile(const char *fileName, fileHandle_t *fileNum, const EFSOpenMode openMode)
{
	fsHandleIndex_t	*handle;
	int				fileSize = -1;

	*fileNum = FS_GetFreeHandle(&handle);

	Com_NormalizePath(handle->name, sizeof(handle->name), fileName);
	handle->openMode = openMode;

	// Open under the desired mode
	switch(openMode)
	{
	case FS_MODE_APPEND_BINARY:
		fileSize = FS_OpenFileAppend(handle, true);
		break;
	case FS_MODE_APPEND_TEXT:
		fileSize = FS_OpenFileAppend(handle, false);
		break;

	case FS_MODE_READ_BINARY:
		fileSize = FS_OpenFileRead(handle);
		break;

	case FS_MODE_WRITE_BINARY:
		fileSize = FS_OpenFileWrite(handle, true);
		break;
	case FS_MODE_WRITE_TEXT:
		fileSize = FS_OpenFileWrite(handle, false);
		break;

	default:
		Com_Error(ERR_FATAL, "FS_OpenFile: %s: invalid mode '%i'", handle->name, openMode);
		break;
	}

	// Failed
	if (fileSize == -1)
	{
		memset(handle, 0, sizeof(fsHandleIndex_t));
		*fileNum = 0;
	}

	return fileSize;
}


/*
==============
FS_CloseFile
==============
*/
void FS_CloseFile(fileHandle_t fileNum)
{
	// Get local handle
	fsHandleIndex_t *handle = FS_GetHandle(fileNum);
	if (!handle->inUse)
		return;

	// Close file/zip
	if (handle->regFile)
	{
		fclose(handle->regFile);
		handle->regFile = NULL;
	}
	else
		assert(0);

	// Clear handle
	handle->inUse = false;
	handle->name[0] = '\0';
}

// ==========================================================================

/*
============
FS_LoadFile

Filename are reletive to the egl search path.
A NULL buffer will just return the file length without loading.
-1 is returned if it wasn't found, 0 is returned if it's a blank file. In both cases a buffer is set to NULL.
============
*/
int FS_LoadFile(const char *path, void **buffer, const bool terminate)
{
	// Look for it in the filesystem or pack files
	fileHandle_t fileNum;
	int fileLen = FS_OpenFile(path, &fileNum, FS_MODE_READ_BINARY);
	if (!fileNum || fileLen <= 0)
	{
		if (buffer)
			*buffer = NULL;
		if (fileNum)
			FS_CloseFile (fileNum);
		if (fileLen >= 0)
			return 0;
		return -1;
	}

	// Just needed to get the length
	if (!buffer)
	{
		FS_CloseFile(fileNum);
		return fileLen;
	}

	// Allocate a local buffer
	uint32 termLen;
	if (terminate)
	{
		termLen = 2;
	}
	else
	{
		termLen = 0;
	}
	byte *buf = (byte*)Mem_PoolAlloc(fileLen+termLen, com_fileSysPool, 0);
	*buffer = buf;

	// Copy the file data to a local buffer
	FS_Read(buf, fileLen, fileNum);
	FS_CloseFile(fileNum);

	// Terminate if desired
	if (termLen)
		Q_strncpyz((char *)buf+fileLen, "\n\0", termLen);
	return fileLen+termLen;
}


/*
=============
_FS_FreeFile
=============
*/
void _FS_FreeFile(void *buffer, const char *fileName, const int fileLine)
{
	if (buffer)
		_Mem_Free(buffer, fileName, fileLine);
}

// ==========================================================================

/*
============
FS_FileExists

Filename are reletive to the egl search path.
Just like calling FS_LoadFile with a NULL buffer.
============
*/
int FS_FileExists(const char *path)
{
	// Look for it in the filesystem or pack files
	fileHandle_t fileNum;
	int fileLen = FS_OpenFile(path, &fileNum, FS_MODE_READ_BINARY);
	if (!fileNum || fileLen <= 0)
		return -1;

	// Just needed to get the length
	FS_CloseFile(fileNum);
	return fileLen;
}

char		sys_findBase[MAX_OSPATH];
char		sys_findPath[MAX_OSPATH];
HANDLE		sys_findHandle = INVALID_HANDLE_VALUE;

static bool Sys_CompareFileAttributes (int found, uint32 mustHave, uint32 cantHave)
{
	// read only
	if (found & FILE_ATTRIBUTE_READONLY) {
		if (cantHave & SFF_RDONLY)
			return false;
	}
	else if (mustHave & SFF_RDONLY)
		return false;

	// hidden
	if (found & FILE_ATTRIBUTE_HIDDEN) {
		if (cantHave & SFF_HIDDEN)
			return false;
	}
	else if (mustHave & SFF_HIDDEN)
		return false;

	// system
	if (found & FILE_ATTRIBUTE_SYSTEM) {
		if (cantHave & SFF_SYSTEM)
			return false;
	}
	else if (mustHave & SFF_SYSTEM)
		return false;

	// subdir
	if (found & FILE_ATTRIBUTE_DIRECTORY) {
		if (cantHave & SFF_SUBDIR)
			return false;
	}
	else if (mustHave & SFF_SUBDIR)
		return false;

	// arch
	if (found & FILE_ATTRIBUTE_ARCHIVE) {
		if (cantHave & SFF_ARCH)
			return false;
	}
	else if (mustHave & SFF_ARCH)
		return false;

	return true;
}

/*
================
Sys_FindClose
================
*/
void Sys_FindClose (void)
{
	if (sys_findHandle != INVALID_HANDLE_VALUE)
		FindClose (sys_findHandle);

	sys_findHandle = INVALID_HANDLE_VALUE;
}


/*
================
Sys_FindFirst
================
*/
char *Sys_FindFirst (char *path, uint32 mustHave, uint32 cantHave)
{
	WIN32_FIND_DATA	findinfo;

	if (sys_findHandle != INVALID_HANDLE_VALUE)
		Com_Printf (0, "Sys_BeginFind without close");

	Com_FilePath (path, sys_findBase, sizeof(sys_findBase));
	sys_findHandle = FindFirstFile (path, &findinfo);

	if (sys_findHandle == INVALID_HANDLE_VALUE)
		return NULL;

	if (!Sys_CompareFileAttributes (findinfo.dwFileAttributes, mustHave, cantHave))
		return NULL;

	Q_snprintfz (sys_findPath, sizeof(sys_findPath), "%s/%s", sys_findBase, findinfo.cFileName);
	return sys_findPath;
}


/*
================
Sys_FindNext
================
*/
char *Sys_FindNext (uint32 mustHave, uint32 cantHave)
{
	WIN32_FIND_DATA	findinfo;

	if (sys_findHandle == INVALID_HANDLE_VALUE)
		return NULL;

	if (!FindNextFile (sys_findHandle, &findinfo))
		return NULL;

	if (!Sys_CompareFileAttributes (findinfo.dwFileAttributes, mustHave, cantHave))
		return NULL;

	Q_snprintfz (sys_findPath, sizeof(sys_findPath), "%s/%s", sys_findBase, findinfo.cFileName);
	return sys_findPath;
}


/*
================
Sys_FindFiles
================
*/
int Sys_FindFiles (char *path, char *pattern, char **fileList, int maxFiles, int fileCount, bool recurse, bool addFiles, bool addDirs)
{
	WIN32_FIND_DATA	findInfo;
	HANDLE			findHandle;
	BOOL			findRes = TRUE;
	char			findPath[MAX_OSPATH], searchPath[MAX_OSPATH];

	Q_snprintfz (searchPath, sizeof(searchPath), "%s/*", path);

	findHandle = FindFirstFile (searchPath, &findInfo);
	if (findHandle == INVALID_HANDLE_VALUE)
		return fileCount;

	while (findRes == TRUE) {
		// Check for invalid file name
		if (findInfo.cFileName[strlen(findInfo.cFileName)-1] == '.') {
			findRes = FindNextFile (findHandle, &findInfo);
			continue;
		}

		Q_snprintfz (findPath, sizeof(findPath), "%s/%s", path, findInfo.cFileName);

		if (findInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			// Add a directory
			if (addDirs && fileCount < maxFiles)
				fileList[fileCount++] = Mem_StrDup (findPath);

			// Recurse down the next directory
			if (recurse)
				fileCount = Sys_FindFiles (findPath, pattern, fileList, maxFiles, fileCount, recurse, addFiles, addDirs);
		}
		else {
			// Match pattern
			if (!Q_WildcardMatch (pattern, findPath, 1)) {
				findRes = FindNextFile (findHandle, &findInfo);
				continue;
			}

			// Add a file
			if (addFiles && fileCount < maxFiles)
				fileList[fileCount++] = Mem_StrDup (findPath);
		}

		findRes = FindNextFile (findHandle, &findInfo);
	}

	FindClose (findHandle);

	return fileCount;
}


/*
================
FS_AddGameDirectory

Sets fs_gameDir, adds the directory to the head of the path, and loads *.pak/*.pkz
================
*/
static void FS_AddGameDirectory (char *dir, char *gamePath)
{
	fsPath_t	*search;

	if (fs_developer->Integer())
		Com_Printf (0, "FS_AddGameDirectory: adding \"%s\"\n", dir);

	// Set as game directory
	Q_strncpyz(fs_gameDir, dir, sizeof(fs_gameDir));

	// Add the directory to the search path
	search = (fsPath_t*)Mem_PoolAlloc (sizeof(fsPath_t), com_fileSysPool, 0);
	Q_strncpyz(search->pathName, dir, sizeof(search->pathName));
	Q_strncpyz(search->gamePath, gamePath, sizeof(search->gamePath));
	search->next = fs_searchPaths;
	fs_searchPaths = search;
}

/*
=============================================================================

	GAME PATH

=============================================================================
*/

/*
============
FS_Gamedir
============
*/
const char *FS_Gamedir()
{
	if (*fs_gameDir)
		return fs_gameDir;
	else
		return BASE_MODDIRNAME;
}


/*
================
FS_SetGamedir

Sets the gamedir and path to a different directory.
================
*/
void FS_SetGamedir(char *dir, bool firstTime)
{
	fsPath_t	*next;
	int			i;

	// Make sure it's not a path
	if (strstr (dir, "..") || strchr (dir, '/') || strchr (dir, '\\') || strchr (dir, ':'))
	{
		Com_Printf(PRNT_WARNING, "FS_SetGamedir: Gamedir should be a single directory name, not a path\n");
		return;
	}

	// Free old inverted paths
	if (fs_invSearchPaths)
	{
		Mem_Free(fs_invSearchPaths);
		fs_invSearchPaths = NULL;
	}

	// Free up any current game dir info
	for ( ; fs_searchPaths != fs_baseSearchPath ; fs_searchPaths=next)
	{
		next = fs_searchPaths->next;

		Mem_Free(fs_searchPaths);
	}

	// Load packages
	Q_snprintfz(fs_gameDir, sizeof(fs_gameDir), "%s/%s", fs_basedir->String(), dir);

	// Store a copy of the search paths inverted for FS_FindFiles
	for (fs_numInvSearchPaths=0, next=fs_searchPaths ; next ; next=next->next, fs_numInvSearchPaths++);
	fs_invSearchPaths = (fsPath_t**)Mem_PoolAlloc(sizeof(fsPath_t) * fs_numInvSearchPaths, com_fileSysPool, 0);
	for (i=fs_numInvSearchPaths-1, next=fs_searchPaths ; i>=0 ; next=next->next, i--)
		fs_invSearchPaths[i] = next;
}


/*
=============================================================================

	FILE SEARCHING

=============================================================================
*/

/*
================
FS_FindFiles
================
*/
int FS_FindFiles(const char *path, const char *filter, const char *extension, char **fileList, int maxFiles, const bool addGameDir, const bool recurse)
{
	// Sanity check
	if (maxFiles > FS_MAX_FINDFILES)
	{
		Com_Printf(PRNT_ERROR, "FS_FindFiles: maxFiles(%i) > %i, forcing %i...\n", maxFiles, FS_MAX_FINDFILES, FS_MAX_FINDFILES);
		maxFiles = FS_MAX_FINDFILES;
	}

	// Search through the path, one element at a time
	int fileCount = 0;
	for (int pathNum=0 ; pathNum<fs_numInvSearchPaths ; pathNum++)
	{
		fsPath_t *search = fs_invSearchPaths[pathNum];

		// Directory tree
		char dir[MAX_OSPATH];
		Q_snprintfz(dir, sizeof(dir), "%s/%s", search->pathName, path);

		char *dirFiles[FS_MAX_FINDFILES];
		int dirCount;
		if (extension)
		{
			char ext[MAX_QEXT];
			Q_snprintfz(ext, sizeof(ext), "*.%s", extension);
			dirCount = Sys_FindFiles(dir, ext, dirFiles, FS_MAX_FINDFILES, 0, recurse, true, false);
		}
		else
		{
			dirCount = Sys_FindFiles(dir, "*", dirFiles, FS_MAX_FINDFILES, 0, recurse, true, true);
		}

		for (int fileNum=0 ; fileNum<dirCount ; fileNum++)
		{
			// Match filter
			if (filter)
			{
				if (!Q_WildcardMatch(filter, dirFiles[fileNum]+strlen(search->pathName)+1, 1))
				{
					Mem_Free(dirFiles[fileNum]);
					continue;
				}
			}

			// Found something
			char *name = dirFiles[fileNum] + strlen(search->pathName) + 1;
			if (fileCount < maxFiles)
			{
				// Ignore duplicates
				bool bFound = false;
				for (int i=0 ; i<fileCount ; i++)
				{
					if (!Q_stricmp(fileList[i], name))
						break;
				}

				if (!bFound)
				{
					if (addGameDir)
						fileList[fileCount++] = Mem_PoolStrDup(Q_VarArgs("%s/%s", search->gamePath, name), com_fileSysPool, 0);
					else
						fileList[fileCount++] = Mem_PoolStrDup(name, com_fileSysPool, 0);
				}
			}

			Mem_Free(dirFiles[fileNum]);
		}
	}

	return fileCount;
}


/*
=============
_FS_FreeFileList
=============
*/
void _FS_FreeFileList (char **list, int num, const char *fileName, const int fileLine)
{
	int		i;

	for (i=0 ; i<num ; i++) {
		if (!list[i])
			continue;

		_Mem_Free (list[i], fileName, fileLine);
		list[i] = NULL;
	}
}


/*
================
FS_NextPath

Allows enumerating all of the directories in the search path
================
*/
char *FS_NextPath (char *prevPath)
{
	fsPath_t	*s;
	char		*prev;

	if (!prevPath)
		return fs_gameDir;

	prev = fs_gameDir;
	for (s=fs_searchPaths ; s ; s=s->next)
	{
		if (prevPath == prev)
			return s->pathName;
		prev = s->pathName;
	}

	return NULL;
}

/*
=============================================================================

	INIT / SHUTDOWN

=============================================================================
*/

/*
================
FS_Init
================
*/
void FS_Init()
{
	fsPath_t	*next;
	int			i;

	fs_basedir		= QNew (com_gamePool, 0) CCvar ("basedir",			".", 0);
	fs_cddir		= QNew (com_gamePool, 0) CCvar ("cddir",			"",		0);
	fs_game			= QNew (com_gamePool, 0) CCvar ("game",			"",		0);
	fs_gamedircvar	= QNew (com_gamePool, 0) CCvar ("gamedir",			"",		0);
	fs_developer	= QNew (com_gamePool, 0) CCvar ("fs_developer",	"",		0);

	if (fs_cddir->String()[0])
		FS_AddGameDirectory(Q_VarArgs("%s/"BASE_MODDIRNAME, fs_cddir->String()), BASE_MODDIRNAME);

	FS_AddGameDirectory(Q_VarArgs("%s/"BASE_MODDIRNAME, fs_basedir->String()), BASE_MODDIRNAME);

	// Any set gamedirs will be freed up to here
	fs_baseSearchPath = fs_searchPaths;

	// Load the game directory
	if (fs_game->String()[0])
		FS_SetGamedir(fs_game->String(), true);
	else
	{
		// Store a copy of the search paths inverted for FS_FindFiles
		for (fs_numInvSearchPaths=0, next=fs_searchPaths ; next ; next=next->next, fs_numInvSearchPaths++);
		fs_invSearchPaths = (fsPath_t**)Mem_PoolAlloc (sizeof(fsPath_t) * fs_numInvSearchPaths, com_fileSysPool, 0);
		for (i=fs_numInvSearchPaths-1, next=fs_searchPaths ; i>=0 ; next=next->next, i--)
			fs_invSearchPaths[i] = next;
	}

	// Check memory integrity
	Mem_CheckPoolIntegrity (com_fileSysPool);
}