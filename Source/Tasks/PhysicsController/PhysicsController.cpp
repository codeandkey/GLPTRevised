#include "PhysicsController.h"

using namespace Neptune;
using namespace Tasks;

PhysicsController::PhysicsController(void) : Kernel::Task("_PhysicsController") {
	phys_space_handle=new b2World(b2Vec2(0.0f,-50.0f));

	phys_space_handle->SetAllowSleeping(true);
}

PhysicsController::~PhysicsController(void) {

	if (phys_space_handle) delete phys_space_handle;
}

b2Body* PhysicsController::AddPhysicsShape(b2BodyDef* target_body) {	
	return phys_space_handle->CreateBody(target_body);
}

void PhysicsController::DestroyPhysicsShape(b2Body* body_handle) {
	phys_space_handle->DestroyBody(body_handle);
}

void PhysicsController::TaskStep(void) {
	// Do fun things with delta times in the future.
	// Until then, use a fixed timestep, like this.

	const float timestep = 1.0f / 80.0f;

	phys_space_handle->Step(timestep,3,8);
}

void PhysicsController::RaycastWorld(b2RayCastInput input,b2RayCastCallback* target) {
	phys_space_handle->RayCast(target,input.p1,input.p2);
}