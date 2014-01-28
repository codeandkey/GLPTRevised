#pragma once

#include <neptune/Neptune.h>

#include "../../Actions/ActionModule.h"

namespace Entities {
	class Player : public Neptune::ECS::Entity {
	public:
		void InitEvent(void);
		void StepEvent(void);
		void DrawEvent(void);
		void DestroyEvent(void);

		float X(void);
		float Y(void);
		float Angle(void);
	private:

		Actions::AnimatedSprite* animation_sprite_handle;
		Actions::PhysBox* physbox_handle;
	};
}