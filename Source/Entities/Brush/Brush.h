#pragma once

#include <neptune/Neptune.h>

#include "../../Actions/ActionModule.h"

namespace Entities {
	class Brush : public Neptune::ECS::Entity {
	public:
		void InitEvent(void);

		void StepEvent(void);
		void DrawEvent(void);

		~Brush(void);
	private:

		Actions::AnimatedSprite* animation_handle;
		Actions::PhysBox* physbox_handle;
	};
}