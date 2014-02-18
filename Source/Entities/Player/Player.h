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
		void SpecialEvent(void*);

		float X(void);
		float Y(void);
		float Angle(void);
		float Width(void);
		float Height(void);

		void SetGrounded(bool);
		bool IsGrounded(void);
	private:
		bool is_grounded;

		Actions::PhysBox* physbox_handle;
		Actions::PhysSensor* lower_sensor;

		Actions::AnimatedSprite* sprite_core_handle;
		Actions::AnimatedSprite* sprite_hat_handle;
		Actions::AnimatedSprite* sprite_rings_handle;

		float sprite_core_x, sprite_core_y, sprite_core_angle;
		float sprite_hat_x, sprite_hat_y, sprite_hat_angle;
		float sprite_rings_x, sprite_rings_y, sprite_rings_angle;

		float rings_angle_speed;

		float initial_x, initial_y;
	};
}