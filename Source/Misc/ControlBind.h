#pragma once

#include <Neptune/Neptune.h>

namespace Misc {
	class ControlBind {
	public:
		static void ReloadControlsFromFile(void);
		static void LoadKeybinds(void);
		static int GetKey(std::string);

	private:
		static std::vector<std::pair<std::string, int>> control_map;
	};
}