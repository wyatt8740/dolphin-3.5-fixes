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
#ifndef _CPU_H
#define _CPU_H

#include "Common.h"

namespace Common {
	class Event;
}

class CCPU
{
public:
	// init 
	static void Init(int cpu_core);

	// shutdown
	static void Shutdown();

	// starts the CPU
	static void Run();

	// causes shutdown
	static void Stop(); 
	// Reset
	static void Reset();

	// StepOpcode (Steps one Opcode)
	static void StepOpcode(Common::Event *event = 0);

	// one step only
	static void SingleStep();

	// Enable or Disable Stepping
	static void EnableStepping(const bool _bStepping);	

	// break, same as EnableStepping(true).
	static void Break();

	// is stepping ?
	static bool IsStepping();

	// waits until is stepping and is ready for a command (paused and fully idle), and acquires a lock on that state.
	// or, if doLock is false, releases a lock on that state and optionally re-disables stepping.
	// calls must be balanced and non-recursive (once with doLock true, then once with doLock false).
	// intended (but not required) to be called from another thread,
	// e.g. when the GUI thread wants to make sure everything is paused so that it can create a savestate.
	// the return value is whether the cpu was unpaused before the call.
	static bool PauseAndLock(bool doLock, bool unpauseOnUnlock=true);
};

#endif

