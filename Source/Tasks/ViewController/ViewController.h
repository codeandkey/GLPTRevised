#pragma once

#include <Neptune/Neptune.h>

namespace Tasks {
	class ViewController : public Neptune::Kernel::Task {
	public:
		ViewController(void);

		void TaskStep(void);

	private:
		float camera_x, camera_y, camera_z;
		float target_camera_x, target_camera_y, target_camera_z;
		float camera_look_x, camera_look_y, camera_look_z;
		float target_camera_look_x, target_camera_look_y, target_camera_look_z;

		float camera_position_animation_factor;
		float camera_look_animation_factor;
	};
}