#include "AimBot.h"

void AimContext::update()
{
	if (!GetAsyncKeyState(18))
		return;

	using std::cout;
	using std::endl;

	int pLocal;
	memoryManager->read(client.dwBase + signatures::dwLocalPlayer, &pLocal, sizeof(pLocal));
	if (!pLocal)
		return;

	int health;
	memoryManager->read(pLocal + netvars::m_iHealth, &health, sizeof(health));
	if (!health)
		return;

	int pEngine;
	memoryManager->read(engine.dwBase + signatures::dwClientState, &pEngine, sizeof(pEngine));
	if (!pEngine)
		return;

	int target = getTarget(pLocal, pEngine);
	if (target == -1)
		return;

	setViewAngle(pEngine, angleToTarget(pLocal, target, 8));
}

Vector AimContext::getBonePos(int pTargetIn, int bone)
{
	int32_t matrix;
	memoryManager->read(pTargetIn + netvars::m_dwBoneMatrix, &matrix, sizeof(matrix));

	Vector result;
	memoryManager->read(matrix + 0x30 * bone + 0xC, &result.x, sizeof(float));
	memoryManager->read(matrix + 0x30 * bone + 0x1C, &result.y, sizeof(float));
	memoryManager->read(matrix + 0x30 * bone + 0x2C, &result.z, sizeof(float));
	//Maybe we can read 1 time instead of 3

	result.z -= 15;
	return result;
}

void AimContext::setViewAngle(uint32_t engineBase, Vector angle)
{
	ClampAngles(angle);
	NormalizeAngles(angle);

	memoryManager->write(engineBase + signatures::dwClientState_ViewAngles, &angle, sizeof(angle));
}

Vector AimContext::angleToTarget(int pLocal, int pTargetIn, int boneIndex)
{
	Vector position, vecView;
	memoryManager->read(pLocal + netvars::m_vecOrigin, &position, sizeof(position));
	memoryManager->read(pLocal + netvars::m_vecViewOffset, &vecView, sizeof(vecView));

	const Vector myView = position + vecView;
	const Vector aimView = getBonePos(pTargetIn, boneIndex);

	Vector dst = CalcAngle(myView, aimView).ToVector();

	NormalizeAngles(dst);

	return dst;
}

int AimContext::getTarget(int pLocal, int clientState)
{
	int currentTarget = -1;
	float misDist = 360.f;

	Vector viewAngles;
	memoryManager->read(clientState + signatures::dwClientState_ViewAngles, &viewAngles, sizeof(viewAngles));

	int playerTeam;
	memoryManager->read(pLocal + netvars::m_iTeamNum, &playerTeam, sizeof(playerTeam));

	for (int i = 0; i <= 64; i++)
	{
		int target;
		memoryManager->read(client.dwBase + signatures::dwEntityList + (i - 1) * 0x10, &target, sizeof(target));
		if (!target || target < 0)
			continue;

		int targetHealth;
		memoryManager->read(target + netvars::m_iHealth, &targetHealth, sizeof(targetHealth));
		if (!targetHealth || targetHealth < 0)
			continue;

		int targetTeam;
		memoryManager->read(target + netvars::m_iTeamNum, &targetTeam, sizeof(targetTeam));
		if (!targetTeam || targetTeam == playerTeam)
			continue;

		bool targetDormant;
		memoryManager->read(target + signatures::m_bDormant, &targetDormant, sizeof(targetDormant));
		if (targetDormant)
			continue;

		Vector angleToTarget = this->angleToTarget(pLocal, target, 8);
		float fov = GetFov(viewAngles.ToQAngle(), angleToTarget.ToQAngle());
		if (fov < misDist && fov <= 20)
		{
			misDist = fov;
			currentTarget = target;
		}
	}

	return currentTarget;
}
