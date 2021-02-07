#pragma once
#ifndef _MEMORY_MANAGER_INCLUDED_
#define _MEMORY_MANAGER_INCLUDED_

#include <string>
#include <vector>
#include <chrono>

#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>

#include "Offsets.h"

using namespace std::chrono_literals;
using std::chrono::seconds;
using std::chrono::milliseconds;

struct PModule
{
	DWORD dwBase, dwSize;
};
constexpr PModule INVALID_PMODULE = PModule{ 0, 0 };

struct Data
{
	void* pData;
	size_t dSize;
	bool acitve;
};

class MemoryManager
{
public:
	bool attach(const std::string& processName, DWORD dwAccess, std::chrono::seconds timeout);

	PModule getModule(const std::string& moduleName);

	void read(ptrdiff_t dwAddress, void* buffer, size_t dSize);
	void write(ptrdiff_t dwAddress, const void* value, size_t dSize);

	void exit();

private:
	HANDLE hProcess;
	DWORD pId;
};

#endif