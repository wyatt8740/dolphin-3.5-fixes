// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef _VERTEXLOADERMANAGER_H
#define _VERTEXLOADERMANAGER_H

#include "Common.h"
#include <string>

namespace VertexLoaderManager
{
	void Init();
	void Shutdown();

	void MarkAllDirty();

	int GetVertexSize(int vtx_attr_group);
	void RunVertices(int vtx_attr_group, int primitive, int count);
	void RunCompiledVertices(int vtx_attr_group, int primitive, int count, u8* Data);

	// For debugging
	void AppendListToString(std::string *dest);
};

void RecomputeCachedArraybases();

#endif  // _VERTEXLOADERMANAGER_H
