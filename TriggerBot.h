#pragma once
#ifndef _TRIGGER_BOT_INCLUDED_
#define _TRIGGER_BOT_INCLUDED_

#include "Context.h"

#include <iostream>

class TriggerContext : public Context
{
public:
	TriggerContext(MemoryManager* mm, LocalPlayer* player, unsigned int db, unsigned int da)
		: Context(mm, player)
	{
		o_crosshairId = localPlayer->address + netvars::m_iCrosshairId;

		delayBefore = db;
		delayAfter = da;
	}
		
	void update();

private:
	ptrdiff_t o_crosshairId;

	unsigned int delayBefore, delayAfter;
};

#endif