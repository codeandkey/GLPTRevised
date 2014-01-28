#pragma once

#include <Box2D/Box2D.h>

#include <neptune/Neptune.h>

namespace Components {
	class PhysicsObject;

	class PhysicsCallback : public Neptune::ECS::Component , public b2RayCastCallback {
	public:
		PhysicsObject* ObjectLineCollision(float x1, float y1, float x2, float y2);
		bool ObjectPointCollision(PhysicsObject*,float x, float y);
	private:
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
		b2Fixture* recent_closest_raycast;
	};
}