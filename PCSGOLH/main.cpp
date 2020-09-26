#include <Windows.h>
#include <thread>
#include <chrono>

#include "sdk.hpp"
#include "loader.hpp"
#include "console.hpp"

DWORD WINAPI load(LPVOID base)
{
	Console::initialize();
	
	Loader::initialize();

	Console::run(base);

	return 0;
}

BOOL APIENTRY DllMain(_In_ HINSTANCE hDll, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		
		HANDLE thread = CreateThread(nullptr, NULL, load, hDll, NULL, nullptr);
		if (!thread)
			return 0;

		CloseHandle(thread);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
		return FALSE;

	return TRUE;
}