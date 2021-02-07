#include "MemoryManager.h"

bool MemoryManager::attach(const std::string& processName, DWORD dwAccess, seconds timeout)
{
	const seconds PAUSE = 1s;
	seconds timer = 0s;

	while (timer < timeout)
	{
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		while (Process32Next(handle, &entry))
		{
			if (processName == entry.szExeFile)
			{
				pId = entry.th32ProcessID;
				CloseHandle(handle);
				hProcess = OpenProcess(dwAccess, false, pId);
				return true;
			}
		}

		Sleep(milliseconds(PAUSE).count());
		timer += PAUSE;
	}

	return false;
}

PModule MemoryManager::getModule(const std::string & moduleName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(entry);

	while (Module32Next(handle, &entry))
	{
		if (moduleName == entry.szModule)
		{
			CloseHandle(handle);
			return PModule{ reinterpret_cast<DWORD>(entry.hModule), entry.modBaseSize };
		}
	}

	return PModule{ 0, 0 };
}

void MemoryManager::read(ptrdiff_t dwAddress, void * buffer, size_t dSize)
{
	ReadProcessMemory(hProcess, reinterpret_cast<LPVOID>(dwAddress), buffer, dSize, nullptr);
}

void MemoryManager::write(ptrdiff_t dwAddress, const void * value, size_t dSize)
{
	WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(dwAddress), value, dSize, nullptr);
}
void MemoryManager::exit()
{
	CloseHandle(hProcess);
}
