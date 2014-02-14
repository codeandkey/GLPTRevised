#include "PhysBox.h"

#include "../../Misc/ParamFetch.h"

using namespace Actions;
using namespace Neptune;

PhysBox::PhysBox(PhysBox::PhysBoxDesc phys_desc) {
	phys_object_handle = new Components::PhysicsObject;

	phys_object_handle->CreateRect(phys_desc.width,phys_desc.height,phys_desc.density,phys_desc.friction,phys_desc.static_object);

	phys_object_handle->SetPosition(0.0f,0.0f);
	phys_object_handle->SetRotation(0.0f);
}

PhysBox::PhysBox(void) {
	phys_object_handle = NULL;
}

PhysBox::~PhysBox(void) {
	if (phys_object_handle) delete phys_object_handle;
}

float PhysBox::X(void) {
	float target_x=0.0f;

	phys_object_handle->GetPosition(&target_x);

	return target_x;
}

float PhysBox::Y(void) {
	float target_y=0.0f;

	phys_object_handle->GetPosition(NULL,&target_y);

	return target_y;
}

float PhysBox::Angle(void) {
	float target_rotation=0.0f;

	phys_object_handle->GetRotation(&target_rotation);

	return target_rotation;
}

float PhysBox::XSpeed(void) {
	float target_xspeed=0.0f;

	phys_object_handle->GetVelocity(&target_xspeed);

	return target_xspeed;
}

float PhysBox::YSpeed(void) {
	float target_yspeed=0.0f;

	phys_object_handle->GetVelocity(NULL,&target_yspeed);

	return target_yspeed;
}

float PhysBox::RSpeed(void) {
	float target_rspeed=0.0f;

	phys_object_handle->GetAngularVelocity(&target_rspeed);

	return target_rspeed;
}

void PhysBox::X(float x) {
	phys_object_handle->SetPosition(x,Y());
}

void PhysBox::Y(float y) {
	phys_object_handle->SetPosition(X(),y);
}

void PhysBox::Angle(float angle) {
	phys_object_handle->SetRotation(angle);
}

void PhysBox::XSpeed(float xs) {
	phys_object_handle->SetVelocity(xs,YSpeed());
}

void PhysBox::YSpeed(float ys) {
	phys_object_handle->SetVelocity(XSpeed(),ys);
}

void PhysBox::RSpeed(float rs) {
	phys_object_handle->SetAngularVelocity(rs);
}

void PhysBox::PushDirectional(float direction, float speed) {
	direction = direction * 3.141f / 180.0f; // Must convert to radians for cos/sin.

	phys_object_handle->ApplyForce(cos(direction) * speed,sin(direction) * speed);
}

void PhysBox::Push(float delta_x, float delta_y) {
	phys_object_handle->ApplyForce(delta_x,delta_y);
}

void PhysBox::RotationalPush(float strength) {
	phys_object_handle->ApplyAngularForce(strength);
}

void PhysBox::SpecialHook(void* data) {
	phys_object_handle = new Components::PhysicsObject;

	std::map<std::string, std::string> map_object = *((std::map<std::string, std::string>*) data);

	float width = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "dim_width");
	float height = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "dim_height");

	float x_position = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "position_x");
	float y_position = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "position_y");

	float phys_density = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "phys_density");
	float phys_friction = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "phys_friction");

	bool phys_static = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "phys_static");

	phys_object_handle->CreateRect(width, height, phys_density, phys_friction, phys_static);

	X(x_position);
	Y(y_position);

	float player_angle = Misc::ParamFetch::Fetch<float, PhysBox>(map_object, "position_angle");

	Angle(player_angle);
}

Components::PhysicsObject* PhysBox::GetPhysObject(void) {
	return this->phys_object_handle;
}
