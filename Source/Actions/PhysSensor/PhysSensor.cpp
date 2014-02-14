#include "PhysSensor.h"

using namespace Actions;

PhysSensor::PhysSensor(float width, float height) : width(width), height(height) {
	sensor_object = new Components::PhysicsCallback;
}

PhysSensor::~PhysSensor(void) {
	if (sensor_object) {
		delete sensor_object;
	}
}

void PhysSensor::X(float x) {
	this->x = x;
}

void PhysSensor::Y(float y) {
	this->y = y;
}

void PhysSensor::Angle(float angle) {
	this->angle = angle;
}

float PhysSensor::X(void) {
	return x;
}

float PhysSensor::Y(void) {
	return y;
}

float PhysSensor::Angle(void) {
	return angle;
}

int PhysSensor::CheckCollision(void) {
	return sensor_object->ObjectBoxCollision(x, y, width, height);
}
