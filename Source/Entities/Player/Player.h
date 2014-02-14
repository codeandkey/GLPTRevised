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
		float Width(void);
		float Height(void);

		void SetGrounded(bool);
		bool IsGrounded(void);
	private:
		bool is_grounded;

		Actions::AnimatedSprite* animation_sprite_handle;
		Actions::PhysBox* physbox_handle;
		Actions::PhysSensor* lower_sensor;
	};
}