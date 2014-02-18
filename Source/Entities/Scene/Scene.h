#pragma once

#include <Neptune/Neptune.h>

#include "../../Actions/ActionModule.h"

namespace Entities {
	class Scene : public Neptune::ECS::Entity {
	public:
		enum SceneMode {
			SceneDarkCloudy
		};

		Scene(SceneMode target_mode);

		void InitEvent(void);

		void DrawEvent(void);
		void StepEvent(void);
	private:
		Actions::AnimatedSprite* cloud_sprite_handle, *cloud_2_sprite_handle;
		Actions::AnimatedSprite* background_star_handle;

		Neptune::Audio::Sound* background_sound_handle;

		SceneMode current_mode;

	};
}