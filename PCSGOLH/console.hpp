#pragma once

#include <Windows.h>
#include <thread>

#include "luastate.hpp"
#include "loader.hpp"
#include "logger.hpp"

namespace Console
{
	void initialize(void);
	void destroy(void);
	void run(LPVOID base);
}