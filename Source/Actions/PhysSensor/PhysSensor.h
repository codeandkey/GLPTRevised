#pragma once

#include <neptune/Neptune.h>

#include "../../Components/PhysicsCallback/PhysicsCallback.h"

namespace Actions {
	class PhysSensor : public Neptune::ECS::Action {
	public:
		PhysSensor(float width, float height);
		~PhysSensor(void);

		int CheckCollision(void);

		float X(void);
		void X(float);
		float Y(void);
		void Y(float);
		float Angle(void);
		void Angle(float);
	private:
		float x, y;
		float angle;
		float width, height;

		Components::PhysicsCallback* sensor_object;
	};
}