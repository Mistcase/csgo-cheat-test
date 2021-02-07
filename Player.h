#pragma once
#ifndef _PLAYER_INFO_FILE_INCLUDED_
#define _PLAYER_INFO_FILE_INCLUDED_

#include "MemoryManager.h"

struct Player
{
	uint32_t health, teamId;
	ptrdiff_t address;
};

class LocalPlayer : public Player
{
public:
	LocalPlayer(MemoryManager* mm);

	void update();

private:
	MemoryManager* memoryManager;
	PModule client;
	ptrdiff_t o_player;
};


#endif