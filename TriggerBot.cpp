#include "TriggerBot.h"

void TriggerContext::update()
{
	uint32_t crosshairId; 
	memoryManager->read(o_crosshairId, &crosshairId, sizeof(crosshairId));
	if (!crosshairId || crosshairId > 64)
		return;

	uint32_t entityBase;
	memoryManager->read(client.dwBase + signatures::dwEntityList + (crosshairId - 1) * 0x10, &entityBase, sizeof(entityBase));
	if (!entityBase)
		return;

	uint32_t entityHp, entityTeam;
	memoryManager->read(entityBase + netvars::m_iHealth, &entityHp, sizeof(entityHp));
	memoryManager->read(entityBase + netvars::m_iTeamNum, &entityTeam, sizeof(entityTeam));
	
	if (!entityHp || entityTeam == localPlayer->teamId)
		return;

	Sleep(delayBefore);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(delayAfter);
}
