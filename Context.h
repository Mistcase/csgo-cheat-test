#pragma once
#ifndef _CONTEXT_FILE_INCLUDED_
#define _CONTEXT_FILE_INCLUDED_

#include "MemoryManager.h"
#include "Player.h"

class Context
{
	Context(const Context&) = delete;
	Context(Context&&) = delete;

protected:
	Context(MemoryManager* mm, LocalPlayer* player);

protected:
	MemoryManager* memoryManager;
	PModule client;

protected:
	LocalPlayer* localPlayer;
};

#endif