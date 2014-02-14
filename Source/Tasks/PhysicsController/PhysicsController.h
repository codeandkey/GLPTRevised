#pragma once

#include <neptune/Neptune.h>
#include <Box2D/Box2D.h>

#ifdef _DEBUG
#pragma comment (lib,"Box2D_d.lib")
#else
#pragma comment (lib,"Box2D.lib")
#endif

namespace Tasks {
	class PhysicsController : public Neptune::Kernel::Task , public Neptune::Singleton::Singleton<PhysicsController> {
	public:
		PhysicsController(void);
		~PhysicsController(void);

		void TaskStep(void);

		b2Body* AddPhysicsShape(b2BodyDef* target_body);
		void DestroyPhysicsShape(b2Body* target_body);

		void RaycastWorld(b2RayCastInput cast_input,b2RayCastCallback* target_callback);
		void QueryWorld(b2AABB area, b2QueryCallback* target_callback);
	private:
		b2World* phys_space_handle;
	};
}