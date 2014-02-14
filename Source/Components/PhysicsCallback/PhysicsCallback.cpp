#include "PhysicsCallback.h"
#include "../PhysicsObject/PhysicsObject.h"
#include "../../Tasks/PhysicsController/PhysicsController.h"

using namespace Components;

float32 PhysicsCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	recent_closest_raycast = fixture;

	return fraction;
}

bool PhysicsCallback::ReportFixture(b2Fixture* fixture) {
	fixture_buffer.push_back(fixture);

	return query_callback_mode;
}

PhysicsObject* PhysicsCallback::ObjectLineCollision(float x1, float y1, float x2, float y2) {
	b2RayCastInput raycast_input;
	
	raycast_input.maxFraction = 1.0f; // The max fraction is actually disregarded during world casting, for some reason.
	raycast_input.p1 = b2Vec2(x1,y1);
	raycast_input.p2 = b2Vec2(x2,y2);

	recent_closest_raycast = NULL;

	Tasks::PhysicsController::Handle()->RaycastWorld(raycast_input,this);

	if (!recent_closest_raycast) return NULL;

	return (PhysicsObject*) recent_closest_raycast->GetUserData();
}

int PhysicsCallback::ObjectBoxCollision(float x, float y, float w, float h, b2Fixture* locate_object) {
	fixture_buffer.clear();
	query_callback_mode = (bool) locate_object;

	b2AABB area;

	area.lowerBound = b2Vec2(x - w, y - h);
	area.upperBound = b2Vec2(x + w, y + h);

	Tasks::PhysicsController::Handle()->QueryWorld(area, this);

	return fixture_buffer.size();
}

bool PhysicsCallback::ObjectPointCollision(PhysicsObject* object,float x, float y) {
	return object->TestPoint(x,y); // This is just a wrapper to accommodate those who forget.
}