#pragma once
#ifndef _WALLHACK_INCLUDED_
#define _WALLHACK_INCLUDED_

#include "Context.h"
#include "Player.h"

#include <iostream>

class WallHackContext : public Context
{
public:

	struct GlowObject
	{
		float r;
		float g;
		float b;
		float a;
		uint8_t unk1[16];
		bool beRenderWhenOccluded;
		bool beRenderWhenUnOccluded;
		bool beFullBloom;
		int glowStyle;
		uint8_t unk2[10];
	};

	const int32_t TEAM_T = 2;
	const int32_t TEAM_CT = 3;

public:
	WallHackContext(MemoryManager* mm, LocalPlayer* player)
		: Context(mm, player)
	{
		o_glowArray = client.dwBase + signatures::dwGlowObjectManager;
		o_glowCount = o_glowArray + 0x4;
	}

	void update();

private:
	ptrdiff_t o_glowArray, o_glowCount;
};

#endif