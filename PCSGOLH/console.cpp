#include "console.hpp"

namespace Console
{
	void initialize(void)
	{
		AllocConsole();
		freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		SetConsoleTitleA("[PCSGOLH] Console");
	}

	void destroy(void)
	{
		fclose((FILE*)stdin);
		fclose((FILE*)stdout);
		FreeConsole();
	}

	void run(LPVOID base)
	{
		std::cout << "\n> ";
		std::string buf;

		while (!Loader::pendingUnload)
		{
			std::getline(std::cin, buf);
			if (luaL_dostring(LuaState::pLuaState, buf.c_str()) != 0)
			{
				Logger::append(Logger::kLogType::ERROR, "Error: %s\n", lua_tostring(LuaState::pLuaState, -1));
			}
			std::cout << "> ";
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
	}
}