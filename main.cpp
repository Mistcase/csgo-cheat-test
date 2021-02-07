#include "MemoryManager.h"
#include "WallHack.h"
#include "TriggerBot.h"
#include "AimBot.h"
#include "Error.h"

int main()
{
	MemoryManager memoryManager;
	if (!memoryManager.attach("csgo.exe", PROCESS_ALL_ACCESS, 10s))
	{
		PrintError("Cannot attach to process!");
		return -1;
	}	
	MessageBox(NULL, "ATTACH!", "Message", MB_ICONASTERISK);

	LocalPlayer localPlayer(&memoryManager);
	WallHackContext wh_context(&memoryManager, &localPlayer);
	TriggerContext tb_context(&memoryManager, &localPlayer, 5, 15);
	AimContext ab_context(&memoryManager, &localPlayer);

	while (true)
	{
		localPlayer.update();
		if (!localPlayer.health)
		{
			Sleep(500);
			continue;
		}

		wh_context.update();
		tb_context.update();
		ab_context.update();
	}

	return 0;
}
