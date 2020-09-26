#include "loader.hpp"
#include "interfaces.h"
#include "luastate.hpp"
#include "binds.hpp"
#include "hooks.hpp"
#include "console.hpp"

#include <luabind/luabind.hpp>

bool Loader::pendingUnload = false;

namespace Loader
{
	void initialize(void)
	{
		printf("=================[PCSGOLH]=================\n");
		printf("Github: www.github.com/xrivendell/pcsgolh\n");
		printf("Compiled: %s @ %s\n\n", __DATE__, __TIME__);
		printf("Press F5 to refresh a lua script\n");
		printf("=================[PCSGOLH]=================\n\n");

		if (Hooks::gWindowProc == NULL)
		{
			HWND hWindow = NULL;
			while (!(hWindow = FindWindowA("Valve001", "Counter-Strike: Global Offensive"))) Sleep(200);
			Hooks::gWindowProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)Hooks::NewWndProc);
		}

		Logger::append(Logger::kLogType::SUCCESS, "Initializing LuaState...\n");
		LuaState::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Interfaces...\n");
		Interfaces::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Initializing Binds...\n");
		Binds::initialize();
	}

	void unload(void)
	{
		pendingUnload = true;

		Logger::append(Logger::kLogType::ERROR, "Restoring WindowProc...\n");
		if (Hooks::gWindowProc != NULL)
			SetWindowLongPtrA(FindWindow("Valve001", NULL), GWL_WNDPROC, (LONG)Hooks::gWindowProc);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Logger::append(Logger::kLogType::ERROR, "Unhooking Interfaces...\n");
		Interfaces::unhook();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Logger::append(Logger::kLogType::ERROR, "Unloading LuaState...\n");
		LuaState::unload();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Logger::append(Logger::kLogType::ERROR, "Destroying Console...\n");
		Console::destroy();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}