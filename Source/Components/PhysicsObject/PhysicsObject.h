#pragma once

#include <Box2D/Box2D.h>
#include <functional>
#include <vector>

namespace Components {
	class PhysicsObject {
	public:
		PhysicsObject(void);
		~PhysicsObject(void);

		void CreateRect(float width, float height,float density, float friction,bool static_object=false);
		void CreateCircle(float radius, float density, float friction,bool static_object=false);

		void GetPosition(float* x=NULL, float* y=NULL);
		void GetRotation(float* rotation=NULL);
		void GetVelocity(float* hspeed=NULL,float* vspeed=NULL);
		void GetAngularVelocity (float* speed=NULL);
		void GetMovementDirection(float* angle=NULL);

		void SetPosition(float x, float y);
		void SetRotation(float rotation);
		void SetVelocity(float hspeed, float vspeed); // Don't do this on a frame-by-frame basis.
		void SetAngularVelocity(float speed);

		void ApplyForce(float hspeed, float vspeed);
		void ApplyAngularForce(float force);

		bool IsStaticBody(void);

		bool TestPoint(float x, float y);

		void GetAllCollisions(std::function<bool(std::vector<std::pair<float, float>>)>);
		// The function passed to GetAllCollisions must return a bool.
		// Returning false will break from the iteration, allowing for more efficiency.

	private:
		bool static_object;

		b2Body* phys_body_handle;
		b2Shape* phys_shape_handle;
	};
}