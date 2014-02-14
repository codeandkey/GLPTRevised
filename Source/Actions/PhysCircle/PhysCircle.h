#pragma once

#include <neptune/Neptune.h>

#include "../../Components/PhysicsObject/PhysicsObject.h"

namespace Actions {
	class PhysCircle : public Neptune::ECS::Action {
	public:
		struct PhysCircleDesc {
			float radius;
			bool static_object;
			float friction;
			float density;

			PhysCircleDesc(void) : radius(1.0f), static_object(false), friction(0.5f), density(1.0f) {}
			PhysCircleDesc(float radius) : radius(radius), static_object(false), friction(0.5f), density(1.0f) {}
			PhysCircleDesc(float radius, bool static_object) : radius(radius), static_object(static_object), friction(0.5f), density(1.0f) {}
			PhysCircleDesc(float radius, bool static_object, float friction, float density) : radius(radius), friction(friction), density(density), static_object(static_object) {}
		};

		PhysCircle(PhysCircleDesc phys_desc = PhysCircleDesc());
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

		Components::PhysicsObject* GetPhysObject(void);
	private:

		Components::PhysicsObject* phys_object_handle;
	};
}