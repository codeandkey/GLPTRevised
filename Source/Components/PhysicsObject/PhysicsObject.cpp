#include "PhysicsObject.h"
#include "../../Tasks/PhysicsController/PhysicsController.h"

using namespace Components;

PhysicsObject::PhysicsObject(void) {
	phys_body_handle = NULL;
	phys_shape_handle = NULL;
}

PhysicsObject::~PhysicsObject(void) {
	if (Tasks::PhysicsController::Exists()) {
		Tasks::PhysicsController::Handle()->DestroyPhysicsShape(phys_body_handle);
	}

	if (phys_shape_handle) delete phys_shape_handle;

	phys_shape_handle = NULL;
	phys_body_handle = NULL;
}

void PhysicsObject::CreateRect(float width, float height,float density, float friction,bool static_object) {
	if (this->phys_body_handle) {
		this->~PhysicsObject(); 

		// Intentionally call the destructor without destroying the object.
		// This is because we are avoiding a memory leak in the program.
		// This is semi-acceptable behavior as the problem is handled efficiently and effectively despite the awkward syntax.
	}

	this->static_object = static_object;

	b2BodyDef phys_body_desc;

	phys_body_desc.type = static_object ? b2_staticBody : b2_dynamicBody;

	phys_body_handle = Tasks::PhysicsController::Handle()->AddPhysicsShape(&phys_body_desc);

	phys_shape_handle = new b2PolygonShape;

	((b2PolygonShape*) phys_shape_handle)->SetAsBox(width,height);

	phys_body_handle->CreateFixture(phys_shape_handle,density)->SetUserData((void*) this);
	phys_body_handle->SetUserData((void*) this); // We store our pointer both in the fixture and in the body. They could be shared.

}

void PhysicsObject::CreateCircle(float radius,float density, float friction, bool static_object) {
	if (this->phys_body_handle) {
		this->~PhysicsObject(); 
	}

	this->static_object = static_object;

	b2BodyDef phys_body_desc;

	phys_body_desc.type = static_object ? b2_staticBody : b2_dynamicBody;

	phys_body_handle = Tasks::PhysicsController::Handle()->AddPhysicsShape(&phys_body_desc);

	phys_shape_handle = new b2CircleShape;

	phys_body_handle->CreateFixture(phys_shape_handle,density)->SetUserData((void*) this);
	phys_body_handle->SetUserData((void*) this);
}

void PhysicsObject::GetPosition(float* x, float* y) {
	b2Vec2 phys_pos=phys_body_handle->GetPosition();

	if (x) *x=(float) phys_pos.x;
	if (y) *y=(float) phys_pos.y;
}

void PhysicsObject::GetRotation(float* rotation) {
	float phys_rotation = phys_body_handle->GetAngle();

	if (rotation) *rotation=(float) phys_rotation * 180.0f / 3.141f;
}

void PhysicsObject::GetVelocity(float* hspeed,float* vspeed) {
	b2Vec2 velocity = phys_body_handle->GetLinearVelocity();

	if (hspeed) *hspeed=velocity.x;
	if (vspeed) *vspeed=velocity.y;
}

void PhysicsObject::GetAngularVelocity(float* velocity) {
	if (velocity) *velocity = phys_body_handle->GetAngularVelocity();
}

void PhysicsObject::SetPosition(float x, float y) {
	phys_body_handle->SetTransform(b2Vec2(x,y),phys_body_handle->GetAngle());
}

void PhysicsObject::SetRotation(float rotation) {
	phys_body_handle->SetTransform(phys_body_handle->GetPosition(),rotation * 3.141f / 180.0f);
	// Setting the rotation like this tends to apply a substantial amount of angular velocity.

	phys_body_handle->SetAngularVelocity(0.0f); 
}

void PhysicsObject::SetVelocity(float hspeed, float vspeed) {
	phys_body_handle->SetLinearVelocity(b2Vec2(hspeed,vspeed));
}

void PhysicsObject::SetAngularVelocity(float speed) {
	phys_body_handle->SetAngularVelocity(speed);
}

bool PhysicsObject::IsStaticBody(void) {
	return static_object;
}

void PhysicsObject::GetMovementDirection(float* angle) {

	float delta_x, delta_y;

	GetVelocity(&delta_x,&delta_y);

	if (angle) *angle = (delta_x ? atan2(delta_y,delta_x) : ((delta_y > 0.0f) ? 3.141f / 2.0f : -3.141f / 2.0f));

}

void PhysicsObject::ApplyForce(float x, float y) {
	phys_body_handle->ApplyLinearImpulse(b2Vec2(x,y),b2Vec2(0.0f,0.0f),true);
}

void PhysicsObject::ApplyAngularForce(float strength) {
	phys_body_handle->ApplyAngularImpulse(strength,true);
}

bool PhysicsObject::TestPoint(float x, float y) {
	return phys_body_handle->GetFixtureList()->TestPoint(b2Vec2(x,y));
}

void PhysicsObject::GetAllCollisions(std::function <bool (std::vector<std::pair<float,float>>)> callback_function) {
	b2ContactEdge* contact_buffer;

	contact_buffer = phys_body_handle->GetContactList();

	while (contact_buffer) {
		b2WorldManifold contact_manifold;
		unsigned int point_count;

		std::vector<std::pair<float, float>> contact_point_buffer;

		point_count = contact_buffer->contact->GetManifold()->pointCount;
		contact_buffer->contact->GetWorldManifold(&contact_manifold);

		for (unsigned int i = 0; i < point_count; i++) {
			contact_point_buffer.push_back(std::make_pair(contact_manifold.points[i].x, contact_manifold.points[i].y));
		}

		if (!callback_function(contact_point_buffer)) {
			break;
		}

		contact_buffer = contact_buffer->next;
	}
}