#pragma once

namespace Loader
{
	extern bool pendingUnload;

	void initialize(void);
	void unload(void);
}