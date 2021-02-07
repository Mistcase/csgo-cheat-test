#include "Player.h"

LocalPlayer::LocalPlayer(MemoryManager * mm)
{
	memoryManager = mm;
	client = memoryManager->getModule("client.dll");

	memoryManager->read(client.dwBase + signatures::dwLocalPlayer, &address, sizeof(address));
}

void LocalPlayer::update()
{
	memoryManager->read(client.dwBase + signatures::dwLocalPlayer, &o_player, sizeof(o_player));
	memoryManager->read(o_player + netvars::m_iHealth, &health, sizeof(health));
	memoryManager->read(o_player + netvars::m_iTeamNum, &teamId, sizeof(teamId));
}
