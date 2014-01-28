#pragma once

#include <neptune/Neptune.h>

// GameController is sort of a level/room controller.
// It manages flushing the Manager and loading maps, etc.

namespace Tasks {
	template <typename T> static Neptune::ECS::Entity* CreateNew(void) { return new T; }

	class GameController : public Neptune::Kernel::Task , public Neptune::Singleton::Singleton<GameController> {
	public:
		GameController(void);

		void TaskStep(void);

		void LoadMap(std::string filename);

		template <typename T> void BindEntity(std::string key) {
			entity_register_map[key]=&CreateNew<T>;
		}
	private:
		std::map<std::string,Neptune::ECS::Entity*(*)(void)> entity_register_map;
	};
}