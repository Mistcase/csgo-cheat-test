#include "Context.h"

Context::Context(MemoryManager* mm, LocalPlayer* player)
{
	memoryManager = mm;
	localPlayer = player;
	client = memoryManager->getModule("client.dll");
}
