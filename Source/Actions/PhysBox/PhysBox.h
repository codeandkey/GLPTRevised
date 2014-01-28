#pragma once

#include <neptune/Neptune.h>

#include "../../Components/PhysicsObject/PhysicsObject.h"

namespace Actions {
	class PhysBox : public Neptune::ECS::Action {
	public:
		struct PhysBoxDesc {
			float width,height;
			bool static_object;
			float friction;
			float density;

			PhysBoxDesc(void) : width(1.0f) , height(1.0f) , static_object(false) , friction(0.5f) , density(1.0f) {}
			PhysBoxDesc(float width, float height) : width(width) , height(height) , static_object(false) , friction(0.5f) , density(1.0f) {}
			PhysBoxDesc(float width, float height, bool static_object) : width(width), height(height) , static_object(static_object) , friction(0.5f) , density(1.0f) {}
			PhysBoxDesc(float width, float height, bool static_object , float friction, float density) : width(width) , height(height) , friction(friction) , density(density) , static_object(static_object) {}
		};

		PhysBox(PhysBoxDesc phys_desc = PhysBoxDesc());
		~PhysBox(void);

		float X(void);
		float Y(void);
		float Angle(void);
		float XSpeed(void);
		float YSpeed(void);
		float RSpeed(void);

		void X(float);
		void Y(float);
		void Angle(float);
		void XSpeed(float);
		void YSpeed(float);
		void RSpeed(float);

		void PushDirectional(float direction, float strength);
		void Push(float delta_x, float delta_y);

		void RotationalPush(float strength);

		void SpecialHook(void* data);
	private:

		Components::PhysicsObject* phys_object_handle;
	};
}