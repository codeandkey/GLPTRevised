#pragma once

#include <Box2D/Box2D.h>

#include <neptune/Neptune.h>

namespace Components {
	class PhysicsObject;

	class PhysicsCallback : public Neptune::ECS::Component , public b2RayCastCallback , public b2QueryCallback {
	public:
		PhysicsObject* ObjectLineCollision(float x1, float y1, float x2, float y2);
		int ObjectBoxCollision(float x, float y, float w, float h, b2Fixture* locate = NULL);
		bool ObjectPointCollision(PhysicsObject*,float x, float y);

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
		bool ReportFixture(b2Fixture* fixture);

	private:
		bool query_callback_mode;

		std::vector<b2Fixture*> fixture_buffer;
		b2Fixture* recent_closest_raycast;
	};
}