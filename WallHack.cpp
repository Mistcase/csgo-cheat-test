#include "WallHack.h"

void WallHackContext::update()
{
	int32_t glowArray, glowCount, entityTeam;
	uint32_t glowObject, entityHp;
	GlowObject Glow;

	memoryManager->read(o_glowArray, &glowArray, sizeof(glowArray));
	memoryManager->read(o_glowCount, &glowCount, sizeof(glowCount));

	for (int i = 0; i < glowCount; i++)
	{
		memoryManager->read(glowArray + 0x38 * i, &glowObject, sizeof(glowObject));
		if (!glowObject)
			continue;

		memoryManager->read(glowObject + netvars::m_iHealth, &entityHp, sizeof(entityHp));
		if (!entityHp)
			continue;

		memoryManager->read(glowObject + netvars::m_iTeamNum, &entityTeam, sizeof(entityTeam));
		if (entityTeam == localPlayer->teamId)
			continue;

		ptrdiff_t currentAddress = glowArray + (i * 0x38) + 0x4;
		memoryManager->read(currentAddress, &Glow, sizeof(Glow)); //How to delete it

		if (entityTeam == TEAM_T)
		{
			Glow.r = 0.8784314f;
			Glow.g = 0.6862745f;
			Glow.b = 0.3372549f;
			Glow.a = 0.6f;
		}
		else if (entityTeam == TEAM_CT)
		{
			Glow.r = 0.447058827f;
			Glow.g = 0.607843161f;
			Glow.b = 0.8666667f;
			Glow.a = 0.6f;
		}
		Glow.beRenderWhenOccluded = true;
		Glow.beRenderWhenUnOccluded = false;

		memoryManager->write(currentAddress, &Glow, sizeof(Glow));
	}
}
