#pragma once
#ifndef _AIMBOT_INCLDUED_
#define _AIMBOT_INCLDUED_

#include "Context.h"
#include "AimMath.h"

class AimContext : public Context
{
public:
	AimContext(MemoryManager* mm, LocalPlayer* player)
		: Context(mm, player)
	{
		clientPanorama = memoryManager->getModule("client_panorama.dll");
		engine = memoryManager->getModule("engine.dll");
	}

	void update();

private:
	Vector getBonePos(int pTargetIn, int bone);
	
	void setViewAngle(uint32_t engineBase, Vector angle);

	Vector angleToTarget(int pLocal, int pTargetIn, int boneMatrix);

	int getTarget(int pLocal, int clientState);

private:
	PModule clientPanorama, engine;

	ptrdiff_t o_boneMatrix;
};

#endif